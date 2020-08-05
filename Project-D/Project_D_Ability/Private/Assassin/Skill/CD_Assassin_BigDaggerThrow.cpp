// Team Project D has all rights this game


#include "Assassin/Skill/CD_Assassin_BigDaggerThrow.h"


UCD_Assassin_BigDaggerThrow::UCD_Assassin_BigDaggerThrow() {
	//쿨타임 설정
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(1.0f));

	//태그 설정
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Skill3"));
}