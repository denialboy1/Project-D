// Team Project D has all rights this game


#include "GE_Archer_Skill2.h"

UGE_Archer_Skill2::UGE_Archer_Skill2() {
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(4.0f));
	Period.SetValue(4.0f);
}