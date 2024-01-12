// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Characters/SI_NPC_Interactable.h"
#include "Abilities/SI_GameplayAbility.h"
#include "SI_Gizbo.generated.h"

class ASI_GizboController;
class UPhysicsHandleComponent;
class USI_AbilitySystemComponent;

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API ASI_Gizbo : public ASI_NPC_Interactable , public IAbilitySystemInterface 
{
	GENERATED_BODY()
	
public:
	ASI_Gizbo();
	USI_AbilitySystemComponent* GetSIAbilitySystemComponent() const;
	
protected:
	virtual void BeginPlay() override;
	void Tick(float DeltaTime);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsHoldingItem;	

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Abilities)
	TArray<TSubclassOf<USI_GameplayAbility>> DefaultAbilities;
	
private:
	
	/** Adjusts the position of the held item in Gizbo's hand.
	* This function is responsible for maintaining the position of the held item in Gizbo's hand. It ensures that if the held object's rigid body goes to sleep, it is awakened to prevent it from detaching. Then, it updates the position and rotation of the held object using the Gizbo's location and specified offsets.
	* Use this function to keep the held object in the correct position while Gizbo is carrying it.
	*/
	void HeldItemPosition();
	
	/** Picks up and attaches the given actor to Gizbo's hand.
	* This function is responsible for picking up and attaching the provided actor to Gizbo's hand. It sets the 'HeldActor' reference to the input actor, attaches it to Gizbo's skeletal mesh using specified attachment rules, and marks Gizbo as holding an item.
	* @param InHitActor The actor to be picked up and attached to Gizbo's hand.
	* Use this function to enable Gizbo to pick up and hold objects in the game.
	*/
	void PickupObject(AActor* InHitActor);
	
	/** Attaches Gizbo to the given actor for pushing or interacting.
	* This function attaches Gizbo to the provided actor, typically used for pushing or interacting with objects in the game. It specifies attachment rules for how Gizbo should be attached to the actor.
	* @param InHitActor The actor to which Gizbo should be attached for pushing or interaction.
	* Use this function to establish an attachment between Gizbo and the target actor for specific gameplay interactions.
	*/
	void PushObject(AActor* InHitActor);
	
	/** Drops the currently held item, detaching it from Gizbo's hand.
	* This function is responsible for dropping the item that Gizbo is currently holding. It detaches the held item from Gizbo's hand using specified detachment rules and updates the 'bIsHoldingItem' flag to indicate that Gizbo is no longer holding an item.
	* Use this function to allow Gizbo to release and drop the currently held item.
	*/
	UFUNCTION(BlueprintCallable)
	void DropItem();
	
	/** Locates nearby interactable objects and triggers relevant interactions.
	* This function is responsible for detecting and locating interactable objects within Gizbo's interaction range. It performs the following steps:
	* 1. Checks if Gizbo's hands are empty (not holding an item).
	* 2. Performs a sweep to collect hit results between a starting and ending point to identify potential interactable objects.
	* 3. Draws debug lines and spheres to visualize the sweep results.
	* 4. Iterates through the hit results to identify interactable objects and initiate interactions based on their tags:
	*    - If a pickupable object is found, Gizbo picks it up.
	*    - If a pushable object is found, a debug message is displayed.
	* Use this function to allow Gizbo to detect and interact with nearby objects within the interaction range.
	*/
	UFUNCTION(BlueprintCallable)
	void LocateInteractable();

	/** Gives default gameplay abilities to Gizbo's ability system component.
	* This function is responsible for granting Gizbo's ability system component the default gameplay abilities specified in the 'DefaultAbilities' array. It iterates through the array and gives each ability with a level of 1 to Gizbo's ability system component.
	* Use this function to provide Gizbo with a set of initial gameplay abilities when needed, ensuring they are available for use in the game.
	*/
	void GiveAbilities();
	
	UPROPERTY(EditAnywhere)
	UPhysicsHandleComponent* PhysicsHandle;
	
	UPROPERTY(EditAnywhere, Category = "Gizbo Item Interaction")
	float InteractDistance;
	UPROPERTY(EditAnywhere, Category = "Gizbo Item Interaction")
	float CarryOffset;
	UPROPERTY(EditAnywhere, Category = "Gizbo Item Interaction")
	float AdjustedDampening;
	// Used to restore item state after Gizbo drops it
	float DefaultDampening;
	UPROPERTY()
	UPrimitiveComponent* ObjectBeingCarried;
	UPROPERTY()
	AActor* HeldActor;
	FRotator CarriedObjectRotation;
	FName PickupSocket = TEXT("Socket_Chest");


};
