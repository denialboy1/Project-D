// Team Project D has all rights this game


#include "GE_Archer_Skill3.h"

UGE_Archer_Skill3::UGE_Archer_Skill3() {
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(8.0f));
	Period.SetValue(8.0f);
}