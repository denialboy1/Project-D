// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionObject.generated.h"

UCLASS()
class PROJECT_D_API AInteractionObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionObject();

	UFUNCTION(Server, WithValidation, Reliable)
	void Interaction();

	UFUNCTION(Server, WithValidation, Reliable)
	void InteractionServer();

	UFUNCTION(NetMulticast, WithValidation, Reliable)
	void InteractionMulti();

	UFUNCTION(Server, WithValidation, Reliable)
	void Set();

	UFUNCTION(Server, WithValidation, Reliable)
	void SetServer();

	UFUNCTION(NetMulticast, WithValidation, Reliable)
	void SetMulti();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
