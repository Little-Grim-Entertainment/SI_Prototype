// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Input/Data/SI_InputConfig.h"
#include "SI_Types.h"

#include "SI_EnhancedInputComponent.generated.h"

class UInputMappingContext;
class UInputAction;
class USI_InputConfig;

UCLASS()
class SI_PROTOTYPE_API USI_EnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	USI_InputConfig* GetInputConfig() const;
	
	template<class UserClass, typename FuncType>
	void BindInputByTag(const USI_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent InTriggerEvent, UserClass* InObject, FuncType InFunc);
};

template <class UserClass, typename FuncType>
void USI_EnhancedInputComponent::BindInputByTag(const USI_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent InTriggerEvent, UserClass* InObject, FuncType InFunc)
{
	check(InInputConfig);
	const UInputAction* InputAction = InInputConfig->GetInputActionByTag(InInputTag);
	if (IsValid(InputAction))
	{
		BindAction(InputAction, InTriggerEvent, InObject, InFunc);
	}
}
