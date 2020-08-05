// Team Project D has all rights this game


#include "Magician/GA_Magician_Roll.h"
#include "UObject/ConstructorHelpers.h"
#include "Magician/MagicianAnimInstance.h"
#include "Magician/MagicianCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemComponent.h"

UGA_Magician_Roll::UGA_Magician_Roll() {

	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Magician/Animation/AM_Magician_Roll.AM_Magician_Roll'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("Magician Roll Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Magician Roll Anim Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}

void UGA_Magician_Roll::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	AMagicianCharacter* MagicianCharacter = Cast<AMagicianCharacter>(GetOwningActorFromActorInfo());
	if (!MagicianCharacter->GetIsRoll()) {

		FRotator Rotator;
		Rotator.Yaw = GetOwningActorFromActorInfo()->GetInstigator()->GetControlRotation().Yaw;

		FVector Forward = UKismetMathLibrary::GetForwardVector(Rotator) * (MagicianCharacter->GetCurMoveForward() * 300);
		FVector Right = UKismetMathLibrary::GetRightVector(Rotator) * (MagicianCharacter->GetCurMoveRight() * 300);
		FVector Vector = FVector(0, 0, 300) + Forward + Right;

		MagicianCharacter->LaunchCharacter(Vector, false, false);
		MagicianCharacter->SetIsRoll(true);
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

