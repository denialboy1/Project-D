// Team Project D has all rights this game


#include "GA_Element_Air.h"
#include "GameplayTagsModule.h"
#include "MagicianCharacter.h"
#include "GE_Element_Air.h"

UGA_Element_Air::UGA_Element_Air() {
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Magician/Animation/AM_Magician_Cast.AM_Magician_Cast'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
		InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
		bServerRespectsRemoteAbilityCancellation = true;
		NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
		NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

		AbilityTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Air"));
		ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Air"));

		CooldownGameplayEffectClass = UGE_Element_Air::StaticClass();
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Air Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Air Load Fail"))
	}


}

void UGA_Element_Air::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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
			MagicianCharacter->ElementTag.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Air"));
			ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Air"));
			MagicianCharacter->SetElementIndex(3);
			UE_LOG(LogTemp, Log, TEXT("MAGICIANcHARACTER ElementIndex : %d"), MagicianCharacter->GetElementIndex())
			UE_LOG(LogTemp, Log, TEXT("MAGICIANcHARACTER not NULL"))
			UE_LOG(LogTemp, Log, TEXT("MAGICIANcHARACTER Element Air"))
		}
	
}