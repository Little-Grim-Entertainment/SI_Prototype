// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AoS_PlayerController.h"

#include "AoS_GameInstance.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Characters/AoS_Nick.h"
#include "Components/Actor/AoS_EnhancedInputComponent.h"
#include "Interfaces/AoS_InteractInterface.h"
#include "MediaAssets/Public/MediaSoundComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputSubsystemInterface.h"
#include "InputAction.h"

AAoS_PlayerController::AAoS_PlayerController()
{
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	
	MediaSoundComponent = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("MediaSoundComponent"));
	MediaSoundComponent->SetupAttachment(RootComponent);

	EnhancedInputSettings = CreateDefaultSubobject<UAoS_EnhancedInputComponent>(TEXT("EnhancedInputSettings"));
}

void AAoS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/*// Old Input System
	check(InputComponent);

	InputComponent->BindAction("Interact", IE_Pressed,this, &AAoS_PlayerController::RequestInteract);
	InputComponent->BindAction("ObservationMode", IE_Pressed,this, &AAoS_PlayerController::RequestObservation);
	InputComponent->BindAxis("MoveForward", this, &AAoS_PlayerController::RequestMoveForward);
	InputComponent->BindAxis("MoveRight", this, &AAoS_PlayerController::RequestMoveRight);
	InputComponent->BindAxis("TurnRate", this, &AAoS_PlayerController::RequestTurnRight);
	InputComponent->BindAxis("LookUpRate", this, &AAoS_PlayerController::RequestLookUp);*/

	// Enhanced Input System
	
	UAoS_EnhancedInputComponent* EnhancedInputComponent = Cast<UAoS_EnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) {return;}

	// Action Bindings
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetActionInput("Interact"), ETriggerEvent::Started, this, &ThisClass::RequestInteract);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetActionInput("ToggleObservationMode"), ETriggerEvent::Started, this, &ThisClass::RequestToggleObservation);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetActionInput("ObserveObject"), ETriggerEvent::Started, this, &ThisClass::RequestObserveObject);

	// Axis Bindings
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetAxisInput("MoveForward"), ETriggerEvent::Triggered, this, &ThisClass::RequestMoveForward);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetAxisInput("MoveRight"),  ETriggerEvent::Triggered, this, &ThisClass::RequestMoveRight);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetAxisInput("TurnRate"),  ETriggerEvent::Triggered, this, &ThisClass::RequestTurnRight);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetAxisInput("LookUpRate"),  ETriggerEvent::Triggered, this, &ThisClass::RequestLookUp);
	
	UAoS_GameInstance* GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstance))
	{
		GameInstance->OnPlayerModeChanged.AddDynamic(this, &ThisClass::OnPlayerModeChanged);
	}
}

void AAoS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	OnCameraSetup.AddDynamic(this, &ThisClass::PostCameraSetup);
	SetupPlayerCamera();
}


void AAoS_PlayerController::SetupPlayerCamera()
{
	Nick = Cast<AAoS_Nick>(GetPawn());
	if (IsValid(Nick))
	{
		if (IsValid(Nick->GetFollowCameraActor()))
		{
			SetViewTarget(Nick->GetFollowCameraActor());
			OnCameraSetup.Broadcast();
		}
	}
}

void AAoS_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(bObservationMode)
	{
		FHitResult HitResult;
		ObservationStart = Nick->GetObservationCameraActor()->GetActorLocation();
		ObservationEnd = Nick->GetObservationCameraActor()->GetActorLocation() + Nick->GetObservationCameraActor()->GetActorForwardVector() * ObservationDistance;
		GetWorld()->LineTraceSingleByChannel(HitResult, ObservationStart, ObservationEnd, ECC_Visibility, FCollisionQueryParams(FName(TEXT("ObservationTrace")), true, this));
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

void AAoS_PlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UAoS_GameInstance* GameInstance = Cast<UAoS_GameInstance>(GetGameInstance());
	if (!IsValid(GameInstance) || !IsValid(PlayerCameraManager)){return;}

	if (GameInstance->GetPlayerMode() != EPlayerMode::PM_NONE)
	{
		PlayerCameraManager->StartCameraFade(0, 1, 0.001, FLinearColor::Black, false, true);
	}
}

void AAoS_PlayerController::OnPlayerModeChanged(EPlayerMode InPlayerMode, EPlayerMode InPreviousPlayerMode)
{

	switch (InPreviousPlayerMode)
	{
	case EPlayerMode::PM_VideoMode:
		{
			if (InPlayerMode != EPlayerMode::PM_LevelLoadingMode)
			{
				PlayerCameraManager->StartCameraFade(1, 0, .5, FLinearColor::Black, false, false);
			}
			break;	
		}
	default:
		{
			break;
		}
	}
	
	switch (InPlayerMode)
	{
	case EPlayerMode::PM_ExplorationMode:
		{
			if (InPreviousPlayerMode == EPlayerMode::PM_LevelLoadingMode)
			{
				PlayerCameraManager->StartCameraFade(1, 0, .5, FLinearColor::Black, false, false);
			}
			break;
		}
	case EPlayerMode::PM_VideoMode:
		{
			PlayerCameraManager->StartCameraFade(0, 1, .2, FLinearColor::Black, false, true);
			break;	
		}
	default:
		{
			break;
		}
	}

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!IsValid(EnhancedInputLocalPlayerSubsystem)) {return;}

	const UInputMappingContext* PreviousMappingContext = EnhancedInputSettings->GetPlayerModeInputMappingContext(InPreviousPlayerMode);
	EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(PreviousMappingContext);
	EnhancedInputLocalPlayerSubsystem->ClearAllMappings();

	const UInputMappingContext* NewMappingContext = EnhancedInputSettings->GetPlayerModeInputMappingContext(InPlayerMode);

	EnhancedInputLocalPlayerSubsystem->AddMappingContext(NewMappingContext, 0);
}


void AAoS_PlayerController::RequestMoveForward(const FInputActionValue& ActionValue)
{
	if  (!bPlayerCanMove || !GetPawn()) return;

	const float Value = ActionValue.Get<FInputActionValue::Axis1D>();
	
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

void AAoS_PlayerController::RequestMoveRight(const FInputActionValue& ActionValue)
{
	if  (!bPlayerCanMove || !GetPawn()) return;

	const float Value = ActionValue.Get<FInputActionValue::Axis1D>();

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

void AAoS_PlayerController::RequestLookUp(const FInputActionValue& ActionValue)
{
	if  (!bPlayerCanTurn || !GetPawn()) return;

	const float AxisValue = ActionValue.Get<FInputActionValue::Axis1D>();

	AddPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAoS_PlayerController::RequestTurnRight(const FInputActionValue& ActionValue)
{
	if  (!bPlayerCanTurn || !GetPawn()) return;

	const float AxisValue = ActionValue.Get<FInputActionValue::Axis1D>();

	AddYawInput(AxisValue * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAoS_PlayerController::RequestInteract()
{
	if (!GetPawn()) {return;}
	
	if(InteractableActor)
	{
		if (const IAoS_InteractInterface* InterfaceActor = Cast<IAoS_InteractInterface>(InteractableActor))
		{
			InterfaceActor->Execute_OnInteract(Cast<UObject>(InteractableActor), InteractableActor);
			OnInteractPressed.Broadcast(InteractableActor, this);
		}
	}
}

void AAoS_PlayerController::RequestToggleObservation()
{
	bObservationMode = !bObservationMode;

	UAoS_GameInstance* GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());

	float CameraTransitionTime = 0.25f;

	DisableInput(this);
	//SetControlRotation(FRotator(0, Nick->GetActorRotation().Yaw, 0));
	//Nick->SetActorRotation(FRotator(0., Nick->GetActorRotation().Yaw, 0));
	
	if(bObservationMode)
	{
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ObservationMode);
		SetViewTargetWithBlend(Nick->GetObservationCameraActor(), CameraTransitionTime);
	}
	else
	{
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);
		SetViewTargetWithBlend(Nick->GetFollowCameraActor(), CameraTransitionTime);
	}
	Nick->GetMesh()->SetVisibility(!bObservationMode);

	CameraBlendDelegate = FTimerDelegate::CreateUObject(this, &AAoS_PlayerController::PostCameraBlend, Nick->GetFollowCameraActor(), Nick->GetObservationCameraActor());
	GetWorld()->GetTimerManager().SetTimer(CameraBlendHandle, CameraBlendDelegate, CameraTransitionTime, false);
}

void AAoS_PlayerController::RequestObserveObject()
{
	if(ObservableActor)
	{
		if (const IAoS_InteractInterface* InterfaceActor = Cast<IAoS_InteractInterface>(ObservableActor))
		{
			InterfaceActor->Execute_OnObserved(Cast<UObject>(ObservableActor), ObservableActor);
		}
	}
}


void AAoS_PlayerController::PostCameraBlend(ACameraActor* InFollowCamera, ACameraActor* InObservationCamera)
{
	Nick->bUseControllerRotationPitch = bObservationMode;
	Nick->bUseControllerRotationYaw = bObservationMode;

	SetControlRotation(FRotator(0, Nick->GetActorRotation().Yaw, 0));
	Nick->SetActorRotation(FRotator(0., Nick->GetActorRotation().Yaw, 0));
	
	EnableInput(this);
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

void AAoS_PlayerController::PostCameraSetup_Implementation()
{
	
}

UMediaSoundComponent* AAoS_PlayerController::GetMediaSoundComponent() const
{
	return MediaSoundComponent;
}
