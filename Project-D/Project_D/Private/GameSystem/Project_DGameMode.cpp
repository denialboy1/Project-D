// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GameSystem/Project_DGameMode.h"
#include "GameSystem/Project_DCharacter.h"
#include "GameSystem/PD_GameStateBase.h"
#include "GameSystem/PD_PlayerState.h"
#include "UObject/ConstructorHelpers.h"

AProject_DGameMode::AProject_DGameMode()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Player/Assassin/BP_Assassin.BP_Assassin_C"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
	static ConstructorHelpers::FClassFinder<APD_GameStateBase> PDGameState(TEXT("/Script/Project_D.PD_GameStateBase"));
	if (PDGameState.Class != NULL)
	{
		GameStateClass = PDGameState.Class;
	}
	static ConstructorHelpers::FClassFinder<APD_PlayerState> PDPlayerState(TEXT("/Script/Project_D.PD_PlayerState"));
	if (PDPlayerState.Class != NULL)
	{
		PlayerStateClass = PDPlayerState.Class;
	}
}
