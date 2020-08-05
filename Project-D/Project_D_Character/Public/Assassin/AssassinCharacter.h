// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Assassin/AssassinAnimInstance.h"

#include "Assassin/GA_Assassin_DoubleJump.h"
#include "Assassin/GA_Assassin_DoubleJump_Cancel.h"
#include "Assassin/GA_Assassin_Launch.h"
#include "Assassin/GA_Assassin_Roll.h"
#include "Assassin/GA_Assassin_WeaponAttack.h"
#include "Assassin/GA_Assassin_WeaponAttack2.h"
#include "Assassin/GA_Assassin_WeaponAttack3.h"

#include "Assassin/Skill/GA_Assassin_DashAttack_BigDaggerThrow_End.h"
#include "Assassin/Skill/GA_Assassin_DashAttack_BigDaggerThrow_Start.h"
#include "Assassin/Skill/GA_Assassin_DashAttack_End.h"
#include "Assassin/Skill/GA_Assassin_DashAttack_Loop.h"
#include "Assassin/Skill/GA_Assassin_DashAttack_Start.h"
#include "Assassin/Skill/GA_Assassin_NeckSlice.h"
#include "Assassin/Skill/GA_Assassin_ThrowDagger.h"
#include "Assassin/Skill/GA_Assassin_ThrowDagger_Spawn.h"

#include "AssassinCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_CHARACTER_API AAssassinCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	AAssassinCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* WeaponAttackCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Skill2Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Skill2AirCollision;


	//�ִ� �ν��Ͻ�
	UAssassinAnimInstance* AssassinAnimInstance;

	//�޺� ���� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack, meta = (AllowPrivateAccess = "true"))
	float MeleeSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack, meta = (AllowPrivateAccess = "true"))
	int AttackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack, meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack, meta = (AllowPrivateAccess = "true"))
	bool bSaveAttack;


	//���� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Jump, meta = (AllowPrivateAccess = "true"))
	int JumpCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Jump, meta = (AllowPrivateAccess = "true"))
	bool bCanDoubleJump;

	//4�� ��ų ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill4, meta = (AllowPrivateAccess = "true"))
	bool bUseSkill4;

	//��ġ �����ϴ� ���� ����Ʈ
	//�⺻���� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayEffect, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Assassin_WeaponAttack;

	//Skill2 ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayEffect, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Assassin_Skill2;

	//Skill4 ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayEffect, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Assassin_Skill4;


	//�⺻ ���� �����Ƽ
	TSubclassOf<UGA_Assassin_WeaponAttack> GA_Assassin_WeaponAttack1;
	TSubclassOf<UGA_Assassin_WeaponAttack2> GA_Assassin_WeaponAttack2;
	TSubclassOf<UGA_Assassin_WeaponAttack3> GA_Assassin_WeaponAttack3;
	TSubclassOf<UGA_Assassin_DoubleJump> GA_Assassin_DoubleJump;
	TSubclassOf<UGA_Assassin_DoubleJump_Cancel> GA_Assassin_DoubleJump_Cancel;
	TSubclassOf<UGA_Assassin_Roll> GA_Assassin_Roll;
	TSubclassOf<UGA_Assassin_Launch> GA_Assassin_Launch;

	//��ų �����Ƽ
	TSubclassOf<UGA_Assassin_DashAttack_BigDaggerThrow_End> GA_Assassin_DashAttack_BigDaggerThrow_End;
	TSubclassOf<UGA_Assassin_DashAttack_BigDaggerThrow_Start> GA_Assassin_DashAttack_BigDaggerThrow_Start;
	TSubclassOf<UGA_Assassin_DashAttack_End> GA_Assassin_DashAttack_End;
	TSubclassOf<UGA_Assassin_DashAttack_Loop> GA_Assassin_DashAttack_Loop;
	TSubclassOf<UGA_Assassin_DashAttack_Start> GA_Assassin_DashAttack_Start;
	TSubclassOf<UGA_Assassin_NeckSlice> GA_Assassin_NeckSlice;
	TSubclassOf<UGA_Assassin_ThrowDagger> GA_Assassin_ThrowDagger;
	TSubclassOf<UGA_Assassin_ThrowDagger_Spawn> GA_Assassin_ThrowDagger_Spawn;

	
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



		
private:
	//�����Ƽ �ʱ�ȭ
	void AbilityInit();

public:
	//�޺�����
	virtual void MulticastRPC_Attack_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void ComboSwitch();

	UFUNCTION(BlueprintCallable)
	void ComboAttackSave();

	UFUNCTION(BlueprintCallable)
	void ResetCombo();



	//���� ����
	UFUNCTION(BlueprintCallable)
	void DoubleJump();

	UFUNCTION(BlueprintCallable)
	void DoubleJumpCancel();

	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable)
	void Launch();
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_Launch();
	virtual void ServerRPC_Launch_Implementation();
	virtual bool ServerRPC_Launch_Validate() { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void MulticastRPC_Launch();
	virtual void MulticastRPC_Launch_Implementation();
	virtual bool MulticastRPC_Launch_Validate() { return true; }



	//�浹ó��
	UFUNCTION()
	void OnComponentBeginOverlap_WeaponAttackCollision(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool FromSweep, const FHitResult& SweeoResult);

	UFUNCTION()
	void OnComponentHit_Capsule(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnComponentBeginOverlap_Skill2Air(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool FromSweep, const FHitResult& SweeoResult);

	UFUNCTION()
	void OnComponentBeginOverlap_Skill2(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool FromSweep, const FHitResult& SweeoResult);
};
