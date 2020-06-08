// Team Project D has all rights this game


#include "GA_Archer_Roll.h"
#include "UObject/ConstructorHelpers.h"
#include "ArcherAnimInstance.h"
#include "ArcherCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemComponent.h"

UGA_Archer_Roll::UGA_Archer_Roll() {

	//¸ùÅ¸ÁÖ ¼³Á¤
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Archer/Animation/AM_Archer_Roll.AM_Archer_Roll'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;

		ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
		InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
		bServerRespectsRemoteAbilityCancellation = true;
		NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
		NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
		UE_LOG(LogTemp, Log, TEXT("Archer Roll Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Archer Roll Anim Load Failed"))
	}

}

void UGA_Archer_Roll::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	AArcherCharacter* ArcherCharacter = Cast<AArcherCharacter>(GetOwningActorFromActorInfo());
	if (!ArcherCharacter->GetIsRoll()) {
		
		FRotator Rotator; 
		Rotator.Yaw = GetOwningActorFromActorInfo()->GetInstigator()->GetControlRotation().Yaw;
		
		FVector Forward = UKismetMathLibrary::GetForwardVector(Rotator) * (ArcherCharacter->GetCurMoveForward() * 700);
		FVector Right = UKismetMathLibrary::GetRightVector(Rotator) * (ArcherCharacter->GetCurMoveRight() * 700);
		FVector Vector = FVector(0, 0, 700) + Forward + Right;
		
		ArcherCharacter->LaunchCharacter(Vector, false, false);
		ArcherCharacter->SetIsRoll(true);
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

