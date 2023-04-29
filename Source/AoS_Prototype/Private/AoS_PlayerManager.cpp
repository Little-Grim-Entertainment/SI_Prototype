// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_PlayerManager.h"
#include "AoS_GameplayTagManager.h"
#include "AoS_NativeGameplayTagLibrary.h"
#include "Components/Actor/AoS_EnhancedInputComponent.h"
#include "Controllers/AoS_PlayerController.h"
#include "UI/AoS_UserWidget.h"

void UAoS_PlayerManager::RequestNewPlayerState(const FGameplayTag& InPlayerState)
{
	if(!InPlayerState.IsValid() || !AoSTagManager->HasParentTag(InPlayerState,AOSTag_Player_State)) {return;}

	AoSTagManager->ReplaceTagWithSameParent(InPlayerState, AOSTag_Player_State);

	PreviousPlayerState = CurrentPlayerState;
	CurrentPlayerState = InPlayerState;
}

const FGameplayTag& UAoS_PlayerManager::GetCurrentPlayerState() const
{
	return CurrentPlayerState;
}

const FGameplayTag& UAoS_PlayerManager::GetPreviousPlayerState() const
{
	return PreviousPlayerState;
}

void UAoS_PlayerManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
}

void UAoS_PlayerManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
	PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());

	if (AoSTagManager->HasParentTag(InAddedTag, AOSTag_UI_Menu))
	{
		AoSTagManager->ReplaceTagWithSameParent(AOSTag_Player_State_Menu,AOSTag_Player_State);
		if (!IsValid(PlayerController)){return;}
		PlayerController->SetMenuMode(true);
		return;
	}
	if (AoSTagManager->HasParentTag(InAddedTag, AOSTag_UI_Screen))
	{
		AoSTagManager->ReplaceTagWithSameParent(AOSTag_Player_State_Inactive,AOSTag_Player_State);
		return;
	}
	if (AoSTagManager->HasParentTag(InAddedTag, AOSTag_Media))
	{
		SecondaryMediaTag = InAddedTag;
		AoSTagManager->ReplaceTagWithSameParent(AOSTag_Player_State_Media,AOSTag_Player_State);
		return;
	}
	
	if(!AoSTagManager->HasParentTag(InAddedTag, AOSTag_Player)){return;}
	
	Super::OnGameplayTagAdded(InAddedTag);

	if(AoSTagManager->HasParentTag(InAddedTag, AOSTag_Player_State))
	{
		CurrentPlayerState = InAddedTag;
	}

	if(InAddedTag == AOSTag_Player_State_Media)
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

void UAoS_PlayerManager::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
	PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());

	if (AoSTagManager->HasParentTag(InRemovedTag, AOSTag_UI_Menu))
	{
		AoSTagManager->RemoveTag(AOSTag_Player_State_Menu);
		if (!IsValid(PlayerController)){return;}
		PlayerController->SetMenuMode(false);
		return;
	}
	if (AoSTagManager->HasParentTag(InRemovedTag, AOSTag_UI_Screen))
	{
		AoSTagManager->RemoveTag(AOSTag_Player_State_Inactive);
		return;
	}
	
	if(!AoSTagManager->HasParentTag(InRemovedTag, AOSTag_Player)){return;}

	Super::OnGameplayTagRemoved(InRemovedTag);

	if(AoSTagManager->HasParentTag(InRemovedTag, AOSTag_Player_State))
	{
		PreviousPlayerState = InRemovedTag;
	}

	if (!IsValid(PlayerController)){return;}
	PlayerController->RemoveInputMappingByTag(InRemovedTag);
}

void UAoS_PlayerManager::InitializeDelegates()
{
	Super::InitializeDelegates();
	
	ExplorationStateDelegate.BindUObject(this, &ThisClass::SetupExplorationState);
	ObservationStateDelegate.BindUObject(this, &ThisClass::SetupObservationState);
	MenuStateDelegate.BindUObject(this, &ThisClass::SetupMenuState);
	MediaStateDelegate.BindUObject(this, &ThisClass::SetupMenuState);
	DialogueStateDelegate.BindUObject(this, &ThisClass::SetupDialogueState);
	InterrogationStateDelegate.BindUObject(this, &ThisClass::SetupInterrogationState);
	InactiveStateDelegate.BindUObject(this, &ThisClass::SetupInactiveState);
}

void UAoS_PlayerManager::InitializeDelegateMaps()
{
	Super::InitializeDelegateMaps();

	PlayerDelegateContainer.Add(AOSTag_Player_State_Exploration, ExplorationStateDelegate);
	PlayerDelegateContainer.Add(AOSTag_Player_State_Observation, ObservationStateDelegate);
	PlayerDelegateContainer.Add(AOSTag_Player_State_Menu, MenuStateDelegate);
	PlayerDelegateContainer.Add(AOSTag_Player_State_Media, MediaStateDelegate);
	PlayerDelegateContainer.Add(AOSTag_Player_State_Dialogue, DialogueStateDelegate);
	PlayerDelegateContainer.Add(AOSTag_Player_State_Interrogation, InterrogationStateDelegate);
	PlayerDelegateContainer.Add(AOSTag_Player_State_Inactive, InactiveStateDelegate);
}

void UAoS_PlayerManager::SetupExplorationState()
{
}

void UAoS_PlayerManager::SetupObservationState()
{
}

void UAoS_PlayerManager::SetupMenuState()
{
}

void UAoS_PlayerManager::SetupDialogueState()
{
}

void UAoS_PlayerManager::SetupInterrogationState()
{
}

void UAoS_PlayerManager::SetupInactiveState()
{
}
