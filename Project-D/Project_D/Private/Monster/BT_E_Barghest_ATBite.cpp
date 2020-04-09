// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_E_Barghest_ATBite.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UBT_E_Barghest_ATBite::UBT_E_Barghest_ATBite()
{
	NodeName = TEXT("Bite");
}

EBTNodeResult::Type UBT_E_Barghest_ATBite::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	Controller = Cast<AE_Barghest_Controller>(OwnerComp.GetAIOwner());
	Pawn = Cast<AE_Barghest>(Controller->GetPawn());
	Anim = Cast<UE_Barghest_Anim>(Pawn->GetMesh()->GetAnimInstance());
	Pawn->TriggerBite = true;

	Controller->EndPatten();
	return EBTNodeResult::Type();
}
