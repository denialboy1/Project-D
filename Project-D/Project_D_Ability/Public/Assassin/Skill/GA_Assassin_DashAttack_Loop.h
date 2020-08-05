// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility_Montage.h"
#include "GA_Assassin_DashAttack_Loop.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_ABILITY_API UGA_Assassin_DashAttack_Loop : public UGameplayAbility_Montage
{
	GENERATED_BODY()
private:
	UAnimMontage* AM_DashAttackLoop;
public:
	UGA_Assassin_DashAttack_Loop();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
