// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_PlayerManager.h"
#include "AoS_GameplayTagManager.h"
#include "AoS_NativeGameplayTagLibrary.h"

void UAoS_PlayerManager::RequestNewPlayerState(const FGameplayTag& InPlayerState)
{
	if(!InPlayerState.IsValid() || !AoSTagManager->HasParentTag(InPlayerState,AOSTag_Player_State)) {return;}

	AoSTagManager->ReplaceTagWithSameParent(InPlayerState, AOSTag_Player_State);
}

void UAoS_PlayerManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UAoS_PlayerManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
	if(!AoSTagManager->HasParentTag(InAddedTag, AOSTag_Player)){return;}

	Super::OnGameplayTagAdded(InAddedTag);
}

void UAoS_PlayerManager::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
	if(!AoSTagManager->HasParentTag(InRemovedTag, AOSTag_Player)){return;}

	Super::OnGameplayTagRemoved(InRemovedTag);
	
}

void UAoS_PlayerManager::InitializeDelegates()
{
	Super::InitializeDelegates();
	
}

void UAoS_PlayerManager::InitializeDelegateMaps()
{
	Super::InitializeDelegateMaps();
	
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
