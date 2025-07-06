// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateController.h"

AGameStateController::AGameStateController()
{
	CurrentPhase = EGamePhase::Planning;
}

void AGameStateController::SetCurrentPhase(EGamePhase NewPhase)
{
	if (CurrentPhase != NewPhase)
	{
		CurrentPhase = NewPhase;

		OnGamePhaseChanged.Broadcast(CurrentPhase);
	}
}