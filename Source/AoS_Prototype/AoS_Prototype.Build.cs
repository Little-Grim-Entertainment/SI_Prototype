// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AoS_Prototype : ModuleRules
{
	public AoS_Prototype(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "SlateCore", "DlgSystem", "MoviePlayer" });
	}
}
