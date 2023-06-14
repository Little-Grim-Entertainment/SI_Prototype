// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SI_NPC_Interactable.h"
#include "Abilities/SI_GameplayAbility.h"
#include "SI_Gizbo.generated.h"

class UPhysicsHandleComponent;
class USI_AbilitySystemComponent;

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API ASI_Gizbo : public ASI_NPC_Interactable
{
	GENERATED_BODY()

	ASI_Gizbo();

	//Gizbo Item Interaction Functions and Variables
public:
	void Tick(float DeltaTime);
	void HeldItemPosition();
	void PickupItem(AActor* InHitActor);
	UFUNCTION(BlueprintCallable)
	void DropItem();
	UFUNCTION(BlueprintCallable)
	void LocatePickupItem();

	UPROPERTY(EditAnywhere)
	UPhysicsHandleComponent* PhysicsHandle;
	UPROPERTY(BlueprintReadOnly)
	bool bIsHoldingItem;
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

	void ConstructGadget(bool InbGiveToNick);
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Abilities)
	USI_AbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Abilities)
	TArray<TSubclassOf<USI_GameplayAbility>> DefaultAbilities;
	USI_AbilitySystemComponent* GetSIAbilitySystemComponent() const;
	void GiveAbilities();
};
