// Team Project D has all rights this game


#include "Archer/Skill/CD_Archer_Skill1.h"
#include "GameplayTagsModule.h"
UCD_Archer_Skill1::UCD_Archer_Skill1() {
	//��Ÿ�� ����
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(3.0f));

	//�±� ����
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Archer.Skill1"));
}