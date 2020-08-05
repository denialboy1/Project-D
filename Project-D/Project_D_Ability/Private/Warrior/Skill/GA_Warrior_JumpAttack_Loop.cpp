// Team Project D has all rights this game


#include "Warrior/Skill/GA_Warrior_JumpAttack_Loop.h"

UGA_Warrior_JumpAttack_Loop::UGA_Warrior_JumpAttack_Loop() {
	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Warrior/Animation/AM_Warrior_JA_Loop_Montage.AM_Warrior_JA_Loop_Montage'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("UGA_Warrior_JumpAttack_Loop Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("UGA_Warrior_JumpAttack_Loop Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}