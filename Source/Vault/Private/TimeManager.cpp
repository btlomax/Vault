// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"

// Sets default values
ATimeManager::ATimeManager()
{
    // Enable ticking
    PrimaryActorTick.bCanEverTick = true;

    // Defaults
    StartTime = 9.0f;       // 9 AM
    EndTime = 17.0f;        // 5 PM
    TimeSpeed = 0.4f;      // 20 mins
    bTimerRunning = true;
    CurrentTime = StartTime;

}

// Called when the game starts or when spawned
void ATimeManager::BeginPlay()
{
	Super::BeginPlay();

    // Initialize time
    CurrentTime = StartTime;
    bTimerRunning = true;

    // Notify UI of initial time
    OnTimeChanged.Broadcast(CurrentTime);
	
}

// Called every frame
void ATimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!bTimerRunning)
        return;

    // Advance time
    float MinutesToAdd = DeltaTime * TimeSpeed;
    float HoursToAdd = MinutesToAdd / 60.f;

    CurrentTime += HoursToAdd;

    // Broadcast time update for UI
    OnTimeChanged.Broadcast(CurrentTime);

    // Check if we've reached the end
    if (CurrentTime >= EndTime)
    {
        bTimerRunning = false;
        OnEndTimeReached.Broadcast();
    }
}

