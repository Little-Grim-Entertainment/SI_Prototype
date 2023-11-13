// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SI_Prototype : ModuleRules
{
	public SI_Prototype(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { 
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"GameplayStateTreeModule",
			"StateTreeModule"
		});
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"AdvancedThirdPersonCamera",
			"AIModule",
			"Core", 
			"CoreUObject",
			"Engine",
			"GameplayAbilities",
			"InputCore",
			"LevelSequence",
			"MediaAssets",
			"MoviePlayer",
			"MovieScene", 
			"NavigationSystem", 
			"Slate", 
			"SlateCore",
			"UMG", 
			"LGDebug", 
			"StateTreeModule" 
		});
	}
}
