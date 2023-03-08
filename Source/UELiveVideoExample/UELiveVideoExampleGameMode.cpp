// Copyright Epic Games, Inc. All Rights Reserved.

#include "UELiveVideoExampleGameMode.h"
#include "UELiveVideoExampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUELiveVideoExampleGameMode::AUELiveVideoExampleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
