// Team Project D has all rights this game


#include "Warrior/CD_Warrior_SpecialCommand.h"
#include "GameplayTagsModule.h"

UCD_Warrior_SpecialCommand::UCD_Warrior_SpecialCommand() {
	//��Ÿ�� ����
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(10.0f));

	//�±� ����
	InheritableOwnedTagsContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Warrior.SpecialCommand"));
}