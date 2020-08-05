// Team Project D has all rights this game

#include "Player/GE_PlayerAlive.h"
#include "AttributeSet_Character.h"

UGE_PlayerAlive::UGE_PlayerAlive() {
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo modifierInfo;
	modifierInfo.ModifierOp = EGameplayModOp::Type::Additive;
	modifierInfo.Magnitude.SetValue(1);

	UAttributeSet_Character* AttributeSet_Character = NewObject<UAttributeSet_Character>();
	modifierInfo.Attribute = AttributeSet_Character->GetHealthAttribute();

	Modifiers.Add(modifierInfo);
}