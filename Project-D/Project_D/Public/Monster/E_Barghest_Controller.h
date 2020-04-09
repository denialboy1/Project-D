// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PD_AIController.h"
#include "E_Barghest_Controller.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_API AE_Barghest_Controller : public APD_AIController
{
	GENERATED_BODY()
	
public:
	AE_Barghest_Controller();

	virtual void Tick(float DeltaTime) override;

public:
	int index;
	float TargetDistance;
	
};
