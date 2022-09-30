// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

using System;
using System.IO;
using UnrealBuildTool;

public class HorizonUI : ModuleRules
{

   
    public HorizonUI(ReadOnlyTargetRules Target)
        : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Private/HorizonUIPrivate.h";
        // MinFilesUsingPrecompiledHeaderOverride = 1;
        //bFasterWithoutUnity = true;
        PublicDefinitions.Add("HORIZONUI_PACKAGE=1");
        PublicIncludePaths.AddRange(
            new string[] {
                // Path.Combine(ModuleDirectory, "Public"),
                // ... add public include paths required here ...
            }
            );


        PrivateIncludePaths.AddRange(
            new string[] {
                // Path.Combine(ModuleDirectory, "Private"),
                // ... add other private include paths required here ...
            }
            );

        // PublicDependencyModuleNames.AddRange(new string[] { });
        PublicDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UMG", "Paper2D" });
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
        PrivateDependencyModuleNames.AddRange(new string[] { "ImageWrapper", "XmlParser" });

        //if (Target.bBuildEditor)
        //{
        //    PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd" });
        //}

        DynamicallyLoadedModuleNames.AddRange(
		new string[]
		{
			// ... add any modules that your module loads dynamically here ...
		}
		);
        PublicDefinitions.Add("WITH_HORIZONUI=1");
    }
}
