// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerVan.h"

// Sets default values
APlayerVan::APlayerVan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerVan::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerVan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

