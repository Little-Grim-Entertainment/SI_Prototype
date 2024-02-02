// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_CharacterTypes.h"
#include "GameFramework/Character.h"
#include "SI_Character.generated.h"

class USI_CharacterManager;
class USI_CharacterData;
class USI_AbilitySystemComponent;
class UPhysicsHandleComponent;

UCLASS()
class SI_PROTOTYPE_API ASI_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASI_Character();

	USI_CharacterData* GetCharacterData() const;
	USI_AbilitySystemComponent* GetAbilitySystemComponent() {return AbilitySystemComponent; };
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPhysicsHandleComponent> PhysicsHandle;

	UPROPERTY(BlueprintReadOnly)
	bool bIsHoldingItem;
	UPROPERTY(EditAnywhere, Category = "AI | Item Interaction")
	float InteractDistance;
	
protected:
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character | Abilities")
	USI_AbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Info")
	USI_CharacterData* CharacterData = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "AI | Item Interaction")
	float CarryOffset;
	UPROPERTY(EditAnywhere, Category = "AI | Item Interaction")
	float AdjustedDampening;
	// Used to restore item state after NPC drops it
	float DefaultDampening;

	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> ObjectBeingCarried;

	UPROPERTY()
	TObjectPtr<AActor> HeldActor;

	FRotator CarriedObjectRotation;
	FName PickupSocket = TEXT("Socket_Chest");

	virtual void BeginPlay() override;
	void HeldItemPosition();
};
