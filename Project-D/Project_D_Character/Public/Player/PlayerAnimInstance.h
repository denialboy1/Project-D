// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_CHARACTER_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerAnim, meta = (AllowPrivateAccess = "true"))
	class APlayerCharacter* PlayerCharacter;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerAnim, meta = (AllowPrivateAccess = "true"))
	bool bIsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerAnim, meta = (AllowPrivateAccess = "true"))
	bool bIsAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerAnim, meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerator;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerAnim, meta = (AllowPrivateAccess = "true"))
	bool bIsFullBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerAnim, meta = (AllowPrivateAccess = "true"))
	bool bIsDash;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerAnim, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerAnim, meta = (AllowPrivateAccess = "true"))
	float Roll;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerAnim, meta = (AllowPrivateAccess = "true"))
	float Pitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerAnim, meta = (AllowPrivateAccess = "true"))
	float Yaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerAnim, meta = (AllowPrivateAccess = "true"))
	float Time;

private:
	virtual void UpdateSpeed();

	virtual void UpdateAccelerate();

	virtual void UpdateJump();

	virtual void UpdateFullBody();

	virtual void UpdateFaceDirection();

	virtual void UpdateCameraLimit();
};
