// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet_Character.h"
#include "AttributeSet_Monster.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_API UAttributeSet_Monster : public UAttributeSet_Character
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Agro", ReplicatedUsing = OnRep_WarriorAgro)
	FGameplayAttributeData WarriorAgro;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Monster, WarriorAgro)

	UPROPERTY(BlueprintReadOnly, Category = "Agro", ReplicatedUsing = OnRep_ArcherAgro)
	FGameplayAttributeData ArcherAgro;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Monster, ArcherAgro)

	UPROPERTY(BlueprintReadOnly, Category = "Agro", ReplicatedUsing = OnRep_MagicianAgro)
	FGameplayAttributeData MagicianAgro;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Monster, MagicianAgro)

	UPROPERTY(BlueprintReadOnly, Category = "Agro", ReplicatedUsing = OnRep_AssassinAgro)
	FGameplayAttributeData AssassinAgro;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Monster, AssassinAgro)

	UPROPERTY(BlueprintReadOnly, Category = "Agro", ReplicatedUsing = OnRep_WarriorMaxAgro)
	FGameplayAttributeData WarriorMaxAgro;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Monster, WarriorMaxAgro)

	UPROPERTY(BlueprintReadOnly, Category = "Agro", ReplicatedUsing = OnRep_ArcherMaxAgro)
	FGameplayAttributeData ArcherMaxAgro;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Monster, ArcherMaxAgro)

	UPROPERTY(BlueprintReadOnly, Category = "Agro", ReplicatedUsing = OnRep_MagicianMaxAgro)
	FGameplayAttributeData MagicianMaxAgro;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Monster, MagicianMaxAgro)

	UPROPERTY(BlueprintReadOnly, Category = "Agro", ReplicatedUsing = OnRep_AssassinMaxAgro)
	FGameplayAttributeData AssassinMaxAgro;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Monster, AssassinMaxAgro)
protected:
	UFUNCTION()
	virtual void OnRep_WarriorAgro();

	UFUNCTION()
	virtual void OnRep_ArcherAgro();

	UFUNCTION()
	virtual void OnRep_MagicianAgro();

	UFUNCTION()
	virtual void OnRep_AssassinAgro();

	UFUNCTION()
	virtual void OnRep_WarriorMaxAgro();

	UFUNCTION()
	virtual void OnRep_ArcherMaxAgro();

	UFUNCTION()
	virtual void OnRep_MagicianMaxAgro();

	UFUNCTION()
	virtual void OnRep_AssassinMaxAgro();
};
