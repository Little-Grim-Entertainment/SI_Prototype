// Fill out your copyright notice in the Description page of Project Settings.


#include "SI_PlayerManager.h"
#include "GameplayTags/SI_GameplayTagManager.h"
#include "GameplayTags/SI_GameplayTagTypes.h"
#include "Controllers/SI_PlayerController.h"
#include "Levels/Data/SI_MapData.h"
#include "Levels/SI_LevelManager.h"
#include "Characters/SI_Nick.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"
#include "Dialogue/SI_DialogueManager.h"

void USI_PlayerManager::RequestNewPlayerState(const FGameplayTag& InPlayerState)
{
	if(!InPlayerState.IsValid() || !SITagManager->HasParentTag(InPlayerState,SITag_Player_State))
		{UE_LOG(LogLG_PlayerManager, VeryVerbose, TEXT("SITagManager does not have a parenttag of SITag_Player_State!")); return;}

	SITagManager->ReplaceTagWithSameParent(InPlayerState, SITag_Player_State);

	PreviousPlayerState = CurrentPlayerState;
	CurrentPlayerState = InPlayerState;	
}

const FGameplayTag& USI_PlayerManager::GetCurrentPlayerState() const
{
	return CurrentPlayerState;
}

const FGameplayTag& USI_PlayerManager::GetPreviousPlayerState() const
{
	return PreviousPlayerState;
}

void USI_PlayerManager::ShowWorld(bool bShouldShow, bool bShouldFade)
{
	if (!IsValid(PlayerController))
		{UE_LOG(LogLG_PlayerManager, Error, TEXT("PlayerController is null unable to show world!")); return;}

	if(bShouldShow)
	{
		if(bShouldFade)
		{
			PlayerController->PlayerCameraManager->StartCameraFade(1, 0, .5, FLinearColor::Black, false, true);
		}
		else
		{
			PlayerController->PlayerCameraManager->StartCameraFade(1, 0, 0, FLinearColor::Black, false, true);
		}
	}
	else
	{
		if(bShouldFade)
		{
			PlayerController->PlayerCameraManager->StartCameraFade(0, 1, .5, FLinearColor::Black, false, true);
		}
		else
		{
			PlayerController->PlayerCameraManager->StartCameraFade(0, 1, .0, FLinearColor::Black, false, true);
		}
	}

	bShowWorld = bShouldShow;
}

USI_AbilitySystemComponent* USI_PlayerManager::GetNickAbilitySystemComponent()
{
	// TODO: @Pace Player Controller is null, fix this
	if(!IsValid(PlayerController)) {return nullptr;}
	
	if(!IsValid(NickAbilitySystemComponent))
	{
		NickAbilitySystemComponent = PlayerController->GetNick()->GetSIAbilitySystemComponent();
	}
	
	return NickAbilitySystemComponent;
}

void USI_PlayerManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
}

//Called from listener of GameplayTagManager OnTagAddedDelegate.Broadcast() in AddNewGameplayTag()
void USI_PlayerManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload)
{
	if(!IsValid(GetWorld())) {}
	
	Super::OnGameplayTagAdded(InAddedTag);
		
	if (SITagManager->HasParentTag(InAddedTag, SITag_UI_Menu))
	{
		if(InAddedTag == SITag_UI_Menu_System)
		{
			SecondaryMenuTag = InAddedTag;
			SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Menu,SITag_Player_State);
			if (!IsValid(PlayerController))
			{UE_LOG(LogLG_PlayerManager, Error, TEXT("PlayerController is null unable to set menu mode!")); return; }

			PlayerController->SetMenuMode(true);
			return;
		}
	}
	if(SITagManager->HasParentTag(InAddedTag, SITag_UI_Screen))
	{
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Inactive,SITag_Player_State);
		return;
	}
	if(SITagManager->HasParentTag(InAddedTag, SITag_Media))
	{
		SecondaryMediaTag = InAddedTag;
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Media,SITag_Player_State);
		return;
	}
	
	if(!SITagManager->HasParentTag(InAddedTag, SITag_Player))
		{UE_LOG(LogLG_PlayerManager, VeryVerbose, TEXT("%s does not have a parenttag of SITag_Player!"),*InAddedTag.ToString()); return;}
	
	if(SITagManager->HasParentTag(InAddedTag, SITag_Player_State))
	{
		CurrentPlayerState = InAddedTag;
	}

	if(InAddedTag != SITag_Player_State_Exploration && InAddedTag != SITag_Player_State_Dialogue)
	{
		SITagManager->RemoveTag(SITag_UI_HUD);
	}

	if(InAddedTag == SITag_Player_State_Media)
	{
		if (!IsValid(PlayerController))
			{UE_LOG(LogLG_PlayerManager, Error, TEXT("PlayerController is null unable to add media input!")); return;}

		PlayerController->AddInputMappingByTag(InAddedTag, SecondaryMediaTag);
		PlayerDelegateContainer.Find(InAddedTag)->Execute();
		return;
	}

	if(InAddedTag == SITag_Player_State_Menu)
	{
		if (!IsValid(PlayerController)){return;}
		PlayerController->AddInputMappingByTag(InAddedTag, SecondaryMenuTag);
		PlayerDelegateContainer.Find(InAddedTag)->Execute();
		return;
	}

	PlayerDelegateContainer.Find(InAddedTag)->Execute();

	if(!IsValid(PlayerController))
		{UE_LOG(LogLG_PlayerManager, Error, TEXT("PlayerController is null unable to add input!")); return; }

	PlayerController->AddInputMappingByTag(InAddedTag);
}

//Called from listener of GameplayTagManager OnTagRemovedDelegate.Broadcast() in RemoveTag()
void USI_PlayerManager::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag, FSITagPayload* InTagPayload)
{
	if(!IsValid(GetWorld()))
		{UE_LOG(LogLG_PlayerManager, Error, TEXT("World is null unable to remove tag!")); return;}
	
	Super::OnGameplayTagRemoved(InRemovedTag);
	
	if(SITagManager->HasParentTag(InRemovedTag, SITag_UI_Menu))
	{
		SecondaryMenuTag = FGameplayTag();
		if(InRemovedTag == SITag_UI_Menu_Map)
		{
			SITagManager->RemoveTag_Internal(SITag_Player_State_Menu);
		}
		else
		{
			SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Exploration, SITag_Player_State);
		}
		if (!IsValid(PlayerController))
			{UE_LOG(LogLG_PlayerManager, Error, TEXT("PlayerController is null unable to set menu mode!")); return;}

		PlayerController->SetMenuMode(false);
		return;
	}

	if(SITagManager->HasParentTag(InRemovedTag, SITag_Media))
	{
		SecondaryMediaTag = FGameplayTag();
		return;
	}
	
	if(SITagManager->HasParentTag(InRemovedTag, SITag_UI_Screen))
	{
		SITagManager->RemoveTag_Internal(SITag_Player_State_Inactive);
		return;
	}
	
	if(!SITagManager->HasParentTag(InRemovedTag, SITag_Player))
		{UE_LOG(LogLG_PlayerManager, VeryVerbose, TEXT("%s does not have a parenttag of SITag_Player!"),*InRemovedTag.ToString()); return;}

	if(InRemovedTag == SITag_Player_State_Dialogue)
	{
		SITagManager->RemoveTag(SITag_UI_HUD_Dialogue);
	}
	else if(InRemovedTag == SITag_Player_State_Interrogation)
	{
		SITagManager->RemoveTag(SITag_UI_Menu_Interrogation);
	}

	if(SITagManager->HasParentTag(InRemovedTag, SITag_Player_State))
	{
		PreviousPlayerState = InRemovedTag;
	}
	
	if(!IsValid(PlayerController))
		{UE_LOG(LogLG_PlayerManager, Error, TEXT("PlayerController is null unable to remove input!")); return;}

	PlayerController->RemoveInputMappingByTag(InRemovedTag);
}

void USI_PlayerManager::OnPlayerStart()
{
	Super::OnPlayerStart();

	PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());
	
	ShowWorld(false, false);
}

void USI_PlayerManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();
	
	if(!bShowWorld)
	{
		ShowWorld(true, true);
	}
}

void USI_PlayerManager::InitializeDelegates()
{
	Super::InitializeDelegates();
	
	DialogueStateDelegate.BindUObject(this, &ThisClass::SetupDialogueState);
	ExplorationStateDelegate.BindUObject(this, &ThisClass::SetupExplorationState);
	InactiveStateDelegate.BindUObject(this, &ThisClass::SetupInactiveState);
	InterrogationStateDelegate.BindUObject(this, &ThisClass::SetupInterrogationState);
	MediaStateDelegate.BindUObject(this, &ThisClass::SetupMenuState);
	MenuStateDelegate.BindUObject(this, &ThisClass::SetupMenuState);
	ObservationStateDelegate.BindUObject(this, &ThisClass::SetupObservationState);
	PossessMovableStateDelegate.BindUObject(this, &ThisClass::SetupPossessMovableState);
	PossessIndicatorStateDelegate.BindUObject(this, &ThisClass::SetupPossessIndicatorState);
	
}

void USI_PlayerManager::InitializeDelegateMaps()
{
	Super::InitializeDelegateMaps();

	PlayerDelegateContainer.Add(SITag_Player_State_Dialogue, DialogueStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Exploration, ExplorationStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Inactive, InactiveStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Interrogation, InterrogationStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Media, MediaStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Menu, MenuStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Observation, ObservationStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_PossessIndicator, PossessIndicatorStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_PossessMovable, PossessMovableStateDelegate);
}


void USI_PlayerManager::SetupDialogueState()
{
	SITagManager->AddNewGameplayTag(SITag_UI_HUD_Dialogue);
	SITagManager->ReplaceTagWithSameParent(SITag_Camera_Mode_Dialogue, SITag_Camera_Mode);
}

void USI_PlayerManager::SetupExplorationState()
{
	TObjectPtr<UWorld> TempWorld = GetWorld();
	if(!IsValid(TempWorld)) {UE_LOG(LogLG_PlayerManager, Error, TEXT("World is null unable to set exploration mode!")); return;}
	TObjectPtr<UGameInstance> TempGameInstance = TempWorld->GetGameInstance();
	if(!IsValid(TempGameInstance)) {UE_LOG(LogLG_PlayerManager, Error, TEXT("GameInstance is null unable to set exploration mode!")); return;}
	TObjectPtr<USI_LevelManager> SILevelManager = TempGameInstance->GetSubsystem<USI_LevelManager>();
	if (!IsValid(SILevelManager) || !IsValid(SILevelManager->GetCurrentMap()))
		{UE_LOG(LogLG_PlayerManager, Error, TEXT("SILevelManager or SILevelManager->GetCurrentMap() is null unable to set exploration mode!")); return;}

	if(!SITagManager->HasGameplayTag(SITag_UI_HUD))
	{
		SITagManager->AddNewGameplayTag_Internal(SITag_UI_HUD);
	}
	
	if (SILevelManager->GetCurrentMap()->MapType == SITag_Map_Type_Interior)
	{
		SITagManager->ReplaceTagWithSameParent(SITag_Camera_Mode_InDoor, SITag_Camera_Mode);
		return;
	}
	SITagManager->ReplaceTagWithSameParent(SITag_Camera_Mode_OutDoor, SITag_Camera_Mode);
}

void USI_PlayerManager::SetupInactiveState()
{
}

void USI_PlayerManager::SetupInterrogationState()
{
	SITagManager->ReplaceTagWithSameParent(SITag_UI_Menu_Interrogation, SITag_UI_Menu);
}

void USI_PlayerManager::SetupMenuState()
{
}

void USI_PlayerManager::SetupObservationState()
{
	SITagManager->ReplaceTagWithSameParent(SITag_Camera_Mode_Observation, SITag_Camera_Mode);
}

void USI_PlayerManager::SetupPossessIndicatorState()
{
}

void USI_PlayerManager::SetupPossessMovableState()
{
	SITagManager->ReplaceTagWithSameParent(SITag_Camera_Mode_PossessMovable, SITag_Camera_Mode);
}
