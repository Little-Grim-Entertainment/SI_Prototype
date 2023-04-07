// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_GameplayTagManager.h"

#include "AoS_GameplayTagTypes.h"


void UAoS_GameplayTagManager::AddNewGameplayTag(const FGameplayTag& InGameplayTag)
{
	FAoS_GameplayTagContainer& ContainerToAddTo = GetContainerTypeByTag(InGameplayTag);
	if (ContainerToAddTo.HasTagExact(InGameplayTag)) {return;}

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
	TArray<FGameplayTag> AllGameplayTags;
	const FAoS_GameplayTagContainer& TagTypeContainer = GetContainerTypeByTag(InNewTag);
	if(!TagTypeContainer.IsValid()){return;}

	TagTypeContainer.GetGameplayTagArray(AllGameplayTags);

	for (FGameplayTag& CurrentGameplayTag : AllGameplayTags)
	{
		if (HasParentTag(CurrentGameplayTag, InParentTag))
		{
			RemoveTag(CurrentGameplayTag);
		}
	}
	
	AddNewGameplayTag(InNewTag);
}

bool UAoS_GameplayTagManager::HasGameplayTag(const FGameplayTag& InGameplayTag)
{
	if (!InGameplayTag.IsValid()){return false;}

	TArray<FAoS_GameplayTagContainer>& AllTagContainers = GetAllTagContainers();

	for (const FAoS_GameplayTagContainer& CurrentContainer : AllTagContainers)
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

TArray<FAoS_GameplayTagContainer>& UAoS_GameplayTagManager::GetAllTagContainers() 
{
	static TArray<FAoS_GameplayTagContainer> AllTagContainers = TArray
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
	TArray<FAoS_GameplayTagContainer>& AllTagContainers = GetAllTagContainers();

	for (FAoS_GameplayTagContainer& CurrentContainer : AllTagContainers)
	{
		if (HasParentTag(InGameplayTag, CurrentContainer.GetParentTag()))
		{
			return CurrentContainer;
		}
	}
		
	static FAoS_GameplayTagContainer EmptyContainer;
	return EmptyContainer;
}




