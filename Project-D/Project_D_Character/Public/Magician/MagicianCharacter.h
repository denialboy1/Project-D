// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerCharacter.h"
#include "Magician/MagicianAnimInstance.h"
#include "Magician/GA_Magician_WeaponAttack.h"
#include "Magician/GA_Magician_Roll.h"

#include "Magician/Element/GA_Element_Fire.h"
#include "Magician/Element/GA_Element_Air.h"
#include "Magician/Element/GA_Element_Water.h"
#include "Magician/Element/GA_Element_Earth.h"

#include "Magician/Skill/GA_Fire.h"
#include "Magician/Skill/GA_Water.h"
#include "Magician/Skill/GA_Earth.h"
#include "Magician/Skill/GA_Air.h"

#include "Magician/Skill/GA_FireAndAir.h"
#include "Magician/Skill/GA_FireAndEarth.h"
#include "Magician/Skill/GA_FireAndWater.h"
#include "Magician/Skill/GA_WaterAndAir.h"
#include "Magician/Skill/GA_WaterAndEarth.h"
#include "Magician/Skill/GA_EarthAndAir.h"

#include "GameplayTagContainer.h"

#include "MagicianCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_CHARACTER_API AMagicianCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
	AMagicianCharacter();
private:

	//애님 인스턴스
	UMagicianAnimInstance* MagicianAnimInstance;

	//기본 동작 어빌리티
	TSubclassOf<UGA_Magician_WeaponAttack> GA_Magician_WeaponAttack;
	TSubclassOf<UGA_Magician_Roll> GA_Magician_Roll;

	//원소 소환 어빌리티
	TSubclassOf<UGA_Element_Fire> GA_Element_Fire;
	TSubclassOf<UGA_Element_Air> GA_Element_Air;
	TSubclassOf<UGA_Element_Water> GA_Element_Water;
	TSubclassOf<UGA_Element_Earth> GA_Element_Earth;
	

	//원소 한개 스킬 어빌리티
	TSubclassOf<UGA_Fire> GA_Fire;
	TSubclassOf<UGA_Water> GA_Water;
	TSubclassOf<UGA_Earth> GA_Earth;
	TSubclassOf<UGA_Air> GA_Air;

	//원소 두개 스킬 어빌리티
	TSubclassOf<UGA_FireAndAir> GA_FireAndAir;
	TSubclassOf<UGA_FireAndEarth> GA_FireAndEarth;
	TSubclassOf<UGA_FireAndWater> GA_FireAndWater;
	TSubclassOf<UGA_WaterAndAir> GA_WaterAndAir;
	TSubclassOf<UGA_WaterAndEarth> GA_WaterAndEarth;
	TSubclassOf<UGA_EarthAndAir> GA_EarthAndAir;

	//소환 원소
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Element, meta = (AllowPrivateAccess = "true"))
	int ElementIndex;

public:
	//원소 보유
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Element)
	TArray<AActor*> AllFireElement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Element)
	TArray<AActor*> AllWaterElement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Element)
	TArray<AActor*> AllEarthElement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Element)
	TArray<AActor*> AllAirElement;

	//사용 가능한 원소 태그
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Element)
	FGameplayTagContainer ElementTag;
	
	//모든 플레이어
	TArray<APlayerCharacter*> AllPlayerCharacter;

private:
	//어빌리티 초기화
	void AbilityInit();


protected:

	void BeginPlay() override;

public:

	void SetElementIndex(int _ElementIndex) { ElementIndex = _ElementIndex; }
	int GetElementIndex() { return ElementIndex; }

	void AddFireElement(AActor* element) { AllFireElement.Add(element); }
	void AddWaterElement(AActor* element) { AllWaterElement.Add(element); }
	void AddEarthElement(AActor* element) { AllEarthElement.Add(element); }
	void AddAireElement(AActor* element) { AllAirElement.Add(element); }
};

