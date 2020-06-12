// Team Project D has all rights this game

#include "GE_Archer_Skill1.h"

UGE_Archer_Skill1::UGE_Archer_Skill1() {
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(4.0f)); 
	Period.SetValue(4.0f);

	
}