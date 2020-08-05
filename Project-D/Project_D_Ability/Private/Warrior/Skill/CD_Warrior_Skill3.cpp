// Team Project D has all rights this game


#include "Warrior/Skill/CD_Warrior_Skill3.h"
#include "GameplayTagsModule.h"
UCD_Warrior_Skill3::UCD_Warrior_Skill3() {
	//��Ÿ�� ����
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(5.0f));

	//�±� ����
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Warrior.Skill3"));
}