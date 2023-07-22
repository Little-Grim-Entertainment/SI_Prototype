// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DialogueSystemEditor : ModuleRules
{
	public DialogueSystemEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine", 
			"GenericGraphRuntime", 
		});

        PublicIncludePaths.AddRange(new string[]
        {
	        "SI_Prototype/Public"
        });
    }
}
