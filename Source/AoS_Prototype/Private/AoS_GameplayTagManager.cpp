// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_GameplayTagManager.h"

#include "AoS_GameInstance.h"
#include "AoS_GameplayTagTypes.h"
#include "Levels/AoS_MapGameplayTagLibrary.h"


void UAoS_GameplayTagManager::AddNewGameplayTag(const FGameplayTag& InGameplayTag)
{
	FAoS_GameplayTagContainer& ContainerToAddTo = GetContainerTypeByTag(InGameplayTag);
	if (!InGameplayTag.IsValid() || ContainerToAddTo.HasTagExact(InGameplayTag)) {return;}

	ContainerToAddTo.AddTag(InGameplayTag);
	OnTagAddedDelegate.Broadcast(InGameplayTag);
}

void UAoS_GameplayTagManager::RemoveTag(const FGameplayTag& InGameplayTag)
{
	FAoS_GameplayTagContainer& ContainerToRemoveFrom = GetContainerTypeByTag(InGameplayTag);
	if (!ContainerToRemoveFrom.HasTagExact(InGameplayTag)) {return;}

	ContainerToRemoveFrom.RemoveTag(InGameplayTag);
	OnTagRemovedDelegate.Broadcast(InGameplayTag);
}

void UAoS_GameplayTagManager::ClearAllTagsFromContainer(FAoS_GameplayTagContainer& InContainerToClear)
{
	TArray<FGameplayTag> AllContainerTags;
	InContainerToClear.GetGameplayTagArray(AllContainerTags);
	for (FGameplayTag& CurrentGameplayTag : AllContainerTags)
	{
		RemoveTag(CurrentGameplayTag);
	}
}

void UAoS_GameplayTagManager::ReplaceTagWithSameParent(const FGameplayTag& InNewTag, const FGameplayTag& InParentTag)
{
	
	const FAoS_GameplayTagContainer& TagTypeContainer = GetContainerTypeByTag(InNewTag);

	if(TagTypeContainer.HasTag(InNewTag)){return;}

	if(TagTypeContainer.IsValid())
	{
		TArray<FGameplayTag> AllGameplayTags;
		TagTypeContainer.GetGameplayTagArray(AllGameplayTags);
		for (FGameplayTag& CurrentGameplayTag : AllGameplayTags)
		{
			if (HasParentTag(CurrentGameplayTag, InParentTag))
			{
				RemoveTag(CurrentGameplayTag);
			}
		}
	}
	
	AddNewGameplayTag(InNewTag);
}

bool UAoS_GameplayTagManager::SwapTags(const FGameplayTag& InOldTag, const FGameplayTag& InNewTag)
{
	const FAoS_GameplayTagContainer& TagTypeContainer = GetContainerTypeByTag(InOldTag);
	const FAoS_GameplayTagContainer& NewTagTypeContainer = GetContainerTypeByTag(InNewTag);

	if(!TagTypeContainer.IsValid() || TagTypeContainer != NewTagTypeContainer){return false;}

	if (TagTypeContainer.HasTag(InOldTag))
	{
		RemoveTag(InOldTag);
		AddNewGameplayTag(InNewTag);
		return true;
	}
	
	return false;
}

bool UAoS_GameplayTagManager::HasGameplayTag(const FGameplayTag& InGameplayTag)
{
	if (!InGameplayTag.IsValid()){return false;}

	for (const TPair<FGameplayTag, FAoS_GameplayTagContainer>& CurrentContainer : AllTagContainers)
	{
		if (CurrentContainer.Value.HasTagExact(InGameplayTag))
		{
			return true;
		}
	}
	
	return false;
}

bool UAoS_GameplayTagManager::HasParentTag(const FGameplayTag& InTagToCheck, const FGameplayTag& InParentTag) const
{
	if (!InParentTag.IsValid())
	{
		return false;
	}

	const FString ParentTagString = InParentTag.ToString();
	const FString TraitTagString = InTagToCheck.ToString();

	for (int32 CurrentCharIndex = 0; CurrentCharIndex < ParentTagString.Len(); CurrentCharIndex++)
	{
		if(TraitTagString[CurrentCharIndex] != ParentTagString[CurrentCharIndex])
		{
			return false;
		}
	}
	
	return true;
}

TMap<FGameplayTag, FAoS_GameplayTagContainer>& UAoS_GameplayTagManager::GetAllTagContainers() 
{
	return AllTagContainers;
}

FOnTagAdded& UAoS_GameplayTagManager::OnTagAdded()
{
	return OnTagAddedDelegate;
}

FOnTagAdded& UAoS_GameplayTagManager::OnTagRemoved()
{
	return OnTagRemovedDelegate;
}

void UAoS_GameplayTagManager::Initialize(FSubsystemCollectionBase& Collection)
{
	InitializeTagContainers();

	Super::Initialize(Collection);

	GameInstance->OnTagManagerInitialized().Broadcast();
}

bool UAoS_GameplayTagManager::CheckContainerForParentTag(const FGameplayTag& InParentTag, const FAoS_GameplayTagContainer& InContainerToCheck) const
{
	if (!InParentTag.IsValid())
	{
		return false;
	}

	const FString ParentTagString = InParentTag.ToString();
	TArray<FGameplayTag> TraitTags;
	InContainerToCheck.GetGameplayTagArray(TraitTags);
	for(const FGameplayTag& TraitTag : TraitTags)
	{
		const FString TraitTagString = TraitTag.ToString();
		if (TraitTagString.Contains(ParentTagString))
		{
			return true;
		}
	}

	return false;
}

FAoS_GameplayTagContainer& UAoS_GameplayTagManager::GetContainerTypeByTag(const FGameplayTag& InGameplayTag)
{
	for (TPair<FGameplayTag, FAoS_GameplayTagContainer>& CurrentContainer : AllTagContainers)
	{
		if (HasParentTag(InGameplayTag, CurrentContainer.Value.GetParentTag()))
		{
			return CurrentContainer.Value;
		}
	}
		
	static FAoS_GameplayTagContainer EmptyContainer;
	return EmptyContainer;
}

void UAoS_GameplayTagManager::InitializeTagContainers()
{
	AllTagContainers.Add(AOSTag_Game_State, GameStateTags);
	AllTagContainers.Add(AOSTag_Player_State, PlayerStateTags);
	AllTagContainers.Add(AOSTag_UI, UITags);
	AllTagContainers.Add(AOSTag_Map, LevelTags);
	AllTagContainers.Add(AOSTag_Media, MediaTags);
	AllTagContainers.Add(AOSTag_Camera, CameraTags);

	for (TPair<FGameplayTag, FAoS_GameplayTagContainer>& CurrentContainerPair : AllTagContainers)
	{
		CurrentContainerPair.Value.SetParentTag(CurrentContainerPair.Key);
	}
}




