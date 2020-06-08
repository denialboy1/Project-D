// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Project_DTarget : TargetRules
{
	public Project_DTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        ExtraModuleNames.AddRange(new string[] { "Project_D", "Project_D_Character", "Project_D_Ability" });
        //ExtraModuleNames.AddRange(new string[] { "Project_D_Character" });
    }
}
