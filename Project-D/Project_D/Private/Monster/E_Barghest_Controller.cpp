// Fill out your copyright notice in the Description page of Project Settings.

#include "E_Barghest_Controller.h"
#include "E_Barghest.h"
#include "E_Barghest_Anim.h"
#include "Kismet/GameplayStatics.h"

AE_Barghest_Controller::AE_Barghest_Controller()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Characters/Monster/QuadrapedCreatures/Barghest/BT_E_Barghest.BT_E_Barghest"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	index = 0;
}

void AE_Barghest_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	index = 0;
	for (int i = 0; i < CurPlayerNum - 1; i++)
	{
		if (DistanceTo[i] > DistanceTo[i + 1])
		{
			index = i + 1;
		}
	}
	Target = Cast<APlayer_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), index));
	
	GetBlackboardComponent()->SetValueAsObject(AE_Barghest_Controller::TargetKey, Target);
	GetBlackboardComponent()->SetValueAsFloat(AE_Barghest_Controller::DistanceToTargetKey, DistanceTo[index]);
}


