// Fill out your copyright notice in the Description page of Project Settings.


#include "SI_PlayerManager.h"
#include "SI_GameplayTagManager.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "Components/Actor/SI_EnhancedInputComponent.h"
#include "Controllers/SI_PlayerController.h"
#include "UI/SI_UserWidget.h"

void USI_PlayerManager::RequestNewPlayerState(const FGameplayTag& InPlayerState)
{
	if(!InPlayerState.IsValid() || !SITagManager->HasParentTag(InPlayerState,SITag_Player_State)) {return;}

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

void USI_PlayerManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());
}

void USI_PlayerManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
	PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());

	if (SITagManager->HasParentTag(InAddedTag, SITag_UI_Menu))
	{
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Menu,SITag_Player_State);
		if (!IsValid(PlayerController)){return;}
		PlayerController->SetMenuMode(true);
		return;
	}
	if (SITagManager->HasParentTag(InAddedTag, SITag_UI_Screen))
	{
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Inactive,SITag_Player_State);
		return;
	}
	if (SITagManager->HasParentTag(InAddedTag, SITag_Media))
	{
		SecondaryMediaTag = InAddedTag;
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Media,SITag_Player_State);
		return;
	}
	
	if(!SITagManager->HasParentTag(InAddedTag, SITag_Player)){return;}
	
	Super::OnGameplayTagAdded(InAddedTag);

	if(SITagManager->HasParentTag(InAddedTag, SITag_Player_State))
	{
		CurrentPlayerState = InAddedTag;
	}

	if(InAddedTag == SITag_Player_State_Media)
	{
		if (!IsValid(PlayerController)){return;}
		PlayerController->AddInputMappingByTag(InAddedTag, SecondaryMediaTag);
		PlayerDelegateContainer.Find(InAddedTag)->Execute();
		return;
	}

	PlayerDelegateContainer.Find(InAddedTag)->Execute();

	if (!IsValid(PlayerController)){return;}
	PlayerController->AddInputMappingByTag(InAddedTag);
	
}

void USI_PlayerManager::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
	PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());

	if (SITagManager->HasParentTag(InRemovedTag, SITag_UI_Menu))
	{
		SITagManager->RemoveTag(SITag_Player_State_Menu);
		if (!IsValid(PlayerController)){return;}
		PlayerController->SetMenuMode(false);
		return;
	}
	if (SITagManager->HasParentTag(InRemovedTag, SITag_UI_Screen))
	{
		SITagManager->RemoveTag(SITag_Player_State_Inactive);
		return;
	}
	
	if(!SITagManager->HasParentTag(InRemovedTag, SITag_Player)){return;}

	Super::OnGameplayTagRemoved(InRemovedTag);

	if(SITagManager->HasParentTag(InRemovedTag, SITag_Player_State))
	{
		PreviousPlayerState = InRemovedTag;
	}

	if (!IsValid(PlayerController)){return;}
	PlayerController->RemoveInputMappingByTag(InRemovedTag);
}

void USI_PlayerManager::InitializeDelegates()
{
	Super::InitializeDelegates();

	DialogueStateDelegate.BindUObject(this, &ThisClass::SetupDialogueState);
	ExplorationStateDelegate.BindUObject(this, &ThisClass::SetupExplorationState);
	GizboActionsStateDelegate.BindUObject(this, &ThisClass::SetupGizboActionsState);
	InactiveStateDelegate.BindUObject(this, &ThisClass::SetupInactiveState);
	InterrogationStateDelegate.BindUObject(this, &ThisClass::SetupInterrogationState);
	MediaStateDelegate.BindUObject(this, &ThisClass::SetupMenuState);
	MenuStateDelegate.BindUObject(this, &ThisClass::SetupMenuState);
	ObservationStateDelegate.BindUObject(this, &ThisClass::SetupObservationState);
	
}

void USI_PlayerManager::InitializeDelegateMaps()
{
	Super::InitializeDelegateMaps();

	PlayerDelegateContainer.Add(SITag_Player_State_Dialogue, DialogueStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Exploration, ExplorationStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_GizboActions, GizboActionsStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Inactive, InactiveStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Interrogation, InterrogationStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Media, MediaStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Menu, MenuStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Observation, ObservationStateDelegate);
	
}

void USI_PlayerManager::SetupDialogueState()
{
}

void USI_PlayerManager::SetupExplorationState()
{
}

void USI_PlayerManager::SetupGizboActionsState()
{
}

void USI_PlayerManager::SetupInactiveState()
{
}

void USI_PlayerManager::SetupInterrogationState()
{
}

void USI_PlayerManager::SetupMenuState()
{
}

void USI_PlayerManager::SetupObservationState()
{
}