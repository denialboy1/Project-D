// Team Project D has all rights this game


#include "Assassin/Skill/CD_Assassin_ThrowDagger.h"

UCD_Assassin_ThrowDagger::UCD_Assassin_ThrowDagger() {
	//��Ÿ�� ����
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(5.0f));

	//�±� ����
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Skill1"));
}