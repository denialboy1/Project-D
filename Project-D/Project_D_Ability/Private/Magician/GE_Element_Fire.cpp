// Team Project D has all rights this game


#include "GE_Element_Fire.h"
#include "GameplayTagsModule.h"
UGE_Element_Fire::UGE_Element_Fire() {
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(4.0f));
	Period.SetValue(4.0f);

	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Fire"));
}