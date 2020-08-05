// Team Project D has all rights this game


#include "Assassin/Skill/CD_Assassin_ThrowDagger.h"

UCD_Assassin_ThrowDagger::UCD_Assassin_ThrowDagger() {
	//쿨타임 설정
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(5.0f));

	//태그 설정
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Skill1"));
}