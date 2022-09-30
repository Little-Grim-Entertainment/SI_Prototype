// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_MapData.generated.h"

UENUM(BlueprintType)
enum class EMapType : uint8
{
	MT_Persistent	UMETA(DisplayName = "Persistent"),
	MT_Menu			UMETA(DisplayName = "Menu"),
	MT_Interior     UMETA(DisplayName = "Interior"),
	MT_Exterior     UMETA(DisplayName = "Exterior"),
	MT_None			UMETA(DisplayName = "NONE")
};

UCLASS()
class AOS_PROTOTYPE_API UAoS_MapData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapDetails")
	FString MapName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapDetails")
	TEnumAsByte<EMapType> MapType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapDetails")
	TSoftObjectPtr<UWorld> Map;

	UFUNCTION()
	void SetStreamingLevelRef(ULevelStreaming* StreamingLevelToSet);

	UFUNCTION()
	ULevelStreaming* GetStreamingLevelRef() const {return StreamingLevelRef;}

private:

	UPROPERTY()
	ULevelStreaming* StreamingLevelRef;
};
