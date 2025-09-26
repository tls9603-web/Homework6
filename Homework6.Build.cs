// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Homework6 : ModuleRules
{
	public Homework6(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
