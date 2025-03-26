// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteamforgeGameMode.h"
#include "SteamforgeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASteamforgeGameMode::ASteamforgeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
