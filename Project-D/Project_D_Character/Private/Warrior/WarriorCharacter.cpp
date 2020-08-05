// Team Project D has all rights this game


#include "Warrior/WarriorCharacter.h"
#include "Warrior/WarriorAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/UnrealMathUtility.h"

AWarriorCharacter::AWarriorCharacter() {

	//���� ���̷��� �޽� �ʱ�ȭ
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WarriorSkeletalMesh(TEXT("/Game/Characters/Player/Warrior/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone"));
	if (WarriorSkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(WarriorSkeletalMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -97));
		GetMesh()->SetRelativeRotation(FRotator(0, 270, 0));
		UE_LOG(LogTemp, Log, TEXT("WarriorSkeletalMesh Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("WarriorSkeletalMesh Fail"));
	}


	//���� �ִ��ν��Ͻ� �ʱ�ȭ
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimInstance(TEXT("/Game/Characters/Player/Warrior/Animation/ABP_Warrior.ABP_Warrior"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Object->GetAnimBlueprintGeneratedClass());
		UE_LOG(LogTemp, Log, TEXT("WarriorAnimInstance Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("WarriorAnimInstance Fail"));
	}

	//Protect �ʱ�ȭ
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ProtectFX_Particle(TEXT("ParticleSystem'/Game/Characters/Player/Warrior/ParagonGreystone/FX/Particles/Greystone/Skins/Novaborn/P_Greystone_Novaborn_ULT_DragonHead.P_Greystone_Novaborn_ULT_DragonHead'"));
	if (ProtectFX_Particle.Succeeded()) {
		ProtectParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Protect"));
		ProtectParticleComponent->SetupAttachment(GetMesh(),FName(TEXT("Chest")));
		if (ProtectParticleComponent) {
			ProtectParticleComponent->Template = ProtectFX_Particle.Object;
		}
		UE_LOG(LogTemp, Log, TEXT("ProtectFX_Particle Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("ProtectFX_Particle Fail"));
	}
	

	

	//�ݸ��� �ʱ�ȭ
	WeaponAttackCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponAttackCollision"));
	if (WeaponAttackCollision) {
		WeaponAttackCollision->SetupAttachment(GetMesh(), FName(TEXT("sword_top")));
		WeaponAttackCollision->OnComponentBeginOverlap.AddDynamic(this, &AWarriorCharacter::OnComponentBeginOverlap_WeaponAttackCollision);
	}

	Skill1Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Skill1Collision"));
	if (Skill1Collision) {
		Skill1Collision->SetupAttachment(GetMesh());
		Skill1Collision->OnComponentBeginOverlap.AddDynamic(this, &AWarriorCharacter::OnComponentBeginOverlap_Skill1Collision);
	}

	Skill3Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Skill3Collision"));
	if (Skill3Collision) {
		Skill3Collision->SetupAttachment(GetMesh());
		Skill3Collision->OnComponentBeginOverlap.AddDynamic(this, &AWarriorCharacter::OnComponentBeginOverlap_Skill3Collision);
		Skill3Collision->OnComponentEndOverlap.AddDynamic(this, &AWarriorCharacter::OnComponentEndOverlap_Skill3Collision);
	}

	Skill4Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Skill4Collision"));
	if (Skill4Collision) {
		Skill4Collision->SetupAttachment(GetMesh());
		//Skill4Collision->OnComponentBeginOverlap.AddDynamic(this, &AWarriorCharacter::OnComponentBeginOverlap_Skill3Collision);
	}

	

	//�����Ƽ �ʱ�ȭ
	AbilityInit();
}


/////////////////////////////////////////    AbilityInit      //////////////////////////////////////////////////
void AWarriorCharacter::AbilityInit() {
	//�Ϲ� ����
	GA_Warrior_WeaponAttack = UGA_Warrior_WeaponAttack::StaticClass();
	if (GA_Warrior_WeaponAttack) {
		WeaponAttack = GA_Warrior_WeaponAttack;
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_WeaponAttack Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_WeaponAttack Fail"));
	}

	//�⺻���� �޺�1
	GA_Warrior_Combo1 = UGA_Warrior_Combo1::StaticClass();
	if (GA_Warrior_Combo1) {
		Combo1 = GA_Warrior_Combo1;
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_Combo1 Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_Combo1 Fail"));
	}

	//�⺻���� �޺�2
	GA_Warrior_Combo2 = UGA_Warrior_Combo2::StaticClass();
	if (GA_Warrior_Combo2) {
		Combo2 = GA_Warrior_Combo2;
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_Combo2 Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_Combo2 Fail"));
	}

	//Ư�� Ŀ�ǵ�
	GA_Warrior_SpecialCommand = UGA_Warrior_SpecialCommand::StaticClass();
	if (GA_Warrior_SpecialCommand) {
		SpecialCommand = GA_Warrior_SpecialCommand;
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_SpecialCommand Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_SpecialCommand Fail"));
	}

	//ȸ�� Ŀ�ǵ�
	GA_Warrior_Roll = UGA_Warrior_Roll::StaticClass();
	if (GA_Warrior_Roll) {
		Roll_Ability = GA_Warrior_Roll;
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_Roll Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_Roll Fail"));
	}

	//���� ���� ��
	GA_Warrior_JumpAttack_Up = UGA_Warrior_JumpAttack_Up::StaticClass();
	if (GA_Warrior_JumpAttack_Up) {
		UseSpell1 = GA_Warrior_JumpAttack_Up;
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_JumpAttack_Up Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_JumpAttack_Up Fail"));
	}

	//���� ���� ����
	GA_Warrior_JumpAttack_Loop = UGA_Warrior_JumpAttack_Loop::StaticClass();
	if (GA_Warrior_JumpAttack_Loop) {
		ExtraSkill.Add(GA_Warrior_JumpAttack_Loop);
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_JumpAttack_Loop Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_JumpAttack_Loop Fail"));
	}

	//���� ���� �ٿ�
	GA_Warrior_JumpAttack_Down = UGA_Warrior_JumpAttack_Down::StaticClass();
	if (GA_Warrior_JumpAttack_Down) {
		ExtraSkill.Add(GA_Warrior_JumpAttack_Down);
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_JumpAttack_Down Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_JumpAttack_Down Fail"));
	}

	//��ų3
	GA_Warrior_Skill3 = UGA_Warrior_Skill3::StaticClass();
	if (GA_Warrior_Skill3) {
		UseSpell3 = GA_Warrior_Skill3;
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_Skill3 Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_Skill3 Fail"));
	}



	//��ų4 : ��ų4�� ��ų2�� ��ü��.
	GA_Warrior_Skill4 = UGA_Warrior_Skill4::StaticClass();
	if (GA_Warrior_Skill4) {
		UseSpell2 = GA_Warrior_Skill4;		
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_Skill4 Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_Skill4 Fail"));
	}

	//��ų4_Fire
	GA_Warrior_Skill4_Fire = UGA_Warrior_Skill4_Fire::StaticClass();
	if (GA_Warrior_Skill4_Fire) {
		ExtraSkill.Add(GA_Warrior_Skill4_Fire);
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_Skill4_Fire Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Warrior_Skill4_Fire Fail"));
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////    BeginPlay     //////////////////////////////////////////////////
void AWarriorCharacter::BeginPlay() {
	Super::BeginPlay();
	WarriorAnimInstance = Cast<UWarriorAnimInstance>(GetMesh()->GetAnimInstance());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////    Tick     //////////////////////////////////////////////////
void AWarriorCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	
	GroundJudge();
	RecoverProtect(DeltaSeconds);
	if (HasAuthority()) {
		SowrdTonado(DeltaSeconds);
	}
}

void AWarriorCharacter::GroundJudge() {
	if (WarriorAnimInstance) {
		if (WarriorAnimInstance->bIsJumpAttack && !WarriorAnimInstance->bIsInAir) {
			GetAbilitySystemComponent()->TryActivateAbilityByClass(GA_Warrior_JumpAttack_Down);
			WarriorAnimInstance->bIsJumpAttack = false;
		}
	}
}
void AWarriorCharacter::RecoverProtect(float DeltaTime) {
	if (FMath::IsNearlyEqual((double)2.0, (double)GetAbilitySystemComponent()->GetNumericAttribute(UAttributeSet_Character::GetMaxHealthAttribute()))) {
		if (ProtectParticleComponent) {
			ProtectParticleComponent->SetActive(true, false);
		}
	}
	else {
		if (FMath::IsNearlyEqual((double)1.0, (double)GetAbilitySystemComponent()->GetNumericAttribute(UAttributeSet_Character::GetMaxHealthAttribute()))) {
			ProtectParticleComponent->SetActive(false, false);
			ProtectResetTime += DeltaTime;
			if (ProtectResetTime >= 10) {
				ProtectResetTime = 0;
				if (GE_Warrior_Heal) {
					GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(GE_Warrior_Heal.GetDefaultObject(),0,FGameplayEffectContextHandle());
				}
			}
		}
	}
	
}

void AWarriorCharacter::SowrdTonado(float DeltaTime) {
	if (Skill3Collision->GetCollisionEnabled() == ECollisionEnabled::NoCollision) {
		MonsterList.Empty();
	}
	else {
		MaxSkill3Time += DeltaTime;
		if (MaxSkill3Time >= 6.0f) {
			MaxSkill3Time = 0.0f;
			Skill3Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		else {
			Skill3Time += DeltaTime;
			if (Skill3Time >= 1.0f) {
				Skill3Time = 0.0f;
				if (GE_Warrior_Skill3Damage) {
					for (int i = 0; i < MonsterList.Num(); i++) {
						GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(GE_Warrior_Skill3Damage.GetDefaultObject(), MonsterList[i]->GetAbilitySystemComponent());
					}
				}
			}
		}
	}
}


/////////////////////////////////////////    �޺� ����      //////////////////////////////////////////////////
void AWarriorCharacter::MulticastRPC_Attack_Implementation() {
	MeleeSpeed = 1.2f;
	if (bIsAttacking) {
		bSaveAttack = true;
	}
	else {
		bIsAttacking = true;
		ComboSwitch();
	}
}


void AWarriorCharacter::ComboAttackSave() {
	if (bSaveAttack) {
		bSaveAttack = false;
		ComboSwitch();
	}
}

void AWarriorCharacter::ResetCombo() {
	AttackCount = 0;
	bSaveAttack = false;
	bIsAttacking = false;
}

void AWarriorCharacter::ComboSwitch() {
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


/////////////////////////////////////////   ��ų1 ����      //////////////////////////////////////////////////
void AWarriorCharacter::MulticastRPC_Skill1_Implementation() {
	UWarriorAnimInstance* AnimInstance = Cast<UWarriorAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance) {
		if (GetMovementComponent()->IsFalling()) {
			AnimInstance->bIsJumpAttack = true;
			GetAbilitySystemComponent()->TryActivateAbilityByClass(GA_Warrior_JumpAttack_Loop);
		}
		else {
			GetAbilitySystemComponent()->TryActivateAbilityByClass(GA_Warrior_JumpAttack_Up);
		}
	}
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////   �ݸ��� �Լ�      //////////////////////////////////////////////////

UFUNCTION()
void AWarriorCharacter::OnComponentBeginOverlap_WeaponAttackCollision(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool FromSweep, const FHitResult& SweeoResult) {
	if (GE_Warrior_Skill3Damage) {
		GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(GE_Warrior_Skill3Damage.GetDefaultObject(), Cast<AMonster_Character>(OtherActor)->GetAbilitySystemComponent());
	}
}

UFUNCTION()
void AWarriorCharacter::OnComponentBeginOverlap_Skill1Collision(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool FromSweep, const FHitResult& SweeoResult) {
	if (GE_Warrior_Skill3Damage) {
		GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(GE_Warrior_Skill1Damage.GetDefaultObject(), Cast<AMonster_Character>(OtherActor)->GetAbilitySystemComponent());
	}
}

UFUNCTION()
void AWarriorCharacter::OnComponentBeginOverlap_Skill3Collision(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool FromSweep, const FHitResult& SweeoResult) {
	AMonster_Character* Monster = Cast<AMonster_Character>(OtherActor);
	if (Monster) {
		MonsterList.Add(Monster);
	}
	
}

UFUNCTION()
void AWarriorCharacter::OnComponentEndOverlap_Skill3Collision(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex) {
	AMonster_Character* Monster = Cast<AMonster_Character>(OtherActor);
	if (Monster) {
		if (MonsterList.Contains(Monster)) {
			MonsterList.RemoveAt(MonsterList.Find(Monster));
			//MonsterList.Remove(*Monster);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////