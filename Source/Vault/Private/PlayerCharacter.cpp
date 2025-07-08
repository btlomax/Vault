// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include <InteractableComponent.h>

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Get the local player controller and enable input
	DoorKeys = FMath::Clamp(DoorKeys, 0, 5);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector Start = GetActorLocation() + FVector(0, 0, 50);
    // To make the forward vector point slightly downward (diagonal), add a small negative Z component and normalize:
    FVector Forward = (GetActorForwardVector() + FVector(0, 0, -0.5f)).GetSafeNormal();
	FVector End = Start + (Forward * 200.f);              

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility,
		Params
	);

	if (bHit && Hit.GetActor())
	{
		UInteractableComponent* Interactable = Hit.GetActor()->FindComponentByClass<UInteractableComponent>();

		if (Interactable != CurrentInteractableComponent)
		{
			// Hide prompt on old interactable (if valid)
			if (CurrentInteractableComponent)
			{
				CurrentInteractableComponent->HidePrompt();
			}

			// Update current interactable and show new prompt (if valid)
			CurrentInteractableComponent = Interactable;

			if (CurrentInteractableComponent)
			{
				CurrentInteractableComponent->ShowPrompt();
				GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Blue, TEXT("Hit something interactable"));
			}
		}
	}
	else
	{
		// No hit: hide prompt and clear current interactable
		if (CurrentInteractableComponent)
		{
			CurrentInteractableComponent->HidePrompt();
			CurrentInteractableComponent = nullptr;
		}
	}
	

	const FColor LineColor = bHit ? FColor::Green : FColor::Red;

	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, 0, 1.0f);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(ZoomInAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ZoomIn);
		EnhancedInputComponent->BindAction(ZoomOutAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ZoomOut);

		//Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
	}
}

void APlayerCharacter::ZoomIn(const FInputActionValue& Value)
{
	// input is a float
	float ZoomValue = Value.Get<float>();

	// Adjust the camera boom length based on the zoom value
	if (CameraBoom)
	{
		CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength + (ZoomValue * 5), 150.f, 1200.f);
	}
}

void APlayerCharacter::ZoomOut(const FInputActionValue& Value)
{
	// input is a float
	float ZoomValue = Value.Get<float>();

	// Adjust the camera boom length based on the zoom value
	if (CameraBoom)
	{
		CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength - (ZoomValue * 5), 150.f, 1200.f);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void APlayerCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void APlayerCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void APlayerCharacter::Interact()
{
	if (CurrentInteractableComponent)
	{
		CurrentInteractableComponent->Interact(this);
	}
}



