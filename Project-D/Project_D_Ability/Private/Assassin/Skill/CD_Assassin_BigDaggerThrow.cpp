// Team Project D has all rights this game


#include "Assassin/Skill/CD_Assassin_BigDaggerThrow.h"


UCD_Assassin_BigDaggerThrow::UCD_Assassin_BigDaggerThrow() {
	//��Ÿ�� ����
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(1.0f));

	//�±� ����
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Skill3"));
}