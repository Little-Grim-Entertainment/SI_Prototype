// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_Types.h"

#include "Engine/LevelStreaming.h"
#include "Data/Maps/AoS_MapData.h"
#include "Data/Cases/AoS_CaseData.h"
#include "Data/Cases/AoS_PartData.h"
#include "Data/Cases/AoS_ObjectiveData.h"
#include "Data/Media/AoS_MediaDataAsset.h"
#include "InputMappingContext.h"
#include "InputAction.h"

FAoS_MusicSettings::FAoS_MusicSettings()
{
}

FAoS_MusicSettings::FAoS_MusicSettings(USoundBase* InMusicSource) :
	MusicSource(InMusicSource)
{
}

FAoS_InputAction::FAoS_InputAction()
{
}

FAoS_InputAction::FAoS_InputAction(UInputAction* InInputAction) :
	InputAction(InInputAction)
{
}

const UInputAction* FAoS_InputAction::GetInputAction() const
{
	return InputAction;
}

const FGameplayTag& FAoS_InputAction::GetInputTag() const
{
	return InputTag;
}

FAoS_InputMapping::FAoS_InputMapping()
{
}

FAoS_InputMapping::FAoS_InputMapping(UInputMappingContext* InInputMappingContext) :
	InputMappingContext(InInputMappingContext)
{
}

const UInputMappingContext* FAoS_InputMapping::GetInputMappingContext() const
{
	return InputMappingContext;
}

const FGameplayTag& FAoS_InputMapping::GetAssociatedTag() const
{
	return AssociatedTag;
}

const FGameplayTag& FAoS_InputMapping::GetSecondaryTag() const
{
	return SecondaryTag;
}

bool FAoS_InputMapping::IsDefaultMappingForMode() const
{
	return bIsDefaultMappingForMode;
}

bool FAoS_InputMapping::operator==(const FAoS_InputMapping& OtherInputMapping) const
{
	return InputMappingContext == OtherInputMapping.InputMappingContext;
}

bool FAoS_InputMapping::operator!=(const FAoS_InputMapping& OtherInputMapping) const
{
	return InputMappingContext != OtherInputMapping.InputMappingContext;
}

FAoS_ObjectiveDetails::FAoS_ObjectiveDetails()
{
}

FAoS_ObjectiveDetails::FAoS_ObjectiveDetails(UAoS_ObjectiveData* InObjectiveData) :
	ObjectiveDataAsset(InObjectiveData)
{
}

void FAoS_ObjectiveDetails::SetIsObjectiveActive(bool bIsActive)
{
	if (bIsObjectiveActive == bIsActive) {return;}
	
	bIsObjectiveActive = bIsActive;
}

void FAoS_ObjectiveDetails::SetIsObjectiveComplete(bool bIsComplete)
{
	if(bIsObjectiveComplete == bIsComplete){return;}
	
	bIsObjectiveComplete = bIsComplete;
}

void FAoS_ObjectiveDetails::ResetObjective()
{
	bIsObjectiveActive = false;
	bIsObjectiveComplete = false;
}

UAoS_ObjectiveData* FAoS_ObjectiveDetails::GetObjectiveData() const
{
	return ObjectiveDataAsset;
}

bool FAoS_ObjectiveDetails::IsObjectiveActive()
{
	return bIsObjectiveActive;
}

bool FAoS_ObjectiveDetails::IsObjectiveComplete()
{
	return bIsObjectiveComplete;
}

bool FAoS_ObjectiveDetails::operator==(const FAoS_ObjectiveDetails& OtherObjective) const
{
	return  OtherObjective.GetObjectiveData() == ObjectiveDataAsset;
}

bool FAoS_ObjectiveDetails::operator!=(const FAoS_ObjectiveDetails& OtherObjective) const
{
	return  OtherObjective.GetObjectiveData() != ObjectiveDataAsset;
}

FAoS_PartDetails::FAoS_PartDetails()
{
}

FAoS_PartDetails::FAoS_PartDetails(UAoS_PartData* InPartData) :
	PartDataAsset(InPartData)
{
}

bool FAoS_PartDetails::CompleteObjective(const UAoS_ObjectiveData* InObjectiveToComplete)
{
	TArray<UAoS_ObjectiveData*> TempActiveObjectives = ActiveObjectives;
	for (UAoS_ObjectiveData* CurrentObjective : TempActiveObjectives)
	{
		if (CurrentObjective == InObjectiveToComplete)
		{
			FAoS_ObjectiveDetails& CurrentObjectiveDetails = GetObjectiveDetails(CurrentObjective);
			CurrentObjectiveDetails.SetIsObjectiveComplete(true);
			CompletedObjectives.AddUnique(CurrentObjective);
			ActiveObjectives.Remove(CurrentObjective);
			return true;
		}
	}
	return false;
}

void FAoS_PartDetails::SetIsPartComplete(bool bIsComplete)
{
	if(bIsPartComplete == bIsComplete){return;}
	
	bIsPartComplete = bIsComplete;
}

void FAoS_PartDetails::ResetPart()
{
	for (TPair<UAoS_ObjectiveData*, FAoS_ObjectiveDetails>& CurrentPartObjective : PartObjectives)
	{
		if(!IsValid(CurrentPartObjective.Key)) {continue;}
		CurrentPartObjective.Value.ResetObjective();
	}

	ActiveObjectives.Empty();
	CompletedObjectives.Empty();
	
	bIsPartActive = false;
	bIsPartComplete = false;
}

void FAoS_PartDetails::SetIsPartActive(bool bIsActive)
{
	if (bIsPartActive == bIsActive) {return;}

	bIsPartActive = bIsActive;
}

bool FAoS_PartDetails::IsPartComplete()
{
	if (bIsPartComplete) {return bIsPartComplete;}

	if (PartObjectives.Num() == CompletedObjectives.Num())
	{
		bIsPartComplete = true;
	}
	
	return bIsPartComplete;
}

UAoS_PartData* FAoS_PartDetails::GetPartData() const
{
	return PartDataAsset;
}

FAoS_ObjectiveDetails& FAoS_PartDetails::GetObjectiveDetails(const UAoS_ObjectiveData* InObjectiveData)
{
	return *PartObjectives.Find(InObjectiveData);
}

TMap<UAoS_ObjectiveData*, FAoS_ObjectiveDetails>& FAoS_PartDetails::GetPartObjectives()
{
	return PartObjectives;
}

TArray<UAoS_ObjectiveData*> FAoS_PartDetails::GetActiveObjectives()
{
	return ActiveObjectives;
}

TArray<UAoS_ObjectiveData*> FAoS_PartDetails::GetCompletedObjectives()
{
	return CompletedObjectives;
}

bool FAoS_PartDetails::operator==(const FAoS_PartDetails& OtherPart) const
{
	return OtherPart.GetPartData() == PartDataAsset;
}

bool FAoS_PartDetails::operator!=(const FAoS_PartDetails& OtherPart) const
{
	return OtherPart.GetPartData() != PartDataAsset;
}

FAoS_CaseDetails::FAoS_CaseDetails()
{
}

FAoS_CaseDetails::FAoS_CaseDetails(UAoS_CaseData* InCaseData) :
	CaseDataAsset(InCaseData)
{
}

void FAoS_CaseDetails::SetIsCaseAccepted(const bool bIsAccepted)
{
	if(bIsCaseAccepted == bIsAccepted){return;}

	bIsCaseAccepted = bIsAccepted;
}

void FAoS_CaseDetails::SetIsCaseActive(const bool bIsActive)
{
	if(bIsCaseActive == bIsActive){return;}
	
	bIsCaseActive = bIsActive;
}

void FAoS_CaseDetails::SetIsCaseComplete(const bool bIsComplete)
{
	if(bIsCaseComplete == bIsComplete){return;}
	
	bIsCaseComplete = bIsComplete;
}

void FAoS_CaseDetails::SetActivePart(UAoS_PartData* InActivePart)
{
	ActivePart = InActivePart;
}

UAoS_CaseData* FAoS_CaseDetails::GetCaseData() const
{
	return CaseDataAsset;
}

bool FAoS_CaseDetails::IsCaseAccepted() const
{
	return bIsCaseAccepted;
}

bool FAoS_CaseDetails::IsCaseComplete() const
{
	return bIsCaseComplete;
}

bool FAoS_CaseDetails::IsCaseActive() const
{
	return bIsCaseActive;
}

void FAoS_CaseDetails::ResetCase()
{
	for (TPair<UAoS_PartData*, FAoS_PartDetails>& CurrentCasePart : CaseParts)
	{
		if(!IsValid(CurrentCasePart.Key)) {continue;}
		CurrentCasePart.Value.ResetPart();
	}

	CompletedParts.Empty();
	ActivePart = nullptr;
	
	bIsCaseAccepted = false;
	bIsCaseActive = false;
	bIsCaseComplete = false;
}

FAoS_PartDetails& FAoS_CaseDetails::GetPartDetails(const UAoS_PartData* InPart)
{
	return *CaseParts.Find(InPart);
}

TMap<UAoS_PartData*, FAoS_PartDetails>& FAoS_CaseDetails::GetCaseParts()
{
	return CaseParts;
}

UAoS_PartData* FAoS_CaseDetails::GetActivePart()
{
	return ActivePart;
}

bool FAoS_CaseDetails::operator==(const FAoS_CaseDetails& OtherCase) const
{
	return OtherCase.GetCaseData() == CaseDataAsset;
}

bool FAoS_CaseDetails::operator!=(const FAoS_CaseDetails& OtherCase) const
{
	return OtherCase.GetCaseData() != CaseDataAsset;
}

const UAoS_PartData* FAoS_CaseDetails::GetActivePart() const
{
	return ActivePart;
}

FAoS_MapState::FAoS_MapState()
{
}

FAoS_MapState::FAoS_MapState(UAoS_MapData* InMapData, FAoS_MediaSettings InIntroSettings, FAoS_MediaSettings InOutroSettings, UAoS_MediaDataAsset* InLoadedIntroMedia, UAoS_MediaDataAsset* InLoadedOutroMedia, ULevelStreaming* InStreamingLevelRef) :
	MapData(InMapData),
	LoadedIntroMedia(InLoadedIntroMedia),
	LoadedOutroMedia(InLoadedOutroMedia)
{
}

void FAoS_MapState::SetMapData(UAoS_MapData* InMapData)
{
	if(!IsValid(InMapData)) {return;}
	MapData = InMapData;
}

UAoS_MapData* FAoS_MapState::GetMapData() const
{
	return MapData;
}

ULevelStreaming* FAoS_MapState::GetStreamingLevelRef() const
{
	return StreamingLevelRef;
}

FAoS_MediaSettings& FAoS_MapState::GetIntroSettings()
{
	return IntroSettings;
}

FAoS_MediaSettings& FAoS_MapState::GetOutroSettings()
{
	return OutroSettings;
}

bool FAoS_MapState::IsStateValid() const
{
	if (IsValid(MapData))
	{
		return true;
	}
	return false;
}

bool FAoS_MapState::HasIntroMedia() const
{
	return IsValid(LoadedIntroMedia);
}

bool FAoS_MapState::HasOutroMedia() const
{
	return IsValid(LoadedOutroMedia);
}

UAoS_MediaDataAsset* FAoS_MapState::GetLoadedIntroMedia() const
{
	return LoadedIntroMedia;
}

UAoS_MediaDataAsset* FAoS_MapState::GetLoadedOutroMedia() const
{
	return LoadedOutroMedia;
}

void FAoS_MapState::SetStreamingLevelRef(ULevelStreaming* InStreamingLevelRef)
{
	if(!IsValid(InStreamingLevelRef)) {return;}
	StreamingLevelRef = InStreamingLevelRef;
}

void FAoS_MapState::LoadIntroMedia(UAoS_MediaDataAsset* InIntroMedia)
{
	if (!IsValid(InIntroMedia)){return;}
	LoadedIntroMedia  = InIntroMedia;
}

void FAoS_MapState::LoadOutroMedia(UAoS_MediaDataAsset* InOutroMedia)
{
	if (!IsValid(InOutroMedia)){return;}
	LoadedOutroMedia = InOutroMedia;
}

void FAoS_MapState::UnLoadIntroMedia()
{
	if (!IsValid(LoadedIntroMedia)){return;}
	LoadedIntroMedia = nullptr;
}

void FAoS_MapState::UnLoadOutroMedia()
{
	if (!IsValid(LoadedOutroMedia)){return;}
	LoadedOutroMedia  = nullptr;
}

bool FAoS_MapState::operator==(const FAoS_MapState& OtherMapState) const
{
	return MapData == OtherMapState.MapData;
}

bool FAoS_MapState::operator!=(const FAoS_MapState& OtherMapState) const
{
	return MapData != OtherMapState.MapData;
}

