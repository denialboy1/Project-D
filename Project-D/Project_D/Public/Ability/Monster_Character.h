// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/BaseCharacter.h"
#include "Ability/AttributeSet_Monster.h"
#include "Monster_Character.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_API AMonster_Character : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Motion)
	TArray<TSubclassOf<UGameplayAbility>> Motions;

protected:
	virtual void BeginPlay() override;
};
