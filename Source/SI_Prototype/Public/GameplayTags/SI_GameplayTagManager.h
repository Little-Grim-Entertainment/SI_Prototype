// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_GameplayTagTypes.h"
#include "Subsystems/SI_GameInstanceSubsystem.h"
#include "SI_GameplayTagManager.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTagAdded, const FGameplayTag& AddedTag, FSITagPayload* InTagPayload);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTagRemoved, const FGameplayTag& RemovedTag, FSITagPayload* InTagPayload);


UCLASS()
class SI_PROTOTYPE_API USI_GameplayTagManager : public USI_GameInstanceSubsystem
{
	GENERATED_BODY()

public:

	// Used to register the tag manager with the gameplay tag manager which then broadcasts
	// the OnTagAdded and OnTagRemoved delegates when tags are added or removed.
	// Use AddNewGameplayTag_Internal() for C++ code.
	UFUNCTION(BlueprintCallable)
	void AddNewGameplayTag(const FGameplayTag& InGameplayTag);
	void AddNewGameplayTag_Internal(const FGameplayTag& InGameplayTag, FSITagPayload* InTagPayload = nullptr);

	UFUNCTION(BlueprintCallable)
	void RemoveTag(const FGameplayTag& InGameplayTag);
	void RemoveTag_Internal(const FGameplayTag& InGameplayTag, FSITagPayload* InTagPayload = nullptr);
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

	FOnTagAdded OnTagAddedDelegate;
	FOnTagRemoved OnTagRemovedDelegate;

	void InitializeTagContainers();
	
	bool CheckContainerForParentTag(const FGameplayTag& InParentTag, const FSI_GameplayTagContainer& InContainerToCheck) const;

	TMap<FGameplayTag, FSI_GameplayTagContainer> AllTagContainers;
};
