// Team Project D has all rights this game


#include "Assassin/Skill/CD_Assassin_NeckSlice.h"

UCD_Assassin_NeckSlice::UCD_Assassin_NeckSlice() {
	//쿨타임 설정
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(2.0f));

	//태그 설정
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Skill2"));
}