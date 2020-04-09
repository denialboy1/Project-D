// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Grux_Controller.h"
#include "Grux.h"
#include "Grux_Anim.h"
#include "BTGrux_ATStone.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_D_API UBTGrux_ATStone : public UBTTaskNode
{
	GENERATED_BODY()

	public:
	UBTGrux_ATStone();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	AGrux_Controller* Grux_Controller;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AGrux* ControllingPawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UGrux_Anim* Animation;

};
