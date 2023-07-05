// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SI_PrototypeEditorTarget : TargetRules
{
	public SI_PrototypeEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		
		ExtraModuleNames.Add("SI_Prototype");
		ExtraModuleNames.Add("SI_Editor");
		ExtraModuleNames.Add("DialogueSystemEditor");
	}
}
