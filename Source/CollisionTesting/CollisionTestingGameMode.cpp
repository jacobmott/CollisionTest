// Copyright Epic Games, Inc. All Rights Reserved.

#include "CollisionTestingGameMode.h"
#include "CollisionTestingPawn.h"

ACollisionTestingGameMode::ACollisionTestingGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ACollisionTestingPawn::StaticClass();
}

