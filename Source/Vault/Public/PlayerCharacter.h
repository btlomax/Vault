// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInteractableComponent;
struct FInputActionValue;

UCLASS()
class APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;

public:
    APlayerCharacter();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

    /** Handles move inputs from either controls or UI interfaces */
    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoMove(float Right, float Forward);

    /** Handles look inputs from either controls or UI interfaces */
    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoLook(float Yaw, float Pitch);

    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

    /** Returns FollowCamera subobject **/
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    TMap<FName, int32> Inventory;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddItemToInventory(FName ItemID, int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItemFromInventory(FName ItemID, int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItemInInventory(FName ItemID, int32 Quantity) const;

private:

    /** Interactable component for interaction with objects in the world */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	UInteractableComponent* CurrentInteractableComponent;

protected:
    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* MoveAction;

    /** Look Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* InteractAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* ZoomInAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* ZoomOutAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
    int DoorKeys;

    /** Initialize input action bindings */
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    /** Called for movement input */
    void Move(const FInputActionValue& Value);

    /** Called for looking input */
    void Look(const FInputActionValue& Value);

	void ZoomIn(const FInputActionValue& Value);

    void ZoomOut(const FInputActionValue& Value);

	void Interact();

};
