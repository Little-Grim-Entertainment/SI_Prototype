// Fill out your copyright notice in the Description page of Project Settings.


#include "SI_Types.h"

#include "Engine/LevelStreaming.h"
#include "Levels/Data/SI_MapData.h"
#include "Cases/Data/SI_PartData.h"
#include "Cases/Data/SI_ObjectiveData.h"
#include "Media/Data/SI_MediaDataAsset.h"

FSI_MusicSettings::FSI_MusicSettings()
{
}

FSI_MusicSettings::FSI_MusicSettings(USoundBase* InMusicSource) :
	MusicSource(InMusicSource)
{
}

FSI_InputAction::FSI_InputAction()
{
}

FSI_InputAction::FSI_InputAction(UInputAction* InInputAction) :
	InputAction(InInputAction)
{
}

const UInputAction* FSI_InputAction::GetInputAction() const
{
	return InputAction;
}

const FGameplayTag& FSI_InputAction::GetInputTag() const
{
	return InputTag;
}

FSI_InputMapping::FSI_InputMapping()
{
}

FSI_InputMapping::FSI_InputMapping(UInputMappingContext* InInputMappingContext) :
	InputMappingContext(InInputMappingContext)
{
}

const UInputMappingContext* FSI_InputMapping::GetInputMappingContext() const
{
	return InputMappingContext;
}

const FGameplayTag& FSI_InputMapping::GetAssociatedTag() const
{
	return AssociatedTag;
}

const FGameplayTag& FSI_InputMapping::GetSecondaryTag() const
{
	return SecondaryTag;
}

bool FSI_InputMapping::IsDefaultMappingForMode() const
{
	return bIsDefaultMappingForMode;
}

bool FSI_InputMapping::operator==(const FSI_InputMapping& OtherInputMapping) const
{
	return InputMappingContext == OtherInputMapping.InputMappingContext;
}

bool FSI_InputMapping::operator!=(const FSI_InputMapping& OtherInputMapping) const
{
	return InputMappingContext != OtherInputMapping.InputMappingContext;
}

FSI_ObjectiveDetails::FSI_ObjectiveDetails()
{
}

FSI_ObjectiveDetails::FSI_ObjectiveDetails(USI_ObjectiveData* InObjectiveData) :
	ObjectiveDataAsset(InObjectiveData)
{
}

void FSI_ObjectiveDetails::SetIsObjectiveActive(bool bIsActive)
{
	if (bIsObjectiveActive == bIsActive) {return;}
	
	bIsObjectiveActive = bIsActive;
}

void FSI_ObjectiveDetails::SetIsObjectiveComplete(bool bIsComplete)
{
	if(bIsObjectiveComplete == bIsComplete){return;}
	
	bIsObjectiveComplete = bIsComplete;
}

void FSI_ObjectiveDetails::ResetObjective()
{
	bIsObjectiveActive = false;
	bIsObjectiveComplete = false;
}

USI_ObjectiveData* FSI_ObjectiveDetails::GetObjectiveData() const
{
	return ObjectiveDataAsset;
}

bool FSI_ObjectiveDetails::IsObjectiveActive()
{
	return bIsObjectiveActive;
}

bool FSI_ObjectiveDetails::IsObjectiveComplete()
{
	return bIsObjectiveComplete;
}

bool FSI_ObjectiveDetails::operator==(const FSI_ObjectiveDetails& OtherObjective) const
{
	return  OtherObjective.GetObjectiveData() == ObjectiveDataAsset;
}

bool FSI_ObjectiveDetails::operator!=(const FSI_ObjectiveDetails& OtherObjective) const
{
	return  OtherObjective.GetObjectiveData() != ObjectiveDataAsset;
}

FSI_PartDetails::FSI_PartDetails()
{
}

FSI_PartDetails::FSI_PartDetails(USI_PartData* InPartData) :
	PartDataAsset(InPartData)
{
}

bool FSI_PartDetails::CompleteObjective(const USI_ObjectiveData* InObjectiveToComplete)
{
	TArray<USI_ObjectiveData*> TempActiveObjectives = ActiveObjectives;
	for (USI_ObjectiveData* CurrentObjective : TempActiveObjectives)
	{
		if (CurrentObjective == InObjectiveToComplete)
		{
			FSI_ObjectiveDetails* CurrentObjectiveDetails = GetObjectiveDetails(CurrentObjective);
			CurrentObjectiveDetails->SetIsObjectiveComplete(true);
			CompletedObjectives.AddUnique(CurrentObjective);
			ActiveObjectives.Remove(CurrentObjective);
			return true;
		}
	}
	return false;
}

void FSI_PartDetails::SetIsPartComplete(bool bIsComplete)
{
	if(bIsPartComplete == bIsComplete){return;}
	
	bIsPartComplete = bIsComplete;
}

void FSI_PartDetails::ResetPart()
{
	for (TPair<USI_ObjectiveData*, FSI_ObjectiveDetails*>& CurrentPartObjective : PartObjectives)
	{
		if(!IsValid(CurrentPartObjective.Key)) {continue;}
		CurrentPartObjective.Value->ResetObjective();
	}

	ActiveObjectives.Empty();
	CompletedObjectives.Empty();
	
	bIsPartActive = false;
	bIsPartComplete = false;
}

void FSI_PartDetails::SetIsPartActive(bool bIsActive)
{
	if (bIsPartActive == bIsActive) {return;}

	bIsPartActive = bIsActive;
}

bool FSI_PartDetails::IsPartComplete()
{
	if (bIsPartComplete) {return bIsPartComplete;}

	if (PartObjectives.Num() == CompletedObjectives.Num())
	{
		bIsPartComplete = true;
	}
	
	return bIsPartComplete;
}

USI_PartData* FSI_PartDetails::GetPartData() const
{
	return PartDataAsset;
}

FSI_ObjectiveDetails* FSI_PartDetails::GetObjectiveDetails(const USI_ObjectiveData* InObjectiveData)
{
	return *PartObjectives.Find(InObjectiveData);
}

TMap<USI_ObjectiveData*, FSI_ObjectiveDetails*>& FSI_PartDetails::GetPartObjectives()
{
	return PartObjectives;
}

TArray<USI_ObjectiveData*> FSI_PartDetails::GetActiveObjectives()
{
	return ActiveObjectives;
}

TArray<USI_ObjectiveData*> FSI_PartDetails::GetCompletedObjectives()
{
	return CompletedObjectives;
}

bool FSI_PartDetails::operator==(const FSI_PartDetails& OtherPart) const
{
	return OtherPart.GetPartData() == PartDataAsset;
}

bool FSI_PartDetails::operator!=(const FSI_PartDetails& OtherPart) const
{
	return OtherPart.GetPartData() != PartDataAsset;
}

FSI_CaseDetails::FSI_CaseDetails()
{
}

FSI_CaseDetails::FSI_CaseDetails(USI_CaseData* InCaseData) :
	CaseDataAsset(InCaseData)
{
}

void FSI_CaseDetails::SetIsCaseAccepted(const bool bIsAccepted)
{
	if(bIsCaseAccepted == bIsAccepted){return;}

	bIsCaseAccepted = bIsAccepted;
}

void FSI_CaseDetails::SetIsCaseActive(const bool bIsActive)
{
	if(bIsCaseActive == bIsActive){return;}
	
	bIsCaseActive = bIsActive;
}

void FSI_CaseDetails::SetIsCaseComplete(const bool bIsComplete)
{
	if(bIsCaseComplete == bIsComplete){return;}
	
	bIsCaseComplete = bIsComplete;
}

void FSI_CaseDetails::SetActivePart(USI_PartData* InActivePart)
{
	ActivePart = InActivePart;
}

USI_CaseData* FSI_CaseDetails::GetCaseData() const
{
	return CaseDataAsset;
}

bool FSI_CaseDetails::IsCaseAccepted() const
{
	return bIsCaseAccepted;
}

bool FSI_CaseDetails::IsCaseComplete() const
{
	return bIsCaseComplete;
}

bool FSI_CaseDetails::IsCaseActive() const
{
	return bIsCaseActive;
}

void FSI_CaseDetails::ResetCase()
{
	for (const TPair<USI_PartData*, FSI_PartDetails*>& CurrentCasePart : CaseParts)
	{
		if(!IsValid(CurrentCasePart.Key)) {continue;}
		CurrentCasePart.Value->ResetPart();
	}

	CompletedParts.Empty();
	ActivePart = nullptr;
	
	bIsCaseAccepted = false;
	bIsCaseActive = false;
	bIsCaseComplete = false;
}

FSI_PartDetails* FSI_CaseDetails::GetPartDetails(const USI_PartData* InPart)
{
	return *CaseParts.Find(InPart);
}

TMap<USI_PartData*, FSI_PartDetails*>& FSI_CaseDetails::GetCaseParts()
{
	return CaseParts;
}

USI_PartData* FSI_CaseDetails::GetActivePart()
{
	return ActivePart;
}

bool FSI_CaseDetails::operator==(const FSI_CaseDetails& OtherCase) const
{
	return OtherCase.GetCaseData() == CaseDataAsset;
}

bool FSI_CaseDetails::operator!=(const FSI_CaseDetails& OtherCase) const
{
	return OtherCase.GetCaseData() != CaseDataAsset;
}

const USI_PartData* FSI_CaseDetails::GetActivePart() const
{
	return ActivePart;
}

FSI_MapState::FSI_MapState()
{
}

FSI_MapState::FSI_MapState(USI_MapData* InMapData, FSI_MediaSettings InIntroSettings, FSI_MediaSettings InOutroSettings, USI_MediaDataAsset* InLoadedIntroMedia, USI_MediaDataAsset* InLoadedOutroMedia, ULevelStreaming* InStreamingLevelRef) :
	MapData(InMapData),
	LoadedIntroMedia(InLoadedIntroMedia),
	LoadedOutroMedia(InLoadedOutroMedia)
{
}

void FSI_MapState::SetMapData(USI_MapData* InMapData)
{
	if(!IsValid(InMapData)) {return;}
	MapData = InMapData;
}

USI_MapData* FSI_MapState::GetMapData() const
{
	return MapData;
}

ULevelStreaming* FSI_MapState::GetStreamingLevelRef() const
{
	return StreamingLevelRef;
}

FSI_MediaSettings& FSI_MapState::GetIntroSettings()
{
	return IntroSettings;
}

FSI_MediaSettings& FSI_MapState::GetOutroSettings()
{
	return OutroSettings;
}

bool FSI_MapState::IsStateValid() const
{
	if (IsValid(MapData))
	{
		return true;
	}
	return false;
}

bool FSI_MapState::HasIntroMedia() const
{
	return IsValid(LoadedIntroMedia);
}

bool FSI_MapState::HasOutroMedia() const
{
	return IsValid(LoadedOutroMedia);
}

USI_MediaDataAsset* FSI_MapState::GetLoadedIntroMedia() const
{
	return LoadedIntroMedia;
}

USI_MediaDataAsset* FSI_MapState::GetLoadedOutroMedia() const
{
	return LoadedOutroMedia;
}

void FSI_MapState::SetStreamingLevelRef(ULevelStreaming* InStreamingLevelRef)
{
	if(!IsValid(InStreamingLevelRef)) {return;}
	StreamingLevelRef = InStreamingLevelRef;
}

void FSI_MapState::LoadIntroMedia(USI_MediaDataAsset* InIntroMedia)
{
	if (!IsValid(InIntroMedia)){return;}
	LoadedIntroMedia  = InIntroMedia;
}

void FSI_MapState::LoadOutroMedia(USI_MediaDataAsset* InOutroMedia)
{
	if (!IsValid(InOutroMedia)){return;}
	LoadedOutroMedia = InOutroMedia;
}

void FSI_MapState::UnLoadIntroMedia()
{
	if (!IsValid(LoadedIntroMedia)){return;}
	LoadedIntroMedia = nullptr;
}

void FSI_MapState::UnLoadOutroMedia()
{
	if (!IsValid(LoadedOutroMedia)){return;}
	LoadedOutroMedia  = nullptr;
}

bool FSI_MapState::operator==(const FSI_MapState& OtherMapState) const
{
	return MapData == OtherMapState.MapData;
}

bool FSI_MapState::operator!=(const FSI_MapState& OtherMapState) const
{
	return MapData != OtherMapState.MapData;
}

FSIGameplayAbilities::FSIGameplayAbilities(UGameplayAbility* InSIAbility, const FGameplayTagContainer& InSIAbilityTagContainer, const FGameplayAbilitySpecHandle& InSIAbilitySpecHandle)
{
	SIAbilityTagContainer = InSIAbilityTagContainer;
	SIAbilitySpecHandle = InSIAbilitySpecHandle;
	SIAbility = InSIAbility;
}

bool FSIGameplayAbilities::operator==(const FSIGameplayAbilities& OtherAbility) const
{
	return SIAbility == OtherAbility.SIAbility;
}
