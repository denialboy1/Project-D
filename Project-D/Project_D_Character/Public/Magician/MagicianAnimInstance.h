// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerAnimInstance.h"
#include "MagicianAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_CHARACTER_API UMagicianAnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MagicianAnim, meta = (AllowPrivateAccess = "true"))
	float YawDelta;
};
