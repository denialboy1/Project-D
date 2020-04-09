// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Project_DGameMode.h"
#include "Project_DCharacter.h"
#include "PD_GameStateBase.h"
#include "PD_PlayerState.h"
#include "UObject/ConstructorHelpers.h"

AProject_DGameMode::AProject_DGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Player/Assassin/BP_Assassin.BP_Assassin_C"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<APD_GameStateBase> GameState(TEXT("/Script/Project_D.PD_GameStateBase"));
	if (GameState.Class != NULL)
	{
		GameStateClass = GameState.Class;
	}
	static ConstructorHelpers::FClassFinder<APD_PlayerState> PlayerState(TEXT("/Script/Project_D.PD_PlayerState"));
	if (PlayerState.Class != NULL)
	{
		PlayerStateClass = PlayerState.Class;
	}
}
