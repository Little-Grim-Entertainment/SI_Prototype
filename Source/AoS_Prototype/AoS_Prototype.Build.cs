// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AoS_Prototype : ModuleRules
{
	public AoS_Prototype(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { 
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"GenericGraphRuntime",
		});
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"AdvancedThirdPersonCamera",
			"AIModule",
			"Core", 
			"CoreUObject",
			"Engine",
			"InputCore",
			"LevelSequence",
			"MediaAssets",
			"MoviePlayer",
			"MovieScene", 
			"NavigationSystem", 
			"Slate", 
			"SlateCore", 
			"UMG",
		});
	}
}
