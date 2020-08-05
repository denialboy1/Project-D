// Team Project D has all rights this game

#include "Player/PlayerAnimInstance.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

void UPlayerAnimInstance::NativeBeginPlay() {
	Super::NativeBeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
}
void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {

	Super::NativeUpdateAnimation(DeltaSeconds);
	
	Time = DeltaSeconds;
	
	if (PlayerCharacter == NULL) {
		return;
	}
	UpdateSpeed();
	UpdateAccelerate();
	UpdateJump();
	UpdateFullBody();
	UpdateFaceDirection();
	//UpdateCameraLimit();
}

void UPlayerAnimInstance::UpdateSpeed()
{
	Speed = PlayerCharacter->GetVelocity().Size();
}


void UPlayerAnimInstance::UpdateAccelerate() {
	FVector vector = PlayerCharacter->GetCharacterMovement()->GetCurrentAcceleration();
	
	if (vector.Size() > 0.0f) {
		bIsAccelerator = true;
	}
	else {
		bIsAccelerator = false;
	}

}

void UPlayerAnimInstance::UpdateJump() {
	bIsAir = PlayerCharacter->GetCharacterMovement()->IsFalling();
}

void UPlayerAnimInstance::UpdateFullBody() {
	if (GetCurveValue(FName("FullBody")) > 0.0f) {
		bIsFullBody = true;
	}
	else {
		bIsFullBody = false;
	}
}

void UPlayerAnimInstance::UpdateFaceDirection() {
	Pitch = PlayerCharacter->GetBaseAimRotation().Pitch;

	if (PlayerCharacter->GetCurMoveRight() == 0 && PlayerCharacter->GetCurMoveForward() < 0) {
		Yaw = 0;
	}
	else {
		FRotator Rotator = PlayerCharacter->GetBaseAimRotation() - PlayerCharacter->GetActorRotation();
		Yaw = Rotator.Yaw;
	}
}

void UPlayerAnimInstance::UpdateCameraLimit() {
	FRotator Rotator = PlayerCharacter->GetControlRotation();
	Rotator.Yaw = FMath::ClampAngle(Rotator.Yaw, -30.0f, 40.0f);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetControlRotation(Rotator);
}