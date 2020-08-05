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

	//갑옷 이펙트 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ProtectParticleComponent;

	//콜리전
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* WeaponAttackCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Skill1Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Skill3Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Skill4Collision;



	//워리어 애님 인스턴스
	UWarriorAnimInstance* WarriorAnimInstance;


	//콤보 어택 관련 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack, meta = (AllowPrivateAccess = "true"))
	float MeleeSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack, meta = (AllowPrivateAccess = "true"))
	int AttackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack, meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack, meta = (AllowPrivateAccess = "true"))
	bool bSaveAttack;


	//수치 조정하는 게임 이펙트
	//힐 수치 조정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayEffect, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Warrior_Heal;

	//기본공격 데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayEffect, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Warrior_WeaponDamage;

	//스킬1 데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayEffect, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Warrior_Skill1Damage;

	//스킬3 데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayEffect, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Warrior_Skill3Damage;



	//프로텍트 복구 타이머
	float ProtectResetTime = 0.0f;

	//스킬3 지속 시간 타이머
	float MaxSkill3Time = 0.0f;
	//스킬3 초당 때리는 타이머
	float Skill3Time = 0.0f;
	

	//몬스터 배열
	TArray<AMonster_Character*> MonsterList;



private:
	//기본 동작 어빌리티
	TSubclassOf<UGA_Warrior_WeaponAttack> GA_Warrior_WeaponAttack;
	TSubclassOf<UGA_Warrior_Combo1> GA_Warrior_Combo1;
	TSubclassOf<UGA_Warrior_Combo2> GA_Warrior_Combo2;
	TSubclassOf<UGA_Warrior_SpecialCommand> GA_Warrior_SpecialCommand;
	TSubclassOf<UGA_Warrior_Roll> GA_Warrior_Roll;

	//스킬 어빌리티
	TSubclassOf<UGA_Warrior_JumpAttack_Up> GA_Warrior_JumpAttack_Up;
	TSubclassOf<UGA_Warrior_JumpAttack_Loop> GA_Warrior_JumpAttack_Loop;
	TSubclassOf<UGA_Warrior_JumpAttack_Down> GA_Warrior_JumpAttack_Down;
	TSubclassOf<UGA_Warrior_Skill3> GA_Warrior_Skill3;
	
	TSubclassOf<UGA_Warrior_Skill4> GA_Warrior_Skill4;							//스킬2를 스킬4로 대체
	TSubclassOf<UGA_Warrior_Skill4_Fire> GA_Warrior_Skill4_Fire;

public:
	



protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	//스킬1 바닥 판정
	void GroundJudge();

	//쉴드 복구
	void RecoverProtect(float DeltaTime);

	//검 회오리
	void SowrdTonado(float DeltaTime);

private:

	//어빌리티 초기화
	void AbilityInit();

	//콤보공격
	virtual void MulticastRPC_Attack_Implementation() override;

	//스킬1
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
