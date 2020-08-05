// Team Project D has all rights this game


#include "Assassin/Skill/CD_Assassin_DashAttack.h"

UCD_Assassin_DashAttack::UCD_Assassin_DashAttack() {
	//��Ÿ�� ����
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(10.0f));

	//�±� ����
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Skill4"));
}