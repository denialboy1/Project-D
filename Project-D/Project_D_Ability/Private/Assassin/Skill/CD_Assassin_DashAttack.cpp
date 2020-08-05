// Team Project D has all rights this game


#include "Assassin/Skill/CD_Assassin_DashAttack.h"

UCD_Assassin_DashAttack::UCD_Assassin_DashAttack() {
	//쿨타임 설정
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(10.0f));

	//태그 설정
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Skill4"));
}