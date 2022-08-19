// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Project_RGBXCharacter.h"
#include "Project_RGBXGameMode.generated.h"


UCLASS(minimalapi)
class AProject_RGBXGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProject_RGBXGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AProject_RGBXCharacter* player1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AProject_RGBXCharacter* player2;

};



