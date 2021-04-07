// Copyright Epic Games, Inc. All Rights Reserved.

#include "blockGameMode.h"
#include "blockPawn.h"

AblockGameMode::AblockGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AblockPawn::StaticClass();
}

