// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "ArcherAnimInstance.h"
#include "GA_Archer_Reload.h"
#include "GA_Archer_WeaponAttack.h"
#include "GA_Archer_Skill1.h"
#include "GA_Archer_Skill2.h"
#include "GA_Archer_Skill3.h"
#include "GA_Archer_Skill4.h"
#include "GA_Archer_Roll.h"
#include "ArcherCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_CHARACTER_API AArcherCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
	AArcherCharacter();
private:
	
	
	//����
	UPROPERTY()
	UUserWidget* AimWidget;

	UPROPERTY()
	TSubclassOf<UUserWidget> AnimWidgetClass;

	UPROPERTY()
	bool bIsAim;

	//�ִ� �ν��Ͻ�
	UArcherAnimInstance* ArcherAnimInstance;

	//�����Ƽ
	TSubclassOf<UGA_Archer_Reload> GA_Archer_Reload;
	TSubclassOf<UGA_Archer_WeaponAttack> GA_Archer_WeaponAttack;
	TSubclassOf<UGA_Archer_Skill1> GA_Archer_Skill1;
	TSubclassOf<UGA_Archer_Skill2> GA_Archer_Skill2;
	TSubclassOf<UGA_Archer_Skill3> GA_Archer_Skill3;
	TSubclassOf<UGA_Archer_Skill4> GA_Archer_Skill4;
	TSubclassOf<UGA_Archer_Roll> GA_Archer_Roll;


protected:
public:
	

private:
	//�����Ƽ �ʱ�ȭ
	void AbilityInit();


protected:
	

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void BeginPlay() override;


	//����
	void Attack() override;
	virtual void ServerRPC_Attack_Implementation() override;
	virtual void MulticastRPC_Attack_Implementation() override;

	//Ư������
	void SpecialCommandAttack() override;
	virtual void ServerRPC_SpecialCommandAttack_Implementation() override;
	virtual void MulticastRPC_SpecialCommandAttack_Implementation() override;
	

	//Ư�� ���� ĵ��
	void SpecialCommandAttackCancel();
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerRPC_SpecialCommandAttackCancel();
	void ServerRPC_SpecialCommandAttackCancel_Implementation();
	bool ServerRPC_SpecialCommandAttackCancel_Validate() { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	void MulticastRPC_SpecialCommandAttackCancel();
	void MulticastRPC_SpecialCommandAttackCancel_Implementation();
	bool MulticastRPC_SpecialCommandAttackCancel_Validate() { return true; }
public:

	bool GetIsAim() { return bIsAim; }
	void SetIsAim(bool _bIsAim) { bIsAim = _bIsAim; }
};
