// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AoS_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AOS_PROTOTYPE_API UAoS_AssetManager : public UAssetManager
{
	GENERATED_BODY()

protected:
	
	virtual void StartInitialLoading() override;
};
