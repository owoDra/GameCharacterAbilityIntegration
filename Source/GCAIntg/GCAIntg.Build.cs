// Copyright (C) 2023 owoDra

using UnrealBuildTool;

public class GCAIntg : ModuleRules
{
	public GCAIntg(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                ModuleDirectory,
                ModuleDirectory + "/GCAIntg",
            }
        );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "GameplayAbilities",
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "GCExt",
                "GAExt",
            }
        );

        SetupIrisSupport(Target);
    }
}
