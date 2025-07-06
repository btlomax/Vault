// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "InteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteracted, AActor*, InteractingPlayer);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAULT_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableComponent();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact(AActor* InteractingActor);

	// Show the prompt on screen
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ShowPrompt();

	// Hide the prompt
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void HidePrompt();

	UPROPERTY(BlueprintAssignable, Category = "Interactable")
	FOnInteracted OnInteracted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	TSubclassOf<UWidgetComponent> PromptWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	UWidgetComponent* FrontPromptWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	UWidgetComponent* RearPromptWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	UWidgetComponent* DoorLockStateWidget;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
