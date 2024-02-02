// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SI_PlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "SI_GameInstance.h"
#include "GameplayTags/SI_NativeGameplayTagLibrary.h"
#include "Components/Actor/SI_EnhancedInputComponent.h"
#include "Interfaces/SI_InteractInterface.h"
#include "MediaAssets/Public/MediaSoundComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputSubsystemInterface.h"
#include "InputAction.h"
#include "LG_DebugMacros.h"
#include "Characters/SI_GizboManager.h"
#include "Media/SI_MediaManager.h"
#include "Media/Data/SI_VideoDataAsset.h"
#include "Media/Data/SI_CinematicDataAsset.h"
#include "Dialogue/SI_DialogueManager.h"
#include "UI/SI_DialogueBox.h"
#include "UI/SI_HUD.h"
#include "UI/SI_UIManager.h"
#include "Input/Data/SI_InputConfig.h"
#include "GameplayTags/SI_GameplayTagManager.h"
#include "SI_PlayerManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Characters/SI_Nick.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"
#include "Characters/SI_Gizbo.h"
#include "SI_Prototype/SI_Prototype.h"

using namespace SI_NativeGameplayTagLibrary;

//DEFINE_LG_LOG_CATEGORY();

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
	if (!IsValid(EnhancedInputComponent)){LG_LOG(LogLG_PlayerController, Error, "EnhancedInputComponent is null") return;}

	const USI_InputConfig* InputConfig = EnhancedInputComponent->GetInputConfig();
	if (!IsValid(InputConfig)) {LG_LOG(LogLG_PlayerController, Error, "InputConfig is null") return;}

	// Axis Bindings
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Axis_1D_MoveForward, ETriggerEvent::Triggered, this, &ThisClass::RequestMoveForward);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Axis_1D_MoveRight,  ETriggerEvent::Triggered, this, &ThisClass::RequestMoveRight);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Axis_1D_TurnRate,  ETriggerEvent::Triggered, this, &ThisClass::RequestTurnRight);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Axis_1D_LookUpRate,  ETriggerEvent::Triggered, this, &ThisClass::RequestLookUp);
	
	// Nick Ability Action Bindings
	/*	These bindings are for the ability system.
	 *	Cancel is set to started so it activates as soon as you press the input.
	 *	Confirm is set to triggered on release of the input
	 *	HoldConfirm is set to triggered after holding the input for a set amount of time 
	 */

	// Menus
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_ToggleSystemMenu, ETriggerEvent::Started, this, &ThisClass::RequestToggleSystemMenu);
	
	// Player Actions
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_CancelAbility, ETriggerEvent::Started, this, &ThisClass::RequestCancelAbility);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_ConfirmAbility, ETriggerEvent::Triggered, this, &ThisClass::RequestConfirmAbility);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_HoldConfirmAbility, ETriggerEvent::Triggered, this, &ThisClass::RequestHoldConfirmAbility);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_AdaptableAction, ETriggerEvent::Started, this, &ThisClass::RequestToggleAdaptableAction);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Interact, ETriggerEvent::Started, this, &ThisClass::RequestInteract);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_ToggleGizboControls, ETriggerEvent::Triggered, this, &ThisClass::RequestToggleGizboCommands);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_ToggleObservationMode, ETriggerEvent::Started, this, &ThisClass::RequestToggleObservation);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_ObserveObject, ETriggerEvent::Started, this, &ThisClass::RequestObserveObject);
	
	// Dialogue
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Dialogue_Next, ETriggerEvent::Started, this, &ThisClass::RequestNextDialogue);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Dialogue_Exit, ETriggerEvent::Started, this, &ThisClass::RequestExitDialogue);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Interrogate_Start, ETriggerEvent::Started, this, &ThisClass::RequestInterrogate);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Interrogate_Stop, ETriggerEvent::Started, this, &ThisClass::RequestStopInterrogate);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Interrogate_Next, ETriggerEvent::Started, this, &ThisClass::RequestNextStatement);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Interrogate_Previous, ETriggerEvent::Started, this, &ThisClass::RequestPreviousStatement);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Interrogate_Press, ETriggerEvent::Started, this, &ThisClass::RequestPress);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Interrogate_Present, ETriggerEvent::Started, this, &ThisClass::RequestPresent);

	// Media
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Media_Skip, ETriggerEvent::Triggered, this, &ThisClass::RequestSkipCinematic);

	// Gadgets
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_UseGadget, ETriggerEvent::Started, this, &ThisClass::RequestUseGadgetPrimary);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_UseGadgetSecondary, ETriggerEvent::Started, this, &ThisClass::RequestUseGadgetSecondary);
	
	// MultiAction Bindings
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_MultiOption_Down, ETriggerEvent::Started, this, &ThisClass::RequestMutliOptionDown);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_MultiOption_Left, ETriggerEvent::Started, this, &ThisClass::RequestMultiOptionLeft);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_MultiOption_Right, ETriggerEvent::Started, this, &ThisClass::RequestMultiOptionRight);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_MultiOption_Up, ETriggerEvent::Started, this, &ThisClass::RequestMultiOptionUp);
	
	// Gizbo Commands Bindings
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_Follow, ETriggerEvent::Started, this, &ThisClass::RequestToggleGizboFollow); //TODO: Amend later
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_UseGadget, ETriggerEvent::Started, this, &ThisClass::RequestGizboUseGadgetPrimary);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_UseGadgetSecondary, ETriggerEvent::Started, this, &ThisClass::RequestGizboUseGadgetSecondary);

	// Gizbo MultiAction Bindings
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_MultiOption_Down, ETriggerEvent::Started, this, &ThisClass::RequestGizboMutliOptionDown);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_MultiOption_Left, ETriggerEvent::Started, this, &ThisClass::RequestGizboMultiOptionLeft);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_MultiOption_Right, ETriggerEvent::Started, this, &ThisClass::RequestGizboMultiOptionRight);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_MultiOption_Up, ETriggerEvent::Started, this, &ThisClass::RequestGizboMultiOptionUp);
}

void ASI_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	const USI_PlayerManager* PlayerManager = GetLocalPlayer()->GetSubsystem<USI_PlayerManager>();
	if(!IsValid(PlayerManager) || !PlayerManager->GetCurrentPlayerState().IsValid())
		{LG_LOG(LogLG_PlayerController, Error, "PlayerManager is null or PlayerState is Invalid") return;}

	SITagManager =  GetWorld()->GetGameInstance()->GetSubsystem<USI_GameplayTagManager>();
	
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

	Nick = Cast<ASI_Nick>(GetCharacter());
	GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GizboManager>();
	if (IsValid(GizboManager))
	{
		Gizbo = GizboManager->GetGizbo();
	}
}

void ASI_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
	if  (!bPlayerCanMove || !GetPawn()) {LG_LOG(LogLG_PlayerController, Error, "Player Cannot Move or Pawn is null cannot move") return;}

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
	if  (!bPlayerCanMove || !GetPawn()) {LG_LOG(LogLG_PlayerController, Error, "SITagManager is null cannot verify tag") return;}

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
	if (!bPlayerCanTurn || !GetPawn()) {LG_LOG(LogLG_PlayerController, Error, "SITagManager is null cannot verify tag") return;}

	const float AxisValue = ActionValue.Get<FInputActionValue::Axis1D>();
	
	AddPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASI_PlayerController::RequestTurnRight(const FInputActionValue& ActionValue)
{
	if  (!bPlayerCanTurn || !GetPawn()) {LG_LOG(LogLG_PlayerController, Error, "Player Cannot Turn or Pawn is null cannot turn") return;}

	const float AxisValue = ActionValue.Get<FInputActionValue::Axis1D>();

	AddYawInput(AxisValue * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASI_PlayerController::RequestInteract()
{
	if (!GetPawn()) {LG_LOG(LogLG_PlayerController, Error, "Pawn is null cannot interact") return;}

	if(Nick->GetSIAbilitySystemComponent()->TryActivateAbilitiesByTag(SITag_Ability_Interact.GetTag().GetSingleTagContainer(), false))
	{
		OnInteractPressed.Broadcast(InteractableActor, Nick);
	}
}

void ASI_PlayerController::RequestInterrogate()
{
	if(!IsValid(SITagManager)) {LG_LOG(LogLG_PlayerController, Error, "SITagManager is null cannot enter Interrogation Mode") return;}

	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if(!IsValid(DialogueManager)) {return;}

	DialogueManager->OnRequestInterrogation();
}

void ASI_PlayerController::RequestNextStatement()
{
	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if(IsValid(DialogueManager))
	{
		DialogueManager->OnNextStatementPressed();
	}
}

void ASI_PlayerController::RequestPreviousStatement()
{
	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if(IsValid(DialogueManager))
	{
		DialogueManager->OnPreviousStatementPressed();
	}
}

void ASI_PlayerController::RequestPress()
{
	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if(IsValid(DialogueManager))
	{
		DialogueManager->OnPressPressed();
	}
}

void ASI_PlayerController::RequestPresent()
{
	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if(IsValid(DialogueManager))
	{
		DialogueManager->OnPresentPressed();
	}
}

void ASI_PlayerController::RequestStopInterrogate()
{
	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if(IsValid(DialogueManager))
	{
		DialogueManager->OnRequestQuitInterrogation();
	}
}

void ASI_PlayerController::RequestToggleObservation()
{
	if(!IsValid(SITagManager)) {LG_LOG(LogLG_PlayerController, Error, "SITagManager is null cannot verify tag") return;}
	
	if(SITagManager->HasGameplayTag(SITag_Player_State_Observation))
	{
		Nick->GetSIAbilitySystemComponent()->CancelAbility(Nick->GetSIAbilitySystemComponent()->GetGameplayAbilityByTag(SITag_Ability_Nick_Observation));
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Exploration, SITag_Player_State);
		Nick->HideMeshes(true);
	}
	else
	{
		Nick->GetSIAbilitySystemComponent()->TryActivateAbilitiesByTag(SITag_Ability_Nick_Observation.GetTag().GetSingleTagContainer(), false);
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Observation, SITag_Player_State);
		Nick->HideMeshes(false);
	}
}

void ASI_PlayerController::RequestObserveObject()
{
	if (Nick->GetCurrentInteractableActor() != nullptr)
	{
		Nick->GetSIAbilitySystemComponent()->TryActivateAbilitiesByTag(SITag_Ability_Nick_ObserveObject.GetTag().GetSingleTagContainer(), false);
		if (Nick->GetCurrentInteractableActor() != nullptr)
		{
			Nick->GetSIAbilitySystemComponent()->TryActivateAbilitiesByTag(SITag_Ability_Interact.GetTag().GetSingleTagContainer(), false);
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
		UIManager->GetPlayerHUD()->GetDialogueBox()->OnNextClicked();
	}
}

void ASI_PlayerController::RequestExitDialogue()
{
	if (USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>())
	{

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
	if(!IsValid(SITagManager)) {LG_LOG(LogLG_PlayerController, Error, "SITagManager is null cannot verify tag") return;}
	
	if(SITagManager->HasGameplayTag(SITag_UI_Menu_System))
	{
		SITagManager->RemoveTag_Internal(SITag_UI_Menu_System);
	}
	else
	{
		SITagManager->ReplaceTagWithSameParent(SITag_UI_Menu_System, SITag_UI_Menu);
	}
}

void ASI_PlayerController::RequestUseGadgetPrimary()
{
	if(!IsValid(SITagManager) || !IsValid(Nick)) {LG_LOG(LogLG_PlayerController, Error, "SITagManager or Nick is null cannot add tag") return;}

	FSITagPayload* Payload = new FSITagPayload(Nick, Nick);

	SITagManager->AddNewGameplayTag_Internal(SITag_Ability_Gadget_UsePrimary, Payload);
}

void ASI_PlayerController::RequestUseGadgetSecondary()
{
	if(!IsValid(SITagManager) || !IsValid(Nick)) {LG_LOG(LogLG_PlayerController, Error, "SITagManager or Nick is null cannot add tag") return;}

	FSITagPayload* Payload = new FSITagPayload(Nick, Nick);
	
	SITagManager->AddNewGameplayTag_Internal(SITag_Ability_Gadget_UseSecondary, Payload);
}

void ASI_PlayerController::RequestToggleGizboFollow()
{
	if(!IsValid(SITagManager) || !IsValid(Nick) || !IsValid(Gizbo)) {LG_LOG(LogLG_PlayerController, Error, "SITagManager, Nick, or Gizbo is null cannot add tag") return;}

	FSITagPayload* Payload = new FSITagPayload(Nick, Gizbo);	
	
	SITagManager->AddNewGameplayTag_Internal(SITag_Ability_AI_Follow, Payload);
}

void ASI_PlayerController::RequestToggleGizboCommands()
{
	if(!bShowingGizboCommands)
	{
		bShowingGizboCommands = true;
		GetSITagManager()->AddNewGameplayTag_Internal(SITag_UI_HUD_QuickAction_Gizbo);
	}
	else
	{
		bShowingGizboCommands = false;
		GetSITagManager()->AddNewGameplayTag_Internal(SITag_UI_HUD_QuickAction_GadgetsOne);
	}
}

void ASI_PlayerController::RequestToggleAdaptableAction()
{
	if(!IsValid(SITagManager) || !IsValid(Nick)) {LG_LOG(LogLG_PlayerController, Error, "SITagManager or Nick is null cannot add tag") return;}
	
	FSITagPayload* Payload = new FSITagPayload(Nick, Nick);
	SITagManager->AddNewGameplayTag_Internal(SITag_Ability_Nick_AdaptableAction, Payload);
	
	bInAdaptableActionMode = true;
}

void ASI_PlayerController::RequestCancelAbility()
{
	bInAdaptableActionMode = false;
	
	if(!IsValid(SITagManager)) {LG_LOG(LogLG_PlayerController, Error, "SITagManager Is Null cannot add tag") return;}
	
	SITagManager->AddNewGameplayTag_Internal(SITag_Ability_Cancel);	
}

void ASI_PlayerController::RequestConfirmAbility()
{
	bInAdaptableActionMode = false;
	
	if(!IsValid(SITagManager)) {LG_LOG(LogLG_PlayerController, Error, "SITagManager Is Null cannot add tag") return;}
	
 	SITagManager->AddNewGameplayTag_Internal(SITag_Ability_Confirm);
}

void ASI_PlayerController::RequestHoldConfirmAbility()
{
	bInAdaptableActionMode = false;
	
	if(!IsValid(SITagManager)) {LG_LOG(LogLG_PlayerController, Error, "SITagManager Is Null cannot add tag") return;}
	
	SITagManager->AddNewGameplayTag_Internal(SITag_Ability_HoldConfirm);
}

void ASI_PlayerController::RequestGizboUseGadgetPrimary()
{
	if(!IsValid(SITagManager) || !IsValid(Nick) || !IsValid(Gizbo)) {LG_LOG(LogLG_PlayerController, Error, "SITagManager, Nick, or Gizbo is null cannot add tag") return;}

	FSITagPayload* Payload = new FSITagPayload(Nick, Gizbo);
	
	SITagManager->AddNewGameplayTag_Internal(SITag_Ability_Gadget_UsePrimary, Payload);
}

void ASI_PlayerController::RequestGizboUseGadgetSecondary()
{
	if(!IsValid(SITagManager) || !IsValid(Nick) || !IsValid(Gizbo)) {LG_LOG(LogLG_PlayerController, Error, "SITagManager, Nick, or Gizbo is null cannot add tag") return;}
	
	FSITagPayload* Payload = new FSITagPayload(Nick, Gizbo);
	
	SITagManager->AddNewGameplayTag_Internal(SITag_Ability_Gadget_UseSecondary, Payload);
}

void ASI_PlayerController::RequestGadget(AActor* InActor, FGameplayTag InGadgetTag)
{
	FGameplayEventData Payload;
	Payload.Target = InActor;
	Payload.EventTag = InGadgetTag;
	Gizbo->GetSIAbilitySystemComponent()->HandleGameplayEvent(Payload.EventTag, &Payload);
}

void ASI_PlayerController::RequestMultiOptionUp()
{
	if(bInAdaptableActionMode)
	{
		RequestConfirmAbility();
	}
	
	USI_UIManager* UIManager = GetGameInstance()->GetSubsystem<USI_UIManager>();
	if(!IsValid(UIManager)) {LG_LOG(LogLG_PlayerController, Error, "UIManager Is Null cannot retrieve tag") return;}
	
	FGameplayTag AbilityTag = UIManager->GetQuickActionAbilityTag(SITag_Input_Action_MultiOption_Up);

	FSITagPayload* Payload = new FSITagPayload(Nick, Nick);
	SITagManager->AddNewGameplayTag_Internal(AbilityTag, Payload);
}

void ASI_PlayerController::RequestMutliOptionDown()
{
	if(bInAdaptableActionMode)
	{
		RequestConfirmAbility();
	}
	
	USI_UIManager* UIManager = GetGameInstance()->GetSubsystem<USI_UIManager>();
	if(!IsValid(UIManager)) {LG_LOG(LogLG_PlayerController, Error, "UIManager Is Null cannot retrieve tag") return;}
	
	FGameplayTag AbilityTag = UIManager->GetQuickActionAbilityTag(SITag_Input_Action_MultiOption_Down);

	FSITagPayload* Payload = new FSITagPayload(Nick, Nick);
	SITagManager->AddNewGameplayTag_Internal(AbilityTag, Payload);
}

void ASI_PlayerController::RequestMultiOptionLeft()
{
	if(bInAdaptableActionMode)
	{
		RequestConfirmAbility();
	}
	
	USI_UIManager* UIManager = GetGameInstance()->GetSubsystem<USI_UIManager>();
	if(!IsValid(UIManager)) {LG_LOG(LogLG_PlayerController, Error, "UIManager Is Null cannot retrieve tag") return;}
	
	FGameplayTag AbilityTag = UIManager->GetQuickActionAbilityTag(SITag_Input_Action_MultiOption_Left);

	FSITagPayload* Payload = new FSITagPayload(Nick, Nick);
	SITagManager->AddNewGameplayTag_Internal(AbilityTag, Payload);
}

void ASI_PlayerController::RequestMultiOptionRight()
{
	if(bInAdaptableActionMode)
	{
		RequestConfirmAbility();
	}
	
	USI_UIManager* UIManager = GetGameInstance()->GetSubsystem<USI_UIManager>();
	if(!IsValid(UIManager)) {LG_LOG(LogLG_PlayerController, Error, "UIManager Is Null cannot retrieve tag") return;}
	
	FGameplayTag AbilityTag = UIManager->GetQuickActionAbilityTag(SITag_Input_Action_MultiOption_Right);

	FSITagPayload* Payload = new FSITagPayload(Nick, Nick);
	SITagManager->AddNewGameplayTag_Internal(AbilityTag, Payload);
}

void ASI_PlayerController::RequestGizboMultiOptionUp()
{
	USI_UIManager* UIManager = GetGameInstance()->GetSubsystem<USI_UIManager>();
	if(!IsValid(UIManager)) {LG_LOG(LogLG_PlayerController, Error, "UIManager Is Null cannot retrieve tag") return;}
	
	FGameplayTag AbilityTag = UIManager->GetQuickActionAbilityTag(SITag_Input_Action_MultiOption_Up);

	FSITagPayload* Payload = new FSITagPayload(Nick, Gizbo);
	SITagManager->AddNewGameplayTag_Internal(AbilityTag, Payload);
}

void ASI_PlayerController::RequestGizboMutliOptionDown()
{
	USI_UIManager* UIManager = GetGameInstance()->GetSubsystem<USI_UIManager>();
	if(!IsValid(UIManager)) {LG_LOG(LogLG_PlayerController, Error, "UIManager Is Null cannot retrieve tag") return;}
	
	FGameplayTag AbilityTag = UIManager->GetQuickActionAbilityTag(SITag_Input_Action_MultiOption_Down);

	FSITagPayload* Payload = new FSITagPayload(Nick, Gizbo);
	SITagManager->AddNewGameplayTag_Internal(AbilityTag, Payload);
}

void ASI_PlayerController::RequestGizboMultiOptionLeft()
{
	USI_UIManager* UIManager = GetGameInstance()->GetSubsystem<USI_UIManager>();
	if(!IsValid(UIManager)) {LG_LOG(LogLG_PlayerController, Error, "UIManager Is Null cannot retrieve tag") return;}
	
	FGameplayTag AbilityTag = UIManager->GetQuickActionAbilityTag(SITag_Input_Action_MultiOption_Left);

	FSITagPayload* Payload = new FSITagPayload(Nick, Gizbo);
	SITagManager->AddNewGameplayTag_Internal(AbilityTag, Payload);
}

void ASI_PlayerController::RequestGizboMultiOptionRight()
{
	USI_UIManager* UIManager = GetGameInstance()->GetSubsystem<USI_UIManager>();
	if(!IsValid(UIManager)) {LG_LOG(LogLG_PlayerController, Error, "UIManager Is Null cannot retrieve tag") return;}
	
	FGameplayTag AbilityTag = UIManager->GetQuickActionAbilityTag(SITag_Input_Action_MultiOption_Right);

	FSITagPayload* Payload = new FSITagPayload(Nick, Gizbo);
	SITagManager->AddNewGameplayTag_Internal(AbilityTag, Payload);
}

void ASI_PlayerController::SetInteractableActor(AActor* InInteractableActor)
{
	InteractableActor = InInteractableActor;
}

AActor* ASI_PlayerController::GetInteractableActor()
{
	return InteractableActor;
}

void ASI_PlayerController::SetObservableActor(AActor* InObservableActor)
{
	ObservableActor = InObservableActor;
}

void ASI_PlayerController::AddInputMappingByTag(const FGameplayTag InMappingTag, const FGameplayTag InSecondaryTag)
{
	if (!InMappingTag.IsValid()) {LG_LOG(LogLG_PlayerController, Error, "InMappingTag Is invalid cannot add InputMapping") return;}
	
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	const UInputMappingContext* MappingToAdd = EnhancedInputSettings->GetInputConfig()->GetInputMappingByTag(InMappingTag, InSecondaryTag);
	const FModifyContextOptions ModifyContextOptions;
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(MappingToAdd, 0, ModifyContextOptions);
}

void ASI_PlayerController::RemoveInputMappingByTag(const FGameplayTag InMappingTag, const FGameplayTag InSecondaryTag)
{
	if (!InMappingTag.IsValid()) {LG_LOG(LogLG_PlayerController, Error, "InMappingTag Is invalid cannot add InputMapping") return;}
	
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