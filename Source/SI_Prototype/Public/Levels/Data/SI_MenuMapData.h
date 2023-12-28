// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Levels/Data/SI_MapData.h"
#include "SI_MenuMapData.generated.h"

class USI_UserWidget;

UCLASS()
class SI_PROTOTYPE_API USI_MenuMapData : public USI_MapData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapDetails")
	TSubclassOf<USI_UserWidget> MapMenuWidgetClass;
};
