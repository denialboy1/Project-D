// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Project_DEditorTarget : TargetRules
{
	public Project_DEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        ExtraModuleNames.AddRange(new string[] { "Project_D", "Project_D_Character", "Project_D_Ability" });
        //ExtraModuleNames.AddRange(new string[] { "Project_D_Character" });

    }
}
