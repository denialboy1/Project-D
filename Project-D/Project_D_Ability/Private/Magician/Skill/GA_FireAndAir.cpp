// Team Project D has all rights this game


#include "Magician/Skill/GA_FireAndAir.h"
#include "Magician/MagicianCharacter.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

UGA_FireAndAir::UGA_FireAndAir() {
	static ConstructorHelpers::FObjectFinder<UBlueprint> SkillObject(TEXT("Blueprint'/Game/Characters/Player/Magician/Ability/Element2_Skill/FireStorm.FireStorm'"));
	if (SkillObject.Succeeded()) {
		Skill = Cast<UClass>(SkillObject.Object->GeneratedClass);
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndAir Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndAir Load Fail"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}

void UGA_FireAndAir::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (Skill != NULL) {
		AMagicianCharacter* Character = Cast<AMagicianCharacter>(GetOwningActorFromActorInfo());

		FVector Location = Character->GetMesh()->GetSocketLocation("Magic");
		Location.Z += 120.0f;

		FRotator Rotator = Character->GetBaseAimRotation();
		Rotator.Pitch = 0.0f;

		FVector Scale = FVector(1.5f, 1.5f, 8.2f);

		FTransform Transform;
		Transform.SetLocation(Location);
		Transform.SetRotation(Rotator.Quaternion());
		Transform.SetScale3D(Scale);

		GetWorld()->SpawnActor<AActor>(Skill, Transform, FActorSpawnParameters());
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndAir Skill Use Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_FireAndAir Skill Use Fail"))
	}
}