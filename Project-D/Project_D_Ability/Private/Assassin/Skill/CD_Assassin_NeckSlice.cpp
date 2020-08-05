// Team Project D has all rights this game


#include "Assassin/Skill/CD_Assassin_NeckSlice.h"

UCD_Assassin_NeckSlice::UCD_Assassin_NeckSlice() {
	//��Ÿ�� ����
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(2.0f));

	//�±� ����
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Skill2"));
}