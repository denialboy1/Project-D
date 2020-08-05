// Team Project D has all rights this game


#include "Assassin/CD_Assassin_Roll.h"

UCD_Assassin_Roll::UCD_Assassin_Roll() {
	//쿨타임 설정
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(0.5f));

	//태그 설정
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Roll"));
}