// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/SI_DialogueManager.h"

#include "Cameras/SI_DialogueCamera.h"
#include "Characters/SI_CharacterGameplayTagLibrary.h"
#include "Characters/SI_CharacterManager.h"
#include "Characters/SI_Nick.h"
#include "Characters/SI_NPC.h"
#include "Controllers/SI_PlayerController.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameModes/SI_GameMode.h"
#include "GameplayTags/SI_GameplayTagManager.h"

void USI_DialogueManager::StartDialogue(ASI_NPC* InNPC)
{
	if(!IsValid(InNPC)) {return;}

	ActiveNPC = InNPC;
	
	ActiveDialogueState = InNPC->GetActiveDialogueState();
	if(!ActiveDialogueState) {return;}

	CurrentDialogueIndex = 0;

	SetNickLocation();
	UpdateActiveSpeaker();
	SpawnDialogueCamera();
		
	SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Dialogue, SITag_Player_State);
}

void USI_DialogueManager::ExitDialogue()
{
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

	SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Exploration, SITag_Player_State);
}

void USI_DialogueManager::OnNextPressed()
{
	if(!ActiveDialogueState) {return;}

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

void USI_DialogueManager::OnPreviousPressed()
{

}

void USI_DialogueManager::OnPressPressed()
{

}

void USI_DialogueManager::OnTextOptionSelected(FText RelatedText)
{

}

void USI_DialogueManager::OnItemOptionSelected(UObject* RelatedItem)
{

}

void USI_DialogueManager::OnInterrogationPressed()
{
	//GameInstance->RequestNewPlayerMode(EPlayerMode::PM_InterrogationMode);
}

FSI_PrimaryDialogue USI_DialogueManager::GetCurrentPrimaryDialogue() const
{
	if(!ActiveDialogueState || ActiveDialogueState->CurrentPrimaryDialogueArray.IsEmpty()) {return FSI_PrimaryDialogue();}

	const FSI_PrimaryDialogue& CurrentPrimaryDialogue = ActiveDialogueState->CurrentPrimaryDialogueArray[CurrentDialogueIndex];

	return CurrentPrimaryDialogue;
}

ASI_Character* USI_DialogueManager::GetActiveSpeaker()
{
	return ActiveSpeaker.Get();
}

void USI_DialogueManager::SetupBindings()
{
	// Get the HUD, get the dialogue box, bind u objects (need to make functions UFUNCTIONs)
}

bool USI_DialogueManager::HasNextOption()
{
	return false;
}

bool USI_DialogueManager::HasPreviousOption()
{
	return false;
}

bool USI_DialogueManager::HasPressOption()
{
	return false;
}

bool USI_DialogueManager::HasTextOptions()
{
	return false;
}

bool USI_DialogueManager::HasItemOptions()
{
	return false;
}

bool USI_DialogueManager::CanEnterInterrogation()
{
	//return (GameInstance->GetPlayerMode() == EPlayerMode::PM_InterrogationMode && CurrentDialogue != nullptr && CurrentDialogue->bIsInterrogationDialogue);
	return false;
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
