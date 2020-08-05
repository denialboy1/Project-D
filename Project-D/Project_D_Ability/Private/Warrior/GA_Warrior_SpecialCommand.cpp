// Team Project D has all rights this game

#include "Warrior/GA_Warrior_SpecialCommand.h"
#include "Warrior/CD_Warrior_SpecialCommand.h"
#include "AbilitySystemComponent.h"
#include "Warrior/WarriorCharacter.h"
#include "GameplayTagsModule.h"

UGA_Warrior_SpecialCommand::UGA_Warrior_SpecialCommand() {

	//��Ÿ�� ����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Warrior/Animation/AM_Warrior_Special.AM_Warrior_Special'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("Warrior SpecialCommand Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Warrior SpecialCommand Anim Load Failed"))
	}

	//��å ����
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

	//�����Ƽ �±� ����
	ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Warrior.SpecialCommand"));

	//��Ÿ�� ����
	CooldownGameplayEffectClass = UCD_Warrior_SpecialCommand::StaticClass();
}


void UGA_Warrior_SpecialCommand::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//��Ÿ ���� �޺�
	AWarriorCharacter* WarriorCharacter = Cast<AWarriorCharacter>(GetActorInfo().OwnerActor);
	if (WarriorCharacter) {
		WarriorCharacter->AttackCount = 0;
		WarriorCharacter->bSaveAttack = false;
		WarriorCharacter->bIsAttacking = false;
	}

	//���� ����
	if (WarriorCharacter) {
		WarriorCharacter->ServerRPC_Invincibility(2.0f, WarriorCharacter->GetCharacterState());
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
