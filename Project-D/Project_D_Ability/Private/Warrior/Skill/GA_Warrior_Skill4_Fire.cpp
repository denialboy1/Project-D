// Team Project D has all rights this game

#include "Warrior/Skill/GA_Warrior_Skill4_Fire.h"
#include "Warrior/WarriorCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

UGA_Warrior_Skill4_Fire::UGA_Warrior_Skill4_Fire() {
	
	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

	//이펙트 초기화
	static ConstructorHelpers::FObjectFinder<UParticleSystem> GreyStonHit_ParticleSystem(TEXT("ParticleSystem'/Game/Characters/Player/Warrior/ParagonGreystone/FX/Particles/Greystone/Abilities/Ultimate/FX/P_Greystone_HToKill_Impact_Local.P_Greystone_HToKill_Impact_Local'"));
	if (GreyStonHit_ParticleSystem.Succeeded()) {
		ParticleSystem = GreyStonHit_ParticleSystem.Object;
		
		UE_LOG(LogTemp, Log, TEXT("GreyStonHit_ParticleSystem Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GreyStonHit_ParticleSystem Fail"));
	}

	//사운드
	static ConstructorHelpers::FObjectFinder<USoundWave> GreyStonHit_SoundWave(TEXT("SoundWave'/Game/Characters/Player/Warrior/Sound/Warrior_Dragon_Fire_Sound.Warrior_Dragon_Fire_Sound'"));
	if (GreyStonHit_SoundWave.Succeeded()) {
		SoundWave = GreyStonHit_SoundWave.Object;
		UE_LOG(LogTemp, Log, TEXT("GreyStonHit_SoundWave Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GreyStonHit_SoundWave Fail"));
	}

	//드래곤 대거 블루프린트 초기화
	static ConstructorHelpers::FObjectFinder<UBlueprint> DragonArrowBlueprint(TEXT("Blueprint'/Game/Characters/Player/Warrior/Blueprint/Dragon_Arrow.Dragon_Arrow'"));
	if (DragonArrowBlueprint.Succeeded()) {
		DaggerClass = DragonArrowBlueprint.Object->GeneratedClass;
		UE_LOG(LogTemp, Log, TEXT("DragonArrowBlueprint Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("DragonArrowBlueprint Load Failed"))
	}

}

void UGA_Warrior_Skill4_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
		AWarriorCharacter* WarriorCharacter = Cast<AWarriorCharacter>(ActorInfo->OwnerActor);
		if (WarriorCharacter) {
			FVector Vector = WarriorCharacter->Skill4Collision->GetComponentLocation();
			FTransform Transform;
			Transform.SetLocation(Vector);
			Transform.SetScale3D(FVector(1, 1, 1));
			UGameplayStatics::SpawnEmitterAtLocation(WarriorCharacter->GetWorld(), ParticleSystem, Transform,true);
			UGameplayStatics::PlaySound2D(WarriorCharacter, SoundWave);
			
			Transform.SetLocation(Vector);
			Transform.SetScale3D(FVector(3, 3, 3));
			WarriorCharacter->GetWorld()->SpawnActor<AActor>(DaggerClass, Transform, FActorSpawnParameters());
		}

		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}
