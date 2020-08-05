// Team Project D has all rights this game


#include "Warrior/Skill/GA_Warrior_JumpAttack_Down.h"
#include "Warrior/WarriorCharacter.h"
#include "Warrior/WarriorAnimInstance.h"

UGA_Warrior_JumpAttack_Down::UGA_Warrior_JumpAttack_Down() {
	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Warrior/Animation/AM_Warrior_JA_End_Montage.AM_Warrior_JA_End_Montage'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("UGA_Warrior_JumpAttack_Down Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("UGA_Warrior_JumpAttack_Down Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}

void UGA_Warrior_JumpAttack_Down::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	//평타 리셋 콤보
	AWarriorCharacter* WarriorCharacter = Cast<AWarriorCharacter>(GetActorInfo().OwnerActor);
	if (WarriorCharacter) {
		WarriorCharacter->AttackCount = 0;
		WarriorCharacter->bSaveAttack = false;
		WarriorCharacter->bIsAttacking = false;
	}

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	if (MontageToPlay != nullptr && AnimInstance != nullptr)
	{

		TArray<FActiveGameplayEffectHandle>	AppliedEffects;

		// Apply GameplayEffects
		TArray<const UGameplayEffect*> Effects;
		GetGameplayEffectsWhileAnimating(Effects);
		if (Effects.Num() > 0)
		{
			UAbilitySystemComponent* const AbilitySystemComponent = ActorInfo->AbilitySystemComponent.Get();
			for (const UGameplayEffect* Effect : Effects)
			{
				FActiveGameplayEffectHandle EffectHandle = AbilitySystemComponent->ApplyGameplayEffectToSelf(Effect, 1.f, MakeEffectContext(Handle, ActorInfo));
				if (EffectHandle.IsValid())
				{
					AppliedEffects.Add(EffectHandle);
				}
			}
		}

		float const Duration = AnimInstance->Montage_Play(MontageToPlay, PlayRate);

		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &UGameplayAbility_Montage::OnMontageEnded, ActorInfo->AbilitySystemComponent, AppliedEffects);
		AnimInstance->Montage_SetEndDelegate(EndDelegate);

		FOnMontageBlendingOutStarted BlendingOutStarted;
		BlendingOutStarted.BindUObject(this, &UGameplayAbility_Montage::OnMontageEnded, ActorInfo->AbilitySystemComponent, AppliedEffects);
		AnimInstance->Montage_SetBlendingOutDelegate(BlendingOutStarted);

		if (SectionName != NAME_None)
		{
			AnimInstance->Montage_JumpToSection(SectionName);
		}
	}
}

void UGA_Warrior_JumpAttack_Down::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted, TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponentPtr, TArray<FActiveGameplayEffectHandle> AppliedEffects)
{
	// Remove any GameplayEffects that we applied
	UAbilitySystemComponent* const AbilitySystemComponent = AbilitySystemComponentPtr.Get();
	if (AbilitySystemComponent)
	{
		for (FActiveGameplayEffectHandle Handle : AppliedEffects)
		{
			AbilitySystemComponent->RemoveActiveGameplayEffect(Handle);
		}
	}

	//점프 상태로 설정.
	AWarriorCharacter* WarriorCharacter = Cast<AWarriorCharacter>(GetActorInfo().OwnerActor);
	UWarriorAnimInstance* WarriorAnimInstance = Cast<UWarriorAnimInstance>(WarriorCharacter->GetMesh()->GetAnimInstance());
	WarriorAnimInstance->bIsJumpAttack = false;
}