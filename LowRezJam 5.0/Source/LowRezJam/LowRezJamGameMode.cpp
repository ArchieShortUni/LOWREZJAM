// Copyright Epic Games, Inc. All Rights Reserved.

#include "LowRezJamGameMode.h"
#include "LowRezJamPawn.h"

ALowRezJamGameMode::ALowRezJamGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ALowRezJamPawn::StaticClass();
}

