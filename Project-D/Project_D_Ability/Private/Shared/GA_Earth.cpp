// Team Project D has all rights this game


#include "GA_Earth.h"
#include "MagicianCharacter.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

UGA_Earth::UGA_Earth() {
	static ConstructorHelpers::FClassFinder<AActor> SkillObject(TEXT("Blueprint'/Game/Characters/Player/Magician/Ability/Element1_Skill/Rock.Rock_C'"));
	if (SkillObject.Succeeded()) {
		Skill = SkillObject.Class;
		ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
		InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
		bServerRespectsRemoteAbilityCancellation = true;
		NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
		NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

		UE_LOG(LogTemp, Log, TEXT("GA_Earth Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Earth Load Fail"))
	}
}

void UGA_Earth::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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
		UE_LOG(LogTemp, Log, TEXT("GA_Earth Skill Use Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Earth Skill Use Fail"))
	}
}