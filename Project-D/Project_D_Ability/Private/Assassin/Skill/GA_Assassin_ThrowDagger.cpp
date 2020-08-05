// Team Project D has all rights this game


#include "Assassin/Skill/GA_Assassin_ThrowDagger.h"
#include "Assassin/Skill/CD_Assassin_ThrowDagger.h"
#include "Assassin/AssassinCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsModule.h"

UGA_Assassin_ThrowDagger::UGA_Assassin_ThrowDagger() {
	//��Ÿ�� ����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Assassin/Animation/AM_Assassin_Throw_Montage.AM_Assassin_Throw_Montage'"));
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

	//�����Ƽ �±� ����
	ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Skill1"));

	//��Ÿ�� ����
	CooldownGameplayEffectClass = UCD_Assassin_ThrowDagger::StaticClass();
}

void UGA_Assassin_ThrowDagger::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	AAssassinCharacter* AssassinCharacter = Cast<AAssassinCharacter>(GetActorInfo().OwnerActor);
	if (AssassinCharacter) {
		//��Ÿ ���� �޺�
		AssassinCharacter->AttackCount = 0;
		AssassinCharacter->bSaveAttack = false;
		AssassinCharacter->bIsAttacking = false;

		//��� ������ 
		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
		UAssassinAnimInstance* AssassinAnimInstance = Cast<UAssassinAnimInstance>(AnimInstance);
		if (AssassinAnimInstance) {
			if (AssassinAnimInstance->bIsInAir) {
				AssassinAnimInstance->Montage_Play(MontageToPlay, 1.0f);
			}
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}