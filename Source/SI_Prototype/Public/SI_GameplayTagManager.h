// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems\SI_GameInstanceSubsystem.h"
#include "SI_GameplayTagTypes.h"
#include "SI_GameplayTagManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTagAdded, const FGameplayTag& AddedTag);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTagRemoved, const FGameplayTag& RemovedTag);

DECLARE_LOG_CATEGORY_EXTERN(LogSI_GameplayTagManager, Log, All);

UCLASS()
class SI_PROTOTYPE_API USI_GameplayTagManager : public USI_GameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Used to register the tag manager with the gameplay tag manager which then broadcasts
	// the OnTagAdded and OnTagRemoved delegates when tags are added or removed.
	UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	void AddNewGameplayTag(const FGameplayTag& InGameplayTag);
	UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	void RemoveTag(const FGameplayTag& InGameplayTag);
	
	void ClearAllTagsFromContainer(FSI_GameplayTagContainer& InContainerToClear);

	// Receives InNewTag and replaces it with InParentTag
	UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	void ReplaceTagWithSameParent(const FGameplayTag& InNewTag, const FGameplayTag& InParentTag);

	//Removes InOldTag and adds InNewTag
	bool SwapTags(const FGameplayTag& InOldTag, const FGameplayTag& InNewTag);

	//Loops through containers to see if the tag is in its container
	UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	bool HasGameplayTag(const FGameplayTag& InGameplayTag);

	//Loops through the TagNames and compares them by character for a match 
	UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	bool HasParentTag(const FGameplayTag& InTagToCheck, const FGameplayTag& InParentTag) const;

	// Returns map of all GameplayTagContainers by Tag
	TMap<FGameplayTag, FSI_GameplayTagContainer>& GetAllTagContainers();

	// Loops through TagContainersMap and returns the proper container 
	FSI_GameplayTagContainer& GetContainerTypeByTag(const FGameplayTag& InGameplayTag);

	FOnTagAdded& OnTagAdded();
	FOnTagAdded& OnTagRemoved();

protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
private:

	FSI_GameplayTagContainer CameraTags;
	FSI_GameplayTagContainer DebugTags;
	FSI_GameplayTagContainer GadgetTags;
	FSI_GameplayTagContainer GameStateTags;
	FSI_GameplayTagContainer LevelTags;
	FSI_GameplayTagContainer MediaTags;
	FSI_GameplayTagContainer MusicTags;
	FSI_GameplayTagContainer PlayerStateTags;
	FSI_GameplayTagContainer UITags;

	FOnTagAdded OnTagAddedDelegate;
	FOnTagRemoved OnTagRemovedDelegate;

	void InitializeTagContainers();
	
	bool CheckContainerForParentTag(const FGameplayTag& InParentTag, const FSI_GameplayTagContainer& InContainerToCheck) const;

	TMap<FGameplayTag, FSI_GameplayTagContainer> AllTagContainers;
};
