// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeManager.generated.h"

// Delegate for when time changes (to update UI)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeChangedSignature, float, CurrentTime);

// Delegate for when end time is reached
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndTimeReachedSignature);

UCLASS()
class VAULT_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    /** Current in-game time in hours, e.g., 9.5 = 9:30 AM */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    float CurrentTime;

    /** Speed multiplier: 60 means 1 real second = 1 in-game minute */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    float TimeSpeed;

    /** When the timer starts (in hours) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    float StartTime;

    /** When the timer ends (in hours) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    float EndTime;

    /** Whether time is progressing */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    bool bTimerRunning;

    /** Delegate: called every time the clock updates */
    UPROPERTY(BlueprintAssignable, Category = "Time")
    FOnTimeChangedSignature OnTimeChanged;

    /** Delegate: called when EndTime is reached */
    UPROPERTY(BlueprintAssignable, Category = "Time")
    FOnEndTimeReachedSignature OnEndTimeReached;

};
