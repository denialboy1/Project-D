// Team Project D has all rights this game


#include "Warrior/Skill/GA_Warrior_Skill4.h"
#include "Warrior/Skill/CD_Warrior_Skill4.h"
#include "GameplayTagsModule.h"

UGA_Warrior_Skill4::UGA_Warrior_Skill4() {
	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Warrior/Animation/AM_Warrior_Skill4.AM_Warrior_Skill4'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("Warrior Skill4 Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Warrior Skill4 Anim Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

	//어빌리티 태그 설정
	ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Warrior.Skill4"));

	//쿨타임 설정
	CooldownGameplayEffectClass = UCD_Warrior_Skill4::StaticClass();

}

void UGA_Warrior_Skill4::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {


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