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

	//�Ѱ�¥�� ���� ���
	bool OneElementAction(FName Tag1, TArray<AActor*>* Elements1, TSubclassOf<UGameplayAbility> Ability);

	//�ΰ��ڸ� ���� ���
	bool TwoElementAction(FName Tag1, FName Tag2, TArray<AActor*>* Elements1, TArray<AActor*>* Elements2,TSubclassOf<UGameplayAbility> Ability);

	//����� ���� ����
	void DestroyElement(TArray<AActor*>* Elements);

	//��� ���� ����ϸ� �±׿��� ����
	void RemoveTagForZeroElement(TArray<AActor*> Element,FGameplayTag Tag);
};
