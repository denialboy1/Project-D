// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gamesystem/PD_AIController.h"
#include "Grux_Controller.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_API AGrux_Controller : public APD_AIController
{
	GENERATED_BODY()
	
	AGrux_Controller();

private:

public:
	UFUNCTION()
	void PlayDoublePain();

	UFUNCTION()
	void PlayStone();

	UFUNCTION()
	void PlayStampede();
};
