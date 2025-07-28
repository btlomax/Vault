// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSpawnPoint.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObjectSpawnPoint::AObjectSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AObjectSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	float RandomValue = FMath::FRandRange(0.0f, 1.0f);

	if(RandomValue > 0.5f)
	{
		ItemType = EItemType::Lootable;
	}
	else
	{
		ItemType = EItemType::NonLootable;
	}

	switch (ItemType)
	{
		case EItemType::Lootable:
			if(LootableActorClass)
			{
				GetWorld()->SpawnActor<AActor>(LootableActorClass, GetActorTransform());
			}

			break;

		case EItemType::NonLootable:
			if(NonLootableActorClass)
			{
				AStaticMeshActor* Mesh = GetWorld()->SpawnActor<AStaticMeshActor>(GetActorLocation(), GetActorRotation());

				if(Mesh)
					Mesh->GetStaticMeshComponent()->SetStaticMesh(NonLootableActorClass);
			}

			break;
	}
}



