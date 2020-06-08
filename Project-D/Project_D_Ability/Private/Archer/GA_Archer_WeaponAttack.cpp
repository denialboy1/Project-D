// Team Project D has all rights this game

#include "GA_Archer_WeaponAttack.h"
#include "UObject/ConstructorHelpers.h"
#include "ArcherAnimInstance.h"
#include "AbilitySystemComponent.h"

UGA_Archer_WeaponAttack::UGA_Archer_WeaponAttack() {
	
	//¸ùÅ¸ÁÖ ¼³Á¤
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Archer/Animation/AM_Archer_WeaponAttack.AM_Archer_WeaponAttack'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;

		ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
		InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
		bServerRespectsRemoteAbilityCancellation = true;
		NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
		NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
		UE_LOG(LogTemp, Log, TEXT("Archer WeaponAttack Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Archer WeaponAttack Anim Load Failed"))
	}
	
}

void UGA_Archer_WeaponAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
