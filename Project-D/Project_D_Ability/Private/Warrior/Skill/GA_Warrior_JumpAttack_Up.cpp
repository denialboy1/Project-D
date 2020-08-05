// Team Project D has all rights this game


#include "Warrior/Skill/GA_Warrior_JumpAttack_Up.h"
#include "Warrior/WarriorCharacter.h"
#include "Warrior/WarriorAnimInstance.h"
#include "Warrior/Skill/CD_Warrior_JumpAttack.h"
#include "GameplayTagsModule.h"

UGA_Warrior_JumpAttack_Up::UGA_Warrior_JumpAttack_Up() {
	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Warrior/Animation/AM_Warrior_JA_Start_Montage.AM_Warrior_JA_Start_Montage'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("UGA_Warrior_JumpAttack_Up Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("UGA_Warrior_JumpAttack_Up Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

	//어빌리티 태그 설정
	ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Warrior.Skill1"));

	//쿨타임 설정
	CooldownGameplayEffectClass = UCD_Warrior_JumpAttack::StaticClass();
}

void UGA_Warrior_JumpAttack_Up::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData){

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
		//앞으로 점프
		UWarriorAnimInstance* WarriorAnimInstance = Cast<UWarriorAnimInstance>(WarriorCharacter->GetMesh()->GetAnimInstance());
		WarriorAnimInstance->bIsJumpAttack = true;

		FVector V = FRotationMatrix(WarriorCharacter->GetActorRotation()).GetScaledAxis(EAxis::X) * 500.0f + FVector(0, 0, 500.0f);
		WarriorCharacter->LaunchCharacter(V, false, false);

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
		
		//OnInterupted

		if (SectionName != NAME_None)
		{
			AnimInstance->Montage_JumpToSection(SectionName);
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}

