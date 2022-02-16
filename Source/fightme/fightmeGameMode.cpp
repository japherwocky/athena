// Copyright Epic Games, Inc. All Rights Reserved.

#include "fightmeGameMode.h"
#include "fightmeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AfightmeGameMode::AfightmeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
