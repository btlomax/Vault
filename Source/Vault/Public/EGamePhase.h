// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EGamePhase.generated.h"

/**
 * 
 */

 /// Enum representing the different phases of the game
UENUM(BlueprintType)
enum class EGamePhase : uint8
{
	Planning UMETA(DisplayName = "Planning"),
	Recon UMETA(DisplayName = "Recon"),
	Heist UMETA(DisplayName = "Heist"),
	Escape UMETA(DisplayName = "Escape"),
	GameOver UMETA(DisplayName = "Game Over")
};
