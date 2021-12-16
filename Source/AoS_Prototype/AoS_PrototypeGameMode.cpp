// Copyright Epic Games, Inc. All Rights Reserved.

#include "AoS_PrototypeGameMode.h"
#include "AoS_PrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAoS_PrototypeGameMode::AAoS_PrototypeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
