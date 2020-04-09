// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Grux_Controller.h"
#include "BTServiceGrux_SearchTarget.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_D_API UBTServiceGrux_SearchTarget : public UBTService
{
	GENERATED_BODY()

	public:
	UBTServiceGrux_SearchTarget();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)	override;

	// ���� Ÿ�ٿ��� ȸ��
	void TurnToTarget();


public:
	// Ÿ������ ���� �÷��̾� �ε��� �ѹ�
	int TargetNum;

	// ������ ���� ������
	int PattenNum;

	// ���� ���� ���� �÷��̾� ��
	int CurPlayerNum;

private:
	AGrux_Controller* Grux_Controller;

	ACharacter* TargetPlayer;

	APawn* ControllingPawn;
};
