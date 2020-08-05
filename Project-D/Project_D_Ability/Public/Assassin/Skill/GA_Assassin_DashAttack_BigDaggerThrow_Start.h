// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility_Montage.h"
#include "GA_Assassin_DashAttack_BigDaggerThrow_Start.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_ABILITY_API UGA_Assassin_DashAttack_BigDaggerThrow_Start : public UGameplayAbility_Montage
{
	GENERATED_BODY()
public:
	UGA_Assassin_DashAttack_BigDaggerThrow_Start();
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
};
