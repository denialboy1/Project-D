// Team Project D has all rights this game


#include "MagicianCharacter.h"

#include "Kismet/GameplayStatics.h"

AMagicianCharacter::AMagicianCharacter() {

	//������ ���̷��� �޽� �ʱ�ȭ
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MagicianSkeletalMesh(TEXT("/Game/Characters/Player/Magician/ParagonSerath/Characters/Heroes/Serath/Meshes/Serath.Serath"));
	if (MagicianSkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MagicianSkeletalMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -97));
		GetMesh()->SetRelativeRotation(FRotator(0, 270, 0));
		UE_LOG(LogTemp, Log, TEXT("MagicianSkeletalMesh Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("MagicianSkeletalMesh Fail"));
	}


	//������ �ִ��ν��Ͻ� �ʱ�ȭ
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> MagicianAnimInstance(TEXT("/Game/Characters/Player/Magician/Animation/ABP_Magician.ABP_Magician"));
	if (MagicianAnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(MagicianAnimInstance.Object->GetAnimBlueprintGeneratedClass());
		UE_LOG(LogTemp, Log, TEXT("MagicianAnimInstance Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("MagicianAnimInstance Fail"));
	}


	//�����Ƽ �ʱ�ȭ
	AbilityInit();

	//���� �ʱ�ȭ 
	ElementIndex = 0;
}

/////////////////////////////////////////    AbilityInit      //////////////////////////////////////////////////
void AMagicianCharacter::AbilityInit() {

	//���ݾ����Ƽ
	GA_Magician_WeaponAttack = UGA_Magician_WeaponAttack::StaticClass();
	if (GA_Magician_WeaponAttack) {
		WeaponAttack = GA_Magician_WeaponAttack;
		UE_LOG(LogTemp, Log, TEXT("GA_Magician_WeaponAttack Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Magician_WeaponAttack Fail"));
	}

	//Skill1
	GA_Magician_Skill1 = UGA_Element_Fire::StaticClass();
	if (GA_Magician_Skill1) {
		UseSpell1 = GA_Magician_Skill1;
		UE_LOG(LogTemp, Log, TEXT("GA_Magician_Skill1 Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Magician_Skill1 Fail"));
	}

	////Skill2
	GA_Magician_Skill2 = UGA_Element_Air::StaticClass();
	if (GA_Magician_Skill2) {
		UseSpell2 = GA_Magician_Skill2;
		UE_LOG(LogTemp, Log, TEXT("GA_Magician_Skill2 Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Magician_Skill2 Fail"));
	}

	////Skill3
	GA_Magician_Skill3 = UGA_Element_Water::StaticClass();
	if (GA_Magician_Skill3) {
		UseSpell3 = GA_Magician_Skill3;
		UE_LOG(LogTemp, Log, TEXT("GA_Magician_Skill3 Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Magician_Skill3 Fail"));
	}

	////Skill4
	GA_Magician_Skill4 = UGA_Element_Earth::StaticClass();
	if (GA_Magician_Skill4) {
		UseSpell4 = GA_Magician_Skill4;
		UE_LOG(LogTemp, Log, TEXT("GA_Magician_Skill4 Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Magician_Skill4 Fail"));
	}


	////Roll
	GA_Magician_Roll = UGA_Magician_Roll::StaticClass();
	if (GA_Magician_Roll) {
		Roll_Ability = GA_Magician_Roll;
		UE_LOG(LogTemp, Log, TEXT("GA_Magician_Roll Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Magician_Roll Fail"));
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////


void AMagicianCharacter::BeginPlay() {
	Super::BeginPlay();

	//������ �ִ� �ν��Ͻ� �̸� ĳ�����ص�
	if (MagicianAnimInstance == NULL) {
		MagicianAnimInstance = Cast<UMagicianAnimInstance>(GetMesh()->GetAnimInstance());
	}


}


