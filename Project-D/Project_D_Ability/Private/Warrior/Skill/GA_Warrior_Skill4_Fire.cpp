// Team Project D has all rights this game

#include "Warrior/Skill/GA_Warrior_Skill4_Fire.h"
#include "Warrior/WarriorCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

UGA_Warrior_Skill4_Fire::UGA_Warrior_Skill4_Fire() {
	
	//��å ����
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

	//����Ʈ �ʱ�ȭ
	static ConstructorHelpers::FObjectFinder<UParticleSystem> GreyStonHit_ParticleSystem(TEXT("ParticleSystem'/Game/Characters/Player/Warrior/ParagonGreystone/FX/Particles/Greystone/Abilities/Ultimate/FX/P_Greystone_HToKill_Impact_Local.P_Greystone_HToKill_Impact_Local'"));
	if (GreyStonHit_ParticleSystem.Succeeded()) {
		ParticleSystem = GreyStonHit_ParticleSystem.Object;
		
		UE_LOG(LogTemp, Log, TEXT("GreyStonHit_ParticleSystem Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GreyStonHit_ParticleSystem Fail"));
	}

	//����
	static ConstructorHelpers::FObjectFinder<USoundWave> GreyStonHit_SoundWave(TEXT("SoundWave'/Game/Characters/Player/Warrior/Sound/Warrior_Dragon_Fire_Sound.Warrior_Dragon_Fire_Sound'"));
	if (GreyStonHit_SoundWave.Succeeded()) {
		SoundWave = GreyStonHit_SoundWave.Object;
		UE_LOG(LogTemp, Log, TEXT("GreyStonHit_SoundWave Succeed"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GreyStonHit_SoundWave Fail"));
	}

	//�巡�� ��� �������Ʈ �ʱ�ȭ
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
