// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability/AttributeSet_Monster.h"

void UAttributeSet_Monster::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAttributeSet_Monster, WarriorAgro);
	DOREPLIFETIME(UAttributeSet_Monster, ArcherAgro);
	DOREPLIFETIME(UAttributeSet_Monster, MagicianAgro);
	DOREPLIFETIME(UAttributeSet_Monster, AssassinAgro);
	DOREPLIFETIME(UAttributeSet_Monster, WarriorMaxAgro);
	DOREPLIFETIME(UAttributeSet_Monster, ArcherMaxAgro);
	DOREPLIFETIME(UAttributeSet_Monster, MagicianMaxAgro);
	DOREPLIFETIME(UAttributeSet_Monster, AssassinMaxAgro);
}

void UAttributeSet_Monster::OnRep_WarriorAgro()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Monster, WarriorAgro,0);
}

void UAttributeSet_Monster::OnRep_ArcherAgro()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Monster, ArcherAgro, 0);
}

void UAttributeSet_Monster::OnRep_MagicianAgro()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Monster, MagicianAgro, 0);
}

void UAttributeSet_Monster::OnRep_AssassinAgro()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Monster, AssassinAgro, 0);
}

void UAttributeSet_Monster::OnRep_WarriorMaxAgro()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Monster, WarriorMaxAgro, 0);
}

void UAttributeSet_Monster::OnRep_ArcherMaxAgro()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Monster, ArcherMaxAgro, 0);
}

void UAttributeSet_Monster::OnRep_MagicianMaxAgro()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Monster, MagicianMaxAgro, 0);
}

void UAttributeSet_Monster::OnRep_AssassinMaxAgro()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Monster, AssassinMaxAgro, 0);
}