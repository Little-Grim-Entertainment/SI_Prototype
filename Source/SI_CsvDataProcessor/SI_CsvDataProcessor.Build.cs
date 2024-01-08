using UnrealBuildTool;

public class SI_CsvDataProcessor : ModuleRules
{
    public SI_CsvDataProcessor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                // Unreal
                "Core", 
                "GameplayTags",

                // Plugins
                "RuntimeDataTable",
                "EasyCsv",
                
                // Spade Investigations
                "SI_Prototype",

                // Little Grim
                "LGCoreLibrary",
                "LGCsvDataProcessor",
                "LGDialogueSystem"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
            }
        );
    }
}