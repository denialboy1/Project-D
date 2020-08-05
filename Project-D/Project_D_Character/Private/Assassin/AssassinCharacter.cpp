// Team Project D has all rights this game


#include "Assassin/AssassinCharacter.h"
#include "Ability/Monster_character.h"

AAssassinCharacter::AAssassinCharacter() {

	//도적 스켈레톤 메쉬 초기화
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AAssassinSkeletalMesh(TEXT("/Game/Characters/Player/Assassin/ParagonKallari/Characters/Heroes/Kallari/Meshes/Kallari.Kallari"));
	if (AAssassinSkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(AAssassinSkeletalMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -97));
		GetMesh()->SetRelativeRotation(FRotator(0, 270, 0));
		UE_LOG(LogTemp, Log, TEXT("AAssassinSkeletalMesh Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("AAssassinSkeletalMesh Fail"));
	}


	//도적 애님인스턴스 초기화
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimInstance(TEXT("AnimBlueprint'/Game/Characters/Player/Assassin/Animation/ABP_Assasin.ABP_Assasin'"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Object->GetAnimBlueprintGeneratedClass());
		UE_LOG(LogTemp, Log, TEXT("AssasinAnimInstance Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("AssasinAnimInstance Fail"));
	}

	//콜리전 초기화
	WeaponAttackCollision = CreateDefaultSubobject<USphereComponent>(TEXT("WeaponAttackCollision"));
	if (WeaponAttackCollision) {
		WeaponAttackCollision->SetupAttachment(GetMesh(), FName(TEXT("sword_top")));
		WeaponAttackCollision->OnComponentBeginOverlap.AddDynamic(this, &AAssassinCharacter::OnComponentBeginOverlap_WeaponAttackCollision);
	}

	
	if (GetMesh()) {
		GetMesh()->OnComponentHit.AddDynamic(this, &AAssassinCharacter::OnComponentHit_Capsule);
	}
	
	Skill2Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Skill2Collision"));
	if (Skill2Collision) {
		Skill2Collision->SetupAttachment(GetMesh());
		Skill2Collision->OnComponentBeginOverlap.AddDynamic(this, &AAssassinCharacter::OnComponentBeginOverlap_Skill2);
	}

	Skill2AirCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Skill2AirCollision"));
	if (Skill2AirCollision) {
		Skill2AirCollision->SetupAttachment(GetMesh());
		Skill2AirCollision->OnComponentBeginOverlap.AddDynamic(this, &AAssassinCharacter::OnComponentBeginOverlap_Skill2Air);
	}



	//어빌리티 초기화
	AbilityInit();

	AssassinAnimInstance = Cast<UAssassinAnimInstance>(GetMesh()->GetAnimInstance());
}


/////////////////////////////////////////    AbilityInit      //////////////////////////////////////////////////
void AAssassinCharacter::AbilityInit() {
	//기본 공격1
	GA_Assassin_WeaponAttack1 = UGA_Assassin_WeaponAttack::StaticClass();
	if (GA_Assassin_WeaponAttack1) {
		WeaponAttack = GA_Assassin_WeaponAttack1;
		UE_LOG(LogTemp, Log, TEXT("UGA_Assassin_WeaponAttack Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("UGA_Assassin_WeaponAttack Fail"));
	}

	//기본 공격2
	GA_Assassin_WeaponAttack2 = UGA_Assassin_WeaponAttack2::StaticClass();
	if (GA_Assassin_WeaponAttack2) {
		Combo1 = GA_Assassin_WeaponAttack2;
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_WeaponAttack2 Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_WeaponAttack2 Fail"));
	}

	//기본 공격3
	GA_Assassin_WeaponAttack3 = UGA_Assassin_WeaponAttack3::StaticClass();
	if (GA_Assassin_WeaponAttack3) {
		Combo2 = GA_Assassin_WeaponAttack3;
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_WeaponAttack3 Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_WeaponAttack3 Fail"));
	}

	//더블 점프
	GA_Assassin_DoubleJump = UGA_Assassin_DoubleJump::StaticClass();
	if (GA_Assassin_DoubleJump) {
		ExtraSkill.Add(GA_Assassin_DoubleJump);
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_DoubleJump Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_DoubleJump Fail"));
	}

	//더블 점프 캔슬
	GA_Assassin_DoubleJump_Cancel = UGA_Assassin_DoubleJump_Cancel::StaticClass();
	if (GA_Assassin_DoubleJump_Cancel) {
		ExtraSkill.Add(GA_Assassin_DoubleJump_Cancel);
		
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_DoubleJump_Cancel Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_DoubleJump_Cancel Fail"));
	}

	//회피
	GA_Assassin_Roll = UGA_Assassin_Roll::StaticClass();
	if (GA_Assassin_Roll) {
		Roll_Ability = GA_Assassin_Roll;
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_Roll Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_Roll Fail"));
	}

	//순간 가속
	GA_Assassin_Launch = UGA_Assassin_Launch::StaticClass();
	if (GA_Assassin_Launch) {
		ExtraSkill.Add(GA_Assassin_Launch);
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_Launch Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_Launch Fail"));
	}


	//큰 대거 날리기 시작
	GA_Assassin_DashAttack_BigDaggerThrow_Start = UGA_Assassin_DashAttack_BigDaggerThrow_Start::StaticClass();
	if (GA_Assassin_DashAttack_BigDaggerThrow_Start) {
		UseSpell3 = GA_Assassin_DashAttack_BigDaggerThrow_Start;
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_DashAttack_BigDaggerThrow_Start Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_DashAttack_BigDaggerThrow_Start Fail"));
	}

	//큰 대거 날리기 종료
	GA_Assassin_DashAttack_BigDaggerThrow_End = UGA_Assassin_DashAttack_BigDaggerThrow_End::StaticClass();
	if (GA_Assassin_DashAttack_BigDaggerThrow_End) {
		ExtraSkill.Add(GA_Assassin_DashAttack_BigDaggerThrow_End);
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_DashAttack_BigDaggerThrow_End Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_DashAttack_BigDaggerThrow_End Fail"));
	}



	//대쉬어택 시작
	GA_Assassin_DashAttack_Start = UGA_Assassin_DashAttack_Start::StaticClass();
	if (GA_Assassin_DashAttack_Start) {
		UseSpell4 = GA_Assassin_DashAttack_Start;
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_DashAttack_Start Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_DashAttack_Start Fail"));
	}

	//대쉬 어택 진행중
	GA_Assassin_DashAttack_Loop = UGA_Assassin_DashAttack_Loop::StaticClass();
	if (GA_Assassin_DashAttack_Loop) {
		ExtraSkill.Add(GA_Assassin_DashAttack_Loop);
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_DashAttack_Loop Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_DashAttack_Loop Fail"));
	}

	//대쉬 어택 종료
	GA_Assassin_DashAttack_End = UGA_Assassin_DashAttack_End::StaticClass();
	if (GA_Assassin_DashAttack_End) {
		ExtraSkill.Add(GA_Assassin_DashAttack_End);
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_DashAttack_End Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_DashAttack_End Fail"));
	}

	//목자르기
	GA_Assassin_NeckSlice = UGA_Assassin_NeckSlice::StaticClass();
	if (GA_Assassin_NeckSlice) {
		UseSpell2 = GA_Assassin_NeckSlice;
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_NeckSlice Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_NeckSlice Fail"));
	}

	//작은 대거 날리기
	GA_Assassin_ThrowDagger = UGA_Assassin_ThrowDagger::StaticClass();
	if (GA_Assassin_ThrowDagger) {
		UseSpell1 = GA_Assassin_ThrowDagger;
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_ThrowDagger Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_ThrowDagger Fail"));
	}

	//큰 대거 스폰
	GA_Assassin_ThrowDagger_Spawn = UGA_Assassin_ThrowDagger_Spawn::StaticClass();
	if (GA_Assassin_ThrowDagger_Spawn) {
		ExtraSkill.Add(GA_Assassin_ThrowDagger_Spawn);
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_ThrowDagger_Spawn Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Assassin_ThrowDagger_Spawn Fail"));
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////    Key Bind      //////////////////////////////////////////////////
void AAssassinCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AAssassinCharacter::DoubleJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AAssassinCharacter::DoubleJumpCancel);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////    콤보 공격      //////////////////////////////////////////////////
void AAssassinCharacter::MulticastRPC_Attack_Implementation() {
	MeleeSpeed = 1.2f;
	if (bIsAttacking) {
		bSaveAttack = true;
	}
	else {
		bIsAttacking = true;
		ComboSwitch();
	}
}


void AAssassinCharacter::ComboAttackSave() {
	if (bSaveAttack) {
		bSaveAttack = false;
		ComboSwitch();
	}
}

void AAssassinCharacter::ResetCombo() {
	AttackCount = 0;
	bSaveAttack = false;
	bIsAttacking = false;
}

void AAssassinCharacter::ComboSwitch() {
	TSubclassOf<UGameplayAbility> Ability;
	switch (AttackCount) {
	case 0:
		AttackCount = 1;
		Ability = WeaponAttack;
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Attack1"));
		break;
	case 1:
		AttackCount = 2;
		Ability = Combo1;
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Attack2"));
		break;
	case 2:
		AttackCount = 3;
		Ability = Combo2;;
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Attack3"));
		break;
	}
	GetAbilitySystemComponent()->TryActivateAbilityByClass(Ability);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////더블 점프///////////////////////////////////////////////
void AAssassinCharacter::DoubleJump() {
	if(JumpCount == 0){
		Jump();
	}
	else if(JumpCount == 1) {
		GetAbilitySystemComponent()->TryActivateAbilityByClass(GA_Assassin_DoubleJump);
	}
	JumpCount++;
}

void AAssassinCharacter::DoubleJumpCancel() {
	GetAbilitySystemComponent()->TryActivateAbilityByClass(GA_Assassin_DoubleJump_Cancel);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////땅 착지///////////////////////////////////////////////
void AAssassinCharacter::Landed(const FHitResult& Hit) {
	JumpCount = 0;

	if (AssassinAnimInstance) {
		AssassinAnimInstance->bIsNeckSlice = false;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////튀어나가기///////////////////////////////////////////////
void AAssassinCharacter::Launch()
{
	ServerRPC_Launch();
}

void AAssassinCharacter::ServerRPC_Launch_Implementation()
{
	MulticastRPC_Launch();
}

void AAssassinCharacter::MulticastRPC_Launch_Implementation() {
	GetAbilitySystemComponent()->TryActivateAbilityByClass(GA_Assassin_Launch);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////충돌처리///////////////////////////////////////////////
void AAssassinCharacter::OnComponentBeginOverlap_WeaponAttackCollision(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool FromSweep, const FHitResult& SweeoResult) {
	if (GE_Assassin_WeaponAttack) {
		AMonster_Character* Monster_Character = Cast<AMonster_Character>(OtherActor);
		if (Monster_Character) {
			GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(GE_Assassin_WeaponAttack.GetDefaultObject(), Monster_Character->GetAbilitySystemComponent());
		}
	}
}

void AAssassinCharacter::OnComponentHit_Capsule(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	if (bUseSkill4) {
		GetAbilitySystemComponent()->TryActivateAbilityByClass(GA_Assassin_DashAttack_End);
		bUseSkill4 = false;

		if (GE_Assassin_Skill4) {
			AMonster_Character* Monster_Character = Cast<AMonster_Character>(OtherActor);
			if (Monster_Character) {
				GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(GE_Assassin_Skill4.GetDefaultObject(), Monster_Character->GetAbilitySystemComponent());
			}
		}
	}

	GetCharacterMovement()->Velocity = FVector(0, 0, 0);
}

void AAssassinCharacter::OnComponentBeginOverlap_Skill2Air(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool FromSweep, const FHitResult& SweeoResult) {
	if (GE_Assassin_Skill2) {
		AMonster_Character* Monster_Character = Cast<AMonster_Character>(OtherActor);
		if (Monster_Character) {
			GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(GE_Assassin_Skill2.GetDefaultObject(), Monster_Character->GetAbilitySystemComponent());
		}
	}
}

void AAssassinCharacter::OnComponentBeginOverlap_Skill2(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool FromSweep, const FHitResult& SweeoResult){
	if (GE_Assassin_Skill2) {
		AMonster_Character* Monster_Character = Cast<AMonster_Character>(OtherActor);
		if (Monster_Character) {
			GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(GE_Assassin_Skill2.GetDefaultObject(), Monster_Character->GetAbilitySystemComponent());
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////