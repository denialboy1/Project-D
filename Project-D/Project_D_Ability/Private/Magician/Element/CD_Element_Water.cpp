// Team Project D has all rights this game


#include "Magician/Element/CD_Element_Water.h"
#include "GameplayTagsModule.h"
UCD_Element_Water::UCD_Element_Water() {
	//��Ÿ�� ����
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(4.0f));
	
	//�±� ����
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Water"));
}