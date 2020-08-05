// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility_Montage.h"
#include "GA_Element_Water.generated.h"
/**
 *
 */
UCLASS()
class PROJECT_D_ABILITY_API UGA_Element_Water : public UGameplayAbility_Montage
{
	GENERATED_BODY()

		UGA_Element_Water();

private:
	class AMagicianCharacter* MagicianCharacter;


private:
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
