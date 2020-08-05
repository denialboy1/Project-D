// Team Project D has all rights this game


#include "Magician/Element/CD_Element_Air.h"
#include "GameplayTagsModule.h"
UCD_Element_Air::UCD_Element_Air() {
	//쿨타임 설정
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(4.0f));

	//태그 설정
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Air"));
}