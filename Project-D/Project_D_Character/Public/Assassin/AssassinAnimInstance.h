// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerAnimInstance.h"
#include "AssassinAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_CHARACTER_API UAssassinAnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanDoubleJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsNeckSlice;
};
