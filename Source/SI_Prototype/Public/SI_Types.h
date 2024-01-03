// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Media\Data\SI_MediaDataAsset.h"
#include "Media\SI_MediaTypes.h"
#include "Engine/DataTable.h"
#include "GameplayAbilitySpec.h"
#include "SI_Types.generated.h"

class USI_GameplayAbility;
class UGameplayAbility;
class USI_LevelManager;
class USoundBase;
class UInputAction;
class UInputMappingContext;
class USI_MapData;
class ULevelStreaming;
class USI_MediaDataAsset;
class USI_CaseData;
class USI_PartData;
class USI_ObjectiveData;

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_MusicSettings
{
	GENERATED_BODY()

	FSI_MusicSettings();
	FSI_MusicSettings(USoundBase* InMusicSource);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music", meta = (Categories = "Audio.Music"))
	FGameplayTag MusicTag;
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
struct SI_PROTOTYPE_API FSI_InputAction
{
	GENERATED_BODY()

	FSI_InputAction();
	FSI_InputAction(UInputAction* InInputAction);
	
	const UInputAction* GetInputAction() const;
	const FGameplayTag& GetInputTag() const;
	
private:
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction = nullptr; 

	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "Input"))
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_InputMapping
{
	GENERATED_BODY()

	FSI_InputMapping();
	FSI_InputMapping(UInputMappingContext* InInputMappingContext);

	const UInputMappingContext* GetInputMappingContext() const;
	const FGameplayTag& GetAssociatedTag() const;
	const FGameplayTag& GetSecondaryTag() const;
	bool IsDefaultMappingForMode() const;
	
	bool operator==(const FSI_InputMapping& OtherInputMapping) const;
	bool operator!=(const FSI_InputMapping& OtherInputMapping) const;

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
struct SI_PROTOTYPE_API FSI_ObjectiveDetails
{
	GENERATED_BODY()

	FSI_ObjectiveDetails();
	FSI_ObjectiveDetails(USI_ObjectiveData* InObjectiveData);

	void SetIsObjectiveActive(bool bIsActive);
	void SetIsObjectiveComplete(bool bIsComplete);

	void ResetObjective();

	USI_ObjectiveData* GetObjectiveData() const;

	bool IsObjectiveActive();
	bool IsObjectiveComplete();

	bool operator==(const FSI_ObjectiveDetails& OtherObjective) const;
	bool operator!=(const FSI_ObjectiveDetails& OtherObjective) const;
	
private:
	
	UPROPERTY()
	USI_ObjectiveData* ObjectiveDataAsset = nullptr;

	bool bIsObjectiveActive = false;
	bool bIsObjectiveComplete = false;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PartDetails
{
	GENERATED_BODY()

	FSI_PartDetails();
	FSI_PartDetails(USI_PartData* InPartData);

	bool CompleteObjective(const USI_ObjectiveData* InObjectiveToComplete);

	void SetIsPartActive(bool bIsActive);
	void SetIsPartComplete(bool bIsComplete);

	void ResetPart();
	
	bool IsPartComplete();

	USI_PartData* GetPartData() const;

	FSI_ObjectiveDetails* GetObjectiveDetails(const USI_ObjectiveData* InObjectiveData);

	TMap<USI_ObjectiveData*, FSI_ObjectiveDetails*>& GetPartObjectives();
	TArray<USI_ObjectiveData*> GetActiveObjectives();
	TArray<USI_ObjectiveData*> GetCompletedObjectives();

	bool operator==(const FSI_PartDetails& OtherPart) const;
	bool operator!=(const FSI_PartDetails& OtherPart) const;
	
private:
	
	UPROPERTY()
	USI_PartData* PartDataAsset = nullptr;

	UPROPERTY()
	TArray<USI_ObjectiveData*> ActiveObjectives;
	UPROPERTY()
	TArray<USI_ObjectiveData*> CompletedObjectives;

	TMap<USI_ObjectiveData*, FSI_ObjectiveDetails*> PartObjectives;

	bool bIsPartActive = false;
	bool bIsPartComplete = false;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_CaseDetails
{
	GENERATED_BODY()

	FSI_CaseDetails();
	FSI_CaseDetails(USI_CaseData* InCaseData);

	void SetIsCaseAccepted(const bool bIsAccepted);
	void SetIsCaseActive(const bool bIsActive);
	void SetIsCaseComplete(const bool bIsComplete);
	void SetActivePart(USI_PartData* InActivePart);
	
	USI_CaseData* GetCaseData() const;

	bool IsCaseAccepted() const;
	bool IsCaseComplete() const;
	bool IsCaseActive() const;

	void ResetCase();
	
	FSI_PartDetails* GetPartDetails(const USI_PartData* InPart);
	TMap<USI_PartData*, FSI_PartDetails*>& GetCaseParts();
	USI_PartData* GetActivePart();

	bool operator==(const FSI_CaseDetails& OtherCase) const;
	bool operator!=(const FSI_CaseDetails& OtherCase) const;
	
private:

	UPROPERTY()
	USI_CaseData* CaseDataAsset = nullptr;
	
	UPROPERTY()
	USI_PartData* ActivePart = nullptr;
	
	TMap<USI_PartData*, FSI_PartDetails*> CaseParts;
	
	UPROPERTY()
	TArray<USI_PartData*> CompletedParts;

	bool bIsCaseAccepted = false;
	bool bIsCaseActive = false;
	bool bIsCaseComplete = false;
	
	const USI_PartData* GetActivePart() const;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_MapState
{
	GENERATED_BODY()

	FSI_MapState();
	FSI_MapState(USI_MapData* InMapData, FSI_MediaSettings InIntroSettings = FSI_MediaSettings(), FSI_MediaSettings InOutroSettings = FSI_MediaSettings(), USI_MediaDataAsset* InLoadedIntroMedia = nullptr, USI_MediaDataAsset* InLoadedOutroMedia = nullptr, ULevelStreaming* InStreamingLevelRef = nullptr);

	UPROPERTY(BlueprintReadOnly, Category = "Levels")
	USI_MapData* MapData = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Levels")
	ULevelStreaming* StreamingLevelRef = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Media")
	USI_MediaDataAsset* LoadedIntroMedia = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Media")
	USI_MediaDataAsset* LoadedOutroMedia = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Media")
	FSI_MediaSettings IntroSettings;
	UPROPERTY(BlueprintReadOnly, Category = "Media")
	FSI_MediaSettings OutroSettings;
	
	void SetMapData(USI_MapData* InMapData);
	void SetStreamingLevelRef(ULevelStreaming* InStreamingLevelRef);

	USI_MapData* GetMapData() const;
	ULevelStreaming* GetStreamingLevelRef() const;

	FSI_MediaSettings& GetIntroSettings();
	FSI_MediaSettings& GetOutroSettings();

	bool IsStateValid() const;

	bool HasIntroMedia() const;
	bool HasOutroMedia() const;

	void LoadIntroMedia(USI_MediaDataAsset* InIntroMedia);
	void LoadOutroMedia(USI_MediaDataAsset* InOutroMedia);
	
	void UnLoadIntroMedia();
	void UnLoadOutroMedia();

	USI_MediaDataAsset* GetLoadedIntroMedia() const;
	USI_MediaDataAsset* GetLoadedOutroMedia() const;

	bool operator==(const FSI_MapState& OtherMapState) const;
	bool operator!=(const FSI_MapState& OtherMapState) const;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_QuckActionOptions : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag QuickActionTag;

	UPROPERTY(EditDefaultsOnly)
	FText QuickActionPrompt;

	UPROPERTY(EditAnywhere)
	UTexture2D* QuickActionImage;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSIGameplayAbilities
{
	GENERATED_BODY()

	FSIGameplayAbilities() = default;
	FSIGameplayAbilities(UGameplayAbility* InSIAbility, const FGameplayTagContainer& InSIAbilityTagContainer, const FGameplayAbilitySpecHandle& InSIAbilitySpecHandle);

	bool operator==(const FSIGameplayAbilities& OtherAbility) const;
	
	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	FGameplayTagContainer SIAbilityTagContainer;
	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	FGameplayAbilitySpecHandle SIAbilitySpecHandle;
	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	UGameplayAbility* SIAbility;
};