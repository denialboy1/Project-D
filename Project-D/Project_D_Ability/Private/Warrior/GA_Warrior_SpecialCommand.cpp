// Team Project D has all rights this game

#include "Warrior/GA_Warrior_SpecialCommand.h"
#include "Warrior/CD_Warrior_SpecialCommand.h"
#include "AbilitySystemComponent.h"
#include "Warrior/WarriorCharacter.h"
#include "GameplayTagsModule.h"

UGA_Warrior_SpecialCommand::UGA_Warrior_SpecialCommand() {

	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Warrior/Animation/AM_Warrior_Special.AM_Warrior_Special'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("Warrior SpecialCommand Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Warrior SpecialCommand Anim Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

	//어빌리티 태그 설정
	ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Warrior.SpecialCommand"));

	//쿨타임 설정
	CooldownGameplayEffectClass = UCD_Warrior_SpecialCommand::StaticClass();
}


void UGA_Warrior_SpecialCommand::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//평타 리셋 콤보
	AWarriorCharacter* WarriorCharacter = Cast<AWarriorCharacter>(GetActorInfo().OwnerActor);
	if (WarriorCharacter) {
		WarriorCharacter->AttackCount = 0;
		WarriorCharacter->bSaveAttack = false;
		WarriorCharacter->bIsAttacking = false;
	}

	//무적 설정
	if (WarriorCharacter) {
		WarriorCharacter->ServerRPC_Invincibility(2.0f, WarriorCharacter->GetCharacterState());
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
