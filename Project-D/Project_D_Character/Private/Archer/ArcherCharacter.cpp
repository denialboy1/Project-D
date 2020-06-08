// Team Project D has all rights this game

#include "ArcherCharacter.h"
#include "Kismet/GameplayStatics.h"

AArcherCharacter::AArcherCharacter() {
	
	//에임 UI 초기화
	static ConstructorHelpers::FClassFinder<UUserWidget> AimPointWidget(TEXT("/Game/UI/Character/AimPoint.AimPoint_C"));

	if (AimPointWidget.Succeeded()) {
		AnimWidgetClass = AimPointWidget.Class;
		UE_LOG(LogTemp, Log, TEXT("AimWidgetClass Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("AimWidgetClass Fail"));
	}


	
	//아쳐 스켈레톤 메쉬 초기화
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArcherSkeletalMesh(TEXT("/Game/Characters/Player/Archer/ParagonSparrow/Characters/Heroes/Sparrow/Meshes/Sparrow.Sparrow"));
	if (ArcherSkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(ArcherSkeletalMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -97));
		GetMesh()->SetRelativeRotation(FRotator(0, 270, 0));
		UE_LOG(LogTemp, Log, TEXT("ArcherSkeletalMesh Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("ArcherSkeletalMesh Fail"));
	}

	
	//아쳐 애님인스턴스 초기화
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> ArcherAnimInstance(TEXT("/Game/Characters/Player/Archer/ABP_Archer.ABP_Archer"));
	if (ArcherAnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(ArcherAnimInstance.Object->GetAnimBlueprintGeneratedClass());
		UE_LOG(LogTemp, Log, TEXT("ArcherAnimInstance Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("ArcherAnimInstance Fail"));
	}
	
	//어빌리티 초기화
	AbilityInit();

	//초기화
	bIsAim = false;
}

/////////////////////////////////////////    AbilityInit      //////////////////////////////////////////////////
void AArcherCharacter::AbilityInit() {
	//장전 어빌리티 추가
	GA_Archer_Reload = UGA_Archer_Reload::StaticClass();
	if (GA_Archer_Reload) {
		SpecialCommand = GA_Archer_Reload;
		UE_LOG(LogTemp, Log, TEXT("GA_Archer_Reload Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Archer_Reload Fail"));
	}

	//공격어빌리티
	GA_Archer_WeaponAttack = UGA_Archer_WeaponAttack::StaticClass();
	if (GA_Archer_Reload) {
		WeaponAttack = GA_Archer_WeaponAttack;
		UE_LOG(LogTemp, Log, TEXT("GA_Archer_WeaponAttack Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Archer_WeaponAttack Fail"));
	}

	//Skill1
	GA_Archer_Skill1= UGA_Archer_Skill1::StaticClass();
	if (GA_Archer_Skill1) {
		UseSpell1 = GA_Archer_Skill1;
		UE_LOG(LogTemp, Log, TEXT("GA_Archer_Skill1 Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Archer_Skill1 Fail"));
	}

	////Skill2
	GA_Archer_Skill2 = UGA_Archer_Skill2::StaticClass();
	if (GA_Archer_Skill2) {
		UseSpell2 = GA_Archer_Skill2;
		UE_LOG(LogTemp, Log, TEXT("GA_Archer_Skill2 Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Archer_Skill2 Fail"));
	}

	////Skill3
	GA_Archer_WeaponAttack = UGA_Archer_Skill3::StaticClass();
	if (GA_Archer_Skill3) {
		UseSpell3 = GA_Archer_Skill3;
		UE_LOG(LogTemp, Log, TEXT("GA_Archer_Skill3 Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Archer_Skill3 Fail"));
	}

	////Skill4
	GA_Archer_WeaponAttack = UGA_Archer_Skill4::StaticClass();
	if (GA_Archer_Skill4) {
		UseSpell4 = GA_Archer_Skill4;
		UE_LOG(LogTemp, Log, TEXT("GA_Archer_Skill4 Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Archer_Skill4 Fail"));
	}


	////Roll
	GA_Archer_Roll = UGA_Archer_Roll::StaticClass();
	if (GA_Archer_Roll) {
		Roll_Ability = GA_Archer_Roll;
		UE_LOG(LogTemp, Log, TEXT("GA_Archer_Roll Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Archer_Roll Fail"));
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////




void AArcherCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//활 조준 풀기
	PlayerInputComponent->BindAction("SpecialCommand", IE_Released, this, &AArcherCharacter::SpecialCommandAttackCancel);
}


void AArcherCharacter::BeginPlay() {
	Super::BeginPlay();

	//에임 ui 생성
	if (AnimWidgetClass != NULL && AimWidget == NULL) {
		AimWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), AnimWidgetClass);
		AimWidget->AddToViewport();
		AimWidget->SetVisibility(ESlateVisibility::Hidden);
	}


	//아쳐 애님 인스턴스 미리 캐스팅해둠
	if (ArcherAnimInstance == NULL) {
		ArcherAnimInstance = Cast<UArcherAnimInstance>(GetMesh()->GetAnimInstance());
	}
	
}


/////////////////////////////////////////    Attack      //////////////////////////////////////////////////
void AArcherCharacter::Attack() {
	ServerRPC_Attack();
}
void AArcherCharacter::ServerRPC_Attack_Implementation() {
	MulticastRPC_Attack();
}

void AArcherCharacter::MulticastRPC_Attack_Implementation() {
	if (ArcherAnimInstance->bIsReloadPose) {
		GetAbilitySystemComponent()->TryActivateAbilityByClass(WeaponAttack);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////    SpecialCommandAttack      //////////////////////////////////////////////////
void AArcherCharacter::SpecialCommandAttack() {
	CameraBoom->SocketOffset = FVector(0, 10, 60);
	CameraBoom->TargetArmLength = -70;
	ServerRPC_SpecialCommandAttack();
}

void AArcherCharacter::ServerRPC_SpecialCommandAttack_Implementation() {
	MulticastRPC_SpecialCommandAttack();
}

void AArcherCharacter::MulticastRPC_SpecialCommandAttack_Implementation() {
	GetAbilitySystemComponent()->TryActivateAbilityByClass(SpecialCommand);
	ArcherAnimInstance->bIsReloadPose = true;
	GetCharacterMovement()->MaxWalkSpeed = 450;
	if (AimWidget) {
		AimWidget->SetVisibility(ESlateVisibility::Visible);
		bIsAim = true;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////    SpecialCommandAttackCancel      //////////////////////////////////////////////////
void AArcherCharacter::SpecialCommandAttackCancel() {
	CameraBoom->SocketOffset = FVector(0, 0, 100);
	CameraBoom->TargetArmLength = 200;
	ServerRPC_SpecialCommandAttackCancel();
}

void AArcherCharacter::ServerRPC_SpecialCommandAttackCancel_Implementation() {
	MulticastRPC_SpecialCommandAttackCancel();
}

void AArcherCharacter::MulticastRPC_SpecialCommandAttackCancel_Implementation() {
	GetAbilitySystemComponent()->TryActivateAbilityByClass(SpecialCommand);
	ArcherAnimInstance->bIsReloadPose = false;
	GetCharacterMovement()->MaxWalkSpeed = 600;
	if (AimWidget) {
		AimWidget->SetVisibility(ESlateVisibility::Hidden);
		bIsAim = false;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
