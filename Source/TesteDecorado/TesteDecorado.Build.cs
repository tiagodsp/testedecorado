// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class TesteDecorado : ModuleRules
{

    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    //ThirdParty folder direcotory
    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }


	public TesteDecorado(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        bEnableExceptions = true;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Include third party libraries
        if(Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicIncludePaths.AddRange(new string[] {
                Path.Combine(ThirdPartyPath, "websocketpp", "includes"),
                Path.Combine(ThirdPartyPath, "boost_1_65_1", "includes")
            });

            PublicLibraryPaths.AddRange(new string[] {
                Path.Combine(ThirdPartyPath, "boost_1_65_1", "lib64-msvc-14.0")
            });

        }
	}
}
