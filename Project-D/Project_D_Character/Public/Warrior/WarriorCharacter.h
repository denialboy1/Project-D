// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerCharacter.h"
#include "Warrior/WarriorAnimInstance.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Ability/Monster_character.h"

#include "Warrior/GA_Warrior_WeaponAttack.h"
#include "Warrior/GA_Warrior_Combo1.h"
#include "Warrior/GA_Warrior_Combo2.h"
#include "Warrior/GA_Warrior_SpecialCommand.h"
#include "Warrior/GA_Warrior_Roll.h"

#include "Warrior/Skill/GA_Warrior_JumpAttack_Up.h"
#include "Warrior/Skill/GA_Warrior_JumpAttack_Loop.h"
#include "Warrior/Skill/GA_Warrior_JumpAttack_Down.h"
#include "Warrior/Skill/GA_Warrior_Skill3.h"
#include "Warrior/Skill/GA_Warrior_Skill4.h"
#include "Warrior/Skill/GA_Warrior_Skill4_Fire.h"

#include "WarriorCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_CHARACTER_API AWarriorCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	AWarriorCharacter();

	//���� ����Ʈ ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ProtectParticleComponent;

	//�ݸ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* WeaponAttackCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Skill1Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Skill3Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Skill4Collision;



	//������ �ִ� �ν��Ͻ�
	UWarriorAnimInstance* WarriorAnimInstance;


	//�޺� ���� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack, meta = (AllowPrivateAccess = "true"))
	float MeleeSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack, meta = (AllowPrivateAccess = "true"))
	int AttackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack, meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack, meta = (AllowPrivateAccess = "true"))
	bool bSaveAttack;


	//��ġ �����ϴ� ���� ����Ʈ
	//�� ��ġ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayEffect, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Warrior_Heal;

	//�⺻���� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayEffect, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Warrior_WeaponDamage;

	//��ų1 ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayEffect, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Warrior_Skill1Damage;

	//��ų3 ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayEffect, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Warrior_Skill3Damage;



	//������Ʈ ���� Ÿ�̸�
	float ProtectResetTime = 0.0f;

	//��ų3 ���� �ð� Ÿ�̸�
	float MaxSkill3Time = 0.0f;
	//��ų3 �ʴ� ������ Ÿ�̸�
	float Skill3Time = 0.0f;
	

	//���� �迭
	TArray<AMonster_Character*> MonsterList;



private:
	//�⺻ ���� �����Ƽ
	TSubclassOf<UGA_Warrior_WeaponAttack> GA_Warrior_WeaponAttack;
	TSubclassOf<UGA_Warrior_Combo1> GA_Warrior_Combo1;
	TSubclassOf<UGA_Warrior_Combo2> GA_Warrior_Combo2;
	TSubclassOf<UGA_Warrior_SpecialCommand> GA_Warrior_SpecialCommand;
	TSubclassOf<UGA_Warrior_Roll> GA_Warrior_Roll;

	//��ų �����Ƽ
	TSubclassOf<UGA_Warrior_JumpAttack_Up> GA_Warrior_JumpAttack_Up;
	TSubclassOf<UGA_Warrior_JumpAttack_Loop> GA_Warrior_JumpAttack_Loop;
	TSubclassOf<UGA_Warrior_JumpAttack_Down> GA_Warrior_JumpAttack_Down;
	TSubclassOf<UGA_Warrior_Skill3> GA_Warrior_Skill3;
	
	TSubclassOf<UGA_Warrior_Skill4> GA_Warrior_Skill4;							//��ų2�� ��ų4�� ��ü
	TSubclassOf<UGA_Warrior_Skill4_Fire> GA_Warrior_Skill4_Fire;

public:
	



protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	//��ų1 �ٴ� ����
	void GroundJudge();

	//���� ����
	void RecoverProtect(float DeltaTime);

	//�� ȸ����
	void SowrdTonado(float DeltaTime);

private:

	//�����Ƽ �ʱ�ȭ
	void AbilityInit();

	//�޺�����
	virtual void MulticastRPC_Attack_Implementation() override;

	//��ų1
	virtual void MulticastRPC_Skill1_Implementation() override;


public:

	UFUNCTION(BlueprintCallable)
	void ComboSwitch();

	UFUNCTION(BlueprintCallable)
	void ComboAttackSave();

    UFUNCTION(BlueprintCallable)
	void ResetCombo();

	UFUNCTION()
	void OnComponentBeginOverlap_WeaponAttackCollision(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool FromSweep, const FHitResult& SweeoResult);

	UFUNCTION()
	void OnComponentBeginOverlap_Skill1Collision(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool FromSweep, const FHitResult& SweeoResult);
	
	UFUNCTION()
	void OnComponentBeginOverlap_Skill3Collision(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool FromSweep, const FHitResult& SweeoResult);
	
	UFUNCTION()
	void OnComponentEndOverlap_Skill3Collision(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex);


};
