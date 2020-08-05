// Team Project D has all rights this game


#include "Magician/Element/GA_Element_Water.h"
#include "Magician/Element/CD_Element_Water.h"
#include "Magician/MagicianCharacter.h"
#include "GameplayTagsModule.h"



UGA_Element_Water::UGA_Element_Water() {

	//��Ÿ�� ����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Magician/Animation/AM_Magician_Cast.AM_Magician_Cast'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Water Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Water Load Fail"))
	}

	//��å ����
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

	//�±� ����
	ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Water"));

	//��Ÿ�� ����
	CooldownGameplayEffectClass = UCD_Element_Water::StaticClass();
}

void UGA_Element_Water::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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
			MagicianCharacter->ElementTag.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Water"));
			ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Water"));
			MagicianCharacter->SetElementIndex(1);
			UE_LOG(LogTemp, Log, TEXT("MAGICIANcHARACTER ElementIndex : %d"), MagicianCharacter->GetElementIndex())
			UE_LOG(LogTemp, Log, TEXT("MAGICIANcHARACTER not NULL"))
			UE_LOG(LogTemp, Log, TEXT("MAGICIANcHARACTER Element Water"))
		}
}