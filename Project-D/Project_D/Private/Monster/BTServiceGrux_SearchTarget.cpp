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

	// �������� ���� ����
	if (Grux_Controller != nullptr)
	{
		if (Grux_Controller->CanAct) // AI�� �ൿ ������ �� / ������ ������ ��
		{
			PattenNum = FMath::RandRange(1, 3);
			Grux_Controller->StartPatten(); // �ٸ� ���� ���� ���ϰ� ����
			UE_LOG(LogTemp, Warning, TEXT("Patten : %d"), PattenNum);

			switch (PattenNum)
			{
			case 1: // DoublePain : ��׷� ��ġ�� ���� ���� ������ ���� ����
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

			case 2: // StoneThrow : ��׷� ��ġ�� ���� ���� ������ �� ������
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
			TargetPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), TargetNum); // Ÿ���ε����� �÷��̾ ������
			if (TargetPlayer != nullptr)
			{
				//TurnToTarget(); // ��󿡰� ȸ��
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AGrux_Controller::TargetKey, TargetPlayer); // BB Ÿ�� ����

			}
		}
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AGrux_Controller::DistanceToTargetKey, Grux_Controller->DistanceTo[TargetNum]); // Ÿ�ٰ��� �Ÿ�
		//OwnerComp.GetBlackboardComponent()->SetValueAsVector(AGrux_Controller::TargetPosKey, TargetPlayer->GetActorLocation()); // Ÿ���� ��ġ
	}
}

void UBTServiceGrux_SearchTarget::TurnToTarget()
{
	FVector LookVector = TargetPlayer->GetActorLocation() - ControllingPawn->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	//ControllingPawn->SetActorRotation(FMath::RInterpTo(ControllingPawn->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f)); �̰� �ȵ� �̤�
	ControllingPawn->SetActorRotation(TargetRot);
}