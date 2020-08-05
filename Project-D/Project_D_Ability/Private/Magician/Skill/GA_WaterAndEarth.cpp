// Team Project D has all rights this game


#include "Magician/Skill/GA_WaterAndEarth.h"
#include "Magician/MagicianCharacter.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

UGA_WaterAndEarth::UGA_WaterAndEarth() {
	static ConstructorHelpers::FObjectFinder<UBlueprint> SkillObject(TEXT("Blueprint'/Game/Characters/Player/Magician/Ability/Element2_Skill/IceWall.IceWall'"));
	if (SkillObject.Succeeded()) {
		Skill = Cast<UClass>(SkillObject.Object->GeneratedClass);
		UE_LOG(LogTemp, Log, TEXT("GA_WaterAndEarth Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_WaterAndEarth Load Fail"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}

void UGA_WaterAndEarth::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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

		GetWorld()->SpawnActor<AActor>(Skill, Transform, FActorSpawnParameters());
		UE_LOG(LogTemp, Log, TEXT("GA_WaterAndEarth Skill Use Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_WaterAndEarth Skill Use Fail"))
	}
}