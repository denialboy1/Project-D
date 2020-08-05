// Team Project D has all rights this game


#include "Magician/Skill/GA_EarthAndAir.h"
#include "Magician/MagicianCharacter.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

UGA_EarthAndAir::UGA_EarthAndAir() {

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

	UE_LOG(LogTemp, Log, TEXT("GA_EarthAndAir Load Succeess"))
}

void UGA_EarthAndAir::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AMagicianCharacter* Character = Cast<AMagicianCharacter>(GetOwningActorFromActorInfo());
	for (auto PlayerCharacter : Character->AllPlayerCharacter) {
		PlayerCharacter->ServerRPC_Fast(5.0f);
	}
	
	UE_LOG(LogTemp, Log, TEXT("GA_EarthAndAir Skill Use Succeess"))

}