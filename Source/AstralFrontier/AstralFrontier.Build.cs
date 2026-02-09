// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class AstralFrontier : ModuleRules
{
	public AstralFrontier(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        CppCompileWarningSettings.UndefinedIdentifierWarningLevel = WarningLevel.Off;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "NetCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		string SQLitePath = Path.Combine(ModuleDirectory, "ThirdParty", "SQLite");

		PublicIncludePaths.Add(SQLitePath);

		// Ensure sqlite3.c is compiled
		PrivateDefinitions.Add("SQLITE_THREADSAFE=1");
		PrivateDefinitions.Add("SQLITE_ENABLE_FTS5=1");
		PrivateDefinitions.Add("SQLITE_ENABLE_JSON1=1");

        PrivateDefinitions.Add("SQLITE_OS_WIN=1");
        PrivateDefinitions.Add("SQLITE_OS_UNIX=0");
        PrivateDefinitions.Add("SQLITE_OS_OTHER=0");
        PrivateDefinitions.Add("SQLITE_OS_KV=0");


        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
