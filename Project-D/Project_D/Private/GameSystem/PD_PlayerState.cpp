// Fill out your copyright notice in the Description page of Project Settings.

#include "PD_PlayerState.h"
#include "net/UnrealNetwork.h"

APD_PlayerState::APD_PlayerState()
{
	bReplicates = true;
	AgroGage = 0;
}

int32 APD_PlayerState::GetAgro()
{
	return AgroGage;
}

void APD_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APD_PlayerState, AgroGage);
}
