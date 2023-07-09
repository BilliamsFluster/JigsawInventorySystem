// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JigsawInventory : ModuleRules
{
	public JigsawInventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG" });
	}
}
