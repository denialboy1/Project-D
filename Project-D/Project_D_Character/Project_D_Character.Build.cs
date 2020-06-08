// Fill out your copyright notice in the Description page of Project Settings. 

using UnrealBuildTool;

public class Project_D_Character : ModuleRules
{
	public Project_D_Character(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "Core", "CoreUObject", "Engine", "InputCore", "GameplayTasks", "Project_D_Ability","UMG","Project_D" });

		DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
	}
}
