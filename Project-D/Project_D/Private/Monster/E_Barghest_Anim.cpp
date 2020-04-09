// Fill out your copyright notice in the Description page of Project Settings.

#include "E_Barghest_Anim.h"
#include "E_Barghest.h"
#include "PD_AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

UE_Barghest_Anim::UE_Barghest_Anim()
{
	CurrentPawnSpeed = 0.0f;
	IsDead = false;
	IsInAir = false;
	IsTarget = false;
	TriggerBite = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AT_BITE_READY(TEXT("/Game/Characters/Monster/QuadrapedCreatures/Barghest/Animations/Montage/BARGHEST_BiteReady.BARGHEST_BiteReady"));
	if (AT_BITE_READY.Succeeded())
	{
		AT_Bite_Ready = AT_BITE_READY.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AT_BITE(TEXT("/Game/Characters/Monster/QuadrapedCreatures/Barghest/Animations/Montage/BARGHEST_Bite.BARGHEST_Bite"));
	if (AT_BITE.Succeeded())
	{
		AT_Bite = AT_BITE.Object;
	}
}

void UE_Barghest_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;

	auto Controller = Cast<APD_AIController>(Pawn->GetController());
	if (!::IsValid(Controller)) return;

	IsDead = Controller->isDead;

	if (!IsDead)
	{
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}
