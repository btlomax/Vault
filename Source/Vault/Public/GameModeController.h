// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EGamePhase.h"
#include "GameModeController.generated.h"

/**
 * 
 */
UCLASS()
class VAULT_API AGameModeController : public AGameModeBase
{
	GENERATED_BODY()

public:

	AGameModeController();

	// Advance to new phase
	UFUNCTION(BlueprintCallable, Category = "Game Phase")
	void SetGamePhase(EGamePhase NewPhase);

	UFUNCTION(BlueprintCallable, Category = "Game Phase")
	EGamePhase GetCurrentPhase() const;
	
};
