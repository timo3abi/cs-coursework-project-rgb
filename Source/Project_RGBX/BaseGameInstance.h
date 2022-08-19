// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EFighterTag : uint8
{
	VE_Canvas UMETA(DisplayName = "Canvas"),
	VE_Gris UMETA(DisplayName = "Gris"),
	VE_Mauve UMETA(DisplayName = "Mauve"),
	VE_Marigold UMETA(DisplayName = "Marigold"),
	VE_Azul UMETA(DisplayName = "Azul"),
	VE_Carmine UMETA(DisplayName = "Carmine"),
	VE_Jade UMETA(DisplayName = "Jade"),
	VE_Dummy UMETA(DisplayName = "Dummy")
};

UCLASS()
class PROJECT_RGBX_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	EFighterTag fighterTag;
};
