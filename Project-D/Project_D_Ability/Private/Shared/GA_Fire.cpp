// Team Project D has all rights this game


#include "GA_Fire.h"
#include "MagicianCharacter.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

UGA_Fire::UGA_Fire() {
	static ConstructorHelpers::FClassFinder<AActor> SkillObject(TEXT("Blueprint'/Game/Characters/Player/Magician/Ability/Element1_Skill/FireBall.FireBall_C'"));
	if (SkillObject.Succeeded()) {
		Skill = SkillObject.Class;
		ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
		InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
		bServerRespectsRemoteAbilityCancellation = true;
		NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
		NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

		UE_LOG(LogTemp, Log, TEXT("GA_Fire Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Fire Load Fail"))
	}
}

void UGA_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (Skill != NULL) {
		AMagicianCharacter* Character = Cast<AMagicianCharacter>(GetOwningActorFromActorInfo());
		FVector Location = Character->GetMesh()->GetSocketLocation("Magic");
		FRotator Rotator = Character->GetBaseAimRotation();
		FVector Scale = FVector(1.5, 1.5, 1.5);
		FTransform Transform;
		Transform.SetLocation(Location);
		Transform.SetRotation(Rotator.Quaternion());
		Transform.SetScale3D(Scale);

		GetWorld()->SpawnActor<AActor>(Skill->StaticClass(), Transform, FActorSpawnParameters());
		UE_LOG(LogTemp, Log, TEXT("GA_Fire Skill Use Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Fire Skill Use Fail"))
	}
}