// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/BTGrux_ATDoublePain.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTGrux_ATDoublePain::UBTGrux_ATDoublePain()
{
	NodeName = TEXT("DoublePain");
}

EBTNodeResult::Type UBTGrux_ATDoublePain::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	ControllingPawn = Cast<AGrux>(OwnerComp.GetAIOwner()->GetPawn());
	Animation = Cast<UGrux_Anim>(ControllingPawn->GetMesh()->GetAnimInstance());
	Cast<AGrux_Controller>(OwnerComp.GetAIOwner())->PlayDoublePain();

	Cast<AGrux_Controller>(OwnerComp.GetAIOwner())->EndPatten(); // 패턴 종료
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}