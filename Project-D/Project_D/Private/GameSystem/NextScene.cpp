// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSystem/NextScene.h"

// Sets default values
ANextScene::ANextScene()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	Trigger->SetBoxExtent(FVector(200.0f, 200.0f, 20.0f));
	Trigger->SetCollisionProfileName(TEXT("NextScene"));
	RootComponent = Trigger;
}

// Called when the game starts or when spawned
void ANextScene::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANextScene::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANextScene::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFroomSweep, const FHitResult& SweepResult)
{
	
}
