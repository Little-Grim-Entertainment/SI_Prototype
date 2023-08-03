// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LGDebug : ModuleRules
{
	public LGDebug(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateDependencyModuleNames.AddRange(new string[] {
				"GameplayTags",
		});
		
		PublicDependencyModuleNames.AddRange(new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UMG",
		});
	}
}
