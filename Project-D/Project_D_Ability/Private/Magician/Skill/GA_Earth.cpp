// Team Project D has all rights this game


#include "Magician/Skill/GA_Earth.h"
#include "Magician/MagicianCharacter.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

UGA_Earth::UGA_Earth() {
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> SkillObject(TEXT("Blueprint'/Game/Characters/Player/Magician/Ability/Element1_Skill/Rock.Rock'"));
	if (SkillObject.Succeeded()) {
		Skill = Cast<UClass>(SkillObject.Object->GeneratedClass);
		UE_LOG(LogTemp, Log, TEXT("GA_Earth Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Earth Load Fail"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
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

		GetWorld()->SpawnActor<AActor>(Skill, Transform, FActorSpawnParameters());
		UE_LOG(LogTemp, Log, TEXT("GA_Earth Skill Use Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Earth Skill Use Fail"))
	}
}