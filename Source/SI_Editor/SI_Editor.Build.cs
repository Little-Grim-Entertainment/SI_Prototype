using UnrealBuildTool;

public class SI_Editor : ModuleRules
{
    public SI_Editor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Blutility",
                "Core",
                "GameplayTags",
                "UMG",
                "UnrealEd",
                
                // Plugins
                "RuntimeDataTable",
                "EasyCsv",
                
                // Spade Investigations
                "SI_Prototype",
                "SI_CsvDataProcessor",

                // Little Grim
                "LGCoreLibrary",
                "LGCsvDataProcessor",
                "LGDialogueSystem", 
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "InputCore",
                "LevelEditor",
                "PropertyEditor",
                "Slate",
                "SlateCore",
            }
        );
    }
}