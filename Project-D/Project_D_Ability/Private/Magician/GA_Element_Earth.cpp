// Team Project D has all rights this game


#include "GA_Element_Earth.h"
#include "GameplayTagsModule.h"
#include "MagicianCharacter.h"
#include "GE_Element_Earth.h"

UGA_Element_Earth::UGA_Element_Earth() {
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("AnimMontage'/Game/Characters/Player/Magician/Animation/AM_Magician_Cast.AM_Magician_Cast'"));
	if (Montage.Succeeded()) {
		MontageToPlay = Montage.Object;
		ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
		InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
		bServerRespectsRemoteAbilityCancellation = true;
		NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
		NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;

		AbilityTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Earth"));
		ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Earth"));

		CooldownGameplayEffectClass = UGE_Element_Earth::StaticClass();
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Earth Load Succeess"))
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GA_Element_Earth Load Fail"))
	}


}

void UGA_Element_Earth::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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
			MagicianCharacter->ElementTag.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Earth"));
			ActivationBlockedTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Earth"));
			MagicianCharacter->SetElementIndex(2);
			UE_LOG(LogTemp, Log, TEXT("MAGICIANcHARACTER ElementIndex : %d"), MagicianCharacter->GetElementIndex())
			UE_LOG(LogTemp, Log, TEXT("MAGICIANcHARACTER not NULL"))
			UE_LOG(LogTemp, Log, TEXT("MAGICIANcHARACTER Element Earth"))
		}
}