// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility_Montage.h"
#include "GA_Assassin_WeaponAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_ABILITY_API UGA_Assassin_WeaponAttack : public UGameplayAbility_Montage
{
	GENERATED_BODY()
public:
	UGA_Assassin_WeaponAttack();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
