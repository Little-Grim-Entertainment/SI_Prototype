// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_Types.h"
#include "AoS_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class AOS_PROTOTYPE_API UAoS_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputMappingContext* GetInputMappingByTag(const FGameplayTag& InAssociatedPlayerModeTag, const FGameplayTag& InSecondaryTag = FGameplayTag()) const;
	const UInputAction* GetInputActionByTag(const FGameplayTag& InInputTag) const;

	const TArray<FAoS_InputMapping>& GetInputMappings();
	const TArray<FAoS_InputAction>& GetBasicInputActions();
	const TArray<FAoS_InputAction>& GetDialogueInputActions();
	const TArray<FAoS_InputAction>& GetMovementInputActions();
	const TArray<FAoS_InputAction>& GetGizboInputActions();

private:

	UPROPERTY(EditDefaultsOnly, Category = "InputMappings", meta = (TitleProperty = "InputMapping"))
	TArray<FAoS_InputMapping> InputMappings;
		
	UPROPERTY(EditDefaultsOnly, Category = "InputActions", meta = (TitleProperty = "InputAction"))
	TArray<FAoS_InputAction> BasicInputActions;
	
	UPROPERTY(EditDefaultsOnly, Category = "InputActions", meta = (TitleProperty = "InputAction"))
	TArray<FAoS_InputAction> DialogueInputActions;
	
	UPROPERTY(EditDefaultsOnly, Category = "InputActions", meta = (TitleProperty = "InputAction"))
	TArray<FAoS_InputAction> MovementInputActions;

	UPROPERTY(EditDefaultsOnly, Category = "InputActions", meta = (TitleProperty = "InputAction"))
	TArray<FAoS_InputAction> GizboInputActions;
};
