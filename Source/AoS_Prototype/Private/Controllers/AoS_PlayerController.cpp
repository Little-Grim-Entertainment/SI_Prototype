// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AoS_PlayerController.h"

#include "AoS_GameInstance.h"
#include "Actors/AoS_InteractableActor.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Characters/AoS_Nick.h"
#include "Cinematics/AoS_CinematicsManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameModes/AoS_GameMode.h"
#include "Interfaces/AoS_InteractInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "MediaAssets/Public/MediaSoundComponent.h"
#include "UI/AoS_HUD.h"

AAoS_PlayerController::AAoS_PlayerController()
{
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	MediaSoundComponent = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("MediaSoundComponent"));
	MediaSoundComponent->SetupAttachment(RootComponent);
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
		GameInstance->OnPlayerModeChanged.AddDynamic(this, &ThisClass::OnPlayerModeChanged);
		OnPlayerModeChanged(GameInstance->GetPlayerMode());
	}

	Nick = Cast<AAoS_Nick>(GetPawn()); 
}

void AAoS_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(bObservationMode)
	{
		FHitResult HitResult;
		ObservationStart = Nick->GetObservationCamera()->GetComponentLocation();
		ObservationEnd = Nick->GetObservationCamera()->GetComponentLocation() + Nick->GetObservationCamera()->GetForwardVector() * ObservationDistance;
		GetWorld()->LineTraceSingleByChannel(HitResult, ObservationStart, ObservationEnd, ECC_Pawn);
		if(HitResult.GetActor())
		{
			AActor* HitActor = HitResult.GetActor();
			const bool bObservable = HitActor->ActorHasTag(FName(TEXT("Observable")));
			
			if(bObservable && HitActor != ObservableActor)
			{
				ObservableActor = HitActor;
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("On"));
			}
			else if(!bObservable && ObservableActor)
			{
				ObservableActor = nullptr;
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Off"));
			}
		}
		else if(ObservableActor)
		{
			ObservableActor = nullptr;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Off"));
		}
	}
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
	if (!GetPawn()) {return;}

	if(ObservableActor)
	{
		if (const IAoS_InteractInterface* InterfaceActor = Cast<IAoS_InteractInterface>(ObservableActor))
		{
			InterfaceActor->Execute_OnObserved(Cast<UObject>(ObservableActor), ObservableActor);
		}
	}
	else if(InteractableActor)
	{
		if (const IAoS_InteractInterface* InterfaceActor = Cast<IAoS_InteractInterface>(InteractableActor))
		{
			InterfaceActor->Execute_OnInteract(Cast<UObject>(InteractableActor), InteractableActor);
			OnInteractPressed.Broadcast(InteractableActor, this);
		}
	}
}

void AAoS_PlayerController::RequestObservation()
{
	bObservationMode = !bObservationMode;

	UCameraComponent* FollowCameraComponent = Nick->GetFollowCamera();
	UCameraComponent* ObservationCameraComponent = Nick->GetObservationCamera();

	const FVector FollowCamLocation = FollowCameraComponent->GetComponentLocation();
	const FRotator FollowCamRotation = FollowCameraComponent->GetComponentRotation();

	FVector ObservationCamLocation = ObservationCameraComponent->GetComponentLocation();
	const FRotator ObservationCamRotation = ObservationCameraComponent->GetComponentRotation();

	FVector ForwardVector = Nick->GetFollowCamera()->GetForwardVector();
	ObservationCamLocation *= ForwardVector;
	
	ACameraActor* FollowCameraActor = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), FollowCamLocation, FollowCamRotation);
	ACameraActor* ObservationCameraActor = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), ObservationCamLocation, ObservationCamRotation);
	
	UAoS_GameInstance* GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());

	float CameraTransitionTime = 0.25f;

	DisableInput(this);
	SetControlRotation(FRotator(0, Nick->GetActorRotation().Yaw, 0));
	Nick->SetActorRotation(FRotator(0., Nick->GetActorRotation().Yaw, 0));
	
	if(bObservationMode)
	{
		GameInstance->SetPlayerMode(EPlayerMode::PM_ObservationMode);
		LockPlayerMovement(true, false);
		SetViewTarget(FollowCameraActor);
		SetViewTargetWithBlend(ObservationCameraActor, CameraTransitionTime);
	}
	else
	{
		GameInstance->SetPlayerMode(EPlayerMode::PM_ExplorationMode);
		LockPlayerMovement(false, false);
		SetViewTarget(ObservationCameraActor);
		SetViewTargetWithBlend(FollowCameraActor, CameraTransitionTime);
	}

	CameraBlendDelegate = FTimerDelegate::CreateUObject(this, &AAoS_PlayerController::PostCameraBlend, FollowCameraActor, ObservationCameraActor);
	
	GetWorld()->GetTimerManager().SetTimer(CameraBlendHandle, CameraBlendDelegate, CameraTransitionTime, false);
}

void AAoS_PlayerController::PostCameraBlend(ACameraActor* InFollowCamera, ACameraActor* InObservationCamera)
{
	Nick->GetFollowCamera()->SetActive(!bObservationMode);
	Nick->GetObservationCamera()->SetActive(bObservationMode);
	
	Nick->bUseControllerRotationPitch = bObservationMode;
	Nick->bUseControllerRotationYaw = bObservationMode;

	InFollowCamera->Destroy();
	InObservationCamera->Destroy();

	EnableInput(this);
}

void AAoS_PlayerController::OnPlayerModeChanged(EPlayerMode InPlayerMode)
{
	switch (InPlayerMode)
	{
		case EPlayerMode::PM_ExplorationMode:
		{
			LockPlayerMovement(false, false);
			break;
		}
		case EPlayerMode::PM_VideoMode:
		{
			PlayerCameraManager->StartCameraFade(0, 1, .01, FLinearColor::Black, false, true);
			LockPlayerMovement(true, true);
			break;	
		}
		default:
		{
			LockPlayerMovement(true, true);
			break;
		}
	}
}

void AAoS_PlayerController::LockPlayerMovement(bool bLockMovement, bool bLockTurning)
{
	bPlayerCanMove = !bLockMovement;
	bPlayerCanTurn = !bLockTurning;
}

void AAoS_PlayerController::SetInteractableActor(AActor* InInteractableActor)
{
	InteractableActor = InInteractableActor;
}

void AAoS_PlayerController::SetObservableActor(AActor* InObservableActor)
{
	ObservableActor = InObservableActor;
}

UMediaSoundComponent* AAoS_PlayerController::GetMediaSoundComponent() const
{
	return MediaSoundComponent;
}
