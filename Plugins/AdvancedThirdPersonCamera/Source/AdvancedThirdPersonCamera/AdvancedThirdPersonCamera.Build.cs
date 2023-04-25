// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class AdvancedThirdPersonCamera : ModuleRules
	{
		public AdvancedThirdPersonCamera(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

			PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"GameplayTags",
				"CinematicCamera",
				"UMG",
				"GameplayCameras"
			}
			);
		}
	}
}
 
