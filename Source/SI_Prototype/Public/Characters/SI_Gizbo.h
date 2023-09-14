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

	UPROPERTY(BlueprintReadOnly)
	FVector MoveToLocation;
	UPROPERTY(BlueprintReadOnly)
	bool bDirectedRotation;
	UPROPERTY(BlueprintReadOnly)
	FRotator MoveToRotation;
	
protected:
	virtual void BeginPlay() override;
	void Tick(float DeltaTime);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsHoldingItem;	

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Abilities)
	TArray<TSubclassOf<USI_GameplayAbility>> DefaultAbilities;
	
private:
	
	// Sets held item's position when picked up
	void HeldItemPosition();
	//Attaches item to PhysicsHandle
	void PickupObject(AActor* InHitActor);
	//Attach to Item and move it to specified location
	void PushObject(AActor* InHitActor);
	//Drops item being held and PhysicsHandle location
	UFUNCTION(BlueprintCallable)
	void DropItem();
	//Fires a trace to locate interactable object
	UFUNCTION(BlueprintCallable)
	void LocateInteractable();
	
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

	void GiveAbilities();
};
