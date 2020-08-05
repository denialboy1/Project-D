// Team Project D has all rights this game


#include "Magician/Skill/GA_Water.h"
#include "Magician/MagicianCharacter.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

UGA_Water::UGA_Water() {
	static ConstructorHelpers::FObjectFinder<UBlueprint> SkillObject(TEXT("Blueprint'/Game/Characters/Player/Magician/Ability/Element1_Skill/WaterBall.WaterBall'"));
	if (SkillObject.Succeeded()) {
		Skill = Cast<UClass>(SkillObject.Object->GeneratedClass);
		UE_LOG(LogTemp, Log, TEXT("GA_Water Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Water Load Fail"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}

void UGA_Water::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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

		GetWorld()->SpawnActor<AActor>(Skill, Transform, FActorSpawnParameters());
		UE_LOG(LogTemp, Log, TEXT("GA_Water Skill Use Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Water Skill Use Fail"))
	}
}