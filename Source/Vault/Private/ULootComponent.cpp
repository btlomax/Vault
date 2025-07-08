// Fill out your copyright notice in the Description page of Project Settings.


#include "ULootComponent.h"

// Sets default values for this component's properties
UULootComponent::UULootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UULootComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UULootComponent::GenerateLoot()
{
    SelectedLoot.Empty();

    for (const FLootItem& Item : PossibleLoot)
    {
        if (FMath::FRand() <= Item.Probability)
        {
            SelectedLoot.Add(Item.ItemID);
        }
    }
}

