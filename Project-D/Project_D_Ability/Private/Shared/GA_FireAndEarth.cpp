// Team Project D has all rights this game


#include "GA_FireAndEarth.h"
#include "MagicianCharacter.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

UGA_FireAndEarth::UGA_FireAndEarth() {
	static ConstructorHelpers::FClassFinder<AActor> SkillObject(TEXT("Blueprint'/Game/Characters/Player/Magician/Ability/Element2_Skill/FireStone.FireStone_C'"));
	if (SkillObject.Succeeded()) {
		Skill = SkillObject.Class;
		ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
		InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
		bServerRespectsRemoteAbilityCancellation = true;
		NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
		NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

		UE_LOG(LogTemp, Log, TEXT("GA_FireAndEarth Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndEarth Load Fail"))
	}
}

void UGA_FireAndEarth::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (Skill != NULL) {
		AMagicianCharacter* Character = Cast<AMagicianCharacter>(GetOwningActorFromActorInfo());
		FVector Location = Character->GetMesh()->GetSocketLocation("Magic");
		FRotator Rotator = Character->GetBaseAimRotation();
		FVector Scale = FVector(0.7f, 0.7f, 0.7f);
		FTransform Transform;
		Transform.SetLocation(Location);
		Transform.SetRotation(Rotator.Quaternion());
		Transform.SetScale3D(Scale);

		GetWorld()->SpawnActor<AActor>(Skill->StaticClass(), Transform, FActorSpawnParameters());
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndEarth Skill Use Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndEarth Skill Use Fail"))
	}
}