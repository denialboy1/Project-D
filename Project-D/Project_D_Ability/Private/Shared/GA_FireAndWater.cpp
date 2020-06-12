// Team Project D has all rights this game


#include "GA_FireAndWater.h"
#include "MagicianCharacter.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

UGA_FireAndWater::UGA_FireAndWater() {
	static ConstructorHelpers::FClassFinder<AActor> SkillObject(TEXT("Blueprint'/Game/Characters/Player/Magician/Ability/Element2_Skill/Cloud.Cloud_C'"));
	if (SkillObject.Succeeded()) {
		Skill = SkillObject.Class;
		ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
		InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
		bServerRespectsRemoteAbilityCancellation = true;
		NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
		NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

		UE_LOG(LogTemp, Log, TEXT("GA_FireAndWater Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndWater Load Fail"))
	}
}

void UGA_FireAndWater::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (Skill != NULL) {
		AMagicianCharacter* Character = Cast<AMagicianCharacter>(GetOwningActorFromActorInfo());
		FVector Location = Character->GetMesh()->GetSocketLocation("Magic");
		FRotator Rotator = Character->GetBaseAimRotation();
		FVector Scale = FVector(1.0f, 1.0f, 1.0f);
		FTransform Transform;
		Transform.SetLocation(Location);
		Transform.SetRotation(Rotator.Quaternion());
		Transform.SetScale3D(Scale);

		GetWorld()->SpawnActor<AActor>(Skill->StaticClass(), Transform, FActorSpawnParameters());
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndWater Skill Use Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndWater Skill Use Fail"))
	}
}