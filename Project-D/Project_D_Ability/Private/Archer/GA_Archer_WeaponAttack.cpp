// Team Project D has all rights this game

#include "Archer/GA_Archer_WeaponAttack.h"
#include "UObject/ConstructorHelpers.h"
#include "Archer/ArcherAnimInstance.h"
#include "AbilitySystemComponent.h"
#include "Archer/ArcherCharacter.h"

UGA_Archer_WeaponAttack::UGA_Archer_WeaponAttack() {
	
	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Archer/Animation/AM_Archer_WeaponAttack.AM_Archer_WeaponAttack'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("Archer WeaponAttack Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Archer WeaponAttack Anim Load Failed"))
	}
	
	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}

void UGA_Archer_WeaponAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (CommitAbility(Handle, ActorInfo,ActivationInfo)) {
		AArcherCharacter* Character = Cast<AArcherCharacter>(GetActorInfo().OwnerActor);
		if (Character) {
			Character->GetAbilitySystemComponent()->PlayMontage(this, ActivationInfo, MontageToPlay, 1.0f);
		}
		//AbilitySystemComponent->PlayMontage(Ability, Ability->GetCurrentActivationInfo(), MontageToPlay, Rate, StartSection) > 0.f)
	}
}
