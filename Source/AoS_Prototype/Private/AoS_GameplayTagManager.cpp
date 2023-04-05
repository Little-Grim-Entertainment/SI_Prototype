// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_GameplayTagManager.h"

#include "AoS_NativeGameplayTagLibrary.h"
#include "Levels/AoS_MapGameplayTagLibrary.h"

void UAoS_GameplayTagManager::AddNewGameplayTag(const FGameplayTag& InGameplayTag)
{
	FGameplayTagContainer& ContainerToAddTo = GetContainerTypeByTag(InGameplayTag);
	if (ContainerToAddTo.HasTagExact(InGameplayTag)) {return;}

	ContainerToAddTo.AddTag(InGameplayTag);
	OnTagAddedDelegate.Broadcast(InGameplayTag);
}

void UAoS_GameplayTagManager::RemoveTag(const FGameplayTag& InGameplayTag)
{
	FGameplayTagContainer& ContainerToRemoveFrom = GetContainerTypeByTag(InGameplayTag);
	if (!ContainerToRemoveFrom.HasTagExact(InGameplayTag)) {return;}

	ContainerToRemoveFrom.RemoveTag(InGameplayTag);
	OnTagRemovedDelegate.Broadcast(InGameplayTag);
}

bool UAoS_GameplayTagManager::HasGameplayTag(const FGameplayTag& InGameplayTag)
{
	if (!InGameplayTag.IsValid()){return false;}

	TArray<FGameplayTagContainer>& AllTagContainers = GetAllTagContainers();

	for (const FGameplayTagContainer& CurrentContainer : AllTagContainers)
	{
		if (CurrentContainer.HasTagExact(InGameplayTag))
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
	if (TraitTagString.Contains(ParentTagString))
	{
		return true;
	}
	
	return false;
}

TArray<FGameplayTagContainer>& UAoS_GameplayTagManager::GetAllTagContainers() 
{
	static TArray<FGameplayTagContainer> AllTagContainers = TArray
{
	GameStateTags,
	PlayerModeTags,
	UITags,
	LevelTags,
	MediaTags, 
	CameraTags
};
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

bool UAoS_GameplayTagManager::CheckContainerForParentTag(const FGameplayTag& InParentTag, const FGameplayTagContainer& InContainerToCheck) const
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

FGameplayTagContainer& UAoS_GameplayTagManager::GetContainerTypeByTag(const FGameplayTag& InGameplayTag)
{
	if (HasParentTag(InGameplayTag, AoS_NativeGameplayTagLibrary::AOSTag_Game_State))
	{
		return GameStateTags;
	}
	if (HasParentTag(InGameplayTag, AoS_NativeGameplayTagLibrary::AOSTag_Player_Mode))
	{
		return PlayerModeTags;
	}
	if (HasParentTag(InGameplayTag, AoS_NativeGameplayTagLibrary::AOSTag_UI))
	{
		return UITags;
	}
	if (HasParentTag(InGameplayTag, AoS_MapGameplayTagLibrary::AOSTag_Map))
	{
		return LevelTags;
	}
	if (HasParentTag(InGameplayTag, AoS_NativeGameplayTagLibrary::AOSTag_Media))
	{
		return MediaTags;
	}
	if (HasParentTag(InGameplayTag, AoS_NativeGameplayTagLibrary::AOSTag_Camera))
	{
		return CameraTags;
	}
	
	static FGameplayTagContainer EmptyContainer;
	return EmptyContainer;
}




