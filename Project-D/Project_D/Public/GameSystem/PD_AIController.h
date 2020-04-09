// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Classes/GameFramework/GameState.h"
#include "PD_GameStateBase.h"
#include "Classes/GameFramework/PlayerState.h"
#include "Project_DCharacter.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ConstructorHelpers.h"
#include "Ability/Player_Character.h"
#include "PD_AIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_API APD_AIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void Tick(float DeltaTime) override;

public:
	// �����忡 ����� Ű ����
	static const FName SelfActorKey;
	static const FName HomePosKey;
	static const FName TargetKey;
	static const FName DistanceToTargetKey;
	static const FName PattenKey;
	static const FName TargetPosKey;
	static const FName DeadKey;

	APD_AIController();

	// ������, �����̺��Ʈ�� ���� �� ����
	UFUNCTION(BlueprintCallable)
	void RunAI();

	void Dead();

	// �׷����� ���� ������ �ൿ�� ���� �Լ���
	UFUNCTION(BlueprintCallable)
	void StartPatten();

	UFUNCTION(BlueprintCallable)
	void EndPatten();

	//UFUNCTION(NetMulticast, Reliable)
	//void MultiPlayDoublePain();

	//UFUNCTION(Server, Reliable, WithValidation)
	//void ServerPlayDoublePain();

private:

	UPROPERTY(Visibleanywhere)
	class UBlackboardData* BBAsset;

public:
	UPROPERTY(Visibleanywhere)
	class UBehaviorTree* BTAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGameStateBase* GameState;

	// �츮�� ����� �÷��̾� ������Ʈ�� GameState�κ��� �޾ƿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APlayerState*> PlayerArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurPlayerNum;

	// BT���� ����� AgroGage�� PlayerState�� ���� �޾ƿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> AgroGage;

	// ���� �÷��̾���� �Ÿ��� �޾ƿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> DistanceTo;

	// ���� ������¸� üũ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanAct;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayer_Character* Target;
};
