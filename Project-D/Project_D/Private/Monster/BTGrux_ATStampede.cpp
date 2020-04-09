// Fill out your copyright notice in the Description page of Project Settings.

#include "BTGrux_ATStampede.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTGrux_ATStampede::UBTGrux_ATStampede()
{
	NodeName = TEXT("Stampede");
}

EBTNodeResult::Type UBTGrux_ATStampede::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	ControllingPawn = Cast<AGrux>(OwnerComp.GetAIOwner()->GetPawn());
	Animation = Cast<UGrux_Anim>(ControllingPawn->GetMesh()->GetAnimInstance());

	Cast<AGrux_Controller>(OwnerComp.GetAIOwner())->EndPatten(); // 패턴 종료
	OwnerComp.GetAIOwner()->GetCharacter()->GetCharacterMovement()->MaxAcceleration = 2048.0f;
	OwnerComp.GetAIOwner()->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}
