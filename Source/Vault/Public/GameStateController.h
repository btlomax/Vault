// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "EGamePhase.h"
#include "GameStateController.generated.h"

// Delegate to notify listeners when the phase changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePhaseChanged, EGamePhase, NewPhase);

/**
 * 
 */
UCLASS()
class VAULT_API AGameStateController : public AGameStateBase
{
	GENERATED_BODY()

public:

	AGameStateController();

	UPROPERTY(BlueprintReadOnly, Category = "Game Phase")
	EGamePhase CurrentPhase;

	UPROPERTY(BlueprintAssignable, Category = "Game Phase")
	FOnGamePhaseChanged OnGamePhaseChanged;

	// Function to set the current game phase
	UFUNCTION(BlueprintCallable, Category = "Game Phase")
	void SetCurrentPhase(EGamePhase NewPhase);
};
