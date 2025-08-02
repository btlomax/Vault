// Fill out your copyright notice in the Description page of Project Settings.


#include "APlayerVan.h"
#include <PlayerCharacter.cpp>

// Sets default values
AAPlayerVan::AAPlayerVan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAPlayerVan::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAPlayerVan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAPlayerVan::OpenPlanningUI(AActor* Player)
{
	APlayerController* PC = Cast<APlayerController>(Player->GetInstigatorController());

	if (PC)
	{
		FInputModeUIOnly InputMode;
		PC->SetInputMode(InputMode);
	}
}

void AAPlayerVan::ClosePlanningUI(AActor* Player)
{
	APlayerController* PC = Cast<APlayerController>(Player->GetInstigatorController());
	if (PC)
	{
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
	}
}