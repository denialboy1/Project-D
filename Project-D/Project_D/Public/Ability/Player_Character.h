// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/BaseCharacter.h"
#include "Ability/AttributeSet_Player.h"
#include "Player_Character.generated.h"


UENUM(BlueprintType)
enum class AbilityInput : uint8
{
	WeaponAttack UMETA(DisplayName = "Weapon Attack"),
	Combo1 UMETA(DisplayName = "Combo1"),
	Combo2 UMETA(DisplayName = "Combo2"),
	UseSpell1 UMETA(DisplayName = "Use Spell 1"),
	UseSpell2 UMETA(DisplayName = "Use Spell 2"),
	UseSpell3 UMETA(DisplayName = "Use Spell 3"),
	UseSpell4 UMETA(DisplayName = "Use Spell 4"),
	UseItem1 UMETA(DisplayName = "Use Item 1"),
	UseItem2 UMETA(DisplayName = "Use Item 2"),
	UseItem3 UMETA(DisplayName = "Use Item 3"),
	UseItem4 UMETA(DisplayName = "Use Item 4"),
	SpecialCommand UMETA(DisplayName = "Special Command"),
	Roll UMETA(DisplayName = "Roll"),
};

/**
 * 
 */
UCLASS()
class PROJECT_D_API APlayer_Character : public ABaseCharacter
{
	GENERATED_BODY()

public:

	APlayer_Character();

	UFUNCTION(BlueprintCallable)
	virtual float GetAgro() const;

	//Input Ability
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputAbility)
	TSubclassOf<UGameplayAbility> WeaponAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputAbility)
	TSubclassOf<UGameplayAbility> Combo1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputAbility)
	TSubclassOf<UGameplayAbility> Combo2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputAbility)
	TSubclassOf<UGameplayAbility> UseSpell1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputAbility)
	TSubclassOf<UGameplayAbility> UseSpell2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputAbility)
	TSubclassOf<UGameplayAbility> UseSpell3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputAbility)
	TSubclassOf<UGameplayAbility> UseSpell4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputAbility)
	TSubclassOf<UGameplayAbility> UseItem1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputAbility)
	TSubclassOf<UGameplayAbility> UseItem2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputAbility)
	TSubclassOf<UGameplayAbility> UseItem3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputAbility)
	TSubclassOf<UGameplayAbility> UseItem4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputAbility)
	TSubclassOf<UGameplayAbility> SpecialCommand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputAbility)
	TSubclassOf<UGameplayAbility> Roll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillAbility)
	TArray<TSubclassOf<UGameplayAbility>> ExtraSkill;
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void BeginPlay() override;

	void BindAbilitySystemAndAbilityInput();
};
