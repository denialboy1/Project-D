// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster_Character.h"

void AMonster_Character::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent == nullptr) return;

	if (HasAuthority()) {
		int ID = 100;
		for (TSubclassOf<UGameplayAbility> motion : Motions)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(motion.GetDefaultObject(), 1, -1));
			ID++;
		}
	}
}