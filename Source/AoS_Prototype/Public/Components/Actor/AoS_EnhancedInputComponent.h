// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Data/Input/AoS_InputConfig.h"
#include "AoS_Types.h"

#include "AoS_EnhancedInputComponent.generated.h"

enum class EPlayerMode : uint8;
class UInputMappingContext;
class UInputAction;

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

	template<class UserClass, typename FuncType>
	void BindInputByTag(const UAoS_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent InTriggerEvent, UserClass* InObject, FuncType InFunc);
};

template <class UserClass, typename FuncType>
void UAoS_EnhancedInputComponent::BindInputByTag(const UAoS_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent InTriggerEvent, UserClass* InObject, FuncType InFunc)
{
	check(InInputConfig);
	const UInputAction* InputAction = InInputConfig->GetInputActionByTag(InInputTag);
	if (InputAction != nullptr)
	{
		BindAction(InputAction, InTriggerEvent, InObject, InFunc);
	}
}