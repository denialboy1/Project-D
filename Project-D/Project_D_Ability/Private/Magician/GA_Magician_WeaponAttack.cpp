// Team Project D has all rights this game

#include "GA_Magician_WeaponAttack.h"
#include "MagicianCharacter.h"
#include "GameplayTagsModule.h"
#include "GA_Fire.h"
#include "GA_Water.h"
#include "GA_Earth.h"
#include "GA_Air.h"
#include "GA_FireAndAir.h"
#include "GA_FireAndEarth.h"
#include "GA_FireAndWater.h"
#include "GA_WaterAndAir.h"
#include "GA_WaterAndEarth.h"
#include "GA_EarthAndAir.h"


UGA_Magician_WeaponAttack::UGA_Magician_WeaponAttack() {
	

	ReplicationPolicy = EGameplayAbilityReplicationPolicy::Type::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerExecution;
	bServerRespectsRemoteAbilityCancellation = true;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::Type::ServerOnly;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::Type::ClientOrServer;
}

void UGA_Magician_WeaponAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (CommitAbility(Handle, ActorInfo, ActivationInfo)) {
		
		if (GetActorInfo().OwnerActor == nullptr) {
			UE_LOG(LogTemp, Log, TEXT("Owner NULL"))
		}
		else {
			Character = Cast<AMagicianCharacter>(GetActorInfo().OwnerActor);
			UE_LOG(LogTemp, Log, TEXT("Owner not NULL"))
		}
		
		if (Character == nullptr) {
			UE_LOG(LogTemp, Log, TEXT("Magician_WeaponAttack Character NULL"))
		}
		else {
			//쿼리를 이용해서 원소 비교
			//Fire + Air
			if (TwoElementAction("Magician.Element.Fire", "Magician.Element.Air", &Character->AllFireElement, &Character->AllAirElement, UGA_FireAndAir::StaticClass())) {}

			//Fire + Earth
			else if (TwoElementAction("Magician.Element.Fire", "Magician.Element.Earth", &Character->AllFireElement, &Character->AllEarthElement, UGA_FireAndEarth::StaticClass())) {}

			//Fire + Water
			else if (TwoElementAction("Magician.Element.Fire", "Magician.Element.Water", &Character->AllFireElement, &Character->AllWaterElement, UGA_FireAndWater::StaticClass())) {}

			//Water + Air
			else if (TwoElementAction("Magician.Element.Water", "Magician.Element.Air", &Character->AllWaterElement, &Character->AllAirElement, UGA_WaterAndAir::StaticClass())) {}

			//Water + Earth
			else if (TwoElementAction("Magician.Element.Water", "Magician.Element.Earth", &Character->AllWaterElement, &Character->AllEarthElement, UGA_WaterAndEarth::StaticClass())) {}

			//Earth + Air
			else if (TwoElementAction("Magician.Element.Earth", "Magician.Element.Air", &Character->AllEarthElement, &Character->AllAirElement, UGA_EarthAndAir::StaticClass())) {}

			//Fire
			else if (OneElementAction("Magician.Element.Fire", &Character->AllFireElement, UGA_Fire::StaticClass())) {}

			//Water
			else if (OneElementAction("Magician.Element.Water", &Character->AllWaterElement, UGA_Water::StaticClass())) {}

			//Earth
			else if (OneElementAction("Magician.Element.Earth", &Character->AllEarthElement, UGA_Earth::StaticClass())) {}

			//Air
			else if (OneElementAction("Magician.Element.Air", &Character->AllAirElement, UGA_Air::StaticClass())) {}

			//불 원소가 0이면 태그 제거
			RemoveTagForZeroElement(Character->AllFireElement, UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Fire"));
			
			//물 원소가 0이면 태그 제거
			RemoveTagForZeroElement(Character->AllWaterElement, UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Water"));

			//땅 원소가 0이면 태그 제거
			RemoveTagForZeroElement(Character->AllEarthElement, UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Earth"));

			//공기 원소가 0이면 태그 제거
			RemoveTagForZeroElement(Character->AllAirElement, UGameplayTagsManager::Get().RequestGameplayTag("Magician.Element.Air"));

			UE_LOG(LogTemp, Log, TEXT("Magician_WeaponAttack Character not NULL"))
		}
	}	
}

void UGA_Magician_WeaponAttack::DestroyElement(TArray<AActor*>* Elements) {
	if (Elements->Num() > 0) {
		Elements->Top()->Destroy();
		Elements->Pop();
	}
}

bool UGA_Magician_WeaponAttack::OneElementAction(FName Tag1, TArray<AActor*>* Elements1, TSubclassOf<UGameplayAbility> Ability) {
	FGameplayTagQueryExpression TagQueryExpression;
	TagQueryExpression.AddTag(Tag1);
	TagQueryExpression.ExprType = EGameplayTagQueryExprType::Type::AllTagsMatch;

	FGameplayTagQuery TagQuery;
	TagQuery.Build(TagQueryExpression);
	if (TagQuery.Matches(Character->ElementTag)) {
		ENetMode temp = Character->GetNetMode();
		
		//ActorInfo->AvatarActor->GetLocalRole();
		UAbilitySystemComponent* AbilitySystem = Character->GetAbilitySystemComponent();
		if (AbilitySystem->TryActivateAbilityByClass(Ability)) {

			if (Elements1->Num() != 0)
				DestroyElement(Elements1);

			UE_LOG(LogTemp, Log, TEXT("%s %d"), *Tag1.ToString(), Character->AllFireElement.Num())
			return true;
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("%s %d Failed"), *Tag1.ToString(), Character->AllFireElement.Num())
		}
	}

	return false;
}

bool UGA_Magician_WeaponAttack::TwoElementAction(FName Tag1, FName Tag2, TArray<AActor*>* Elements1, TArray<AActor*>* Elements2, TSubclassOf<UGameplayAbility> Ability) {
	FGameplayTagQueryExpression TagQueryExpression;
	TagQueryExpression.AddTag(Tag1);
	TagQueryExpression.AddTag(Tag2);
	TagQueryExpression.ExprType = EGameplayTagQueryExprType::Type::AllTagsMatch;

	FGameplayTagQuery TagQuery;
	TagQuery.Build(TagQueryExpression);
	if (TagQuery.Matches(Character->ElementTag)) {
		if (Character->GetAbilitySystemComponent()->TryActivateAbilityByClass(Ability)) {

			if (Elements1->Num() != 0)
				DestroyElement(Elements1);

			if (Elements2->Num() != 0)
				DestroyElement(Elements2);


			UE_LOG(LogTemp, Log, TEXT("%s %s %d"), *Tag1.ToString(), *Tag2.ToString(), Character->AllFireElement.Num())
			return true;
		}
	}

	return false;
}

void UGA_Magician_WeaponAttack::RemoveTagForZeroElement(TArray<AActor*> Element,FGameplayTag Tag) {
	//원소가 0개면 태그목록에서 삭제
	if (Element.Num() <= 0) {
		Character->ElementTag.RemoveTag(Tag);
		UE_LOG(LogTemp, Log, TEXT("RemoveTag %s"), *Tag.ToString());
	}
}