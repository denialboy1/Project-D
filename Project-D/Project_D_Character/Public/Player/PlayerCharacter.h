// Team Project D has all rights this game

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "AttributeSet_Player.h"
#include "GE_PlayerAlive.h"
#include "GA_Resurrection.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "InteractionObject.h"
#include "PlayerAnimInstance.h"
#include "Sound/SoundWave.h"
#include "PlayerCharacter.generated.h"


UENUM(BlueprintType)
enum class AbilityInput : uint8
{
	WeaponAttack UMETA(DisplayName = "Weapon Attack"),
	Combo1 UMETA(DisplayName = "Combo1"),
	Combo2 UMETA(DisplayName = "Combo2"),
	UseSpell1 UMETA(DisplayName = "Use Spell 1"),
	UseSpell2 UMETA(DisplayName = "Use Spell 2"),
	UseSpell3 UMETA(DisplayName = "Use Spell 3"),
	UseSpell4 UMETA(DisplayName = "Use Spell 4"),
	SpecialCommand UMETA(DisplayName = "Special Command"),
	Roll UMETA(DisplayName = "Roll"),
};

/**
 * 
 */
UCLASS()
class PROJECT_D_CHARACTER_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
private:
	//�÷��̾� ���� ���� ����Ʈ
	UPROPERTY()
	UGE_PlayerAlive* GE_PlayerAlive;

	//�÷��̾� ���� ���� �����Ƽ
	UPROPERTY()
	TSubclassOf<UGA_Resurrection> GA_Resurrection;
protected:

	//ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;



	//ĳ���� �̵�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
		float MaxSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
		float CurMoveForward;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
		float CurMoveRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
		float PreMoveForward;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
		float PreMoveRight;



	//ĳ���� ȸ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	bool bIsRoll;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float RollTimer;



	//���ͷ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
		class UBoxComponent* Interaction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
		class AActor* InteractionActor;

	

	//�����Ƽ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbility)
		TSubclassOf<UGameplayAbility> WeaponAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbility)
		TSubclassOf<UGameplayAbility> Combo1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbility)
		TSubclassOf<UGameplayAbility> Combo2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbility)
		TSubclassOf<UGameplayAbility> UseSpell1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbility)
		TSubclassOf<UGameplayAbility> UseSpell2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbility)
		TSubclassOf<UGameplayAbility> UseSpell3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbility)
		TSubclassOf<UGameplayAbility> UseSpell4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbility)
		TSubclassOf<UGameplayAbility> SpecialCommand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbility)
		TSubclassOf<UGameplayAbility> Roll_Ability;
	
	//�߰��� ��ų�� ���� �� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbility)
		TArray<TSubclassOf<UGameplayAbility>> ExtraSkill;



	//���� ��ƼŬ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Buff)
	UParticleSystemComponent* SpeedUpFX_Component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Buff)
	UParticleSystem* SpeedUpFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Buff)
	UParticleSystemComponent* SlowFX_Component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Buff)
	UParticleSystem* SlowFX;



	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dead)
	UParticleSystemComponent* DeadFX_Component;


	//��Ȱ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alive)
	UParticleSystemComponent* AliveFX_Component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alive)
	UParticleSystem* AliveFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alive)
	USoundWave* AliveSound;

	public:

private:
	

	void RollTimeUpdate(float DeltaTime);
	void InvincibilityTimeUpdate(float DeltaTime);
	void StunTimeUpdate(float DeltaTime);
	void SlowTimeUpdate(float DeltaTime);
	void FastTimeUpdate(float DeltaTime);

protected:
	APlayerCharacter();
	//�⺻ �����Լ�
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//�̵����� �Լ�
	void MoveForward(float Value);
	void MoveRight(float Value);
	
	//ī�޶� ���� �Լ�
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	//�����Ƽ �ý��ۿ� �����Ƽ �ο��ϴ� �Լ�
	void BindAbilitySystemAndAbilityInput();


	//�뽬
	virtual void DashPressed();
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_DashPressed();
	virtual void ServerRPC_DashPressed_Implementation();
	virtual bool ServerRPC_DashPressed_Validate() { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void Multicast_DashPressed();
	virtual void Multicast_DashPressed_Implementation();
	virtual bool Multicast_DashPressed_Validate() { return true; }
	
	virtual void DashReleased();
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_DashReleased();
	virtual void ServerRPC_DashReleased_Implementation();
	virtual bool ServerRPC_DashReleased_Validate() { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void Multicast_DashReleased();
	virtual void Multicast_DashReleased_Implementation();
	virtual bool Multicast_DashReleased_Validate() { return true; }


	//ȸ��
	void Roll();
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_Roll(CC PrevState);
	virtual void ServerRPC_Roll_Implementation(CC PrevState);
	virtual bool ServerRPC_Roll_Validate(CC PrevState) { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void Multicast_Roll(CC PrevState);
	virtual void Multicast_Roll_Implementation(CC PrevState);
	virtual bool Multicast_Roll_Validate(CC PrevState) { return true; }

	
	//����
	virtual void Attack();
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_Attack();
	virtual void ServerRPC_Attack_Implementation();
	virtual bool ServerRPC_Attack_Validate() { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void MulticastRPC_Attack();
	virtual void MulticastRPC_Attack_Implementation();
	virtual bool MulticastRPC_Attack_Validate() { return true; }
	
	//Ư������
	virtual void SpecialCommandAttack();
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_SpecialCommandAttack();
	virtual void ServerRPC_SpecialCommandAttack_Implementation();
	virtual bool ServerRPC_SpecialCommandAttack_Validate() { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void MulticastRPC_SpecialCommandAttack();
	virtual void MulticastRPC_SpecialCommandAttack_Implementation();
	virtual bool MulticastRPC_SpecialCommandAttack_Validate() { return true; }


	//��ų1
	void Skill1();
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_Skill1();
	virtual void ServerRPC_Skill1_Implementation();
	virtual bool ServerRPC_Skill1_Validate() { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void MulticastRPC_Skill1();
	virtual void MulticastRPC_Skill1_Implementation();
	virtual bool MulticastRPC_Skill1_Validate() { return true; }

	//��ų2
	void Skill2();
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_Skill2();
	virtual void ServerRPC_Skill2_Implementation();
	virtual bool ServerRPC_Skill2_Validate() { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void MulticastRPC_Skill2();
	virtual void MulticastRPC_Skill2_Implementation();
	virtual bool MulticastRPC_Skill2_Validate() { return true; }

	//��ų3
	void Skill3();
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_Skill3();
	virtual void ServerRPC_Skill3_Implementation();
	virtual bool ServerRPC_Skill3_Validate() { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void MulticastRPC_Skill3();
	virtual void MulticastRPC_Skill3_Implementation();
	virtual bool MulticastRPC_Skill3_Validate() { return true; }

	//��ų4
	void Skill4();
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_Skill4();
	virtual void ServerRPC_Skill4_Implementation();
	virtual bool ServerRPC_Skill4_Validate() { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void MulticastRPC_Skill4();
	virtual void MulticastRPC_Skill4_Implementation();
	virtual bool MulticastRPC_Skill4_Validate() { return true; }


	//��ȣ�ۿ�
	void InteractionAction();
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_InteractionAction();
	virtual void ServerRPC_InteractionAction_Implementation();
	virtual bool ServerRPC_InteractionAction_Validate() { return true; }


	//��Ȱ
	void Revive();
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_Revive(APlayerCharacter* PlayerCharacter);
	virtual void ServerRPC_Revive_Implementation(APlayerCharacter* PlayerCharacter);
	virtual bool ServerRPC_Revive_Validate(APlayerCharacter* PlayerCharacter) { return true; }
	

	//�̵��ӵ� ���� ����
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_Fast(float Time);
	virtual void ServerRPC_Fast_Implementation(float Time);
	virtual bool ServerRPC_Fast_Validate(float Time) { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void MulticastRPC_Fast(float Time);
	virtual void MulticastRPC_Fast_Implementation(float Time);
	virtual bool MulticastRPC_Fast_Validate(float Time) { return true; }

	//�̵��ӵ� ���� ����
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_Slow(float Time);
	virtual void ServerRPC_Slow_Implementation(float Time);
	virtual bool ServerRPC_Slow_Validate(float Time) { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void MulticastRPC_Slow(float Time);
	virtual void MulticastRPC_Slow_Implementation(float Time);
	virtual bool MulticastRPC_Slow_Validate(float Time) { return true; }

	//����
	UFUNCTION()
	virtual void Stun(float Time);

	//����
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_Invincibility(float Time, CC PrevState);
	virtual void ServerRPC_Invincibility_Implementation(float Time, CC PrevState);
	virtual bool ServerRPC_Invincibility_Validate(float Time, CC PrevState) { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void MulticastRPC_Invincibility(float Time, CC PrevState);
	virtual void MulticastRPC_Invincibility_Implementation(float Time, CC PrevState);
	virtual bool MulticastRPC_Invincibility_Validate(float Time, CC PrevState) { return true; }


	//����
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_Dead();
	virtual void ServerRPC_Dead_Implementation();
	virtual bool ServerRPC_Dead_Validate() { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void MulticastRPC_Dead();
	virtual void MulticastRPC_Dead_Implementation();
	virtual bool MulticastRPC_Dead_Validate() { return true; }


	//��Ƴ���
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void ServerRPC_Alive();
	virtual void ServerRPC_Alive_Implementation();
	virtual bool ServerRPC_Alive_Validate() { return true; }
	UFUNCTION(NetMulticast, WithValidation, Reliable)
	virtual void MulticastRPC_Alive();
	virtual void MulticastRPC_Alive_Implementation();
	virtual bool MulticastRPC_Alive_Validate() { return true; }

	//ü�� ���� �Լ�
	void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	public:
	
	float GetCurMoveForward() { return CurMoveForward; }
	float GetCurMoveRight() { return CurMoveRight; }

	bool GetIsRoll(){return bIsRoll;}
	void SetIsRoll(bool _bIsRoll) { bIsRoll = _bIsRoll; }
};
