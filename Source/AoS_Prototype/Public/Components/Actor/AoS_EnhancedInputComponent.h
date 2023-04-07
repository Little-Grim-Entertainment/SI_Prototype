// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Data/Input/AoS_InputConfig.h"
#include "AoS_Types.h"

#include "AoS_EnhancedInputComponent.generated.h"

class UInputMappingContext;
class UInputAction;
class UAoS_InputConfig;

UCLASS()
class AOS_PROTOTYPE_API UAoS_EnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	UAoS_InputConfig* GetInputConfig() const;
	
	template<class UserClass, typename FuncType>
	void BindInputByTag(const UAoS_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent InTriggerEvent, UserClass* InObject, FuncType InFunc);
};

template <class UserClass, typename FuncType>
void UAoS_EnhancedInputComponent::BindInputByTag(const UAoS_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent InTriggerEvent, UserClass* InObject, FuncType InFunc)
{
	check(InInputConfig);
	const UInputAction* InputAction = InInputConfig->GetInputActionByTag(InInputTag);
	if (IsValid(InputAction))
	{
		BindAction(InputAction, InTriggerEvent, InObject, InFunc);
	}
}
