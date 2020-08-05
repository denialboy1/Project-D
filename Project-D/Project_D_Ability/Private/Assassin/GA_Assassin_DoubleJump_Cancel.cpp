// Team Project D has all rights this game


#include "Assassin/GA_Assassin_DoubleJump_Cancel.h"
#include "Assassin/AssassinCharacter.h"
UGA_Assassin_DoubleJump_Cancel::UGA_Assassin_DoubleJump_Cancel() {
	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}

void UGA_Assassin_DoubleJump_Cancel::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	AAssassinCharacter* AssassinCharacter = Cast<AAssassinCharacter>(OwnerInfo->OwnerActor);
	AssassinCharacter->bCanDoubleJump = false;
}