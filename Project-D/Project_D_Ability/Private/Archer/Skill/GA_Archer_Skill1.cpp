// Team Project D has all rights this game


#include "Archer/Skill/GA_Archer_Skill1.h"
#include "Archer/Skill/CD_Archer_Skill1.h"
#include "Archer/ArcherAnimInstance.h"
#include "Archer/ArcherCharacter.h"
#include "AbilitySystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameplayTagsModule.h"

UGA_Archer_Skill1::UGA_Archer_Skill1() {

	//��Ÿ�� ����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Archer/Animation/AM_Archer_Skill1.AM_Archer_Skill1'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("Archer Skill1 Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Archer Skill1 Anim Load Failed"))
	}


	//��å ����
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;


	//�����Ƽ �±� ����
	ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Archer.Skill1"));

	//��Ÿ�� ����
	CooldownGameplayEffectClass = UCD_Archer_Skill1::StaticClass();

}