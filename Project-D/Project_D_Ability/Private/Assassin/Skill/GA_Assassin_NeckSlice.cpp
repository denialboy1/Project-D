// Team Project D has all rights this game


#include "Assassin/Skill/GA_Assassin_NeckSlice.h"
#include "Assassin/Skill/CD_Assassin_NeckSlice.h"
#include "Assassin/AssassinCharacter.h"
#include "Assassin/AssassinAnimInstance.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsModule.h"

UGA_Assassin_NeckSlice::UGA_Assassin_NeckSlice() {
	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Assassin/Animation/AM_Assassin_RoleAttack_Montage.AM_Assassin_RoleAttack_Montage'"));
	if (Montage.Succeeded()) {
		AM_NeckSlice = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("UGA_Assassin_DashAttack_BigDaggerThrow_Start Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("UGA_Assassin_DashAttack_BigDaggerThrow_Start Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;


	//어빌리티 태그 설정
	ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Skill2"));

	//쿨타임 설정
	CooldownGameplayEffectClass = UCD_Assassin_NeckSlice::StaticClass();
}


void UGA_Assassin_NeckSlice::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}
	AAssassinCharacter* AssassinCharacter = Cast<AAssassinCharacter>(GetActorInfo().OwnerActor);
	if (AssassinCharacter) {
		//평타 리셋 콤보
		AssassinCharacter->AttackCount = 0;
		AssassinCharacter->bSaveAttack = false;
		AssassinCharacter->bIsAttacking = false;
	}

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	UAssassinAnimInstance* AssassinAnimInstance = Cast<UAssassinAnimInstance>(AnimInstance);

	if (AssassinAnimInstance->bIsInAir) {
		Cast<AAssassinCharacter>(ActorInfo->OwnerActor)->LaunchCharacter(FVector(0, 0, 300), false, false);
		AssassinAnimInstance->bIsNeckSlice = true;
	}
	else {
		AnimInstance->Montage_Play(AM_NeckSlice, 1.0f);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}



