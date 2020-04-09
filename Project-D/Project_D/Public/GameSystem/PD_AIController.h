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
	// 블랙보드에 사용할 키 선언
	static const FName SelfActorKey;
	static const FName HomePosKey;
	static const FName TargetKey;
	static const FName DistanceToTargetKey;
	static const FName PattenKey;
	static const FName TargetPosKey;
	static const FName DeadKey;

	APD_AIController();

	// 블랙보드, 비헤이비어트리 설정 및 실행
	UFUNCTION(BlueprintCallable)
	void RunAI();

	void Dead();

	// 그럭스의 패턴 설정시 행동을 막는 함수들
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

	// 우리가 사용할 플레이어 스테이트를 GameState로부터 받아옴
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APlayerState*> PlayerArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurPlayerNum;

	// BT에서 사용할 AgroGage를 PlayerState로 부터 받아옴
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> AgroGage;

	// 현재 플레이어들의 거리를 받아옴
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> DistanceTo;

	// 패턴 실행상태를 체크할 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanAct;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayer_Character* Target;
};
