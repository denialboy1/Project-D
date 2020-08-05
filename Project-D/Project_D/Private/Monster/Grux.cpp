// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/Grux.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Monster/Grux_Anim.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AGrux::AGrux()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CKDoublePain = true;

	// ½ºÄÌ·¹Å» ¸Þ½Ã ¼³Á¤
	static const ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_GRUX(TEXT("/Game/Characters/Monster/ParagonGrux/Characters/Heroes/Grux/Meshes/Grux.Grux"));
	if (SM_GRUX.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_GRUX.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));

	// ¾Ö´ÔÀÎ½ºÅÏ½º ¼³Á¤
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> GRUX_ANIM(TEXT("/Game/Characters/Monster/Grux/Animation/BP_GruxAnim.BP_GruxAnim_C"));
	if (GRUX_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(GRUX_ANIM.Class);
	}
	
	GetMesh()->SetIsReplicated(true);
	// Ãæµ¹ Ã¼Å© Ä¸½¶ ¼³Á¤
	GetCapsuleComponent()->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));

	// AIController ¼³Á¤
	static ConstructorHelpers::FClassFinder<AGrux_Controller> GRUX_AICONTROLLER(TEXT("/Game/Characters/Monster/Grux/BP_Grux_Controller.BP_Grux_Controller_C"));
	if (GRUX_AICONTROLLER.Succeeded())
	{
		AIControllerClass = GRUX_AICONTROLLER.Class;
	}
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	DoublePainCollsion = CreateDefaultSubobject<UBoxComponent>(FName("CollisionMesh"));
	DoublePainCollsion->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	NomalAttackCollision = CreateDefaultSubobject<UBoxComponent>(FName("NormalAttack"));
	NomalAttackCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AGrux::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGrux::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CKDoublePain)
	{
		Cast<UGrux_Anim>(GetMesh()->GetAnimInstance())->PlayAT_DoublePain();
		CKDoublePain = true;
	}
}

// Called to bind functionality to input
void AGrux::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGrux::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGrux, CKDoublePain);
}