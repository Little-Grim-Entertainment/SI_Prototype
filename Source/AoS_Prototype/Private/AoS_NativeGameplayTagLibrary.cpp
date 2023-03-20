// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_NativeGameplayTagLibrary.h"

namespace AoS_NativeGameplayTagLibrary
{
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Game_State_Playing, "Game.State.Playing")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Game_State_Paused, "Game.State.Paused")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Game_State_Loading, "Game.State.Loading")
	
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_State_Exploration, "Player.State.Exploration")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_State_Observation, "Player.State.Observation")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_State_Menu, "Player.State.Menu")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_State_Media, "Player.State.Media")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_State_Dialogue, "Player.State.Dialogue")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_State_Interrogation, "Player.State.Interrogation")
	
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Menu_Type_Main, "Menu.Type.Main")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Menu_Type_System, "Menu.Type.System")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Menu_Type_Game, "Menu.Type.Game")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Menu_Type_Vendor, "Menu.Type.Vendor")

	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Media_Type_Cinematic, "Media.Type.Cinematic")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Media_Type_Video, "Media.Type.Video")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Media_Type_TitleCard, "Media.Type.TitleCard")
	
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Camera_Mode_OutDoor, "Camera.Mode.OutDoor")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Camera_Mode_InDoor, "Camera.Mode.InDoor")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Camera_Mode_Observation, "Camera.Mode.Observation")
}