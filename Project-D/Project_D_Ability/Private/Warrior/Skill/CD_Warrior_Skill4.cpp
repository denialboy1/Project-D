// Team Project D has all rights this game


#include "Warrior/Skill/CD_Warrior_Skill4.h"
#include "GameplayTagsModule.h"
UCD_Warrior_Skill4::UCD_Warrior_Skill4() {
	//쿨타임 설정
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(2.5f));

	//태그 설정
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Warrior.Skill4"));
}