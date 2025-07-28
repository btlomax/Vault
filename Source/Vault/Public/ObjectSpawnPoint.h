#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EItemType.h"
#include "ObjectSpawnPoint.generated.h"

UCLASS()
class VAULT_API AObjectSpawnPoint : public AActor
{
    GENERATED_BODY()

public:
    AObjectSpawnPoint();

protected:
    virtual void BeginPlay() override;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    EItemType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TSubclassOf<AActor> LootableActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    UStaticMesh* NonLootableActorClass;
};