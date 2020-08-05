// Team Project D has all rights this game


#include "Assassin/Skill/GA_Assassin_DashAttack_BigDaggerThrow_End.h"
#include "Assassin/AssassinCharacter.h"
#include "AbilitySystemComponent.h"

UGA_Assassin_DashAttack_BigDaggerThrow_End::UGA_Assassin_DashAttack_BigDaggerThrow_End() {
	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UBlueprint> BigDaggerBlueprint(TEXT("Blueprint'/Game/Characters/Player/Assassin/BluePrint/BigDagger.BigDagger'"));
	if (BigDaggerBlueprint.Succeeded()) {
		DaggerClass = BigDaggerBlueprint.Object->GeneratedClass;
		UE_LOG(LogTemp, Log, TEXT("BigDaggerBlueprint Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("BigDaggerBlueprint Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}


void UGA_Assassin_DashAttack_BigDaggerThrow_End::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	AAssassinCharacter* AssassinCharacter = Cast<AAssassinCharacter>(ActorInfo->OwnerActor);
	if (AssassinCharacter) {
		AssassinCharacter->Launch();

		FTransform Transform;
		FVector Location = AssassinCharacter->GetActorLocation();
		Location.Z -= 90;
		Transform.SetLocation(Location);
		Transform.SetRotation(AssassinCharacter->GetBaseAimRotation().Quaternion());
		Transform.SetScale3D(FVector(2, 2, 2));
		AssassinCharacter->GetWorld()->SpawnActor<AActor>(DaggerClass, Transform, FActorSpawnParameters());

	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}


