// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Project_RGBXCharacter.h"
#include "Project_RGBXGameMode.generated.h"

UENUM(BlueprintType)
enum class EFighterTag : uint8
{
	VE_Dummy UMETA(DisplayName = "Dummy"),
	VE_Shoto UMETA(DisplayName = "Shoto"),
	VE_Charge UMETA(DisplayName = "Charge"),
	VE_Rekka UMETA(DisplayName = "Rekka"),
	VE_Zoner UMETA(DisplayName = "Zoner"),
	VE_Rushdown UMETA(DisplayName = "Rushdown"),
	VE_Grappler UMETA(DisplayName = "Grappler")
};

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



