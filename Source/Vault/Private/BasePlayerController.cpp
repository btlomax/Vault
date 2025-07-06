// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	// Ensure the DefaultMappingContext is valid
	if (DefaultMappingContext == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("DefaultMappingContext is not set in ABasePlayerController! Please assign a valid Input Mapping Context."));
		return;
	}
	// Add the DefaultMappingContext to the player's input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}