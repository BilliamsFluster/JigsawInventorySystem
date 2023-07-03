// Copyright Epic Games, Inc. All Rights Reserved.

#include "JigsawInventoryGameMode.h"
#include "JigsawInventoryCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJigsawInventoryGameMode::AJigsawInventoryGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
