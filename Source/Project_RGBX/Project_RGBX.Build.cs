// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_RGBX : ModuleRules
{
	public Project_RGBX(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
