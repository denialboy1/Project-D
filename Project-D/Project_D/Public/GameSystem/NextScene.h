// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_D.h"
#include "GameFramework/Actor.h"
#include "NextScene.generated.h"

UCLASS()
class PROJECT_D_API ANextScene : public AActor
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	ANextScene();

public:
	UPROPERTY(VisibleAnywhere, Category = System)
	UBoxComponent* Trigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

};
