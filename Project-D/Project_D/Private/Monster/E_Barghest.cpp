// Fill out your copyright notice in the Description page of Project Settings.

#include "E_Barghest.h"
#include "E_Barghest_Anim.h"
#include "E_BArghest_Controller.h"
#include "ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"

// Sets default values
AE_Barghest::AE_Barghest()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBite = false;

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UE_Barghest_Anim> ANIMATION(TEXT("/Game/Characters/Monster/QuadrapedCreatures/Barghest/Animations/BP_E_Barghest_Anim.BP_E_Barghest_Anim_C"));
	if (ANIMATION.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIMATION.Class);
		UE_LOG(LogTemp, Warning, TEXT("set success"));
	}

	static ConstructorHelpers::FClassFinder<AE_Barghest_Controller> CONTROLLER(TEXT("/Game/Characters/Monster/QuadrapedCreatures/Barghest/Blueprint/BP_E_Barghest_Controller.BP_E_Barghest_Controller_C"));
	if (CONTROLLER.Succeeded())
	{
		AIControllerClass = CONTROLLER.Class;
	}
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	NomalAttackCollision = CreateDefaultSubobject<UBoxComponent>(FName("CollisionMesh"));
	NomalAttackCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AE_Barghest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AE_Barghest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentSpeed = GetVelocity().Size();
}

// Called to bind functionality to input
void AE_Barghest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AE_Barghest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AE_Barghest, CurrentSpeed);
	DOREPLIFETIME(AE_Barghest, TriggerBite);
}