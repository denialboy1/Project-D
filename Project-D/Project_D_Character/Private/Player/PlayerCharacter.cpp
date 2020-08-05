// Team Project D has all rights this game

#include "Player/PlayerCharacter.h"
#include "Components/CapsuleComponent.h"

/////////////////////////////////////////    Constructor      //////////////////////////////////////////////////
APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	//GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	Interaction = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction"));
	Interaction->SetupAttachment(RootComponent);
	Interaction->SetRelativeLocation(FVector(70, 0, 0));
	Interaction->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//어빌리티
	GE_PlayerAlive = NewObject<UGE_PlayerAlive>();
	GA_Resurrection = UGA_Resurrection::StaticClass();

	//캐릭터 상태 초기화
	CharacterState = CC::NORMAL;

	//파티클 미리 가져오기
	static ConstructorHelpers::FObjectFinder<UParticleSystem> SpeedUpFX_Particle(TEXT("/Game/Temp/VFX_Toolkit_V1/ParticleSystems/356Days/SpeedUp_Effect.SpeedUp_Effect"));
	SpeedUpFX = SpeedUpFX_Particle.Object;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> SlowFX_Particle(TEXT("/Game/Characters/Monster/Forest/Fairy/FX/Particles/Use/P_Fairy_SlowField_Player.P_Fairy_SlowField_Player"));
	SlowFX = SlowFX_Particle.Object;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> AliveFX_Particle(TEXT("/Game/Characters/Player/Shared/FX/Revival/ParticleSystems/356Days/Revive.Revive"));
	AliveFX = AliveFX_Particle.Object;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> DeadFX_Particle(TEXT("/Game/Maps/Release/In/Demonstration/Particle/P_Gargoyle_On.P_Gargoyle_On"));
	DeadFX = DeadFX_Particle.Object;

	//사운드 미리 가져오기
	static ConstructorHelpers::FObjectFinder<USoundWave> Alive_SoundWave(TEXT("/Game/Characters/Player/Shared/Audio/Shared_Revival_02.Shared_Revival_02"));
	AliveSound = Alive_SoundWave.Object;


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////    Key Bind      //////////////////////////////////////////////////
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::DashPressed);
	PlayerInputComponent->BindAction("Dash", IE_Released, this, &APlayerCharacter::DashReleased);

	//Interaction key
	PlayerInputComponent->BindAction("E", IE_Pressed, this, &APlayerCharacter::InteractionAction);

	//부활키
	PlayerInputComponent->BindAction("R", IE_Pressed, this, &APlayerCharacter::Revive);

	//공격키
	PlayerInputComponent->BindAction("WeaponAttack", IE_Pressed, this, &APlayerCharacter::Attack);

	//특수공격
	PlayerInputComponent->BindAction("SpecialCommand", IE_Pressed, this, &APlayerCharacter::SpecialCommandAttack);

	//회피기
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &APlayerCharacter::Roll);
	
	//스킬
	PlayerInputComponent->BindAction("UseSpell1", IE_Pressed, this, &APlayerCharacter::Skill1);
	PlayerInputComponent->BindAction("UseSpell2", IE_Pressed, this, &APlayerCharacter::Skill2);
	PlayerInputComponent->BindAction("UseSpell3", IE_Pressed, this, &APlayerCharacter::Skill3);
	PlayerInputComponent->BindAction("UseSpell4", IE_Pressed, this, &APlayerCharacter::Skill4);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds("ConfirmInput", "CancelInput", "AbilityInput"));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////    BeginPlay      //////////////////////////////////////////////////
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent == nullptr) return;


	// 해당 어빌리티가 등록되어 있으면 키 값에 연결
	if (HasAuthority()) {
		BindAbilitySystemAndAbilityInput();

		int ID = 100;
		for (TSubclassOf<UGameplayAbility> skill : ExtraSkill)
		{
			if (skill) {
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(skill.GetDefaultObject(), 1, ID));
				ID++;
			}
		}
	}

	AbilitySystemComponent->ApplyGameplayEffectToSelf(GE_PlayerAlive, 0, AbilitySystemComponent->MakeEffectContext());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////    Tick      //////////////////////////////////////////////////
void APlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//회피기 타이머
	RollTimeUpdate(DeltaTime);

	//CC기 타이머
	switch (CharacterState) {
	case CC::INVINCIBILITY:
		InvincibilityTimeUpdate(DeltaTime);
		break;
	case CC::STUN:
		StunTimeUpdate(DeltaTime);
		break;
	case CC::FAST:
		FastTimeUpdate(DeltaTime);
		break;
	case CC::SLOW:
		SlowTimeUpdate(DeltaTime);
		break;
	}

	if (CharacterState == CC::INVINCIBILITY && PrevCharacterState == CC::SLOW) {
		SlowTimeUpdate(DeltaTime);
	}

	if (CharacterState == CC::INVINCIBILITY && PrevCharacterState == CC::FAST) {
		FastTimeUpdate(DeltaTime);
	}
}

void APlayerCharacter::RollTimeUpdate(float DeltaTime) {
	
	if (bIsRoll) {
		RollTimer += DeltaTime;
		if (RollTimer >= 1.5f) bIsRoll = false;
	}
}

void APlayerCharacter::InvincibilityTimeUpdate(float DeltaTime) {
	InvincibilityTimer += DeltaTime;
	if (InvincibilityTimer >= InvincibilityTime) {
		CharacterState = PrevCharacterState;
	}
}
void APlayerCharacter::StunTimeUpdate(float DeltaTime) {
	StunTimer += DeltaTime;
	if (StunTimer >= StunTime) {
		CharacterState = CC::NORMAL;
	}
}
void APlayerCharacter::SlowTimeUpdate(float DeltaTime) {
	SlowTimer += DeltaTime;
	if (SlowTimer >= SlowTime) {
		CharacterState = CC::NORMAL;
		GetCharacterMovement()->MaxWalkSpeed = InitMoveSpeed;
		MoveSpeed = InitMoveSpeed;
		SlowFX_Component->DestroyComponent();
	}
	else {
		FVector Vector = GetActorLocation();
		Vector.Z -= GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		SlowFX_Component->SetWorldLocation(Vector);
	}
}
void APlayerCharacter::FastTimeUpdate(float DeltaTime) {
	FastTimer += DeltaTime;
	if (FastTimer >= FastTime) {
		CharacterState = CC::NORMAL;
		GetCharacterMovement()->MaxWalkSpeed = InitMoveSpeed;
		MoveSpeed = InitMoveSpeed;
		SpeedUpFX_Component->DestroyComponent();
	}
	else {
		FVector Vector = GetActorLocation();
		Vector.Z -= GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		SpeedUpFX_Component->SetWorldLocation(Vector);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////






/////////////////////////////////////////    Ability Allocate      //////////////////////////////////////////////////
void APlayerCharacter::BindAbilitySystemAndAbilityInput()
{
	if (WeaponAttack) {
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(WeaponAttack.GetDefaultObject(), 1, 0));
	}

	if (Combo1) {
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Combo1.GetDefaultObject(), 1, 1));
	}

	if (Combo2) {
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Combo2.GetDefaultObject(), 1, 2));
	}

	if (UseSpell1)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UseSpell1.GetDefaultObject(), 1, 3));
	}
	if (UseSpell2)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UseSpell2.GetDefaultObject(), 1, 4));
	}
	if (UseSpell3)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UseSpell3.GetDefaultObject(), 1, 5));
	}
	if (UseSpell4)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UseSpell4.GetDefaultObject(), 1, 6));
	}

	if (SpecialCommand)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(SpecialCommand.GetDefaultObject(), 1, 7));
	}

	if (Roll_Ability)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Roll_Ability.GetDefaultObject(), 1, 8));
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////    Camera Control      //////////////////////////////////////////////////
void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////    Character Move      //////////////////////////////////////////////////
void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && bIsAlive)
	{
		PreMoveForward = CurMoveForward;
		CurMoveForward = Value;

		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, CurMoveForward);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && bIsAlive)
	{
		PreMoveRight = CurMoveRight;
		CurMoveRight = Value;

		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, CurMoveRight);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////    DashPressed      //////////////////////////////////////////////////
void APlayerCharacter::DashPressed()
{
	UE_LOG(LogTemp, Log, TEXT("DashPress"));
	ServerRPC_DashPressed();
	
}

void APlayerCharacter::ServerRPC_DashPressed_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("DashPress_server"));
	Multicast_DashPressed();
}

void APlayerCharacter::Multicast_DashPressed_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("DashPress_multicast"));
	if (CharacterState == CC::NORMAL) {
		UE_LOG(LogTemp, Log, TEXT("DashPress_Action"));
		GetCharacterMovement()->MaxWalkSpeed = 950;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////    DashReleased      //////////////////////////////////////////////////
void APlayerCharacter::DashReleased()
{
	ServerRPC_DashReleased();
}

void APlayerCharacter::ServerRPC_DashReleased_Implementation()
{
	Multicast_DashReleased();
}

void APlayerCharacter::Multicast_DashReleased_Implementation()
{
	if (CharacterState == CC::NORMAL) {
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////    Roll      //////////////////////////////////////////////////
void APlayerCharacter::Roll() {
	ServerRPC_Roll(CharacterState);
}

void APlayerCharacter::ServerRPC_Roll_Implementation(CC PrevState)
{
	Multicast_Roll(PrevState);
}

void APlayerCharacter::Multicast_Roll_Implementation(CC PrevState) {
	if (bIsAlive) {
		if (!bIsRoll) {
			GetAbilitySystemComponent()->TryActivateAbilityByClass(Roll_Ability);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////    Attack      //////////////////////////////////////////////////
void APlayerCharacter::Attack() 
{
	ServerRPC_Attack();
}

void APlayerCharacter::ServerRPC_Attack_Implementation()
{
	MulticastRPC_Attack();
}

void APlayerCharacter::MulticastRPC_Attack_Implementation() {
	GetAbilitySystemComponent()->TryActivateAbilityByClass(WeaponAttack);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////    SpecialCommandAttack      //////////////////////////////////////////////////
void APlayerCharacter::SpecialCommandAttack() {
	if (bIsAlive) {
		GetAbilitySystemComponent()->TryActivateAbilityByClass(SpecialCommand);
	}
}

void APlayerCharacter::ServerRPC_SpecialCommandAttack_Implementation()
{
	MulticastRPC_SpecialCommandAttack();
}

void APlayerCharacter::MulticastRPC_SpecialCommandAttack_Implementation() {
	GetAbilitySystemComponent()->TryActivateAbilityByClass(SpecialCommand);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////    Skill1      //////////////////////////////////////////////////
void APlayerCharacter::Skill1() {
	ServerRPC_Skill1();
}

void APlayerCharacter::ServerRPC_Skill1_Implementation()
{
	MulticastRPC_Skill1();
}

void APlayerCharacter::MulticastRPC_Skill1_Implementation() {
	if (bIsAlive) {
		GetAbilitySystemComponent()->TryActivateAbilityByClass(UseSpell1);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////    Skill2      //////////////////////////////////////////////////
void APlayerCharacter::Skill2() {
	ServerRPC_Skill2();
}

void APlayerCharacter::ServerRPC_Skill2_Implementation()
{
	MulticastRPC_Skill2();
}

void APlayerCharacter::MulticastRPC_Skill2_Implementation() {
	if (bIsAlive) {
		GetAbilitySystemComponent()->TryActivateAbilityByClass(UseSpell2);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////    Skill3      //////////////////////////////////////////////////
void APlayerCharacter::Skill3() {
	ServerRPC_Skill3();
}

void APlayerCharacter::ServerRPC_Skill3_Implementation()
{
	MulticastRPC_Skill3();
}

void APlayerCharacter::MulticastRPC_Skill3_Implementation() {
	if (bIsAlive) {
		GetAbilitySystemComponent()->TryActivateAbilityByClass(UseSpell3);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////    Skill4      /////////////////////////////////////////////////
void APlayerCharacter::Skill4() {
	ServerRPC_Skill4();
}

void APlayerCharacter::ServerRPC_Skill4_Implementation()
{
	MulticastRPC_Skill4();
}

void APlayerCharacter::MulticastRPC_Skill4_Implementation() {
	if (bIsAlive) {
		GetAbilitySystemComponent()->TryActivateAbilityByClass(UseSpell4);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////    Interaction      /////////////////////////////////////////////////
void APlayerCharacter::InteractionAction()
{
	ServerRPC_InteractionAction();
}

void APlayerCharacter::ServerRPC_InteractionAction_Implementation()
{
	if (InteractionActor != nullptr) {
		AInteractionObject* inter = Cast<AInteractionObject>(InteractionActor);
		if (inter != nullptr) {
			inter->Interaction();
		}
	}
}

void APlayerCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Interaction_BeginPlay"));
	if(OtherActor != this)
		InteractionActor = OtherActor;
}

void APlayerCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Interaction_BeginPlay"));
	InteractionActor = nullptr;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////    Revive      /////////////////////////////////////////////////
void APlayerCharacter::Revive() {
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(InteractionActor);
	if (PlayerCharacter != nullptr) {
		ServerRPC_Revive(PlayerCharacter);
	}
	
}

void APlayerCharacter::ServerRPC_Revive_Implementation(APlayerCharacter* PlayerCharacter)
{
	GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(GE_PlayerAlive, PlayerCharacter->GetAbilitySystemComponent());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////    FastBuff      /////////////////////////////////////////////////
void APlayerCharacter::ServerRPC_Fast_Implementation(float Time)
{
	MulticastRPC_Fast(Time);
}

void APlayerCharacter::MulticastRPC_Fast_Implementation(float Time) {
	//초기화
	FastTime = Time;
	FastTimer = 0;
	MoveSpeed = InitMoveSpeed * 2;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	CharacterState = CC::FAST;


	//기존 버프이펙트 삭제
	if (SpeedUpFX_Component != nullptr) {
		SpeedUpFX_Component->DestroyComponent();
	}
	
	//이펙트 설정
	FVector Vector = GetCapsuleComponent()->GetComponentLocation();
	Vector.Z = 0;
	FRotator Rotator(0, 270, 0);
	FTransform Transform;
	Transform.SetLocation(Vector);
	Transform.SetRotation(Rotator.Quaternion());
	SpeedUpFX_Component = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpeedUpFX, Transform);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////






/////////////////////////////////////    SlowBuff      /////////////////////////////////////////////////
void APlayerCharacter::ServerRPC_Slow_Implementation(float Time)
{
	MulticastRPC_Slow(Time);
}

void APlayerCharacter::MulticastRPC_Slow_Implementation(float Time) {
	//초기화
	SlowTime = Time;
	SlowTimer = 0;
	MoveSpeed = InitMoveSpeed / 2;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	CharacterState = CC::SLOW;

	//기존 버프이펙트 삭제
	if (SlowFX_Component != nullptr) {
		SlowFX_Component->DestroyComponent();
	}

	//이펙트 설정
	FVector Vector = GetCapsuleComponent()->GetComponentLocation();
	Vector.Z = 0;
	FRotator Rotator(0, 0, 0);
	FTransform Transform;
	Transform.SetLocation(Vector);
	Transform.SetRotation(Rotator.Quaternion());
	SlowFX_Component = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SlowFX, Transform);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////    StunBuff      /////////////////////////////////////////////////
void APlayerCharacter::Stun(float Time) {
	StunTime = Time;
	StunTimer = 0;
	CharacterState = CC::STUN;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////    InvincibilityBuff      /////////////////////////////////////////////////
void APlayerCharacter::ServerRPC_Invincibility_Implementation(float Time, CC PrevState)
{
	MulticastRPC_Invincibility(Time,PrevState);
}

void APlayerCharacter::MulticastRPC_Invincibility_Implementation(float Time, CC PrevState) {
	//초기화
	InvincibilityTime = Time;
	InvincibilityTimer = 0;
	
	if (PrevState != CC::INVINCIBILITY) {
		PrevCharacterState = PrevState;
	}

	CharacterState = CC::INVINCIBILITY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////    Dead      /////////////////////////////////////////////////
void APlayerCharacter::ServerRPC_Dead_Implementation() {
	MulticastRPC_Dead();
}

void APlayerCharacter::MulticastRPC_Dead_Implementation()
{
	Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance())->bIsDead = true;

	if (DeadFX_Component != nullptr) {
		DeadFX_Component->Activate();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////    Alive      /////////////////////////////////////////////////
void APlayerCharacter::ServerRPC_Alive_Implementation() {
	MulticastRPC_Alive();
}

void APlayerCharacter::MulticastRPC_Alive_Implementation()
{
	Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance())->bIsDead = false;
	bIsAlive = true;

	
	FTransform Transform = GetActorTransform();
	FVector Vector = Transform.GetLocation();
	Vector.Z -= 100;
	Transform.SetLocation(Vector);
	AliveFX_Component = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AliveFX, Transform);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), AliveSound, GetActorLocation());

	if (DeadFX_Component != nullptr) {
		DeadFX_Component->Deactivate();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////