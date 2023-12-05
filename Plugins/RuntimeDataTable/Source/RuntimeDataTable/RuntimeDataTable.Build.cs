// Copyright Jared Therriault 2019, 2022

using UnrealBuildTool;
using System.IO;

public class RuntimeDataTable : ModuleRules
{
    private string ThirdPartyPath
    {
        get { return Path.Combine(PluginDirectory, "Source/ThirdParty"); }
    }
    
    public RuntimeDataTable(ReadOnlyTargetRules target) : base(target)
    {
        PrivateIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Private"), Path.Combine(ThirdPartyPath, "jwt-cpp") });
        PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Public") });
        
        PublicSystemIncludePaths.AddRange(
            new string[]
            {
                Path.Combine(ThirdPartyPath),
            }
        );

        PublicDependencyModuleNames.AddRange(new string[] { "Json", "JsonUtilities", "OpenSSL", "Slate", "SlateCore", "UMG", "EasyCsv" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject", "HTTP", "InputCore" });

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
    }
}
