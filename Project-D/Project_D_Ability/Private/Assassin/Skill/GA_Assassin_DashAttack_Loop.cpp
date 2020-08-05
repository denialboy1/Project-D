// Team Project D has all rights this game


#include "Assassin/Skill/GA_Assassin_DashAttack_Loop.h"
#include "Assassin/AssassinCharacter.h"
#include "AbilitySystemComponent.h"

UGA_Assassin_DashAttack_Loop::UGA_Assassin_DashAttack_Loop() {
	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Assassin/Animation/AM_Assassin_DashAttack_Loop.AM_Assassin_DashAttack_Loop'"));
	if (Montage.Succeeded()) {
		AM_DashAttackLoop = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("UGA_Assassin_DashAttack_Loop Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("UGA_Assassin_DashAttack_Loop Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}


void UGA_Assassin_DashAttack_Loop::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	AAssassinCharacter* AssassinCharacter = Cast<AAssassinCharacter>(ActorInfo->OwnerActor);
	FVector Vector = AssassinCharacter->GetBaseAimRotation().Vector() * 5000.0f;
	Cast<AAssassinCharacter>(ActorInfo->OwnerActor)->LaunchCharacter(Vector, false, false);

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	if (AnimInstance) {
		AnimInstance->Montage_Play(AM_DashAttackLoop, 1.0f);
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}

