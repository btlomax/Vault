// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EItemType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemType : uint8
{
	Lootable UMETA(DisplayName = "Lootable"),
	NonLootable UMETA(DisplayName = "Non-Lootable"),
};
