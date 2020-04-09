// Fill out your copyright notice in the Description page of Project Settings.

#include "Player_Character.h"

APlayer_Character::APlayer_Character()
{
}

float APlayer_Character::GetAgro() const
{
	return 0;
}

void APlayer_Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds("ConfirmInput", "CancelInput", "AbilityInput"));
}

void APlayer_Character::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent == nullptr) return;

	// 해당 어빌리티가 등록되어 있으면 키 값에 연결
	if (HasAuthority()) {
		BindAbilitySystemAndAbilityInput();

		int ID = 100;
		for (TSubclassOf<UGameplayAbility> skill : ExtraSkill)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(skill.GetDefaultObject(), 1, ID));
			ID++;
		}
	}
	

	
}

void APlayer_Character::BindAbilitySystemAndAbilityInput()
{
	if (WeaponAttack) {
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(WeaponAttack.GetDefaultObject(), 1, 0));
	}
	
	if (Combo1) {
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Combo1.GetDefaultObject(), 1, 1));
	}

	if (Combo2) {
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Combo2.GetDefaultObject(), 1, 2));
	}

	if (UseSpell1)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UseSpell1.GetDefaultObject(), 1, 3));
	}
	if (UseSpell2)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UseSpell2.GetDefaultObject(), 1, 4));
	}
	if (UseSpell3)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UseSpell3.GetDefaultObject(), 1, 5));
	}
	if (UseSpell4)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UseSpell4.GetDefaultObject(), 1, 6));
	}

	if (UseItem1)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UseItem1.GetDefaultObject(), 1, 7));
	}

	if (UseItem2)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UseItem2.GetDefaultObject(), 1, 8));
	}

	if (UseItem3)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UseItem3.GetDefaultObject(), 1, 9));
	}

	if (UseItem4)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UseItem4.GetDefaultObject(), 1, 10));
	}

	if (SpecialCommand)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(SpecialCommand.GetDefaultObject(), 1, 11));
	}

	if (Roll)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Roll.GetDefaultObject(), 1, 12));
	}
}

