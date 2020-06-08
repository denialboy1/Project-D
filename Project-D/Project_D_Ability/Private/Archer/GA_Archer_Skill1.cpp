// Team Project D has all rights this game


#include "GA_Archer_Skill1.h"
#include "UObject/ConstructorHelpers.h"
#include "ArcherAnimInstance.h"
#include "ArcherCharacter.h"
#include "AbilitySystemComponent.h"

UGA_Archer_Skill1::UGA_Archer_Skill1() {

	//¸ùÅ¸ÁÖ ¼³Á¤
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Archer/Animation/AM_Archer_Skill1.AM_Archer_Skill1'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;

		ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
		InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
		bServerRespectsRemoteAbilityCancellation = true;
		NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
		NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

		//ÄðÅ¸ÀÓ ¼³Á¤
		CooldownGameplayEffectClass = UGE_Archer_Skill1::StaticClass();

		UE_LOG(LogTemp, Log, TEXT("Archer Skill1 Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Archer Skill1 Anim Load Failed"))
	}

}

void UGA_Archer_Skill1::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!Cast<AArcherCharacter>(GetOwningActorFromActorInfo())->GetIsAim()) return; 

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
