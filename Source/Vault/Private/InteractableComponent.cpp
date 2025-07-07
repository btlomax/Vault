// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	

	// ...
}


// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	
	if(FrontPromptWidget)
		FrontPromptWidget->SetHiddenInGame(true);

	if(RearPromptWidget)
		RearPromptWidget->SetHiddenInGame(true);

	// ...
	
}


// Called every frame
void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractableComponent::Interact(AActor* InteractingActor)
{
	OnInteracted.Broadcast(InteractingActor);
}

void UInteractableComponent::ShowPrompt()
{
	if (FrontPromptWidget)
	{
		FrontPromptWidget->SetHiddenInGame(false);
	}

	if (RearPromptWidget)
	{
		RearPromptWidget->SetHiddenInGame(false);
	}

	if(DoorLockStateWidget)
	{
		DoorLockStateWidget->SetHiddenInGame(false);
	}
}

void UInteractableComponent::HidePrompt()
{
	if (FrontPromptWidget)
	{
		FrontPromptWidget->SetHiddenInGame(true);
	}

	if (RearPromptWidget)
	{
		RearPromptWidget->SetHiddenInGame(true);
	}

	if(DoorLockStateWidget)
	{
		DoorLockStateWidget->SetHiddenInGame(true);
	}
}

