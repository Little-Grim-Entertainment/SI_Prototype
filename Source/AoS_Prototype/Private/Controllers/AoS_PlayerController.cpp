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
#include "Actors/AoS_MoveToIndicator.h"
#include "Cameras/AoS_PlayerCameraManager.h"
#include "Characters/AoS_GizboManager.h"
#include "Media/AoS_MediaManager.h"
#include "Controllers/AoS_GizboController.h"
#include "Data/Media/AoS_VideoDataAsset.h"
#include "Data/Media/AoS_CinematicDataAsset.h"
#include "Dialogue/AoS_DialogueManager.h"
#include "Dialogue/DialogueSession.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/AoS_DialogueBox.h"
#include "UI/AoS_HUD.h"
#include "UI/AoS_UIManager.h"
#include "Kismet/KismetMathLibrary.h"

using namespace AoS_NativeGameplayTagLibrary;

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

	// Enhanced Input System
	
	UAoS_EnhancedInputComponent* EnhancedInputComponent = Cast<UAoS_EnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) {return;}

	// Action Bindings
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetActionInput("Interact"), ETriggerEvent::Started, this, &ThisClass::RequestInteract);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetActionInput("ToggleObservationMode"), ETriggerEvent::Started, this, &ThisClass::RequestToggleObservation);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetActionInput("ToggleSystemMenu"), ETriggerEvent::Started, this, &ThisClass::RequestToggleSystemMenu);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetActionInput("ObserveObject"), ETriggerEvent::Started, this, &ThisClass::RequestObserveObject);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetActionInput("SkipCinematic"), ETriggerEvent::Triggered, this, &ThisClass::RequestSkipCinematic);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetActionInput("NextDialogue"), ETriggerEvent::Started, this, &ThisClass::RequestNextDialogue);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetActionInput("PreviousDialogue"), ETriggerEvent::Started, this, &ThisClass::RequestPreviousDialogue);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetActionInput("ExitDialogue"), ETriggerEvent::Started, this, &ThisClass::RequestExitDialogue);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetActionInput("GizboFollowTemp"), ETriggerEvent::Started, this, &ThisClass::RequestGizboFollowTemp); //TODO: Amend later
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetActionInput("GizboMoveToTemp"), ETriggerEvent::Started, this, &ThisClass::RequestGizboMoveToTemp); //TODO: Amend later
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetActionInput("GizboMoveToConfirm"), ETriggerEvent::Started, this, &ThisClass::RequestGizboMoveToConfirm); 
	
	// Axis Bindings
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetAxisInput("MoveForward"), ETriggerEvent::Triggered, this, &ThisClass::RequestMoveForward);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetAxisInput("MoveRight"),  ETriggerEvent::Triggered, this, &ThisClass::RequestMoveRight);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetAxisInput("TurnRate"),  ETriggerEvent::Triggered, this, &ThisClass::RequestTurnRight);
	EnhancedInputComponent->BindAction(EnhancedInputSettings->GetAxisInput("LookUpRate"),  ETriggerEvent::Triggered, this, &ThisClass::RequestLookUp);
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Action_Interact, ETriggerEvent::Started, this, &ThisClass::RequestInteract);
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Action_ToggleObservationMode, ETriggerEvent::Started, this, &ThisClass::RequestToggleObservation);
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Action_ToggleSystemMenu, ETriggerEvent::Started, this, &ThisClass::RequestToggleSystemMenu);
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Action_ObserveObject, ETriggerEvent::Started, this, &ThisClass::RequestObserveObject);
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Action_Media_Skip, ETriggerEvent::Triggered, this, &ThisClass::RequestSkipCinematic);
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Action_Dialogue_Next, ETriggerEvent::Started, this, &ThisClass::RequestNextDialogue);
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Action_Dialogue_Previous, ETriggerEvent::Started, this, &ThisClass::RequestPreviousDialogue);
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Action_Dialogue_Exit, ETriggerEvent::Started, this, &ThisClass::RequestExitDialogue);
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Action_Gizbo_Follow, ETriggerEvent::Started, this, &ThisClass::RequestGizboFollowTemp); //TODO: Amend later
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Action_Gizbo_MoveTo, ETriggerEvent::Started, this, &ThisClass::RequestGizboMoveToTemp); //TODO: Amend later
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Action_Gizbo_MoveToConfirm, ETriggerEvent::Started, this, &ThisClass::RequestGizboMoveToConfirm); 
	
	// Axis Bindings
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Axis_1D_MoveForward, ETriggerEvent::Triggered, this, &ThisClass::RequestMoveForward);
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Axis_1D_MoveRight,  ETriggerEvent::Triggered, this, &ThisClass::RequestMoveRight);
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Axis_1D_TurnRate,  ETriggerEvent::Triggered, this, &ThisClass::RequestTurnRight);
	EnhancedInputComponent->BindInputByTag(InputConfig,AOSTag_Input_Axis_1D_LookUpRate,  ETriggerEvent::Triggered, this, &ThisClass::RequestLookUp);
	
	UAoS_GameInstance* GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstance))
	{
		GameInstance->OnPlayerModeChanged.AddDynamic(this, &ThisClass::OnPlayerModeChanged);
	}
}

void AAoS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
}


void AAoS_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
		
	UpdateMoveToIndicatorPosition();
}

bool AAoS_PlayerController::UpdateMoveToIndicatorPosition() const
{
	if(!IsValid(Nick)) {return false;}
	
	//TODO: Should this functionality be moved into the AoS_MoveToIndicator class?
	if (bMoveToMarker)
	{
		FHitResult HitResult;
		FVector Start = Nick->GetFollowCameraActor()->GetActorLocation();
		FVector End = Nick->GetFollowCameraActor()->GetActorLocation() + Nick->GetFollowCameraActor()->GetActorForwardVector() * 10000;
		GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel2);

		//TODO: Amend later once GAS is implemented, to check specifically for surfaces that can be traversed.
		if (HitResult.GetActor())
		{
			FVector HitLocation = HitResult.ImpactPoint;

			// Check whether the 'Move To' indicator is within a specific radius
			double Distance = (HitLocation - Nick->GetActorLocation()).Length();
			
			if (Distance < AdaptableActionMaximumRadius)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Orange, FString::SanitizeFloat(Distance, 0));
				return MoveToActor->SetActorLocation(HitLocation);
			}

			// Keep the 'Move To' actor confined to the bounds of a circle, with radius AdaptableActionMaximumRadius
			// See https://gamedev.stackexchange.com/questions/9607/moving-an-object-in-a-circular-path and
			// https://www.euclideanspace.com/maths/geometry/trig/inverse/index.htm and
			// https://forums.unrealengine.com/t/how-to-get-an-angle-between-2-vectors/280850

			//TODO: Requires further tuning, to make sure that the rotation is correct.
			//When the 'MoveTo' actor currently hits the boundary, it causes the indicator to jump away from where it was previously aligned.
			FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Nick->GetFollowCameraActor()->GetActorLocation(), HitLocation);
			double NickArcTan = atan2(Nick->GetFollowCameraActor()->GetActorLocation().Y, Nick->GetFollowCameraActor()->GetActorLocation().X);
			double MoveToArcTan = atan2(UKismetMathLibrary::GetForwardVector(Rotation).Y, UKismetMathLibrary::GetForwardVector(Rotation).X);
			double Angle = MoveToArcTan - NickArcTan;
				
			float Cosine = cos(Angle);
			float Sine = sin(Angle);
				
			HitLocation.X = Nick->GetActorLocation().X + Cosine * AdaptableActionMaximumRadius;
			HitLocation.Y = Nick->GetActorLocation().Y + Sine * AdaptableActionMaximumRadius;
			Distance = (HitLocation - Nick->GetActorLocation()).Length();
				
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Orange, FString::SanitizeFloat(Distance, 0));
			return MoveToActor->SetActorLocation(HitLocation);
		}
	}

	return bMoveToMarker;
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
		case EPlayerMode::PM_CinematicMode:
		{
			if (!IsValid(Nick)) {break;}
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
		case EPlayerMode::PM_CinematicMode:
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
	/*bObservationMode = !bObservationMode;

	UAoS_GameInstance* GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());

	float CameraTransitionTime = 0.35f;

	DisableInput(this);
	
	if(bObservationMode)
	{
		Cast<AAoS_PlayerCameraManager>(PlayerCameraManager)->ViewPitchMin = -89;
		Cast<AAoS_PlayerCameraManager>(PlayerCameraManager)->ViewPitchMax = 89;
		Nick->SetActorRotation(FRotator(0., Nick->GetFollowCameraActor()->GetActorRotation().Yaw, 0));
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ObservationMode);
		SetViewTargetWithBlend(Nick->GetObservationCameraActor(), CameraTransitionTime);
	}
	else
	{
		Cast<AAoS_PlayerCameraManager>(PlayerCameraManager)->ViewPitchMin = -60;
		Cast<AAoS_PlayerCameraManager>(PlayerCameraManager)->ViewPitchMax = 20;
		Nick->SetActorRotation(FRotator(0, Nick->GetActorRotation().Yaw, Nick->GetActorRotation().Roll));
		SetControlRotation(FRotator(Nick->GetActorRotation()));
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);
		SetViewTargetWithBlend(Nick->GetFollowCameraActor(), CameraTransitionTime);
	}
	Nick->HideMeshes(!bObservationMode);

	GetWorld()->GetTimerManager().SetTimer(CameraBlendHandle, this, &AAoS_PlayerController::PostCameraBlend, CameraTransitionTime, false);*/
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

void AAoS_PlayerController::RequestSkipCinematic()
{
	if (UAoS_MediaManager* MediaManager = GetWorld()->GetSubsystem<UAoS_MediaManager>())
	{
		if (IsValid(MediaManager->GetLoadedVideo()))
		{
			MediaManager->SkipMedia(MediaManager->GetLoadedVideo());	
		}
		else if (IsValid(MediaManager->GetLoadedCinematic()))
		{
			MediaManager->SkipMedia(MediaManager->GetLoadedCinematic());
		}
	}
	
}

void AAoS_PlayerController::RequestNextDialogue()
{
	UAoS_UIManager* UIManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_UIManager>();
	UAoS_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<UAoS_DialogueManager>();
	if (UIManager && DialogueManager)
	{
		if (DialogueManager->HasNextOption())
		{
			UIManager->GetPlayerHUD()->GetDialogueBox()->OnNextClicked();
		}
	}
}

void AAoS_PlayerController::RequestPreviousDialogue()
{
	UAoS_UIManager* UIManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_UIManager>();
	UAoS_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<UAoS_DialogueManager>();
	if (UIManager && DialogueManager)
	{
		if (DialogueManager->HasPreviousOption())
		{
			UIManager->GetPlayerHUD()->GetDialogueBox()->OnPreviousClicked();
		}
	}
}

void AAoS_PlayerController::RequestExitDialogue()
{
	if (UAoS_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<UAoS_DialogueManager>())
	{
		DialogueManager->GetCurrentDialogue()->ExitDialogue();
	}
	if (InteractableActor)
	{
		if (const IAoS_InteractInterface* InterfaceActor = Cast<IAoS_InteractInterface>(InteractableActor))
		{
			InterfaceActor->Execute_OnInteractEnd(Cast<UObject>(InteractableActor), InteractableActor);
		}
	}
}

void AAoS_PlayerController::RequestToggleSystemMenu()
{
	UAoS_UIManager* UIManager = GetGameInstance()->GetSubsystem<UAoS_UIManager>();
	if (IsValid(UIManager))
	{
		UIManager->ToggleSystemMenu();
	}
}

void AAoS_PlayerController::RequestGizboFollowTemp()
{
	if (UAoS_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_GizboManager>())
	{
		GizboManager->GetGizboController()->ToggleFollow();
	}
}

void AAoS_PlayerController::RequestGizboMoveToTemp()
{
	if (UAoS_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_GizboManager>())
	{
		MoveToActor = SpawnMoveToMarker();
		bMoveToMarker = true;
		GizboManager->GetGizboController()->ToggleWait();
	}
}

void AAoS_PlayerController::RequestGizboMoveToConfirm()
{
	if (bMoveToMarker)
	{
		if (UAoS_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_GizboManager>())
		{
			bMoveToMarker = false;
			Cast<AAoS_MoveToIndicator>(MoveToActor)->SetPerceptionStimuliSource();
			MoveToActor = nullptr;
			GizboManager->GetGizboController()->ToggleMoveTo();

			//TODO: Replace current marker, with a new one in the same location (in an attempt to bypass Perception woes)
			/*FVector MarkerLocation = MoveToActor->GetActorLocation();
			bMoveToMarker = false;
			MoveToActor->Destroy();
			MoveToActor = nullptr;

			MoveToActor = SpawnMoveToMarker();
			MoveToActor->SetActorLocation(MarkerLocation);
			Cast<AAoS_MoveToIndicator>(MoveToActor)->SetPerceptionStimuliSource();
			MoveToActor = nullptr;
			GizboManager->GetGizboController()->ToggleMoveTo();*/
		}
	}
		
}

void AAoS_PlayerController::RequestGizboMoveToCancel()
{
	if (bMoveToMarker)
	{
		bMoveToMarker = false;
		MoveToActor->Destroy();
		MoveToActor = nullptr;
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
