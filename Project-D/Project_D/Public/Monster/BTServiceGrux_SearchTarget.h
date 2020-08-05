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

	// 정한 타겟에게 회전
	void TurnToTarget();


public:
	// 타겟으로 삼을 플레이어 인덱스 넘버
	int TargetNum;

	// 패턴을 정할 랜덤값
	int PattenNum;

	// 현재 게임 중인 플레이어 수
	int CurPlayerNum;

private:
	AGrux_Controller* Grux_Controller;

	ACharacter* TargetPlayer;

	APawn* ControllingPawn;
};
