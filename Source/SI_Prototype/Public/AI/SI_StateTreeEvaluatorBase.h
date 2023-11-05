// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeEvaluatorBlueprintBase.h"
#include "SI_StateTreeEvaluatorBase.generated.h"

class ASI_Gizbo;
class ASI_Nick;
/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_StateTreeEvaluatorBase : public UStateTreeEvaluatorBlueprintBase
{
	GENERATED_BODY()

public:

	// Must be EditAnywhere for them to show up on the component in the Editor
	// Category needs to be "Context", "Input" or "Output"
	UPROPERTY(EditAnywhere, Category = "Context")
	ASI_Gizbo* Gizbo;
	UPROPERTY(EditAnywhere, Category = "Output")
	ASI_Nick* Nick;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Output")
	FVector MoveToLocation;
};
