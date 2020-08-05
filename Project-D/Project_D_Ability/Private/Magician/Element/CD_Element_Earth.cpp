// Team Project D has all rights this game


#include "Magician/Element/CD_Element_Earth.h"
#include "GameplayTagsModule.h"
UCD_Element_Earth::UCD_Element_Earth() {
	//��Ÿ�� ����
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(4.0f));

	//�±� ����
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Earth"));
}