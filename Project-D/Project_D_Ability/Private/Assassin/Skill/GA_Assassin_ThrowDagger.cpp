// Team Project D has all rights this game


#include "Assassin/Skill/GA_Assassin_ThrowDagger.h"
#include "Assassin/Skill/CD_Assassin_ThrowDagger.h"
#include "Assassin/AssassinCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsModule.h"

UGA_Assassin_ThrowDagger::UGA_Assassin_ThrowDagger() {
	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Assassin/Animation/AM_Assassin_Throw_Montage.AM_Assassin_Throw_Montage'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("Warrior Roll Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Warrior Roll Anim Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

	//어빌리티 태그 설정
	ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Skill1"));

	//쿨타임 설정
	CooldownGameplayEffectClass = UCD_Assassin_ThrowDagger::StaticClass();
}

void UGA_Assassin_ThrowDagger::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	AAssassinCharacter* AssassinCharacter = Cast<AAssassinCharacter>(GetActorInfo().OwnerActor);
	if (AssassinCharacter) {
		//평타 리셋 콤보
		AssassinCharacter->AttackCount = 0;
		AssassinCharacter->bSaveAttack = false;
		AssassinCharacter->bIsAttacking = false;

		//대거 던지기 
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