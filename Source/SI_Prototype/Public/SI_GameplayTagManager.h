// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems\SI_GameInstanceSubsystem.h"
#include "SI_GameplayTagTypes.h"
#include "SI_GameplayTagManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTagAdded, const FGameplayTag& AddedTag);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTagRemoved, const FGameplayTag& RemovedTag);

UCLASS()
class SI_PROTOTYPE_API USI_GameplayTagManager : public USI_GameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	void AddNewGameplayTag(const FGameplayTag& InGameplayTag);
	UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	void RemoveTag(const FGameplayTag& InGameplayTag);
	
	void ClearAllTagsFromContainer(FSI_GameplayTagContainer& InContainerToClear);
	
	UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	void ReplaceTagWithSameParent(const FGameplayTag& InNewTag, const FGameplayTag& InParentTag);
	
	bool SwapTags(const FGameplayTag& InOldTag, const FGameplayTag& InNewTag);

	UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	bool HasGameplayTag(const FGameplayTag& InGameplayTag);
	UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	bool HasParentTag(const FGameplayTag& InTagToCheck, const FGameplayTag& InParentTag) const;
	
	TMap<FGameplayTag, FSI_GameplayTagContainer>& GetAllTagContainers();
	FSI_GameplayTagContainer& GetContainerTypeByTag(const FGameplayTag& InGameplayTag);

	FOnTagAdded& OnTagAdded();
	FOnTagAdded& OnTagRemoved();

protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
private:

	FOnTagAdded OnTagAddedDelegate;
	FOnTagRemoved OnTagRemovedDelegate;

	void InitializeTagContainers();
	
	bool CheckContainerForParentTag(const FGameplayTag& InParentTag, const FSI_GameplayTagContainer& InContainerToCheck) const;

	TMap<FGameplayTag, FSI_GameplayTagContainer> AllTagContainers;

	FSI_GameplayTagContainer CameraTags;
	FSI_GameplayTagContainer GadgetTags;
	FSI_GameplayTagContainer GameStateTags;
	FSI_GameplayTagContainer LevelTags;
	FSI_GameplayTagContainer MediaTags;
	FSI_GameplayTagContainer MusicTags;
	FSI_GameplayTagContainer PlayerStateTags;
	FSI_GameplayTagContainer UITags;
	FSI_GameplayTagContainer DebugTags;
};
