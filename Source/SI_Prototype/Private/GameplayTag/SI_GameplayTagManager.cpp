// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayTag/SI_GameplayTagManager.h"

#include "SI_GameInstance.h"
#include "GameplayTag/SI_NativeGameplayTagLibrary.h"
#include "Abilities/SI_AbilityGameplayTagLibrary.h"
#include "Levels/SI_MapGameplayTagLibrary.h"
#include "LG_DebugMacros.h"
#include "SI_Prototype/SI_Prototype.h"

void USI_GameplayTagManager::AddNewGameplayTag(const FGameplayTag& InGameplayTag, FSITagPayload* InTagPayload)
{
	FSI_GameplayTagContainer& ContainerToAddTo = GetContainerTypeByTag(InGameplayTag);
	if (!InGameplayTag.IsValid()) return;

	if(HasParentTag(InGameplayTag, SITag_Ability))
	{
		LG_LOG(LogLG_GameplayTagManager, Log, "Ability Tag Added: %s", *InGameplayTag.ToString());
		OnTagAddedDelegate.Broadcast(InGameplayTag, InTagPayload);
		return;
	}
	
	if(HasParentTag(InGameplayTag, SITag_Behavior))
	{
		LG_LOG(LogLG_GameplayTagManager, Log, "Behavior Tag Added: %s", *InGameplayTag.ToString());
		OnTagAddedDelegate.Broadcast(InGameplayTag, InTagPayload);
		return;
	}
	
	ContainerToAddTo.AddTag(InGameplayTag);
	OnTagAddedDelegate.Broadcast(InGameplayTag, InTagPayload);
}

void USI_GameplayTagManager::RemoveTag(const FGameplayTag& InGameplayTag, FSITagPayload* InTagPayload)
{
	FSI_GameplayTagContainer& ContainerToRemoveFrom = GetContainerTypeByTag(InGameplayTag);
	if (!ContainerToRemoveFrom.HasTagExact(InGameplayTag)) {return;}
	
	ContainerToRemoveFrom.RemoveTag(InGameplayTag);
	OnTagRemovedDelegate.Broadcast(InGameplayTag, InTagPayload);
}

void USI_GameplayTagManager::ClearAllTagsFromContainer(FSI_GameplayTagContainer& InContainerToClear)
{
	TArray<FGameplayTag> AllContainerTags;
	InContainerToClear.GetGameplayTagArray(AllContainerTags);
	for (FGameplayTag& CurrentGameplayTag : AllContainerTags)
	{
		RemoveTag(CurrentGameplayTag);
	}
}

void USI_GameplayTagManager::ReplaceTagWithSameParent(const FGameplayTag& InNewTag, const FGameplayTag& InParentTag)
{
	const FSI_GameplayTagContainer& TagTypeContainer = GetContainerTypeByTag(InNewTag);

	if(TagTypeContainer.HasTagExact(InNewTag)){return;}

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

bool USI_GameplayTagManager::SwapTags(const FGameplayTag& InOldTag, const FGameplayTag& InNewTag)
{
	const FSI_GameplayTagContainer& TagTypeContainer = GetContainerTypeByTag(InOldTag);
	const FSI_GameplayTagContainer& NewTagTypeContainer = GetContainerTypeByTag(InNewTag);

	if(!TagTypeContainer.IsValid() || TagTypeContainer != NewTagTypeContainer){return false;}

	if (TagTypeContainer.HasTag(InOldTag))
	{
		RemoveTag(InOldTag);
		AddNewGameplayTag(InNewTag);
		return true;
	}
	
	return false;
}

bool USI_GameplayTagManager::HasGameplayTag(const FGameplayTag& InGameplayTag)
{
	if (!InGameplayTag.IsValid()){return false;}

	for (const TPair<FGameplayTag, FSI_GameplayTagContainer>& CurrentContainer : AllTagContainers)
	{
		if (CurrentContainer.Value.HasTagExact(InGameplayTag))
		{
			return true;
		}
	}
	
	return false;
}

bool USI_GameplayTagManager::HasParentTag(const FGameplayTag& InTagToCheck, const FGameplayTag& InParentTag) const
{
	if (!InParentTag.IsValid() || !InTagToCheck.IsValid())
	{
		return false;
	}
	
	const FString ParentTagString = InParentTag.ToString();
	const FString TraitTagString = InTagToCheck.ToString();
	
	if(ParentTagString.Len() > TraitTagString.Len()) return false;

	for (int32 CurrentCharIndex = 0; CurrentCharIndex < ParentTagString.Len(); CurrentCharIndex++)
	{
		if(TraitTagString[CurrentCharIndex] != ParentTagString[CurrentCharIndex])
		{
			return false;
		}
	}
	
	return true;
}

TMap<FGameplayTag, FSI_GameplayTagContainer>& USI_GameplayTagManager::GetAllTagContainers() 
{
	return AllTagContainers;
}

FOnTagAdded& USI_GameplayTagManager::OnTagAdded()
{
	return OnTagAddedDelegate;
}

FOnTagAdded& USI_GameplayTagManager::OnTagRemoved()
{
	return OnTagRemovedDelegate;
}

void USI_GameplayTagManager::Initialize(FSubsystemCollectionBase& Collection)
{
	InitializeTagContainers();

	Super::Initialize(Collection);

	GameInstance->OnTagManagerInitialized().Broadcast();
}

bool USI_GameplayTagManager::CheckContainerForParentTag(const FGameplayTag& InParentTag, const FSI_GameplayTagContainer& InContainerToCheck) const
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

FSI_GameplayTagContainer& USI_GameplayTagManager::GetContainerTypeByTag(const FGameplayTag& InGameplayTag)
{
	for (TPair<FGameplayTag, FSI_GameplayTagContainer>& CurrentContainer : AllTagContainers)
	{
		if (HasParentTag(InGameplayTag, CurrentContainer.Value.GetParentTag()))
		{
			return CurrentContainer.Value;
		}
	}
		
	static FSI_GameplayTagContainer EmptyContainer;
	return EmptyContainer;
}

void USI_GameplayTagManager::InitializeTagContainers()
{
	AllTagContainers.Add(SITag_Camera, CameraTags);
	AllTagContainers.Add(SITag_Debug, DebugTags);
	AllTagContainers.Add(SITag_Gadget, GadgetTags);
	AllTagContainers.Add(SITag_Game_State, GameStateTags);
	AllTagContainers.Add(SITag_Map, LevelTags);
	AllTagContainers.Add(SITag_Media, MediaTags);
	AllTagContainers.Add(SITag_Audio_Music, MusicTags);
	AllTagContainers.Add(SITag_Player_State, PlayerStateTags);
	AllTagContainers.Add(SITag_UI, UITags);

	for (TPair<FGameplayTag, FSI_GameplayTagContainer>& CurrentContainerPair : AllTagContainers)
	{
		CurrentContainerPair.Value.SetParentTag(CurrentContainerPair.Key);
	}
}