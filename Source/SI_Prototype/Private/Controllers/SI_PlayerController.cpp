// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SI_PlayerController.h"

#include "SI_GameInstance.h"
#include "SI_GameplayTagManager.h"
#include "Components/Actor/SI_EnhancedInputComponent.h"
#include "Interfaces/SI_InteractInterface.h"
#include "MediaAssets/Public/MediaSoundComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputSubsystemInterface.h"
#include "InputAction.h"
#include "Cameras/SI_PlayerCameraManager.h"
#include "Characters/SI_GizboManager.h"
#include "Media/SI_MediaManager.h"
#include "Controllers/SI_GizboController.h"
#include "Data/Media/SI_VideoDataAsset.h"
#include "Data/Media/SI_CinematicDataAsset.h"
#include "Dialogue/SI_DialogueManager.h"
#include "Dialogue/SI_DialogueSession.h"
#include "UI/SI_DialogueBox.h"
#include "UI/SI_HUD.h"
#include "UI/SI_UIManager.h"
#include "Data/Input/SI_InputConfig.h"
#include "SI_Prototype/SI_Prototype.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "SI_PlayerManager.h"
#include "Actors/SI_InteractableActor.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Characters/SI_Nick.h"
#include "EngineUtils.h" // ActorIterator


using namespace SI_NativeGameplayTagLibrary;

ASI_PlayerController::ASI_PlayerController()
{
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	
	MediaSoundComponent = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("MediaSoundComponent"));
	MediaSoundComponent->SetupAttachment(RootComponent);

	EnhancedInputSettings = CreateDefaultSubobject<USI_EnhancedInputComponent>(TEXT("EnhancedInputSettings"));
}

void ASI_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	USI_EnhancedInputComponent* EnhancedInputComponent = Cast<USI_EnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)){return;}

	const USI_InputConfig* InputConfig = EnhancedInputComponent->GetInputConfig();
	if (!IsValid(InputConfig)) {return;}
	
	// Axis Bindings
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Interact, ETriggerEvent::Started, this, &ThisClass::RequestInteract);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_ToggleObservationMode, ETriggerEvent::Started, this, &ThisClass::RequestToggleObservation);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_ToggleSystemMenu, ETriggerEvent::Started, this, &ThisClass::RequestToggleSystemMenu);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_ObserveObject, ETriggerEvent::Started, this, &ThisClass::RequestObserveObject);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Media_Skip, ETriggerEvent::Triggered, this, &ThisClass::RequestSkipCinematic);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Dialogue_Next, ETriggerEvent::Started, this, &ThisClass::RequestNextDialogue);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Dialogue_Previous, ETriggerEvent::Started, this, &ThisClass::RequestPreviousDialogue);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Dialogue_Exit, ETriggerEvent::Started, this, &ThisClass::RequestExitDialogue);
	//EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_Follow, ETriggerEvent::Ongoing, this, &ThisClass::RequestGizboFollowTemp);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_Follow, ETriggerEvent::Started, this, &ThisClass::RequestGizboFollowTemp); //TODO: Amend later
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_MoveTo, ETriggerEvent::Started, this, &ThisClass::RequestToggleGizboAdaptableAction); //TODO: Amend later
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_MoveToConfirm, ETriggerEvent::Started, this, &ThisClass::RequestGizboAdaptableActionConfirm); 
	
	// Axis Bindings
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Axis_1D_MoveForward, ETriggerEvent::Triggered, this, &ThisClass::RequestMoveForward);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Axis_1D_MoveRight,  ETriggerEvent::Triggered, this, &ThisClass::RequestMoveRight);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Axis_1D_TurnRate,  ETriggerEvent::Triggered, this, &ThisClass::RequestTurnRight);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Axis_1D_LookUpRate,  ETriggerEvent::Triggered, this, &ThisClass::RequestLookUp);
}

void ASI_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	const USI_PlayerManager* PlayerManager = GetLocalPlayer()->GetSubsystem<USI_PlayerManager>();
	if(!IsValid(PlayerManager) || !PlayerManager->GetCurrentPlayerState().IsValid()) {return;}

	if(PlayerManager->GetCurrentPlayerState() == SITag_Player_State_Menu)
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

	if (USI_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GizboManager>())
	{
		GizboManager->Nick = Cast<ASI_Nick>(GetCharacter());
	}
}

void ASI_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(bObservationMode)
	{
		//line trace that ignores nick and only targets objects with the tag "SI_ObservationTarget"
		FHitResult HitResult;
		const FVector StartLocation = PlayerCameraManager->GetCameraLocation();
		const FVector EndLocation = StartLocation + (PlayerCameraManager->GetCameraRotation().Vector() * 1000);
		GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);
		//debug line to show the line trace
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 0.1f, 0, 1);

		//if the line trace hits an object with the tag "SI_ObservationTarget" then set the observation target to that object
		if(HitResult.GetActor() && HitResult.GetActor()->ActorHasTag(TEXT("Observable")))
		{
			//print to screen the name of the object that is being observed
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Observing: %s"), *HitResult.GetActor()->GetName()));
		}
		
	}
}

void ASI_PlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	USI_GameInstance* GameInstance = Cast<USI_GameInstance>(GetGameInstance());
	if (!IsValid(GameInstance) || !IsValid(PlayerCameraManager)){return;}

	/*if (GameInstance->GetPlayerMode() != EPlayerMode::PM_NONE)
	{
		PlayerCameraManager->StartCameraFade(0, 1, 0.001, FLinearColor::Black, false, true);
	}*/
}

void ASI_PlayerController::RequestMoveForward(const FInputActionValue& ActionValue)
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

void ASI_PlayerController::RequestMoveRight(const FInputActionValue& ActionValue)
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

void ASI_PlayerController::RequestLookUp(const FInputActionValue& ActionValue)
{
	if (!bPlayerCanTurn || !GetPawn()) return;

	const float AxisValue = ActionValue.Get<FInputActionValue::Axis1D>();
	
	AddPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASI_PlayerController::RequestTurnRight(const FInputActionValue& ActionValue)
{
	if  (!bPlayerCanTurn || !GetPawn()) return;

	const float AxisValue = ActionValue.Get<FInputActionValue::Axis1D>();

	AddYawInput(AxisValue * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASI_PlayerController::RequestInteract()
{
	if (!GetPawn()) {return;}
	
	if(InteractableActor)
	{
		if (const ISI_InteractInterface* InterfaceActor = Cast<ISI_InteractInterface>(InteractableActor))
		{
			InterfaceActor->Execute_OnInteract(InteractableActor, InteractableActor);
			OnInteractPressed.Broadcast(InteractableActor, this);
		}
	}
}

void ASI_PlayerController::RequestToggleObservation()
{
	/*bObservationMode = !bObservationMode;

	USI_GameInstance* GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());

	float CameraTransitionTime = 0.35f;

	DisableInput(this);
	
	if(bObservationMode)
	{
		Cast<ASI_PlayerCameraManager>(PlayerCameraManager)->ViewPitchMin = -89;
		Cast<ASI_PlayerCameraManager>(PlayerCameraManager)->ViewPitchMax = 89;
		Nick->SetActorRotation(FRotator(0., Nick->GetFollowCameraActor()->GetActorRotation().Yaw, 0));
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ObservationMode);
		SetViewTargetWithBlend(Nick->GetObservationCameraActor(), CameraTransitionTime);
	}
	else
	{
		Cast<ASI_PlayerCameraManager>(PlayerCameraManager)->ViewPitchMin = -60;
		Cast<ASI_PlayerCameraManager>(PlayerCameraManager)->ViewPitchMax = 20;
		Nick->SetActorRotation(FRotator(0, Nick->GetActorRotation().Yaw, Nick->GetActorRotation().Roll));
		SetControlRotation(FRotator(Nick->GetActorRotation()));
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);
		SetViewTargetWithBlend(Nick->GetFollowCameraActor(), CameraTransitionTime);
	}
	Nick->HideMeshes(!bObservationMode);

	GetWorld()->GetTimerManager().SetTimer(CameraBlendHandle, this, &ASI_PlayerController::PostCameraBlend, CameraTransitionTime, false);*/

	USI_GameplayTagManager* SITagManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GameplayTagManager>();
	SITagManager->AddNewGameplayTag(SITag_Player_State_Observation);
}

void ASI_PlayerController::RequestObserveObject()
{
	if(ObservableActor)
	{
		if (const ISI_InteractInterface* InterfaceActor = Cast<ISI_InteractInterface>(ObservableActor))
		{
			InterfaceActor->Execute_OnObserved(Cast<UObject>(ObservableActor), ObservableActor);
		}
	}
}

void ASI_PlayerController::RequestSkipCinematic()
{
	if (USI_MediaManager* MediaManager = GetWorld()->GetSubsystem<USI_MediaManager>())
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

void ASI_PlayerController::RequestNextDialogue()
{
	USI_UIManager* UIManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_UIManager>();
	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if (UIManager && DialogueManager)
	{
		if (DialogueManager->HasNextOption())
		{
			UIManager->GetPlayerHUD()->GetDialogueBox()->OnNextClicked();
		}
	}
}

void ASI_PlayerController::RequestPreviousDialogue()
{
	USI_UIManager* UIManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_UIManager>();
	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if (UIManager && DialogueManager)
	{
		if (DialogueManager->HasPreviousOption())
		{
			UIManager->GetPlayerHUD()->GetDialogueBox()->OnPreviousClicked();
		}
	}
}

void ASI_PlayerController::RequestExitDialogue()
{
	if (USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>())
	{
		DialogueManager->GetCurrentDialogue()->ExitDialogue();
	}
	if (InteractableActor)
	{
		if (const ISI_InteractInterface* InterfaceActor = Cast<ISI_InteractInterface>(InteractableActor))
		{
			InterfaceActor->Execute_OnInteractEnd(Cast<UObject>(InteractableActor), InteractableActor);
		}
	}
}

void ASI_PlayerController::RequestToggleSystemMenu()
{
	USI_UIManager* UIManager = GetGameInstance()->GetSubsystem<USI_UIManager>();
	if (IsValid(UIManager))
	{
		UIManager->ToggleSystemMenu();
	}
}

void ASI_PlayerController::RequestGizboFollowTemp()
{
	if (USI_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GizboManager>())
	{
		GizboManager->GetGizboController()->ToggleFollow();
	}
}

void ASI_PlayerController::RequestToggleGizboAdaptableAction()
{
	bAdaptableActionMode = !bAdaptableActionMode;
	
	if(bAdaptableActionMode)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Gizbo: AdaptableAction")));
		UE_LOG(LogSIAI, Log, TEXT("%s : SI_PlayerController::RequestToggleGizboAdaptableAction Initiated"), *GetNameSafe(GetPawn()));

		InitializeGizboAdaptableAction();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Gizbo: AdaptableAction")));
		UE_LOG(LogSIAI, Log, TEXT("%s : SI_PlayerController::RequestToggleGizboAdaptableAction Cancelled"), *GetNameSafe(GetPawn()));

		CancelGizboAdaptableAction();
	}
}

void ASI_PlayerController::RequestGizboAdaptableActionConfirm()
{
	bAdaptableActionMode = false;
	
	if (USI_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GizboManager>())
	{
		//Cast<AAoS_MoveToIndicator>(MoveToIndicator)->SetPerceptionStimuliSource();
		GizboManager->GetGizboController()->ToggleMoveTo();
		GizboManager->CancelUpdateIndicatorPositionTimer();
		GizboManager->HideMoveToIndicator();
	}
	CancelInteractableHighlight();
}

void ASI_PlayerController::InitializeGizboAdaptableAction()
{
	if (USI_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GizboManager>())
	{
		ASI_PlayerCameraManager* AOSCamera = Cast<ASI_PlayerCameraManager>(this->PlayerCameraManager);
		if(!IsValid(AOSCamera)) return;
		
		GizboManager->StartAdaptableAction(AOSCamera, GetPawn(), bMoveToMarker);
	}
	HighlightInteractables();
}

void ASI_PlayerController::CancelGizboAdaptableAction()
{
	if (USI_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GizboManager>())
	{
		GizboManager->CancelUpdateIndicatorPositionTimer();
		GizboManager->HideMoveToIndicator();
		GizboManager->GetGizboController()->ToggleWait();
	}
	CancelInteractableHighlight();
}

void ASI_PlayerController::HighlightInteractables()
{
	for(TActorIterator<ASI_InteractableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ASI_InteractableActor* HitInteractableActor = *ActorItr;
		if(FVector::Distance(HitInteractableActor->GetActorLocation(), GetPawn()->GetActorLocation()) < 2000.0f)
		{//TODO:: Convert distance to a int from MagicNumber
			HitInteractableActor->HighlightMesh->SetVisibility(true);	
		}
		else
		{
			HitInteractableActor->HighlightMesh->SetVisibility(false);
		}
	}
}

void ASI_PlayerController::CancelInteractableHighlight()
{
	for(TActorIterator<ASI_InteractableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if(ASI_InteractableActor* HitInteractableActor = *ActorItr)
		{
			HitInteractableActor->HighlightMesh->SetVisibility(false);
		}
	}
}

void ASI_PlayerController::SetInteractableActor(AActor* InInteractableActor)
{
	InteractableActor = InInteractableActor;
}

void ASI_PlayerController::SetObservableActor(AActor* InObservableActor)
{
	ObservableActor = InObservableActor;
}

void ASI_PlayerController::AddInputMappingByTag(const FGameplayTag InMappingTag, const FGameplayTag InSecondaryTag)
{
	if (!InMappingTag.IsValid()) {return;}
	
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	const UInputMappingContext* MappingToAdd = EnhancedInputSettings->GetInputConfig()->GetInputMappingByTag(InMappingTag, InSecondaryTag);
	const FModifyContextOptions ModifyContextOptions;
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(MappingToAdd, 0, ModifyContextOptions);
}

void ASI_PlayerController::RemoveInputMappingByTag(const FGameplayTag InMappingTag, const FGameplayTag InSecondaryTag)
{
	if (!InMappingTag.IsValid()) {return;}
	
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	const UInputMappingContext* MappingToRemove = EnhancedInputSettings->GetInputConfig()->GetInputMappingByTag(InMappingTag, InSecondaryTag);
	EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(MappingToRemove);
}

void ASI_PlayerController::SetFocusedWidget(USI_UserWidget* InWidgetToFocus)
{
	FocusedWidget = InWidgetToFocus;
}

void ASI_PlayerController::SetMenuMode(bool bSetMenuMode)
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

UMediaSoundComponent* ASI_PlayerController::GetMediaSoundComponent() const
{
	return MediaSoundComponent;
}

bool ASI_PlayerController::IsInMenuMode() const
{
	return bInMenuMode;
}
