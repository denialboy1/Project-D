// Team Project D has all rights this game


#include "Assassin/Skill/GA_Assassin_DashAttack_End.h"

#include "Assassin/AssassinCharacter.h"
#include "AbilitySystemComponent.h"

UGA_Assassin_DashAttack_End::UGA_Assassin_DashAttack_End() {
	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Assassin/Animation/AM_Assassin_DashAttack_End.AM_Assassin_DashAttack_End'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("UGA_Assassin_DashAttack_End Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("UGA_Assassin_DashAttack_End Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}

