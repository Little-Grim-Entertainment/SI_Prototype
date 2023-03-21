// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_Types.h"
#include "AoS_InputConfig.generated.h"

class UInputAction;

UCLASS()
class AOS_PROTOTYPE_API UAoS_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputAction* GetInputActionByTag(const FGameplayTag& InInputTag) const;

	const TArray<FAoS_InputAction>& GetBasicInputActions();
	const TArray<FAoS_InputAction>& GetDialogueInputActions();
	const TArray<FAoS_InputAction>& GetMovementInputActions();
	const TArray<FAoS_InputAction>& GetGizboInputActions();

private:

	
	
	UPROPERTY(EditDefaultsOnly, meta = (TitleProperty = "InputAction"))
	TArray<FAoS_InputAction> BasicInputActions;
	
	UPROPERTY(EditDefaultsOnly, meta = (TitleProperty = "InputAction"))
	TArray<FAoS_InputAction> DialogueInputActions;
	
	UPROPERTY(EditDefaultsOnly, meta = (TitleProperty = "InputAction"))
	TArray<FAoS_InputAction> MovementInputActions;

	UPROPERTY(EditDefaultsOnly, meta = (TitleProperty = "InputAction"))
	TArray<FAoS_InputAction> GizboInputActions;
};
