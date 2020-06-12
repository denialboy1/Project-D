// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Magician_WeaponAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_ABILITY_API UGA_Magician_WeaponAttack : public UGameplayAbility
{
	GENERATED_BODY()

	UGA_Magician_WeaponAttack();
private:
	class AMagicianCharacter* Character;

	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	//한개짜리 원소 사용
	bool OneElementAction(FName Tag1, TArray<AActor*>* Elements1, TSubclassOf<UGameplayAbility> Ability);

	//두개자리 원소 사용
	bool TwoElementAction(FName Tag1, FName Tag2, TArray<AActor*>* Elements1, TArray<AActor*>* Elements2,TSubclassOf<UGameplayAbility> Ability);

	//사용한 원소 삭제
	void DestroyElement(TArray<AActor*>* Elements);

	//모든 원소 사용하면 태그에서 삭제
	void RemoveTagForZeroElement(TArray<AActor*> Element,FGameplayTag Tag);
};
