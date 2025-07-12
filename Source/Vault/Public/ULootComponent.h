// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FLootItem.h"
#include "ULootComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAULT_API UULootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UULootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
	TArray<FLootItem> PossibleLoot;

	UPROPERTY(BlueprintReadOnly, Category = "Loot")
	TArray<FName> SelectedLoot;

	UFUNCTION(BlueprintCallable, Category = "Loot")
	void GenerateLoot();

	UFUNCTION(BlueprintCallable, Category = "Loot")
	void RemoveLoot(FName ItemID);
};
