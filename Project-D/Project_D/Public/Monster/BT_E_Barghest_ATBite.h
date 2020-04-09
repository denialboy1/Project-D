// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "E_Barghest_Controller.h"
#include "E_Barghest.h"
#include "E_Barghest_Anim.h"
#include "BT_E_Barghest_ATBite.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_API UBT_E_Barghest_ATBite : public UBTTaskNode
{
	GENERATED_BODY()
	
public :
	UBT_E_Barghest_ATBite();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	AE_Barghest* Pawn;
	
	UE_Barghest_Anim* Anim;

	AE_Barghest_Controller* Controller;
};
