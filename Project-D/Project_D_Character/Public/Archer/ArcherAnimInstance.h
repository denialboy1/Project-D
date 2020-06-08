// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerAnimInstance.h"
#include "ArcherAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_CHARACTER_API UArcherAnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ArcherAnim, meta = (AllowPrivateAccess = "true"))
	bool bIsReloadPose;
};
