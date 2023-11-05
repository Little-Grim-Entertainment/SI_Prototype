// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SI_LocalPlayerSubsystem.h"
#include "SI_AbilityManager.generated.h"

class USI_AbilitySystemComponent;
class USI_GizboManager;
class USI_PlayerManager;

DECLARE_LOG_CATEGORY_EXTERN(LogSI_AbilityManager, Log, All);

/**
 * 
 */

UCLASS()
class SI_PROTOTYPE_API USI_AbilityManager : public USI_LocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	/** Responds to the addition of a gameplay tag and takes corresponding actions.
	* This function is triggered when a gameplay tag is added to the system. It first checks if the added tag has a parent tag related to abilities ('SITag_Ability'). If not, it exits.
	* If the added tag is one of the specific ability-related tags ('SITag_Ability_Cancel', 'SITag_Ability_Confirm', or 'SITag_Ability_HoldConfirm'), it performs actions related to loose ability tags.
	* Otherwise, it attempts to activate an ability associated with the added tag, using any provided payload data.
	* @param InAddedTag The gameplay tag that has been added.
	* @param InTagPayload Additional payload data associated with the added tag.
	*/
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload) override;
	
protected:

	virtual void OnGameModeBeginPlay() override;

	/**
	* Tries to activate an ability associated with a specific gameplay tag.
	*
	* This function attempts to activate an ability corresponding to the provided gameplay tag. It performs the following steps:
	* 1. Checks if the provided payload data is not null. If null, it logs an error and exits.
	* 2. Retrieves the ability system component of the target from the payload data.
	* 3. Verifies the validity of the obtained ability system component. If null, it logs an error and exits.
	* 4. Retrieves the specific ability associated with the given tag.
	* 5. Ensures the validity of the obtained ability. If null, it logs an error and exits.
	* 6. Logs a message indicating the attempt to activate the ability.
	* 7. Tries to activate the ability using the provided gameplay tag.
	*
	* @param InAddedTag The gameplay tag associated with the ability to be activated.
	* @param InTagPayload Additional payload data used to determine the target and ability system component.
	*
	* Use this function to trigger the activation of an ability based on a specific gameplay tag, given the necessary payload data.
	*/
	void TryActivateAbilityByTag(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload);

	/**
	* Tries to cancel an active ability associated with a specific gameplay tag.
	*
	* This function attempts to cancel an active ability corresponding to the provided gameplay tag. It performs the following steps:
	* 1. Retrieves the ability system component of the target from the provided payload data.
	* 2. Verifies the validity of the obtained ability system component. If null, it logs an error and exits.
	* 3. Retrieves the specific ability associated with the given tag.
	* 4. Ensures the validity of the obtained ability. If null, it logs an error and exits.
	* 5. Logs a message indicating the cancellation of the ability.
	* 6. Cancels the identified ability using the ability system component.
	*
	* @param InAddedTag The gameplay tag associated with the ability to be canceled.
	* @param InTagPayload Additional payload data used to determine the target and ability system component.
	*
	* Use this function to attempt the cancellation of an active ability based on a specific gameplay tag, given the necessary payload data.
	*/
	//TODO: Pace... Do I need this?
	void TryCancelAbilityByTag(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload);

	/**
	* Adds and removes a gameplay tag as a loose tag for Nick's ability system component.
	*
	* This function performs the following actions:
	* 1. Checks if Nick's ability system component is valid. If not, it attempts to retrieve it from the PlayerManager. If unsuccessful, it logs an error and exits.
	* 2. Adds the provided gameplay tag as a loose tag for Nick's ability system component.
	* 3. Removes the same gameplay tag as a loose tag.
	* 4. Logs a message to indicate that the tag was added and removed as a loose tag.
	*
	* @param InAddedTag The gameplay tag to be added and removed as a loose tag.
	*
	* Use this function to manage loose gameplay tags associated with Nick's ability system component.
	*/
	void AddRemoveLooseAbilityTags(const FGameplayTag& InAddedTag);

	UPROPERTY()
	USI_AbilitySystemComponent* GizboAbilitySystemComponent;
	UPROPERTY()
	USI_AbilitySystemComponent* NickAbilitySystemComponent;
	
};
