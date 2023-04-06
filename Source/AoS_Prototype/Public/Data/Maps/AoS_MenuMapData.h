// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Maps/AoS_MapData.h"
#include "AoS_MenuMapData.generated.h"

class UAoS_UserWidget;

UCLASS()
class AOS_PROTOTYPE_API UAoS_MenuMapData : public UAoS_MapData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapDetails")
	TSubclassOf<UAoS_UserWidget> MapMenuWidgetClass;
};
