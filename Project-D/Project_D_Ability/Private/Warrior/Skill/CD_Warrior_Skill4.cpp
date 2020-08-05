// Team Project D has all rights this game


#include "Warrior/Skill/CD_Warrior_Skill4.h"
#include "GameplayTagsModule.h"
UCD_Warrior_Skill4::UCD_Warrior_Skill4() {
	//��Ÿ�� ����
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(2.5f));

	//�±� ����
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Warrior.Skill4"));
}