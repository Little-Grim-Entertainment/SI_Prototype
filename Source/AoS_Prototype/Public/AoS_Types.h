// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Media/AoS_MediaDataAsset.h"
#include "Media/AoS_MediaTypes.h"
#include "AoS_GameplayTagTypes.h"
#include "AoS_Types.generated.h"

class UAoS_LevelManager;
class USoundBase;
class UInputAction;
class UInputMappingContext;
class UAoS_MapData;
class ULevelStreaming;
class UAoS_MediaDataAsset;
class UAoS_CaseData;
class UAoS_PartData;
class UAoS_ObjectiveData;

USTRUCT(BlueprintType)
struct FAoS_MusicSettings
{
	GENERATED_BODY()

	FAoS_MusicSettings();
	FAoS_MusicSettings(USoundBase* InMusicSource);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	USoundBase* MetaSoundSource = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	USoundBase* MusicSource = nullptr;
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

	FAoS_InputAction();
	FAoS_InputAction(UInputAction* InInputAction);
	
	const UInputAction* GetInputAction() const;
	const FGameplayTag& GetInputTag() const;
	
private:
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction = nullptr; 

	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "Input"))
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FAoS_InputMapping
{
	GENERATED_BODY()

	FAoS_InputMapping();
	FAoS_InputMapping(UInputMappingContext* InInputMappingContext);

	const UInputMappingContext* GetInputMappingContext() const;
	const FGameplayTag& GetAssociatedTag() const;
	const FGameplayTag& GetSecondaryTag() const;
	bool IsDefaultMappingForMode() const;
	
	bool operator==(const FAoS_InputMapping& OtherInputMapping) const;
	bool operator!=(const FAoS_InputMapping& OtherInputMapping) const;

private:
	
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "Player.Mode"))
	FGameplayTag AssociatedTag;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag SecondaryTag;

	UPROPERTY(EditDefaultsOnly)
	bool bIsDefaultMappingForMode = false;
};

USTRUCT(BlueprintType)
struct FAoS_ObjectiveDetails
{
	GENERATED_BODY()

	FAoS_ObjectiveDetails();
	FAoS_ObjectiveDetails(UAoS_ObjectiveData* InObjectiveData);

	void SetIsObjectiveActive(bool bIsActive);
	void SetIsObjectiveComplete(bool bIsComplete);

	void ResetObjective();

	UAoS_ObjectiveData* GetObjectiveData() const;

	bool IsObjectiveActive();
	bool IsObjectiveComplete();

	bool operator==(const FAoS_ObjectiveDetails& OtherObjective) const;
	bool operator!=(const FAoS_ObjectiveDetails& OtherObjective) const;
	
private:
	
	UPROPERTY()
	UAoS_ObjectiveData* ObjectiveDataAsset = nullptr;

	bool bIsObjectiveActive = false;
	bool bIsObjectiveComplete = false;
};

USTRUCT(BlueprintType)
struct FAoS_PartDetails
{
	GENERATED_BODY()

	FAoS_PartDetails();
	FAoS_PartDetails(UAoS_PartData* InPartData);

	bool CompleteObjective(const UAoS_ObjectiveData* InObjectiveToComplete);

	void SetIsPartActive(bool bIsActive);
	void SetIsPartComplete(bool bIsComplete);

	void ResetPart();
	
	bool IsPartComplete();

	UAoS_PartData* GetPartData() const;

	FAoS_ObjectiveDetails& GetObjectiveDetails(const UAoS_ObjectiveData* InObjectiveData);

	TMap<UAoS_ObjectiveData*, FAoS_ObjectiveDetails>& GetPartObjectives();
	TArray<UAoS_ObjectiveData*> GetActiveObjectives();
	TArray<UAoS_ObjectiveData*> GetCompletedObjectives();

	bool operator==(const FAoS_PartDetails& OtherPart) const;
	bool operator!=(const FAoS_PartDetails& OtherPart) const;
	
private:
	
	UPROPERTY()
	UAoS_PartData* PartDataAsset = nullptr;

	UPROPERTY()
	TMap<UAoS_ObjectiveData*, FAoS_ObjectiveDetails> PartObjectives;
	UPROPERTY()
	TArray<UAoS_ObjectiveData*> ActiveObjectives;
	UPROPERTY()
	TArray<UAoS_ObjectiveData*> CompletedObjectives;

	bool bIsPartActive = false;
	bool bIsPartComplete = false;
};

USTRUCT(BlueprintType)
struct FAoS_CaseDetails
{
	GENERATED_BODY()

	FAoS_CaseDetails();
	FAoS_CaseDetails(UAoS_CaseData* InCaseData);

	void SetIsCaseAccepted(const bool bIsAccepted);
	void SetIsCaseActive(const bool bIsActive);
	void SetIsCaseComplete(const bool bIsComplete);
	void SetActivePart(UAoS_PartData* InActivePart);
	
	UAoS_CaseData* GetCaseData() const;

	bool IsCaseAccepted() const;
	bool IsCaseComplete() const;
	bool IsCaseActive() const;

	void ResetCase();
	
	FAoS_PartDetails& GetPartDetails(const UAoS_PartData* InPart);
	TMap<UAoS_PartData*, FAoS_PartDetails>& GetCaseParts();
	UAoS_PartData* GetActivePart();

	bool operator==(const FAoS_CaseDetails& OtherCase) const;
	bool operator!=(const FAoS_CaseDetails& OtherCase) const;
	
private:

	UPROPERTY()
	UAoS_CaseData* CaseDataAsset = nullptr;
	
	UPROPERTY()
	UAoS_PartData* ActivePart = nullptr;
	
	TMap<UAoS_PartData*, FAoS_PartDetails> CaseParts;
	
	UPROPERTY()
	TArray<UAoS_PartData*> CompletedParts;

	bool bIsCaseAccepted = false;
	bool bIsCaseActive = false;
	bool bIsCaseComplete = false;
	
	const UAoS_PartData* GetActivePart() const;
};

USTRUCT(BlueprintType)
struct FAoS_MapState
{
	GENERATED_BODY()

	FAoS_MapState();
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
