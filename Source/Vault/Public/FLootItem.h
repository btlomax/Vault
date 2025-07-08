// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FLootItem.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FLootItem
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot Item")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot Item")
	float Probability;

};

