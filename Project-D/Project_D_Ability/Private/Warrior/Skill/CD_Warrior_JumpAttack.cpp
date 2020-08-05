// Team Project D has all rights this game


#include "Warrior/Skill/CD_Warrior_JumpAttack.h"

#include "GameplayTagsModule.h"
UCD_Warrior_JumpAttack::UCD_Warrior_JumpAttack() {
	//��Ÿ�� ����
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(3.0f));

	//�±� ����
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Warrior.Skill1"));
}