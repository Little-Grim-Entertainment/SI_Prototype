// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AoS_PlayerController.h"
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
	
	InputComponent->BindAxis("MoveForward", this, &AAoS_PlayerController::RequestMoveForward);
	InputComponent->BindAxis("MoveRight", this, &AAoS_PlayerController::RequestMoveRight);

	InputComponent->BindAxis("TurnRate", this, &AAoS_PlayerController::RequestTurnRight);
	InputComponent->BindAxis("LookUpRate", this, &AAoS_PlayerController::RequestLookUp);
}

void AAoS_PlayerController::BeginPlay()
{
	if (PlayerHUD_Class)
	{
		PlayerHUD = CreateWidget<UAoS_HUD>(GetWorld()->GetFirstPlayerController(), PlayerHUD_Class, "PlayerHUD");
		ShowHUD();
	}

	Super::BeginPlay();
}

void AAoS_PlayerController::RequestMoveForward(float Value)
{
	if  (!bPlayerCanMove) return;
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
	if  (!bPlayerCanMove) return;
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
	if  (!bPlayerCanTurn) return;
	AddPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAoS_PlayerController::RequestTurnRight(float AxisValue)
{
	if  (!bPlayerCanTurn) return;
	AddYawInput(AxisValue * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAoS_PlayerController::RequestInteract()
{
	if (!FocusedActor) {return;}
	OnInteractPressed(FocusedActor, this);
}

void AAoS_PlayerController::AddToInteractableActors(AActor* ActorToAdd)
{
	InteractableActors.AddUnique(ActorToAdd);
	OnInteractableActorAdded.Broadcast(InteractableActors);
}

void AAoS_PlayerController::RemoveFromInteractableActors(AActor* ActorToRemove)
{
	InteractableActors.Remove(ActorToRemove);
	if (InteractableActors.Num() == 0)
	{
		OnInteractableActorRemoved.Broadcast();
	}
}

UAoS_HUD* AAoS_PlayerController::GetPlayerHUD()
{
	if (!PlayerHUD) {return nullptr;}
	return PlayerHUD;
}

void AAoS_PlayerController::ShowHUD()
{
	if (!PlayerHUD) {return;}
	PlayerHUD->AddToViewport();
}

void AAoS_PlayerController::HideHUD()
{
	if (!PlayerHUD) {return;}
	PlayerHUD->RemoveFromViewport();
}

void AAoS_PlayerController::RefreshHUD()
{
	HideHUD();
	ShowHUD();
}

void AAoS_PlayerController::LockPlayerMovement(bool bLockMovement, bool bLockTurning)
{
	bPlayerCanMove = !bLockMovement;
	bPlayerCanTurn = !bLockTurning;
}

void AAoS_PlayerController::SetFocusedActor(AActor* ActorToSet)
{
	if (ActorToSet)
	{
		FocusedActor = ActorToSet;
		OnInteractableActorFound(FocusedActor);
	}
	else
	{
		OnInteractableActorLost(FocusedActor);
		FocusedActor = nullptr;
	}
}
