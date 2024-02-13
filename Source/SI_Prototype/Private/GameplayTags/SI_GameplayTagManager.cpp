// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayTags\SI_GameplayTagManager.h"

#include "LG_DebugMacros.h"
#include "SI_GameInstance.h"
#include "Abilities/SI_AbilityGameplayTagLibrary.h"
#include "GameplayTags/SI_NativeGameplayTagLibrary.h"
#include "Characters/SI_NPC.h"
#include "Controllers/SI_NPCController.h"
#include "Levels/SI_MapGameplayTagLibrary.h"
#include "SI_Prototype/SI_Prototype.h"

void USI_GameplayTagManager::AddNewGameplayTag(const FGameplayTag& InGameplayTag)
{
	AddNewGameplayTag_Internal(InGameplayTag);
}

void USI_GameplayTagManager::AddNewGameplayTag_Internal(const FGameplayTag& InGameplayTag, AActor* InCaller, AActor* InTarget)
{
	FSI_GameplayTagContainer& ContainerToAddTo = GetContainerTypeByTag(InGameplayTag);
	if (!InGameplayTag.IsValid()) return;

	FSITagPayload* Payload = new FSITagPayload(InCaller, InTarget);
	
	if(HasParentTag(InGameplayTag, SITag_Ability_Nick))
	{
		LG_LOG(LogLG_GameplayTagManager, Log, "Ability Tag Added: %s", *InGameplayTag.ToString());

		OnTagAddedDelegate.Broadcast(InGameplayTag, Payload);
		return;
	}

	if(HasParentTag(InGameplayTag, SITag_Ability_AI))
	{
		LG_LOG(LogLG_GameplayTagManager, Log, "Ability Tag Added: %s", *InGameplayTag.ToString());

		OnTagAddedDelegate.Broadcast(InGameplayTag, Payload);
		return;
	}
	
	if(HasParentTag(InGameplayTag, SITag_Ability_Adaptable))
	{
		LG_LOG(LogLG_GameplayTagManager, Log, "Ability Tag Added: %s", *InGameplayTag.ToString());
		ASI_NPC* NPC = Cast<ASI_NPC>(InTarget);
		if(IsValid(NPC))
		{
			ASI_NPCController* Controller = Cast<ASI_NPCController>(NPC->GetController());
			if(!IsValid(Controller)) {LG_LOG(LogLG_PlayerController, Error, "Controller Is Null cannot retrieve tag") return;}
			FSI_NPCMemory* NPCMemory = Controller->GetNPCMemory();
			if(!NPCMemory) {LG_LOG(LogLG_PlayerController, Error, "NPCMemory Is Null cannot retrieve tag") return;}

			const FGameplayTag NextActionTag = GetAbilityTagFromAdaptableTag(InGameplayTag);
			if(NextActionTag == InGameplayTag) {LG_LOG(LogLG_GameplayTagManager, Error, "NextActionTag is the same as InGameplayTag did not find AbilityTag it needs to be added to InitializeAdapatableActionTagPairs() ") return;}
			
			NPCMemory->SetNextActionTag(NextActionTag);
			NPCMemory->SetAbilityCaller(InCaller);
			NPCMemory->SetAbilityInstigator(InTarget);
		}
		OnTagAddedDelegate.Broadcast(InGameplayTag, Payload);
		return;
	}
	
	if(HasParentTag(InGameplayTag, SITag_Behavior))
	{
		LG_LOG(LogLG_GameplayTagManager, Log, "Behavior Tag Added: %s", *InGameplayTag.ToString());

		OnTagAddedDelegate.Broadcast(InGameplayTag, Payload);
		return;
	}
	
	ContainerToAddTo.AddTag(InGameplayTag);
	OnTagAddedDelegate.Broadcast(InGameplayTag, Payload);
}

void USI_GameplayTagManager::RemoveTag(const FGameplayTag& InGameplayTag)
{
	RemoveTag_Internal(InGameplayTag);
}

void USI_GameplayTagManager::RemoveTag_Internal(const FGameplayTag& InGameplayTag, FSITagPayload* InTagPayload)
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
		RemoveTag_Internal(CurrentGameplayTag);
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
				RemoveTag_Internal(CurrentGameplayTag);
			}
		}
	}
	
	AddNewGameplayTag_Internal(InNewTag);
}

bool USI_GameplayTagManager::SwapTags(const FGameplayTag& InOldTag, const FGameplayTag& InNewTag)
{
	const FSI_GameplayTagContainer& TagTypeContainer = GetContainerTypeByTag(InOldTag);
	const FSI_GameplayTagContainer& NewTagTypeContainer = GetContainerTypeByTag(InNewTag);

	if(!TagTypeContainer.IsValid() || TagTypeContainer != NewTagTypeContainer){return false;}

	if (TagTypeContainer.HasTag(InOldTag))
	{
		RemoveTag_Internal(InOldTag);
		AddNewGameplayTag_Internal(InNewTag);
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
	InitializeAdapatableActionTagPairs();

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
	AllTagContainers.Add(SITag_Camera, FSI_GameplayTagContainer());
	AllTagContainers.Add(SITag_Debug, FSI_GameplayTagContainer());
	AllTagContainers.Add(SITag_Gadget, FSI_GameplayTagContainer());
	AllTagContainers.Add(SITag_Game_State, FSI_GameplayTagContainer());
	AllTagContainers.Add(SITag_Map, FSI_GameplayTagContainer());
	AllTagContainers.Add(SITag_Media, FSI_GameplayTagContainer());
	AllTagContainers.Add(SITag_Audio_Music, FSI_GameplayTagContainer());
	AllTagContainers.Add(SITag_Player_State, FSI_GameplayTagContainer());
	AllTagContainers.Add(SITag_UI, FSI_GameplayTagContainer());

	for (TPair<FGameplayTag, FSI_GameplayTagContainer>& CurrentContainerPair : AllTagContainers)
	{
		CurrentContainerPair.Value.SetParentTag(CurrentContainerPair.Key);
	}
}

void USI_GameplayTagManager::InitializeAdapatableActionTagPairs()
{
	AdaptableActionPairs.Add(SITag_Ability_Adaptable_AI_Interact, SITag_Ability_AI_Interact);
	AdaptableActionPairs.Add(SITag_Ability_Adaptable_AI_Interact_Pickup, SITag_Ability_AI_Interact_Pickup);
	AdaptableActionPairs.Add(SITag_Ability_Adaptable_AI_Interact_Drop, SITag_Ability_AI_Interact_Drop);
	AdaptableActionPairs.Add(SITag_Ability_Adaptable_AI_Interact_Push, SITag_Ability_AI_Interact_Push);
	AdaptableActionPairs.Add(SITag_Ability_Adaptable_AI_Interact_Pull, SITag_Ability_AI_Interact_Pull);
}

const FGameplayTag& USI_GameplayTagManager::GetAbilityTagFromAdaptableTag(const FGameplayTag& InAdaptableActionTag)
{
	if(AdaptableActionPairs.Find(InAdaptableActionTag))
	{
		return *AdaptableActionPairs.Find(InAdaptableActionTag);
	}
	
	return InAdaptableActionTag;
}