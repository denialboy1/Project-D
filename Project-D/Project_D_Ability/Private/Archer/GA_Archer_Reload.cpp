// Team Project D has all rights this game

#include "Archer/GA_Archer_Reload.h"
#include "UObject/ConstructorHelpers.h"
#include "GameplayTagContainer.h"

UGA_Archer_Reload::UGA_Archer_Reload() {
	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Archer/Animation/AM_Archer_Reload.AM_Archer_Reload'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp,Log,TEXT("Archer Reload Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Archer Reload Anim Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}