// Team Project D has all rights this game
#include "Warrior/GA_Warrior_Combo1.h"
#include "AbilitySystemComponent.h"

UGA_Warrior_Combo1::UGA_Warrior_Combo1() {
	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Warrior/Animation/AM_Warrior_2.AM_Warrior_2'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("Warrior Combo1 Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Warrior Combo1 Anim Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}


void UGA_Warrior_Combo1::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
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

		FOnMontageBlendingOutStarted BlendingDelegate;
		BlendingDelegate.BindUObject(this, &UGameplayAbility_Montage::OnMontageEnded, ActorInfo->AbilitySystemComponent, AppliedEffects);
		AnimInstance->Montage_SetBlendingOutDelegate(BlendingDelegate);

		if (SectionName != NAME_None)
		{
			AnimInstance->Montage_JumpToSection(SectionName);
		}
	}
}
