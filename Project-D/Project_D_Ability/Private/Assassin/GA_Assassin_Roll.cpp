// Team Project D has all rights this game


#include "Assassin/GA_Assassin_Roll.h"
#include "Assassin/CD_Assassin_Roll.h"
#include "AbilitySystemComponent.h"
#include "Assassin/AssassinCharacter.h"
#include "Assassin/AssassinAnimInstance.h"
#include "GameplayTagsModule.h"

UGA_Assassin_Roll::UGA_Assassin_Roll() {
	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MontageRoll(TEXT("AnimMontage'/Game/Characters/Player/Assassin/Animation/AM_Assassin_Roll_Montage.AM_Assassin_Roll_Montage'"));
	if (MontageRoll.Succeeded()) {
		AM_Roll = MontageRoll.Object;
		UE_LOG(LogTemp, Log, TEXT("Assassin Roll Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Assassin Roll Anim Load Failed"))
	}

	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MontageAirRoll(TEXT("AnimMontage'/Game/Characters/Player/Assassin/Animation/AM_Assassin_Roll_Air.AM_Assassin_Roll_Air'"));
	if (MontageAirRoll.Succeeded()) {
		AM_AirRoll = MontageAirRoll.Object;
		UE_LOG(LogTemp, Log, TEXT("Assassin Air Roll Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Assassin Air Roll Anim Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

	//어빌리티 태그 설정
	ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Roll"));

	//쿨타임 설정
	CooldownGameplayEffectClass = UCD_Assassin_Roll::StaticClass();
}


void UGA_Assassin_Roll::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	//평타 리셋 콤보
	AAssassinCharacter* AssassinCharacter = Cast<AAssassinCharacter>(GetActorInfo().OwnerActor);
	if (AssassinCharacter) {
		AssassinCharacter->AttackCount = 0;
		AssassinCharacter->bSaveAttack = false;
		AssassinCharacter->bIsAttacking = false;
	}

	//회피 
	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	UAssassinAnimInstance* AssassinAnimInstance = Cast<UAssassinAnimInstance>(AnimInstance);
	if (AssassinAnimInstance) {
		if (AssassinAnimInstance->bIsInAir) {
			AssassinAnimInstance->Montage_Play(AM_AirRoll, 1.0f);
		}
		else {
			AssassinAnimInstance->Montage_Play(AM_Roll, 1.0f);
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}

