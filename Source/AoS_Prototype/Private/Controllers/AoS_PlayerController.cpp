// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AoS_PlayerController.h"

#include "AoS_GameInstance.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "Characters/AoS_Nick.h"
#include "Interfaces/AoS_InteractInterface.h"
#include "UI/AoS_HUD.h"

AAoS_PlayerController::AAoS_PlayerController()
{
	LineTraceComponent = CreateDefaultSubobject<UAoS_LineTraces>(TEXT("LineTraceComponent"));
	
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
}

void AAoS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Interact", IE_Pressed,this, &AAoS_PlayerController::RequestInteract);
	InputComponent->BindAction("ObservationMode", IE_Pressed,this, &AAoS_PlayerController::RequestObservation);
	InputComponent->BindAxis("MoveForward", this, &AAoS_PlayerController::RequestMoveForward);
	InputComponent->BindAxis("MoveRight", this, &AAoS_PlayerController::RequestMoveRight);
	InputComponent->BindAxis("TurnRate", this, &AAoS_PlayerController::RequestTurnRight);
	InputComponent->BindAxis("LookUpRate", this, &AAoS_PlayerController::RequestLookUp);
}

void AAoS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UAoS_GameInstance* GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstance))
	{
		
	}

	Nick = Cast<AAoS_Nick>(GetPawn()); 
}

void AAoS_PlayerController::RequestMoveForward(float Value)
{
	if  (!bPlayerCanMove || !GetPawn()) return;
	if ((Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		GetPawn()->AddMovementInput(Direction, Value);
	}
}

void AAoS_PlayerController::RequestMoveRight(float Value)
{
	if  (!bPlayerCanMove || !GetPawn()) return;
	if ((Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		GetPawn()->AddMovementInput(Direction, Value);
	}
}

void AAoS_PlayerController::RequestLookUp(float AxisValue)
{
	if  (!bPlayerCanTurn || !GetPawn()) return;
	AddPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAoS_PlayerController::RequestTurnRight(float AxisValue)
{
	if  (!bPlayerCanTurn || !GetPawn()) return;
	AddYawInput(AxisValue * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAoS_PlayerController::RequestInteract()
{
	if (!GetPawn() || !IsValid(FocusedActor)) {return;}

	if (IAoS_InteractInterface* InteractableActor = Cast<IAoS_InteractInterface>(FocusedActor))
	{
		InteractableActor->Execute_OnInteract(Cast<UObject>(FocusedActor), FocusedActor);
		OnInteractPressed.Broadcast(FocusedActor, this);
	}
}

void AAoS_PlayerController::RequestObservation()
{
	bObservationMode = !bObservationMode;
	
	UAoS_GameInstance* GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	
	if(bObservationMode)
	{
		GameInstance->SetPlayerMode(EPlayerMode::PM_ObservationMode);
		LockPlayerMovement(true, false);
	}
	else
	{
		GameInstance->SetPlayerMode(EPlayerMode::PM_ExplorationMode);
		LockPlayerMovement(false, false);
	}

	Nick->GetFollowCamera()->SetActive(!bObservationMode);
	Nick->GetObservationCamera()->SetActive(bObservationMode);
	
	Nick->bUseControllerRotationPitch = bObservationMode;
	Nick->bUseControllerRotationYaw = bObservationMode;
}

void AAoS_PlayerController::LockPlayerMovement(bool bLockMovement, bool bLockTurning)
{
	bPlayerCanMove = !bLockMovement;
	bPlayerCanTurn = !bLockTurning;
}

void AAoS_PlayerController::SetFocusedActor(AActor* InActorToFocus)
{
	if (IsValid(InActorToFocus))
	{
		FocusedActor = InActorToFocus;
	}
}
