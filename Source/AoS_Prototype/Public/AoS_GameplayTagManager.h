// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_GameInstanceSubsystem.h"
#include "AoS_GameplayTagTypes.h"
#include "AoS_GameplayTagManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTagAdded, const FGameplayTag& AddedTag);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTagRemoved, const FGameplayTag& RemovedTag);

UCLASS()
class AOS_PROTOTYPE_API UAoS_GameplayTagManager : public UAoS_GameInstanceSubsystem
{
	GENERATED_BODY()

public:

	void AddNewGameplayTag(const FGameplayTag& InGameplayTag);
	void RemoveTag(const FGameplayTag& InGameplayTag);
	bool HasGameplayTag(const FGameplayTag& InGameplayTag);
	bool HasParentTag(const FGameplayTag& InTagToCheck, const FGameplayTag& InParentTag) const;
	TArray<FAoS_GameplayTagContainer>& GetAllTagContainers();

	FOnTagAdded& OnTagAdded();
	FOnTagAdded& OnTagRemoved();

	
private:

	FOnTagAdded OnTagAddedDelegate;
	FOnTagRemoved OnTagRemovedDelegate;

	FAoS_GameplayTagContainer& GetContainerTypeByTag(const FGameplayTag& InGameplayTag);

	bool CheckContainerForParentTag(const FGameplayTag& InParentTag, const FAoS_GameplayTagContainer& InContainerToCheck) const;
	
	FAoS_GameplayTagContainer GameStateTags;
	FAoS_GameplayTagContainer PlayerModeTags;
	FAoS_GameplayTagContainer UITags;
	FAoS_GameplayTagContainer LevelTags;
	FAoS_GameplayTagContainer MediaTags;
	FAoS_GameplayTagContainer CameraTags;
};
