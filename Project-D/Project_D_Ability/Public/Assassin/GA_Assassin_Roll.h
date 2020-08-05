// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Assassin_Roll.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_ABILITY_API UGA_Assassin_Roll : public UGameplayAbility
{
	GENERATED_BODY()

	UAnimMontage* AM_Roll;

	UAnimMontage* AM_AirRoll;


public:
	UGA_Assassin_Roll();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
