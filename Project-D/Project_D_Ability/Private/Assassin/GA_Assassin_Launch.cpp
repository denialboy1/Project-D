// Team Project D has all rights this game


#include "Assassin/GA_Assassin_Launch.h"
#include "Assassin/AssassinCharacter.h"
UGA_Assassin_Launch::UGA_Assassin_Launch() {
	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}


void UGA_Assassin_Launch::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	AAssassinCharacter* AssassinCharacter = Cast<AAssassinCharacter>(ActorInfo->OwnerActor);

	//평타 리셋 콤보
	if (AssassinCharacter) {
		AssassinCharacter->AttackCount = 0;
		AssassinCharacter->bSaveAttack = false;
		AssassinCharacter->bIsAttacking = false;
	}

	//긴급 도약
	if (AssassinCharacter) {
		FRotator Rotator = AssassinCharacter->GetControlRotation();
		Rotator.Roll = 0.f;
		Rotator.Pitch = 0.f;
		FVector Forward = FRotationMatrix(Rotator).GetScaledAxis(EAxis::X) * AssassinCharacter->GetCurMoveForward() * 300.0f;
		FVector Right = FRotationMatrix(Rotator).GetScaledAxis(EAxis::X) * AssassinCharacter->GetCurMoveRight() * 300.0f;
		FVector Up = FVector(0, 0, 400.f);
		AssassinCharacter->LaunchCharacter(Forward + Right + Up, true, true);
	}

	//EndAbility(Handle, ActorInfo,)
}
