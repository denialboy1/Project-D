// Team Project D has all rights this game

#include "GA_Resurrection.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

void UGA_Resurrection::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	if (CommitAbility(Handle, ActorInfo, ActivationInfo)) {

		//��ƼŬ ��ȯ ��ǥ
		FTransform ActorTransform = GetActorInfo().OwnerActor.Get()->GetActorTransform();
		FVector location = ActorTransform.GetLocation();
		location.Z -= 100;
		ActorTransform.SetLocation(location);

		//��ƼŬ ���ϱ�
		static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle(TEXT("/Game/Characters/Player/Shared/FX/Revival/ParticleSystems/356Days/Revive.Revive"));
		ParticleRevive = Particle.Object;

	
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleRevive, ActorTransform);
	}
}
