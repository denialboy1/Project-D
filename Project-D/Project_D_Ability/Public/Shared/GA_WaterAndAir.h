// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_WaterAndAir.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_D_ABILITY_API UGA_WaterAndAir : public UGameplayAbility
{
	GENERATED_BODY()
		UGA_WaterAndAir();
	TSubclassOf<AActor> Skill;
private:
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
