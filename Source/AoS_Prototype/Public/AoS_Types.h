// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Media/AoS_MediaDataAsset.h"
#include "Media/AoS_MediaTypes.h"
#include "AoS_GameplayTagTypes.h"
#include "AoS_Types.generated.h"

class USoundBase;
class UInputAction;
class UInputMappingContext;
class UAoS_MapData;
class ULevelStreaming;
class UAoS_MediaDataAsset;

USTRUCT(BlueprintType)
struct FAoS_MusicSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	USoundBase* MetaSoundSource;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	USoundBase* MusicSource;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	bool bHasIntro = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music", meta=(EditCondition="bHasIntro", EditConditionHides))
	float LoopStart = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	float VolumeMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	float PitchMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	float StartTime = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	bool bShouldFade = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music", meta=(EditCondition="bShouldFade", EditConditionHides))
	bool bUseGlobalFadeSettings = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music", meta=(EditCondition="!bUseGlobalFadeSettings", EditConditionHides))
	float FadeInDuration = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music", meta=(EditCondition="!bUseGlobalFadeSettings", EditConditionHides))
	float FadeOutDuration = 5.0f;
};

USTRUCT(BlueprintType)
struct FAoS_InputAction
{
	GENERATED_BODY()
	
	const UInputAction* GetInputAction() const;
	const FGameplayTag& GetInputTag() const;
	
private:
	
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr; 

	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "Input"))
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FAoS_InputMapping
{
	GENERATED_BODY()

	const UInputMappingContext* GetInputMappingContext() const;
	const FGameplayTag& GetAssociatedPlayerModeTag() const;
	const FGameplayTag& GetSecondaryTag() const;
	bool IsDefaultMappingForMode() const;
	
	bool operator==(const FAoS_InputMapping& OtherInputMapping) const;
	bool operator!=(const FAoS_InputMapping& OtherInputMapping) const;

private:
	

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "Player.Mode"))
	FGameplayTag AssociatedPlayerModeTag;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag SecondaryTag;

	UPROPERTY(EditDefaultsOnly)
	bool bIsDefaultMappingForMode = false;
};

USTRUCT(BlueprintType)
struct FAoS_MapState
{
	GENERATED_BODY()
	
	FAoS_MapState() {}
	FAoS_MapState(UAoS_MapData* InMapData, FAoS_MediaSettings InIntroSettings = FAoS_MediaSettings(), FAoS_MediaSettings InOutroSettings = FAoS_MediaSettings(), UAoS_MediaDataAsset* InLoadedIntroMedia = nullptr, UAoS_MediaDataAsset* InLoadedOutroMedia = nullptr, ULevelStreaming* InStreamingLevelRef = nullptr);

	UPROPERTY(BlueprintReadOnly, Category = "Levels")
	UAoS_MapData* MapData = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Levels")
	ULevelStreaming* StreamingLevelRef = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Media")
	UAoS_MediaDataAsset* LoadedIntroMedia = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Media")
	UAoS_MediaDataAsset* LoadedOutroMedia = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Media")
	FAoS_MediaSettings IntroSettings;
	UPROPERTY(BlueprintReadOnly, Category = "Media")
	FAoS_MediaSettings OutroSettings;
	
	void SetMapData(UAoS_MapData* InMapData);
	void SetStreamingLevelRef(ULevelStreaming* InStreamingLevelRef);

	UAoS_MapData* GetMapData() const;
	ULevelStreaming* GetStreamingLevelRef() const;

	FAoS_MediaSettings& GetIntroSettings();
	FAoS_MediaSettings& GetOutroSettings();

	bool IsStateValid() const;

	bool HasIntroMedia() const;
	bool HasOutroMedia() const;

	void LoadIntroMedia(UAoS_MediaDataAsset* InIntroMedia);
	void LoadOutroMedia(UAoS_MediaDataAsset* InOutroMedia);
	
	void UnLoadIntroMedia();
	void UnLoadOutroMedia();

	UAoS_MediaDataAsset* GetLoadedIntroMedia() const;
	UAoS_MediaDataAsset* GetLoadedOutroMedia() const;

	bool operator==(const FAoS_MapState& OtherMapState) const;
	bool operator!=(const FAoS_MapState& OtherMapState) const;
};
