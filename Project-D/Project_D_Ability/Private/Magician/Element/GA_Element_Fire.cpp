// Team Project D has all rights this game


#include "Magician/Element/GA_Element_Fire.h"
#include "Magician/Element/CD_Element_Fire.h"
#include "Magician/MagicianCharacter.h"
#include "GameplayTagsModule.h"

UGA_Element_Fire::UGA_Element_Fire() {
	//몽타주 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Magician/Animation/AM_Magician_Cast.AM_Magician_Cast'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Fire Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Fire Load Fail"))
	}

	//정책 설정
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

	//태그 설정
	ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Fire"));

	//쿨타임 설정
	CooldownGameplayEffectClass = UCD_Element_Fire::StaticClass();
}

void UGA_Element_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

		if (GetActorInfo().OwnerActor == nullptr) {
			UE_LOG(LogTemp, Log, TEXT("Owner NULL"))
		}
		else {
			MagicianCharacter = Cast<AMagicianCharacter>(GetActorInfo().OwnerActor);
			UE_LOG(LogTemp, Log, TEXT("Owner not NULL"))
		}

		if (MagicianCharacter == nullptr) {
			//MagicianCharacter = Cast<AMagicianCharacter>(GetActorInfo().OwnerActor);
			UE_LOG(LogTemp, Log, TEXT("MAGICIANcHARACTER NULL"))
		}
		else {
			MagicianCharacter->ElementTag.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Fire"));
			ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Fire"));
			MagicianCharacter->SetElementIndex(0);
			UE_LOG(LogTemp, Log, TEXT("MAGICIANcHARACTER ElementIndex : %d"), MagicianCharacter->GetElementIndex())
			UE_LOG(LogTemp, Log, TEXT("MAGICIANcHARACTER not NULL"))
		}
}