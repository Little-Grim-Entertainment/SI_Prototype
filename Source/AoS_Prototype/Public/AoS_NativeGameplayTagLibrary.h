// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace AoS_NativeGameplayTagLibrary
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Game_State_Playing);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Game_State_Paused);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Game_State_Loading);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player_State_Exploration);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player_State_Observation);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player_State_Menu);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player_State_Media);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player_State_Dialogue);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player_State_Interrogation);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Menu_Type_Main);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Menu_Type_System);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Menu_Type_Game);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Menu_Type_Vendor);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Media_Type_Cinematic);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Media_Type_Video);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Media_Type_TitleCard);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Camera_Mode_OutDoor);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Camera_Mode_InDoor);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Camera_Mode_Observation);
}