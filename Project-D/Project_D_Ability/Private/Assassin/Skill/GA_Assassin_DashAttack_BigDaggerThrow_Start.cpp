// Team Project D has all rights this game


#include "Assassin/Skill/GA_Assassin_DashAttack_BigDaggerThrow_Start.h"
#include "Assassin/Skill/CD_Assassin_BigDaggerThrow.h"
#include "Assassin/AssassinCharacter.h"
#include "Assassin/AssassinAnimInstance.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsModule.h"

UGA_Assassin_DashAttack_BigDaggerThrow_Start::UGA_Assassin_DashAttack_BigDaggerThrow_Start() {
	//��Ÿ�� ����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Assassin/Animation/AM_Assassin_DashAttack_BigDaggerThrow.AM_Assassin_DashAttack_BigDaggerThrow'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("UGA_Assassin_DashAttack_BigDaggerThrow_Start Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("UGA_Assassin_DashAttack_BigDaggerThrow_Start Load Failed"))
	}

	//��å ����
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

	//�����Ƽ �±� ����
	ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Assassin.Skill3"));

	//��Ÿ�� ����
	CooldownGameplayEffectClass = UCD_Assassin_BigDaggerThrow::StaticClass();
}



void UGA_Assassin_DashAttack_BigDaggerThrow_Start::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	AAssassinCharacter* AssassinCharacter = Cast<AAssassinCharacter>(GetActorInfo().OwnerActor);
	if (AssassinCharacter) {
		//��Ÿ ���� �޺�
		AssassinCharacter->AttackCount = 0;
		AssassinCharacter->bSaveAttack = false;
		AssassinCharacter->bIsAttacking = false;

		//��� ������ 
		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
		UAssassinAnimInstance* AssassinAnimInstance = Cast<UAssassinAnimInstance>(AnimInstance);
		if (AssassinAnimInstance) {
			if (AssassinAnimInstance->bIsInAir) {
				AssassinAnimInstance->Montage_Play(MontageToPlay, 1.0f);
			}
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
}