// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/Grux_Controller.h"
#include "Monster/Grux_Anim.h"
#include "Monster/Grux.h"

AGrux_Controller::AGrux_Controller()
{
	static const ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Characters/Monster/Grux/BTGrux.BTGrux"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AGrux_Controller::PlayDoublePain()
{
	Cast<AGrux>(GetCharacter())->CKDoublePain = false;
}

void AGrux_Controller::PlayStone()
{
}

void AGrux_Controller::PlayStampede()
{
}
