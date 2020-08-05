// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility_Montage.h"
#include "GA_Warrior_Skill4.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_ABILITY_API UGA_Warrior_Skill4 : public UGameplayAbility_Montage
{
	GENERATED_BODY()
	
public:
	UGA_Warrior_Skill4();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
};
