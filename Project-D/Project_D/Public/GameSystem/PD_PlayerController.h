// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PD_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_API APD_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APD_PlayerController();

	virtual void PostInitializeComponents() override;
	virtual void Possess(APawn* aPawn) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	int PlayerNum;
};
