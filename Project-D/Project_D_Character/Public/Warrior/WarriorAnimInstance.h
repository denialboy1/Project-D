// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WarriorAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_CHARACTER_API UWarriorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsJumpAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInAir;
};
