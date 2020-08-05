// Team Project D has all rights this game


#include "Magician/MagicianCharacter.h"
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
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimInstance(TEXT("/Game/Characters/Player/Magician/Animation/ABP_Magician.ABP_Magician"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Object->GetAnimBlueprintGeneratedClass());
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

	////Roll
	GA_Magician_Roll = UGA_Magician_Roll::StaticClass();
	if (GA_Magician_Roll) {
		Roll_Ability = GA_Magician_Roll;
		UE_LOG(LogTemp, Log, TEXT("GA_Magician_Roll Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Magician_Roll Fail"));
	}

	//Fire Element
	GA_Element_Fire = UGA_Element_Fire::StaticClass();
	if (GA_Element_Fire) {
		UseSpell1 = GA_Element_Fire;
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Fire Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Fire Fail"));
	}

	//Air Element
	GA_Element_Air = UGA_Element_Air::StaticClass();
	if (GA_Element_Air) {
		UseSpell2 = GA_Element_Air;
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Air Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Air Fail"));
	}

	//Water Element
	GA_Element_Water = UGA_Element_Water::StaticClass();
	if (GA_Element_Water) {
		UseSpell3 = GA_Element_Water;
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Water Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Water Fail"));
	}

	//Earth Element
	GA_Element_Earth = UGA_Element_Earth::StaticClass();
	if (GA_Element_Earth) {
		UseSpell4 = GA_Element_Earth;
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Earth Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Earth Fail"));
	}

	//�� ��ų
	GA_Fire = UGA_Fire::StaticClass();
	if (GA_Fire) {
		ExtraSkill.Add(GA_Fire);
		UE_LOG(LogTemp, Log, TEXT("GA_Fire Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Fire Fail"));
	}
	
	//�� ��ų
	GA_Water = UGA_Water::StaticClass();
	if (GA_Water) {
		ExtraSkill.Add(GA_Water);
		UE_LOG(LogTemp, Log, TEXT("GA_Water Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Water Fail"));
	}

	//�� ��ų
	GA_Earth = UGA_Earth::StaticClass();
	if (GA_Earth) {
		ExtraSkill.Add(GA_Earth);
		UE_LOG(LogTemp, Log, TEXT("GA_Earth Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Earth Fail"));
	}

	//���� ��ų
	GA_Air = UGA_Air::StaticClass();
	if (GA_Air) {
		ExtraSkill.Add(GA_Air);
		UE_LOG(LogTemp, Log, TEXT("GA_Air Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Air Fail"));
	}
	
	//�� + ���� ��ų
	GA_FireAndAir = UGA_FireAndAir::StaticClass();
	if (GA_FireAndAir) {
		ExtraSkill.Add(GA_FireAndAir);
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndAir Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndAir Fail"));
	}

	//�� + ���� ��ų
	GA_FireAndEarth = UGA_FireAndEarth::StaticClass();
	if (GA_FireAndEarth) {
		ExtraSkill.Add(GA_FireAndEarth);
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndEarth Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndEarth Fail"));
	}

	//�� + �� ��ų
	GA_FireAndWater = UGA_FireAndWater::StaticClass();
	if (GA_FireAndWater) {
		ExtraSkill.Add(GA_FireAndWater);
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndWater Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndWater Fail"));
	}

	//�� + ���� ��ų
	GA_WaterAndAir = UGA_WaterAndAir::StaticClass();
	if (GA_WaterAndAir) {
		ExtraSkill.Add(GA_WaterAndAir);
		UE_LOG(LogTemp, Log, TEXT("GA_WaterAndAir Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_WaterAndAir Fail"));
	}

	//�� + �� ��ų
	GA_WaterAndEarth = UGA_WaterAndEarth::StaticClass();
	if (GA_WaterAndEarth) {
		ExtraSkill.Add(GA_WaterAndEarth);
		UE_LOG(LogTemp, Log, TEXT("GA_WaterAndEarth Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_WaterAndEarth Fail"));
	}

	//�� + ���� ��ų
	GA_EarthAndAir = UGA_EarthAndAir::StaticClass();
	if (GA_EarthAndAir) {
		ExtraSkill.Add(GA_EarthAndAir);
		UE_LOG(LogTemp, Log, TEXT("GA_EarthAndAir Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_EarthAndAir Fail"));
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


