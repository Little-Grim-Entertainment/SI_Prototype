// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_Types.h"

#include "Engine/LevelStreaming.h"
#include "Data/Maps/AoS_MapData.h"
#include "Data/Media/AoS_MediaDataAsset.h"


const UInputAction* FAoS_InputAction::GetInputAction() const
{
	return InputAction;
}

const FGameplayTag& FAoS_InputAction::GetInputTag() const
{
	return InputTag;
}

const UInputMappingContext* FAoS_InputMapping::GetInputMappingContext() const
{
	return InputMappingContext;
}

const FGameplayTag& FAoS_InputMapping::GetAssociatedPlayerModeTag() const
{
	return AssociatedPlayerModeTag;
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

