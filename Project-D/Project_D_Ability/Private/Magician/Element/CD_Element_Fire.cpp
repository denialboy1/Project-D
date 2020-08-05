// Team Project D has all rights this game


#include "Magician/Element/CD_Element_Fire.h"
#include "GameplayTagsModule.h"
UCD_Element_Fire::UCD_Element_Fire() {
	//��Ÿ�� ����
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(4.0f));

	//�±� ����
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Fire"));
}