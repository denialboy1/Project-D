// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Ability/Monster_Character.h"
#include "Grux_Controller.h"
#include "Grux.generated.h"

UCLASS()
class PROJECT_D_API AGrux : public AMonster_Character
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGrux();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

private:

public:
	class AGrux_Controller* Grux_Controller;

	UPROPERTY(EditAnywhere, replicated)
	bool CKDoublePain;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,replicated)
	UBoxComponent* DoublePainCollsion = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, replicated)
	UBoxComponent* NomalAttackCollision = nullptr;
};
