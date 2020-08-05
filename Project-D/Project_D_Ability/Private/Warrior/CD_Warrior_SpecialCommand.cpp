// Team Project D has all rights this game


#include "Warrior/CD_Warrior_SpecialCommand.h"
#include "GameplayTagsModule.h"

UCD_Warrior_SpecialCommand::UCD_Warrior_SpecialCommand() {
	//쿨타임 설정
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(10.0f));

	//태그 설정
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Warrior.SpecialCommand"));
}