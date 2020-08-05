// Team Project D has all rights this game


#include "Archer/Skill/CD_Archer_Skill2.h"
#include "GameplayTagsModule.h"
UCD_Archer_Skill2::UCD_Archer_Skill2() {
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(3.0f));

	//태그 설정
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Archer.Skill2"));
}