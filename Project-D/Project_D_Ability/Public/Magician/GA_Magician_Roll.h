// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility_Montage.h"
#include "GA_Magician_Roll.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_D_ABILITY_API UGA_Magician_Roll : public UGameplayAbility_Montage
{
	GENERATED_BODY()
public:
	UGA_Magician_Roll();

	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
