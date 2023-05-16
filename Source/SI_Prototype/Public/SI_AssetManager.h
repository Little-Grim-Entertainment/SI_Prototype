// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "SI_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_AssetManager : public UAssetManager
{
	GENERATED_BODY()

protected:
	
	virtual void StartInitialLoading() override;
};
