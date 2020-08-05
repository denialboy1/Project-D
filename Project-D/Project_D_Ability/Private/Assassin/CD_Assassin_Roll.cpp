// Team Project D has all rights this game


#include "Assassin/CD_Assassin_Roll.h"

UCD_Assassin_Roll::UCD_Assassin_Roll() {
	//��Ÿ�� ����
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(0.5f));

	//�±� ����
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Roll"));
}