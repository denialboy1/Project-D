// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability/BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (HasAuthority()) {
		AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
		AbilitySystemComponent->SetIsReplicated(true);

		AttributeSet = CreateDefaultSubobject<UAttributeSet_Character>(TEXT("Attribute"));
	}
	IsAlive = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent == nullptr) return;

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AttributeSet) {
		if (GetHealth() <= 0) {
			if (IsAlive) {
				if (DeadAnimMontage) {
					PlayAnimMontage(DeadAnimMontage);
				}
			}
			IsAlive = false;
		}
	}
}


// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const 
{
	return AbilitySystemComponent;
}


void ABaseCharacter::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->RefreshAbilityActorInfo();
}


float ABaseCharacter::GetHealth() const
{
	return AttributeSet->GetHealth();
}

float ABaseCharacter::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

float ABaseCharacter::GetMoveSpeed() const
{
	return AttributeSet->GetMoveSpeed();
}

//void ABaseCharacter::HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
//{
//	// We only call the BP callback if this is not the initial ability setup
//	OnHealthChanged(DeltaValue, EventTags);
//}

void ABaseCharacter::HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	// We only call the BP callback if this is not the initial ability setup
	if (HasAuthority())
		MultiHandleHealthChanged(DeltaValue, EventTags);
	else
		ServerHandleHealthChanged(DeltaValue, EventTags);
}

void ABaseCharacter::ServerHandleHealthChanged_Implementation(float DeltaValue, const FGameplayTagContainer & EventTags)
{
	MultiHandleHealthChanged(DeltaValue, EventTags);
}

bool ABaseCharacter::ServerHandleHealthChanged_Validate(float DeltaValue, const FGameplayTagContainer & EventTags)
{
	return true;
}

void ABaseCharacter::MultiHandleHealthChanged_Implementation(float DeltaValue, const FGameplayTagContainer & EventTags)
{
	OnHealthChanged(DeltaValue, EventTags);
}
