// Team Project D has all rights this game


#include "Archer/Skill/GA_Archer_Skill4.h"
#include "Archer/Skill/CD_Archer_Skill4.h"
#include "Archer/ArcherAnimInstance.h"
#include "Archer/ArcherCharacter.h"
#include "AbilitySystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameplayTagsModule.h"

UGA_Archer_Skill4::UGA_Archer_Skill4() {

	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Archer/Animation/AM_Archer_Skill4.AM_Archer_Skill4'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("Archer Skill4 Anim Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Archer Skill4 Anim Load Failed"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;


	//어빌리티 태그 설정
	ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Archer.Skill4"));

	//쿨타임 설정
	CooldownGameplayEffectClass = UCD_Archer_Skill4::StaticClass();
}

