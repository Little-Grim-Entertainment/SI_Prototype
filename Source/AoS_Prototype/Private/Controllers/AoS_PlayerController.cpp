// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AoS_PlayerController.h"

#include "AoS_GameInstance.h"
#include "AoS_GameplayTagManager.h"
#include "Components/Actor/AoS_EnhancedInputComponent.h"
#include "Interfaces/AoS_InteractInterface.h"
#include "MediaAssets/Public/MediaSoundComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputSubsystemInterface.h"
#include "InputAction.h"
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
#include "Data/Input/AoS_InputConfig.h"
#include "Kismet/KismetMathLibrary.h"
#include "AoS_NativeGameplayTagLibrary.h"
#include "AoS_PlayerManager.h"
#include "AoS_Prototype/AoS_Prototype.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

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

	UAoS_EnhancedInputComponent* EnhancedInputComponent = Cast<UAoS_EnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)){return;}

	const UAoS_InputConfig* InputConfig = EnhancedInputComponent->GetInputConfig();
	if (!IsValid(InputConfig)) {return;}
	
	// Axis Bindings
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
}

void AAoS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	const UAoS_PlayerManager* PlayerManager = GetLocalPlayer()->GetSubsystem<UAoS_PlayerManager>();
	if(!IsValid(PlayerManager) || !PlayerManager->GetCurrentPlayerState().IsValid()) {return;}

	if(PlayerManager->GetCurrentPlayerState() == AOSTag_Player_State_Menu)
	{
		SetMenuMode(true);
	}
	else
	{
		SetMenuMode(false);
	}

	AddInputMappingByTag(PlayerManager->GetCurrentPlayerState());
	if(PlayerManager->GetPreviousPlayerState().IsValid())
	{
		RemoveInputMappingByTag(PlayerManager->GetPreviousPlayerState());
	}

	if (UAoS_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_GizboManager>())
	{
		GizboManager->Nick = Nick;
	}
}

void AAoS_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
		
	//UpdateMoveToIndicatorPosition();
}

void AAoS_PlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UAoS_GameInstance* GameInstance = Cast<UAoS_GameInstance>(GetGameInstance());
	if (!IsValid(GameInstance) || !IsValid(PlayerCameraManager)){return;}

	/*if (GameInstance->GetPlayerMode() != EPlayerMode::PM_NONE)
	{
		PlayerCameraManager->StartCameraFade(0, 1, 0.001, FLinearColor::Black, false, true);
	}*/
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
	if (!bPlayerCanTurn || !GetPawn()) return;

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
			InterfaceActor->Execute_OnInteract(InteractableActor, InteractableActor);
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

	UAoS_GameplayTagManager* AOSTagManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_GameplayTagManager>();
	AOSTagManager->AddNewGameplayTag(AOSTag_Player_State_Observation);
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Gizbo: MoveTo")));
	UE_LOG(LogAoSAI, Log, TEXT("%s : AoS_PlayerController::RequestGizboMoveToTemp MoveTo Initiated"), *GetNameSafe(GetPawn()));

	if (UAoS_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_GizboManager>())
	{
		AAoS_PlayerCameraManager* AOSCamera = Cast<AAoS_PlayerCameraManager>(this->PlayerCameraManager);
		if(!IsValid(AOSCamera)) return;
		
		GizboManager->StartMoveTo(AOSCamera, GetPawn(), bMoveToMarker);
		GizboManager->GetGizboController()->ToggleWait();
	}
}

void AAoS_PlayerController::RequestGizboMoveToConfirm()
{
	if (UAoS_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_GizboManager>())
	{
		//Cast<AAoS_MoveToIndicator>(MoveToIndicator)->SetPerceptionStimuliSource();
		GizboManager->GetGizboController()->ToggleMoveTo();		
	}
}

void AAoS_PlayerController::RequestGizboMoveToCancel()
{
	if (UAoS_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_GizboManager>())
	{
		GizboManager->GetGizboController()->ToggleMoveTo();		
	}
}

void AAoS_PlayerController::SetInteractableActor(AActor* InInteractableActor)
{
	InteractableActor = InInteractableActor;
}

void AAoS_PlayerController::SetObservableActor(AActor* InObservableActor)
{
	ObservableActor = InObservableActor;
}

void AAoS_PlayerController::AddInputMappingByTag(const FGameplayTag InMappingTag, const FGameplayTag InSecondaryTag)
{
	if (!InMappingTag.IsValid()) {return;}
	
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	const UInputMappingContext* MappingToAdd = EnhancedInputSettings->GetInputConfig()->GetInputMappingByTag(InMappingTag, InSecondaryTag);
	const FModifyContextOptions ModifyContextOptions;
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(MappingToAdd, 0, ModifyContextOptions);
}

void AAoS_PlayerController::RemoveInputMappingByTag(const FGameplayTag InMappingTag, const FGameplayTag InSecondaryTag)
{
	if (!InMappingTag.IsValid()) {return;}
	
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	const UInputMappingContext* MappingToRemove = EnhancedInputSettings->GetInputConfig()->GetInputMappingByTag(InMappingTag, InSecondaryTag);
	EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(MappingToRemove);
}

void AAoS_PlayerController::SetFocusedWidget(UAoS_UserWidget* InWidgetToFocus)
{
	FocusedWidget = InWidgetToFocus;
}

void AAoS_PlayerController::SetMenuMode(bool bSetMenuMode)
{
	if (bSetMenuMode)
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this, FocusedWidget);
		SetShowMouseCursor(true);
	}
	else
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
		SetShowMouseCursor(false);
	}
	
	bInMenuMode = bSetMenuMode;
}

UMediaSoundComponent* AAoS_PlayerController::GetMediaSoundComponent() const
{
	return MediaSoundComponent;
}

bool AAoS_PlayerController::IsInMenuMode() const
{
	return bInMenuMode;
}
