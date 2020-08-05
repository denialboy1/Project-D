// Team Project D has all rights this game


#include "Assassin/GA_Assassin_DoubleJump.h"
#include "AbilitySystemComponent.h"
#include "Assassin/AssassinCharacter.h"
UGA_Assassin_DoubleJump::UGA_Assassin_DoubleJump() {
	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}


void UGA_Assassin_DoubleJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	
	
	AAssassinCharacter* AssassinCharacter = Cast<AAssassinCharacter>(GetActorInfo().OwnerActor);
	if (AssassinCharacter) {
		//평타 리셋 콤보
		AssassinCharacter->AttackCount = 0;
		AssassinCharacter->bSaveAttack = false;
		AssassinCharacter->bIsAttacking = false;

		//더블 점프 온
		AssassinCharacter->bCanDoubleJump = true;
		AssassinCharacter->Launch();
	}
	


}
