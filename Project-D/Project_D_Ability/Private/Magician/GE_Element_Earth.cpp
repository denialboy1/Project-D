// Team Project D has all rights this game


#include "GE_Element_Earth.h"
#include "GameplayTagsModule.h"
UGE_Element_Earth::UGE_Element_Earth() {
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(4.0f));
	Period.SetValue(4.0f);

	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Earth"));
}