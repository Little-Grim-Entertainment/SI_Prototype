// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DialogueSystemEditor : ModuleRules
{
	public DialogueSystemEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UnrealEd", "GenericGraphRuntime", "AoS_Prototype" });

        PublicIncludePaths.AddRange(new string[] { "AoS_Prototype/Public" });
    }
}
