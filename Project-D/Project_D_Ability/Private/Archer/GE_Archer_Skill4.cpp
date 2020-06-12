// Team Project D has all rights this game


#include "GE_Archer_Skill4.h"

UGE_Archer_Skill4::UGE_Archer_Skill4() {
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(12.0f));
	Period.SetValue(12.0f);
}