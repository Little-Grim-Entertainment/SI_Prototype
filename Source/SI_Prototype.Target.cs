// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SI_PrototypeTarget : TargetRules
{
	public SI_PrototypeTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("SI_Prototype");
		ExtraModuleNames.Add("SI_Editor");
		ExtraModuleNames.Add("DialogueSystemEditor");
	}
}
