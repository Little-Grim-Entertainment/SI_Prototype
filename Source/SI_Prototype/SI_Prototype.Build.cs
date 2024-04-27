// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SI_Prototype : ModuleRules
{
	public SI_Prototype(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { 
			"CoreUObject",
			"Engine",
		});
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"AdvancedThirdPersonCamera",
			"AIModule",
			"Core", 
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"GameplayStateTreeModule",
			"InputCore",
			"LevelSequence",
			"MediaAssets",
			"MoviePlayer",
			"MovieScene", 
			"NavigationSystem",
			"Niagara", 
			"RuntimeDataTable",
			"Slate", 
			"SlateCore",
			"UMG",
			"StateTreeModule",
			"SmartObjectsModule",
			
			// LG Plugins
			"LGCoreLibrary",
			"LGDebug", 
			"LGDialogueSystem",
		});
	}
}
