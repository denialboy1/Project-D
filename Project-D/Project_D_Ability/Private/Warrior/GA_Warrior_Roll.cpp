// Team Project D has all rights this game


#include "Warrior/GA_Warrior_Roll.h"
#include "Warrior/WarriorCharacter.h"
#include "AbilitySystemComponent.h"

UGA_Warrior_Roll::UGA_Warrior_Roll() {
	//��Ÿ�� ����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Warrior/Animation/AM_Warrior_Roll_Montage.AM_Warrior_Roll_Montage'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("Warrior Roll Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Warrior Roll Anim Load Failed"))
	}

	//��å ����
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}


void UGA_Warrior_Roll::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//��Ÿ ���� �޺�
	AWarriorCharacter* WarriorCharacter = Cast<AWarriorCharacter>(GetActorInfo().OwnerActor);
	if (WarriorCharacter) {
		WarriorCharacter->AttackCount = 0;
		WarriorCharacter->bSaveAttack = false;
		WarriorCharacter->bIsAttacking = false;
	}

	//������
	FRotator Rotator = WarriorCharacter->GetControlRotation();
	Rotator.Roll = 0;
	Rotator.Pitch = 0;

	FVector V1 = FRotationMatrix(Rotator).GetScaledAxis(EAxis::X) * WarriorCharacter->GetCurMoveForward() * 300.0f;
	FVector V2 = FRotationMatrix(Rotator).GetScaledAxis(EAxis::Y) * WarriorCharacter->GetCurMoveRight() * 300.0f;
	FVector V3 = V1 + V2 + FVector(0, 0, 150.f);

	WarriorCharacter->LaunchCharacter(V3, false, false);


	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

