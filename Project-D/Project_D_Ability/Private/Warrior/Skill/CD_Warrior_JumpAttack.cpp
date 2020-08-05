// Team Project D has all rights this game


#include "Warrior/Skill/CD_Warrior_JumpAttack.h"

#include "GameplayTagsModule.h"
UCD_Warrior_JumpAttack::UCD_Warrior_JumpAttack() {
	//쿨타임 설정
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(3.0f));

	//태그 설정
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Warrior.Skill1"));
}