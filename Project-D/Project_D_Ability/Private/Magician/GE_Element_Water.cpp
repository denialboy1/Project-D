// Team Project D has all rights this game


#include "GE_Element_Water.h"
#include "GameplayTagsModule.h"
UGE_Element_Water::UGE_Element_Water() {
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(4.0f));
	Period.SetValue(4.0f);

	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Water"));
}