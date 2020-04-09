// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Ability/Monster_Character.h"
#include "E_Barghest.generated.h"

UCLASS()
class PROJECT_D_API AE_Barghest : public AMonster_Character
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AE_Barghest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, replicated)
	float CurrentSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, replicated)
	bool TriggerBite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, replicated)
	UBoxComponent* NomalAttackCollision = nullptr;
};
