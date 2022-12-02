// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AoS_Prototype : ModuleRules
{
	public AoS_Prototype(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "GenericGraphRuntime" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Slate", "SlateCore", "MoviePlayer", "UMG", "LevelSequence", "MovieScene", "MediaAssets" });
	}
}
