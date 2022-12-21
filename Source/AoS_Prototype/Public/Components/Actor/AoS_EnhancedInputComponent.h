// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "AoS_EnhancedInputComponent.generated.h"

enum class EPlayerMode : uint8;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FPlayerModeInputMapping
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPlayerMode AssociatedPlayerMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* MappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UInputAction*> ActionInputs;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UInputAction*> AxisInputs;
};


UCLASS()
class AOS_PROTOTYPE_API UAoS_EnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "EnhancedInputs")
	UInputAction* GetActionInput(FString InInputName);
	UFUNCTION(BlueprintPure, Category = "EnhancedInputs")
	UInputAction* GetAxisInput(FString InInputName);
	UFUNCTION(BlueprintPure, Category = "EnhancedInputs")
	UInputMappingContext* GetPlayerModeInputMappingContext(EPlayerMode InPlayerMode);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inputs", meta=(TitleProperty="{AssociatedPlayerMode} Mapping"))
	TArray<FPlayerModeInputMapping> PlayerModeInputMappings;
	
};
