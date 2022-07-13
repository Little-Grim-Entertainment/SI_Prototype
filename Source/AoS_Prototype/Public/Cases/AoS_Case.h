// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_Case.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnObjectiveComplete)

UCLASS()
class AOS_PROTOTYPE_API UAoS_Case : public UDataAsset
{
	GENERATED_BODY()

public:

	UAoS_Case();

	UFUNCTION(BlueprintCallable)
	void CompleteObjective();

	FOnObjectiveComplete OnObjectiveComplete;

private:

	bool bIsComplete;
	
};
