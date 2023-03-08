// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UELiveVideoExample : ModuleRules
{
	public UELiveVideoExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "MediaAssets", "UMG" });
	}
}
