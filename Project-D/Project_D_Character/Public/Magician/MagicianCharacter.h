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

	//�ִ� �ν��Ͻ�
	UMagicianAnimInstance* MagicianAnimInstance;

	//�����Ƽ
	TSubclassOf<UGA_Magician_WeaponAttack> GA_Magician_WeaponAttack;
	TSubclassOf<UGA_Element_Fire> GA_Magician_Skill1;
	TSubclassOf<UGA_Element_Air> GA_Magician_Skill2;
	TSubclassOf<UGA_Element_Water> GA_Magician_Skill3;
	TSubclassOf<UGA_Element_Earth> GA_Magician_Skill4;
	TSubclassOf<UGA_Magician_Roll> GA_Magician_Roll;
	
	

	//��ȯ ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Element, meta = (AllowPrivateAccess = "true"))
	int ElementIndex;

public:
	//���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Element)
	TArray<AActor*> AllFireElement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Element)
	TArray<AActor*> AllWaterElement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Element)
	TArray<AActor*> AllEarthElement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Element)
	TArray<AActor*> AllAirElement;

	//��� ������ ���� �±�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Element)
	FGameplayTagContainer ElementTag;
	
	//��� �÷��̾�
	TArray<APlayerCharacter*> AllPlayerCharacter;

private:
	//�����Ƽ �ʱ�ȭ
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
