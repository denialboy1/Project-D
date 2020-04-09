// Fill out your copyright notice in the Description page of Project Settings.

#include "BTServiceGrux_SearchTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/Tasks/AITask.h"
#include "Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UBTServiceGrux_SearchTarget::UBTServiceGrux_SearchTarget()
{
	NodeName = TEXT("Search");
	Interval = 1.0f;
	TargetNum = 0;
}

void UBTServiceGrux_SearchTarget::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	Grux_Controller = Cast<AGrux_Controller>(OwnerComp.GetAIOwner());
	ControllingPawn = Cast<APawn>(Grux_Controller->GetPawn());
	CurPlayerNum = Grux_Controller->CurPlayerNum;

	// 랜덤으로 패턴 결정
	if (Grux_Controller != nullptr)
	{
		if (Grux_Controller->CanAct) // AI가 행동 가능할 때 / 패턴이 끝났을 때
		{
			PattenNum = FMath::RandRange(1, 3);
			Grux_Controller->StartPatten(); // 다른 패턴 실행 못하게 제한
			UE_LOG(LogTemp, Warning, TEXT("Patten : %d"), PattenNum);

			switch (PattenNum)
			{
			case 1: // DoublePain : 어그로 수치가 제일 높은 적에게 강한 공격
				UE_LOG(LogTemp, Warning, TEXT("DoublePain"));
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(AGrux_Controller::PattenKey, 1);

				TargetNum = 0;
				for (int i = 0; i < CurPlayerNum - 1; i++)
				{
					if (Grux_Controller->AgroGage[i] < Grux_Controller->AgroGage[i + 1])
					{
						TargetNum = i + 1;
					}
				}
				break;

			case 2: // StoneThrow : 어그로 수치가 가장 적은 적에게 돌 던지기
				UE_LOG(LogTemp, Warning, TEXT("Patten2"));
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(AGrux_Controller::PattenKey, 2);

				TargetNum = 0;
				for (int i = 0; i < CurPlayerNum - 1; i++)
				{
					if (Grux_Controller->AgroGage[i] > Grux_Controller->AgroGage[i + 1])
					{
						TargetNum = i + 1;
					}
				}
				break;
			case 3:
				UE_LOG(LogTemp, Warning, TEXT("Patten3"));
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(AGrux_Controller::PattenKey, 3);

				TargetNum = 0;
				for (int i = 0; i < CurPlayerNum - 1; i++)
				{
					if (Grux_Controller->DistanceTo[i] < Grux_Controller->DistanceTo[i + 1])
					{
						TargetNum = i + 1;
					}
				}

				Grux_Controller->GetCharacter()->GetCharacterMovement()->MaxAcceleration = 900000;
				Grux_Controller->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 1500;
				break;
			}

			UE_LOG(LogTemp, Warning, TEXT("Target : %d"), TargetNum);
			TargetPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), TargetNum); // 타겟인덱스의 플레이어를 가져옴
			if (TargetPlayer != nullptr)
			{
				//TurnToTarget(); // 대상에게 회전
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AGrux_Controller::TargetKey, TargetPlayer); // BB 타겟 설정

			}
		}
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AGrux_Controller::DistanceToTargetKey, Grux_Controller->DistanceTo[TargetNum]); // 타겟과의 거리
		//OwnerComp.GetBlackboardComponent()->SetValueAsVector(AGrux_Controller::TargetPosKey, TargetPlayer->GetActorLocation()); // 타겟의 위치
	}
}

void UBTServiceGrux_SearchTarget::TurnToTarget()
{
	FVector LookVector = TargetPlayer->GetActorLocation() - ControllingPawn->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	//ControllingPawn->SetActorRotation(FMath::RInterpTo(ControllingPawn->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f)); 이거 안됨 ㅜㅜ
	ControllingPawn->SetActorRotation(TargetRot);
}