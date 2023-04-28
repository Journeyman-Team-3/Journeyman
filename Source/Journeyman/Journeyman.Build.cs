// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Journeyman : ModuleRules
{
	public Journeyman(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule", "UnrealEd" });
	}
}
