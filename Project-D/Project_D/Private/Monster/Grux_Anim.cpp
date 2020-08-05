// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/Grux_Anim.h"
#include "GameFramework/Character.h"
#include "Monster/Grux.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

UGrux_Anim::UGrux_Anim()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	isDead = false;
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AT_DOUBLEPAIN(TEXT("/Game/Characters/Monster/Grux/Animation/Mongtage/DoublePain_Montage.DoublePain_Montage"));
	if (AT_DOUBLEPAIN.Succeeded())
	{
		AT_DoublePain = AT_DOUBLEPAIN.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AT_STONEIMPACT(TEXT("/Game/Characters/Monster/Grux/Animation/Mongtage/PD_Grux_Stone.PD_Grux_Stone"));
	if (AT_STONEIMPACT.Succeeded())
	{
		AT_Stone = AT_STONEIMPACT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AT_STAMPEDE(TEXT("/Game/Characters/Monster/Grux/Animation/Mongtage/Stampede_Knockup.Stampede_Knockup"));
	if (AT_STAMPEDE.Succeeded())
	{
		AT_Stampede = AT_STAMPEDE.Object;
	}
}
void UGrux_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;

	auto Controller = Cast<APD_AIController>(Pawn->GetController());
	if (!::IsValid(Controller)) return;

	isDead = Controller->isDead;

	if (!isDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}

void UGrux_Anim::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UGrux_Anim, CurrentPawnSpeed);
}

void UGrux_Anim::PlayAT_DoublePain()
{
	if (!isDead)
	{
		if (!IsAnyMontagePlaying())
		{
			Montage_Play(AT_DoublePain, 1.0f);
		}
	}
}

void UGrux_Anim::PlayAT_Stone()
{
	if (!isDead)
	{
		if (!IsAnyMontagePlaying())
		{
			Montage_Play(AT_Stone, 1.0f);
		}
	}
}

void UGrux_Anim::PlayAT_Stampede()
{
	if (!isDead)
	{
		if (!IsAnyMontagePlaying())
		{
			Montage_Play(AT_Stampede, 1.0f);
		}
	}
}