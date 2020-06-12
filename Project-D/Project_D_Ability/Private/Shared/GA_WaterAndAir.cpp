// Team Project D has all rights this game


#include "GA_WaterAndAir.h"
#include "MagicianCharacter.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

UGA_WaterAndAir::UGA_WaterAndAir() {
	static ConstructorHelpers::FClassFinder<AActor> SkillObject(TEXT("Blueprint'/Game/Characters/Player/Magician/Ability/Element2_Skill/WaterPrision.WaterPrision_C'"));
	if (SkillObject.Succeeded()) {
		Skill = SkillObject.Class;
		ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
		InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
		bServerRespectsRemoteAbilityCancellation = true;
		NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
		NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

		UE_LOG(LogTemp, Log, TEXT("GA_WaterAndAir Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_WaterAndAir Load Fail"))
	}
}

void UGA_WaterAndAir::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (Skill != NULL) {
		AMagicianCharacter* Character = Cast<AMagicianCharacter>(GetOwningActorFromActorInfo());
		FVector Location = Character->GetMesh()->GetSocketLocation("Magic");
		FRotator Rotator = Character->GetBaseAimRotation();
		Rotator.Pitch = 0;
		FVector Scale = FVector(1.0, 1.0, 1.0);
		FTransform Transform;
		Transform.SetLocation(Location);
		Transform.SetRotation(Rotator.Quaternion());
		Transform.SetScale3D(Scale);

		GetWorld()->SpawnActor<AActor>(Skill->StaticClass(), Transform, FActorSpawnParameters());
		UE_LOG(LogTemp, Log, TEXT("GA_WaterAndAir Skill Use Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_WaterAndAir Skill Use Fail"))
	}
}