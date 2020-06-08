// Team Project D has all rights this game

#include "InteractionObject.h"

// Sets default values
AInteractionObject::AInteractionObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractionObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractionObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AInteractionObject::Interaction_Validate()
{
	return true;
}

void AInteractionObject::Interaction_Implementation()
{
	if (HasAuthority()) {
		InteractionMulti_Implementation();
	}
	else {
		InteractionServer_Implementation();
	}
}


bool AInteractionObject::InteractionServer_Validate()
{
	return true;
}

void AInteractionObject::InteractionServer_Implementation()
{
	InteractionMulti_Implementation();
}

bool AInteractionObject::InteractionMulti_Validate()
{
	return true;
}

void AInteractionObject::InteractionMulti_Implementation()
{

}

bool AInteractionObject::Set_Validate()
{
	return true;
}

void AInteractionObject::Set_Implementation()
{
	if (HasAuthority()) {
		SetMulti_Implementation();
	}
	else {
		SetServer_Implementation();
	}
}

bool AInteractionObject::SetServer_Validate()
{
	return true;
}

void AInteractionObject::SetServer_Implementation()
{
	SetMulti_Implementation();
}

bool AInteractionObject::SetMulti_Validate()
{
	return true;
}

void AInteractionObject::SetMulti_Implementation()
{

}