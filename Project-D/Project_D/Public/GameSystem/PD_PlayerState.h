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
	// ������ �����ϱ����� �Լ�
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override; 

public:
	// ��׷� ��ġ ��ȯ
	int32 GetAgro();

	// �÷��̾� ��ü�� ������ �ִ� ��׷� ��ġ
	UPROPERTY(EditAnywhere, replicated)
	int32 AgroGage;
};
