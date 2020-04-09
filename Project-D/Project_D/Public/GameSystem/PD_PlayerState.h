// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PD_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_API APD_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
	APD_PlayerState();

public:
	// 서버로 복사하기위한 함수
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override; 

public:
	// 어그로 수치 반환
	int32 GetAgro();

	// 플레이어 자체가 가지고 있는 어그로 수치
	UPROPERTY(EditAnywhere, replicated)
	int32 AgroGage;
};
