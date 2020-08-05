// Team Project D has all rights this game


#include "Assassin/Skill/GA_Assassin_ThrowDagger_Spawn.h"

#include "Assassin/AssassinCharacter.h"
#include "AbilitySystemComponent.h"

UGA_Assassin_ThrowDagger_Spawn::UGA_Assassin_ThrowDagger_Spawn() {
	//드래곤 대거 블루프린트 초기화
	static ConstructorHelpers::FObjectFinder<UBlueprint> DaggerBlueprint(TEXT("Blueprint'/Game/Characters/Player/Assassin/BluePrint/Dagger.Dagger'"));
	if (DaggerBlueprint.Succeeded()) {
		DaggerClass = DaggerBlueprint.Object->GeneratedClass;
		UE_LOG(LogTemp, Log, TEXT("DaggerBlueprint Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("DaggerBlueprint Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}


void UGA_Assassin_ThrowDagger_Spawn::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	AAssassinCharacter* AssassinCharacter = Cast<AAssassinCharacter>(ActorInfo->OwnerActor);
	if (AssassinCharacter) {
		FTransform Transform;
		Transform.SetLocation(AssassinCharacter->GetMesh()->GetSocketLocation(TEXT("DaggerPoint")));
		Transform.SetRotation(AssassinCharacter->GetBaseAimRotation().Quaternion());
		Transform.SetScale3D(FVector(1, 1, 1));
		AssassinCharacter->GetWorld()->SpawnActor<AActor>(DaggerClass, Transform, FActorSpawnParameters());
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}

