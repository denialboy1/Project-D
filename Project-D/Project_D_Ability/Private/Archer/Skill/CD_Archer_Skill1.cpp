// Team Project D has all rights this game


#include "Archer/Skill/CD_Archer_Skill1.h"
#include "GameplayTagsModule.h"
UCD_Archer_Skill1::UCD_Archer_Skill1() {
	//쿨타임 설정
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(3.0f));

	//태그 설정
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Archer.Skill1"));
}