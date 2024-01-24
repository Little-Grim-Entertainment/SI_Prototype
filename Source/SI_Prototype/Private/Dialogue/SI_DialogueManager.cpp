// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/SI_DialogueManager.h"

#include "Cameras/SI_DialogueCamera.h"
#include "Characters/SI_CharacterGameplayTagLibrary.h"
#include "Characters/SI_CharacterManager.h"
#include "Characters/SI_Nick.h"
#include "Characters/SI_NPC.h"
#include "Characters/Data/SI_CharacterData.h"
#include "Controllers/SI_PlayerController.h"
#include "Dialogue/Data/SI_DialogueDataAsset.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameModes/SI_GameMode.h"
#include "GameplayTags/SI_GameplayTagManager.h"
#include "UI/Interrogation/SI_InterrogationWidget.h"

void USI_DialogueManager::StartDialogue(ASI_NPC* InNPC)
{
	if(!IsValid(InNPC)) {return;}

	ActiveNPC = InNPC;
	
	ActiveDialogueState = InNPC->GetActiveDialogueState();
	if(!ActiveDialogueState) {return;}

	CurrentDialogueIndex = 0;
	CurrentStatementIndex = 0;
	CurrentSecondaryDialogueIndex = 0;
	
	bCanPress = false;
	bIsPressing = false;
	bIsResponding = false;
	bInterrogationWidgetLoaded = false;
	bActiveInputDelay = false;
	
	SetNickLocation();
	UpdateActiveSpeaker();
	SpawnDialogueCamera();
		
	SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Dialogue, SITag_Player_State);
}

void USI_DialogueManager::ExitDialogue()
{
	if(bActiveInputDelay) {return;}
	
	ActiveDialogueState = nullptr;
	ASI_PlayerController* PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());
	if(IsValid(PlayerController))
	{
		USI_CharacterManager* CharacterManager = GetWorld()->GetSubsystem<USI_CharacterManager>();
		if(IsValid(CharacterManager))
		{
			PlayerController->Possess(CharacterManager->GetNick());
		}
	}

	ActiveSpeaker = nullptr;
	ActiveNPC = nullptr;

	SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Exploration, SITag_Player_State);
}

void USI_DialogueManager::OnNextDialoguePressed()
{
	if(!ActiveDialogueState || bActiveInputDelay) {return;}

	const int32 NextIndex = CurrentDialogueIndex + 1;
	if(NextIndex < ActiveDialogueState->CurrentPrimaryDialogueArray.Num() - 1)
	{
		CurrentDialogueIndex = NextIndex;
		UpdateActiveSpeaker();
	}
	else
	{
		ExitDialogue();
	}
}

void USI_DialogueManager::OnRequestInterrogation()
{
	if(bActiveInputDelay) {return;}
	
	SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Interrogation, SITag_Player_State);
}

void USI_DialogueManager::OnRequestQuitInterrogation()
{
	if(bActiveInputDelay) {return;}
	
	ExitDialogue();
	ActiveInterrogationWidget = nullptr;
}

void USI_DialogueManager::OnNextStatementPressed()
{
	if(bActiveInputDelay) {return;}

	if(!bInterrogationWidgetLoaded || !ActiveDialogueState || ActiveDialogueState->CurrentPrimaryDialogueArray.IsEmpty()) {return;}

	FLGConversationDialogue* NextDialogue;
	
	if(bIsPressing || bIsResponding)
	{
		const FSI_PrimaryDialogue* CurrentPrimaryDialogue = &ActiveDialogueState->CurrentPrimaryDialogueArray[CurrentStatementIndex];
		if(!CurrentPrimaryDialogue) {return;}
		
		if(bIsPressing)
		{
			TArray<FSI_PressDialogue*> PressDialogueArray;
			GetCurrentPressArray(CurrentPrimaryDialogue, PressDialogueArray);

			if(PressDialogueArray.IsEmpty()) {return;}
		
			const int32 NextIndex = CurrentSecondaryDialogueIndex + 1;
			if(NextIndex > PressDialogueArray.Num() - 1)
			{
				ExitPressOrResponse();
				return;
			}
		
			CurrentSecondaryDialogueIndex = NextIndex;
			NextDialogue = PressDialogueArray[CurrentSecondaryDialogueIndex];
		}
		else
		{
			TArray<FSI_ResponseDialogue*> ResponseDialogueArray;
			GetCurrentResponseArray(CurrentPrimaryDialogue, ResponseDialogueArray);

			const int32 NextIndex = CurrentSecondaryDialogueIndex + 1;
			if(NextIndex > ResponseDialogueArray.Num() - 1)
			{
				ExitPressOrResponse();
				return;
			}
		
			CurrentSecondaryDialogueIndex = NextIndex;
			NextDialogue = ResponseDialogueArray[CurrentSecondaryDialogueIndex];
		}
	}
	else
	{
		int32 NextIndex = CurrentStatementIndex + 1;
		if(NextIndex > ActiveDialogueState->CurrentPrimaryDialogueArray.Num() - 1)
		{
			NextIndex = 0;
		}
		
		CurrentStatementIndex = NextIndex;
		NextDialogue = &ActiveDialogueState->CurrentPrimaryDialogueArray[CurrentStatementIndex];
	}

	UpdateInterrogationDialogue(NextDialogue);
}

void USI_DialogueManager::OnPreviousStatementPressed()
{
	if(bActiveInputDelay) {return;}
	
	if(!bInterrogationWidgetLoaded) {return;}
	if(bIsPressing || bIsResponding)
	{
		// TODO: @Jeff Should we notify player can't go backwards during press dialogue or response dialogue?
		return;
	}
	
	if(!ActiveDialogueState || ActiveDialogueState->CurrentPrimaryDialogueArray.IsEmpty()) {return;}
	
	int32 NextIndex = CurrentStatementIndex - 1;
	if(NextIndex < 0)
	{
		NextIndex = ActiveDialogueState->CurrentPrimaryDialogueArray.Num() - 1;
	}
		
	CurrentStatementIndex = NextIndex;
	const FSI_PrimaryDialogue* CurrentPrimaryDialogue = &ActiveDialogueState->CurrentPrimaryDialogueArray[CurrentStatementIndex];

	UpdateInterrogationDialogue(CurrentPrimaryDialogue);
}



void USI_DialogueManager::OnPressPressed()
{
	if(bActiveInputDelay) {return;}
	
	if(!bCanPress || bIsPressing || !ActiveDialogueState || ActiveDialogueState->CurrentPrimaryDialogueArray.IsEmpty()) {return;}
	
	const FSI_PrimaryDialogue* CurrentPrimaryDialogue = &ActiveDialogueState->CurrentPrimaryDialogueArray[CurrentStatementIndex];
	if(!CurrentPrimaryDialogue) {return;}
	
	TArray<FSI_PressDialogue*> PressDialogueArray;
	GetCurrentPressArray(CurrentPrimaryDialogue, PressDialogueArray);

	if(PressDialogueArray.IsEmpty())
	{
		//TODO: @Jeff do we want default Press dialogue?
		DisplayDefaultResponse();
		return;;
	}

	CurrentSecondaryDialogueIndex = 0;
	
	const FSI_PressDialogue* CurrentPressDialogue = PressDialogueArray[CurrentSecondaryDialogueIndex];
	if(!CurrentPressDialogue) {return;}
	
	UpdateInterrogationDialogue(CurrentPressDialogue);
	bIsPressing = true;
}

void USI_DialogueManager::OnPresentPressed()
{
	if(!bIsPressing || bActiveInputDelay) {return;}

	// Add present UI
}

void USI_DialogueManager::ExitPressOrResponse()
{
	if(!ActiveDialogueState || ActiveDialogueState->CurrentPrimaryDialogueArray.IsEmpty()) {return;}

	const FSI_PrimaryDialogue* CurrentPrimaryDialogue = &ActiveDialogueState->CurrentPrimaryDialogueArray[CurrentStatementIndex];
	if(!CurrentPrimaryDialogue) {return;}

	UpdateInterrogationDialogue(CurrentPrimaryDialogue);
	bIsPressing = false;
	bIsResponding = false;
}

FSI_PrimaryDialogue USI_DialogueManager::GetCurrentPrimaryDialogue() const
{
	if(!ActiveDialogueState || ActiveDialogueState->CurrentPrimaryDialogueArray.IsEmpty()) {return FSI_PrimaryDialogue();}

	const FSI_PrimaryDialogue& CurrentPrimaryDialogue = ActiveDialogueState->CurrentPrimaryDialogueArray[CurrentDialogueIndex];

	return CurrentPrimaryDialogue;
}

FSI_CorrectedDialogue USI_DialogueManager::GetCurrentCorrectedDialogue() const
{
	if(!ActiveDialogueState || ActiveDialogueState->CurrentCorrectedDialogueArray.IsEmpty()) {return FSI_CorrectedDialogue();}

	const FSI_CorrectedDialogue& CurrentCorrectedDialogue = ActiveDialogueState->CurrentCorrectedDialogueArray[CurrentDialogueIndex];

	return CurrentCorrectedDialogue;
}

FSI_DefaultResponse USI_DialogueManager::GetCurrentDefaultResponse() const
{
	if(!ActiveDialogueState || ActiveDialogueState->CurrentDefaultResponseArray.IsEmpty()) {return FSI_DefaultResponse();}

	const FSI_DefaultResponse& CurrentDefaultResponse = ActiveDialogueState->CurrentDefaultResponseArray[CurrentDialogueIndex];

	return CurrentDefaultResponse;
}

ASI_Character* USI_DialogueManager::GetActiveSpeaker()
{
	return ActiveSpeaker.Get();
}

bool USI_DialogueManager::ActiveInputDelay() const
{
	return bActiveInputDelay;
}

void USI_DialogueManager::StartInputDelayTimer(const float& InDelayTime)
{
	UWorld* World = GetWorld();
	if(!IsValid(World)) {return;}

	FTimerHandle InputDelayHandle;
	FTimerDelegate InputDelayDelegate;
	InputDelayDelegate.BindUObject(this, &ThisClass::OnInputDelayEnd_Internal);

	FTimerManager& TimerManager = World->GetTimerManager();
	TimerManager.SetTimer(InputDelayHandle, InputDelayDelegate, InDelayTime, false);
}

FOnInputDelayEnd& USI_DialogueManager::OnInputDelayEnd()
{
	return OnInputDelayEndDelegate;
}

void USI_DialogueManager::SetupBindings()
{
	// Get the HUD, get the dialogue box, bind u objects (need to make functions UFUNCTIONs)
}

void USI_DialogueManager::SetActiveInputDelay(const bool& bInActiveInputDelay)
{
	bActiveInputDelay = bInActiveInputDelay;
}

void USI_DialogueManager::SetActiveInterrogationWidget(USI_InterrogationWidget* InInterrogationWidget)
{
	if(!IsValid(InInterrogationWidget)) {return;}

	ActiveInterrogationWidget = InInterrogationWidget;
	ActiveInterrogationWidget->OnIntroAnimationComplete().AddDynamic(this, &ThisClass::OnInterrogationIntroAnimationComplete);
}

void USI_DialogueManager::InitializeInterrogationWidget()
{
	const ASI_NPC* ActiveNPCPtr = ActiveNPC.Get();
	USI_InterrogationWidget* InterrogationWidget = ActiveInterrogationWidget.Get();
	
	if(!IsValid(ActiveNPCPtr) || !IsValid(InterrogationWidget) || !ActiveDialogueState || ActiveDialogueState->CurrentPrimaryDialogueArray.IsEmpty()) {return;}

	const USI_CharacterData* NPCCharacterData = ActiveNPCPtr->GetCharacterData();
	if(!IsValid(NPCCharacterData))  {return;}

	InterrogationWidget->SetNPCImage(NPCCharacterData->InterrogationImage.Get());
	
	CurrentStatementIndex = 0;
	const FSI_PrimaryDialogue& InitialPrimaryDialogue = ActiveDialogueState->CurrentPrimaryDialogueArray[CurrentStatementIndex];

	UpdateInterrogationDialogue(&InitialPrimaryDialogue);
}

void USI_DialogueManager::GetCurrentPressArray(const FSI_PrimaryDialogue* InCurrentPrimaryDialogue, TArray<FSI_PressDialogue*>& OutPressArray) const
{
	if(!InCurrentPrimaryDialogue || !IsValid(InCurrentPrimaryDialogue->PressDialogueDataTable)) {return;}

	const UDataTable* PressDialogueTable = InCurrentPrimaryDialogue->PressDialogueDataTable;
	if(!IsValid(PressDialogueTable)) {return;}

	PressDialogueTable->GetAllRows(nullptr, OutPressArray);
}

void USI_DialogueManager::GetCurrentResponseArray(const FSI_PrimaryDialogue* InCurrentPrimaryDialogue, TArray<FSI_ResponseDialogue*>& OutResponseArray) const
{
	if(!InCurrentPrimaryDialogue) {return;}

	if(!IsValid(InCurrentPrimaryDialogue->ResponseDialogueDataTable))
	{
		if(!ActiveDialogueState || !IsValid(ActiveDialogueState->ActiveDefaultResponseTable)) {return;}
		const UDataTable* DefaultResponseDialogueTable = ActiveDialogueState->ActiveDefaultResponseTable;

		DefaultResponseDialogueTable->GetAllRows(nullptr, OutResponseArray);
		return;
	}

	const UDataTable* ResponseDialogueTable = InCurrentPrimaryDialogue->ResponseDialogueDataTable;
	if(!IsValid(ResponseDialogueTable)) {return;}

	ResponseDialogueTable->GetAllRows(nullptr, OutResponseArray);
}

void USI_DialogueManager::DisplayDefaultResponse()
{
	if(bIsResponding || !ActiveDialogueState || ActiveDialogueState->CurrentDefaultResponseArray.IsEmpty()) {return;}

	CurrentSecondaryDialogueIndex = 0;

	const FSI_DefaultResponse* CurrentDefaultResponse = &ActiveDialogueState->CurrentDefaultResponseArray[CurrentSecondaryDialogueIndex];
	if(!CurrentDefaultResponse) {return;}
	
	UpdateInterrogationDialogue(CurrentDefaultResponse);
	bIsResponding = true;
}

void USI_DialogueManager::UpdateInterrogationDialogue(const FLGConversationDialogue* InCurrentDialogue)
{
	USI_InterrogationWidget* InterrogationWidget = ActiveInterrogationWidget.Get();
	
	if(!InCurrentDialogue || !IsValid(InterrogationWidget)) {return;}
	if(InCurrentDialogue->SpeakerTag == SI_CharacterGameplayTagLibrary::SITag_Character_Main_NickSpade)
	{
		InterrogationWidget->SetNickDialogue(InCurrentDialogue->Dialogue);
		bCanPress = false;
	}
	else
	{
		InterrogationWidget->SetNPCDialogue(InCurrentDialogue->Dialogue);
		bCanPress = true;
	}
}

void USI_DialogueManager::SetNickLocation()
{
	USI_CharacterManager* CharacterManager = GetWorld()->GetSubsystem<USI_CharacterManager>();
	const ASI_NPC* ActiveNPCPtr = ActiveNPC.Get();
	if(!IsValid(CharacterManager) || !IsValid(ActiveNPCPtr)) {return;}

	ASI_Nick* Nick = CharacterManager->GetNick();
	if(!IsValid(Nick)) {return;}

	const FVector NPCLocation = ActiveNPCPtr->GetActorLocation();
	const FVector NPCForwardVector = ActiveNPCPtr->GetActorForwardVector();
	const FVector Offset = 200.0f * NPCForwardVector;
	const FVector NewNickLocation = FVector(NPCLocation.X + Offset.X, NPCLocation.Y + Offset.Y, Nick->GetActorLocation().Z);

	const FRotator NPCRotation = ActiveNPCPtr->GetActorRotation();
	const FRotator NickRotation = Nick->GetActorRotation();
	float RotationOffset = 180;
	if(NPCRotation.Yaw < 0)
	{
		RotationOffset *= -1.0f;
	}

	const FRotator NewNickRotation = FRotator(NickRotation.Pitch,NPCRotation.Yaw + RotationOffset ,NickRotation.Roll);

	Nick->SetActorLocation(NewNickLocation);
	Nick->SetActorRotation(NewNickRotation);
}

void USI_DialogueManager::UpdateActiveSpeaker()
{
	if(!ActiveDialogueState || ActiveDialogueState->CurrentPrimaryDialogueArray.IsEmpty()) {return;}

	const FSI_PrimaryDialogue& CurrentPrimaryDialogue = ActiveDialogueState->CurrentPrimaryDialogueArray[CurrentDialogueIndex];
	if(CurrentPrimaryDialogue.SpeakerTag == SI_CharacterGameplayTagLibrary::SITag_Character_Main_NickSpade)
	{
		USI_CharacterManager* CharacterManager = GetWorld()->GetSubsystem<USI_CharacterManager>();
		if(IsValid(CharacterManager))
		{
			ActiveSpeaker =  CharacterManager->GetNick();
		}
	}
	else
	{
		ActiveSpeaker = ActiveNPC;
	}
	
	ASI_DialogueCamera* DialogueCameraPtr = DialogueCamera.Get();
	if(!IsValid(DialogueCameraPtr)) {return;}
	
	DialogueCameraPtr->SetNewFocusedCharacter(ActiveSpeaker.Get());
}

void USI_DialogueManager::SpawnDialogueCamera()
{
	UWorld* World = GetWorld();
	ASI_Character* ActiveSpeakerPtr = ActiveSpeaker.Get();
	if(!IsValid(World) || !IsValid(ActiveSpeakerPtr)) {return;}

	const ASI_GameMode* GameMode = Cast<ASI_GameMode>(World->GetAuthGameMode());
	if(!IsValid(GameMode) || !IsValid(GameMode->DialogueCameraClass) || !IsValid(ActiveSpeaker.Get())) {return;}
		
	DialogueCamera = World->SpawnActor<ASI_DialogueCamera>(GameMode->DialogueCameraClass, ActiveSpeakerPtr->GetActorLocation(), ActiveSpeakerPtr->GetActorRotation());

	ASI_DialogueCamera* DialogueCameraPtr = DialogueCamera.Get();
	if(!IsValid(DialogueCameraPtr)) {return;}

	ASI_PlayerController* PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());
	if(IsValid(PlayerController))
	{
		const APawn* PlayerPawn = PlayerController->GetPawn();
		if(IsValid(PlayerPawn))
		{
			UPawnMovementComponent* MovementComponent = PlayerPawn->GetMovementComponent();
			if(IsValid(MovementComponent))
			{
				MovementComponent->StopMovementImmediately();
			}
		}
		PlayerController->StopMovement();
		PlayerController->Possess(DialogueCameraPtr);
	}

	DialogueCameraPtr->SetNewFocusedCharacter(ActiveSpeakerPtr);
}

void USI_DialogueManager::OnInterrogationIntroAnimationComplete()
{
	bInterrogationWidgetLoaded = true;
	InitializeInterrogationWidget();
	
}

void USI_DialogueManager::OnInputDelayEnd_Internal()
{
	bActiveInputDelay = false;
	OnInputDelayEndDelegate.Broadcast();
}

FLGConversationDialogue* USI_DialogueManager::GetCurrentDialogueByType(const int32 InCurrentIndex, const FGameplayTag& InTypeTag)
{
	if(!ActiveDialogueState) {return nullptr;}
	
	if(InTypeTag == SITag_Dialogue_Struct_PrimaryDialogue && !ActiveDialogueState->CurrentPrimaryDialogueArray.IsEmpty() && InCurrentIndex <= ActiveDialogueState->CurrentPrimaryDialogueArray.Num() - 1)
	{
		return &ActiveDialogueState->CurrentPrimaryDialogueArray[InCurrentIndex];
	}
	if(InTypeTag == SITag_Dialogue_Struct_DefaultResponse && !ActiveDialogueState->CurrentDefaultResponseArray.IsEmpty() && InCurrentIndex <= ActiveDialogueState->CurrentDefaultResponseArray.Num() - 1)
	{
		return &ActiveDialogueState->CurrentDefaultResponseArray[InCurrentIndex];
	}
	if(InTypeTag == SITag_Dialogue_Struct_PressDialogue && !ActiveDialogueState->CurrentPrimaryDialogueArray.IsEmpty())
	{
		const FSI_PrimaryDialogue* CurrentPrimaryDialogue = &ActiveDialogueState->CurrentPrimaryDialogueArray[CurrentStatementIndex];
		TArray<FSI_PressDialogue*> PressDialogueArray;
		GetCurrentPressArray(CurrentPrimaryDialogue, PressDialogueArray);
		if(PressDialogueArray.IsEmpty() || InCurrentIndex > PressDialogueArray.Num() - 1) {return nullptr;}
		
		return  PressDialogueArray[InCurrentIndex];
	}
	return nullptr;
}
