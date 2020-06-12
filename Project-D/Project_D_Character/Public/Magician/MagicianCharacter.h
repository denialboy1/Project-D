// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerCharacter.h"
#include "MagicianAnimInstance.h"
#include "GA_Magician_WeaponAttack.h"
#include "GA_Element_Fire.h"
#include "GA_Element_Air.h"
#include "GA_Element_Water.h"
#include "GA_Element_Earth.h"
#include "GA_Magician_Roll.h"
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

	//어빌리티
	TSubclassOf<UGA_Magician_WeaponAttack> GA_Magician_WeaponAttack;
	TSubclassOf<UGA_Element_Fire> GA_Magician_Skill1;
	TSubclassOf<UGA_Element_Air> GA_Magician_Skill2;
	TSubclassOf<UGA_Element_Water> GA_Magician_Skill3;
	TSubclassOf<UGA_Element_Earth> GA_Magician_Skill4;
	TSubclassOf<UGA_Magician_Roll> GA_Magician_Roll;
	
	

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
