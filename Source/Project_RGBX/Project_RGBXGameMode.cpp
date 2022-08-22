// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_RGBXGameMode.h"
#include "Project_RGBXCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_RGBXGameMode::AProject_RGBXGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	player1 = nullptr;
	player2 = nullptr;
}
