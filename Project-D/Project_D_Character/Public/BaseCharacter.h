// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet_Character.h"
#include "Runtime/Engine/Classes/Animation/AnimMontage.h"
#include "BaseCharacter.generated.h"

UENUM(BlueprintType)
enum class CC : uint8 {
	INVINCIBILITY,	//무적
	STUN,			//스턴
	SLOW,			//슬로우
	FAST,			//이속증가
	NORMAL			//기본
};



UCLASS()
class PROJECT_D_CHARACTER_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

private:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	UAttributeSet_Character* AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	TArray<TSubclassOf<class UGameplayEffect>> PassiveGameplayEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAlive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* DeadAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	CC CharacterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	CC PrevCharacterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StunTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlowTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlowTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InvincibilityTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InvincibilityTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FastTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FastTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;
public:
	
private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	
public:	

	// Sets default values for this character's properties
	ABaseCharacter();

	// Implement IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void PossessedBy(AController * NewController) override;

	/** Returns current health, will be 0 if dead */
	UFUNCTION(BlueprintCallable)
	virtual float GetHealth() const;

	/** Returns maximum health, health will never be greater than this */
	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHealth() const;

	/** Returns current movement speed */
	UFUNCTION(BlueprintCallable)
	virtual float GetMoveSpeed() const;

	UFUNCTION()
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerHandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UFUNCTION(NetMulticast, Reliable)
	virtual void MultiHandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	
};
