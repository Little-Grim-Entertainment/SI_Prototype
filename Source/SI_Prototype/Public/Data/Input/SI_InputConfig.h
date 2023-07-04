// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SI_Types.h"
#include "SI_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class SI_PROTOTYPE_API USI_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	
	const UInputMappingContext* GetInputMappingByTag(const FGameplayTag& InAssociatedPlayerModeTag, const FGameplayTag& InSecondaryTag = FGameplayTag()) const;
	const UInputAction* GetInputActionByTag(const FGameplayTag& InInputTag) const;

	const TArray<FSI_InputMapping>& GetPrimaryInputMappings();
	const TArray<FSI_InputMapping>& GetSecondaryInputMappings();
	const TArray<FSI_InputAction>& GetBasicInputActions();
	const TArray<FSI_InputAction>& GetDialogueInputActions();
	const TArray<FSI_InputAction>& GetMovementInputActions();
	const TArray<FSI_InputAction>& GetGizboInputActions();

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "InputMappings", meta = (TitleProperty = "InputMapping"))
	TArray<FSI_InputMapping> PrimaryInputMappings;
	
	UPROPERTY(EditDefaultsOnly, Category = "InputMappings", meta = (TitleProperty = "InputMapping"))
	TArray<FSI_InputMapping> SecondaryInputMappings;
		
	UPROPERTY(EditDefaultsOnly, Category = "InputActions", meta = (TitleProperty = "InputAction"))
	TArray<FSI_InputAction> BasicInputActions;
	
	UPROPERTY(EditDefaultsOnly, Category = "InputActions", meta = (TitleProperty = "InputAction"))
	TArray<FSI_InputAction> DialogueInputActions;
	
	UPROPERTY(EditDefaultsOnly, Category = "InputActions", meta = (TitleProperty = "InputAction"))
	TArray<FSI_InputAction> MovementInputActions;

	UPROPERTY(EditDefaultsOnly, Category = "InputActions", meta = (TitleProperty = "InputAction"))
	TArray<FSI_InputAction> GizboInputActions;
};
