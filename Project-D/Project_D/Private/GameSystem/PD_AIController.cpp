// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSystem/PD_AIController.h"
#include "Components/SkeletalMeshComponent.h"

const FName APD_AIController::SelfActorKey(TEXT("SelfActor"));
const FName APD_AIController::HomePosKey(TEXT("HomePos"));
const FName APD_AIController::TargetKey(TEXT("Target"));
const FName APD_AIController::DistanceToTargetKey(TEXT("DistanceToTarget"));
const FName APD_AIController::PattenKey(TEXT("PattenKey"));
const FName APD_AIController::TargetPosKey(TEXT("TargetPos"));
const FName APD_AIController::DeadKey(TEXT("isDead"));

APD_AIController::APD_AIController()
{
	CanAct = true;
	isDead = false;
	GameState = GetWorld() != NULL ? GetWorld()->GetGameState() : NULL;
	
	static const ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Characters/Monster/BB_Monster.BB_Monster"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	
	AgroGage = { 1, 5, 2, 10 };
	DistanceTo.Init(0, 4);
}

void APD_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurPlayerNum = GameState->PlayerArray.Num();
	for (int i = 0; i < GameState->PlayerArray.Num(); i++)
	{
		if (GameState->PlayerArray[i] != nullptr)
		{
			auto PlayerPawn = GameState->PlayerArray[i]->GetPawn();
			if (!::IsValid(PlayerPawn)) return;

			DistanceTo[i] = PlayerPawn->GetDistanceTo(Cast<AActor>(GetPawn()));
		}
	}

	if (isDead) Dead();
}

void APD_AIController::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Warning, TEXT("PDController couldn't run behavior tree!"));
		}
	}
}

void APD_AIController::Dead()
{
	isDead = true;
	UnPossess();
}

void APD_AIController::StartPatten()
{
	if (CanAct)
	{
		CanAct = false;
		UE_LOG(LogTemp, Warning, TEXT("Patten Start!!"));
	}
}

void APD_AIController::EndPatten()
{
	if (!CanAct)
	{
		UE_LOG(LogTemp, Warning, TEXT("Patten End!!"));
		//GetBlackboardComponent()->SetValueAsObject(TargetKey, nullptr);
		//GetBlackboardComponent()->SetValueAsFloat(DistanceToTargetKey, -1);
		CanAct = true;
	}
}





//void APD_AIController::MultiPlayDoublePain_Implementation()
//{
//	PlayDoublePain();
//}
//
//void APD_AIController::ServerPlayDoublePain_Implementation()
//{
//	MultiPlayDoublePain();
//}
//
//bool APD_AIController::ServerPlayDoublePain_Validate()
//{
//	return true;
//}