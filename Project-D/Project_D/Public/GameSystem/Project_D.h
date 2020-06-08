// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"
DECLARE_LOG_CATEGORY_EXTERN(Project_D, Log, All)

#define PDLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define PDLOG_S (Verbosity) UE_LOG(Project_D, Verbosity, TEXT("%s"), *PDLOG_CALLINFO);
//#define PDLOG (Ve0rbosity, Format, ...) UE_LOG(Project_D, Verbosity, TEXT("%s %s"), *PDLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__));

#ifndef __NETWORKSESSIONTEST_H__
#define __NETWORKSESSIONTEST_H__

#include "Engine.h"
#include "UnrealNetwork.h"
#include "Online.h"
#endif
