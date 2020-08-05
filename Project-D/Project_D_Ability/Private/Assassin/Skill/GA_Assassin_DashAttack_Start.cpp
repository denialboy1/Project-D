// Team Project D has all rights this game


#include "Assassin/Skill/GA_Assassin_DashAttack_Start.h"
#include "Assassin/Skill/CD_Assassin_DashAttack.h"
#include "Assassin/AssassinCharacter.h"
#include "Assassin/AssassinAnimInstance.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsModule.h"

UGA_Assassin_DashAttack_Start::UGA_Assassin_DashAttack_Start() {
	//��Ÿ�� ����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Assassin/Animation/AM_Assassin_DashAttack_Start.AM_Assassin_DashAttack_Start'"));
	if (Montage.Succeeded()) {
		AM_DashAttack = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("UGA_Assassin_DashAttack_Start Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("UGA_Assassin_DashAttack_Start Load Failed"))
	}

	//��å ����
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

	//�����Ƽ �±� ����
	ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Skill4"));

	//��Ÿ�� ����
	CooldownGameplayEffectClass = UCD_Assassin_DashAttack::StaticClass();
}


void UGA_Assassin_DashAttack_Start::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}



	AAssassinCharacter* AssassinCharacter = Cast<AAssassinCharacter>(ActorInfo->OwnerActor);
	if (AssassinCharacter) {
		//��Ÿ ���� �޺�
		AssassinCharacter->AttackCount = 0;
		AssassinCharacter->bSaveAttack = false;
		AssassinCharacter->bIsAttacking = false;
	}


	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	if (AssassinCharacter) {
		AnimInstance->Montage_Play(AM_DashAttack, 1.0f);
		AssassinCharacter->bUseSkill4 = true;
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}

