// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeController.h"
#include "GameStateController.h"

AGameModeController::AGameModeController()
{
	// Set this controller to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GameStateClass = AGameStateController::StaticClass();
}

void AGameModeController::SetGamePhase(EGamePhase NewPhase)
{
	AGameStateController* gameState = GetGameState<AGameStateController>();

	if (gameState)
	{
		gameState->SetCurrentPhase(NewPhase);
	}
}

EGamePhase AGameModeController::GetCurrentPhase() const
{
	AGameStateController* gameState = GetGameState<AGameStateController>();

	if (gameState)
	{
		return gameState->CurrentPhase;
	}
	return EGamePhase::Planning;
}

