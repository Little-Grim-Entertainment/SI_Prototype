// Fill out your copyright notice in the Description page of Project Settings.


#include "SI_NativeGameplayTagLibrary.h"

namespace SI_NativeGameplayTagLibrary
{
	UE_DEFINE_GAMEPLAY_TAG(SITag_Audio, "Audio")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Audio_Music, "Audio.Music")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Audio_Music_Pause, "Audio.Music.Pause")
		
	UE_DEFINE_GAMEPLAY_TAG(SITag_Camera, "Camera")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Camera_Mode, "Camera.Mode")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Camera_Mode_OutDoor, "Camera.Mode.OutDoor")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Camera_Mode_InDoor, "Camera.Mode.InDoor")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Camera_Mode_Observation, "Camera.Mode.Observation")
	
	UE_DEFINE_GAMEPLAY_TAG(SITag_Game, "Game")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Game_State, "Game.State")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Game_State_Playing, "Game.State.Playing")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Game_State_Paused, "Game.State.Paused")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Game_State_Loading, "Game.State.Loading")

	UE_DEFINE_GAMEPLAY_TAG(SITag_Input, "Input")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action, "Input.Action")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Interact, "Input.Action.Interact")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_ToggleObservationMode, "Input.Action.ToggleObservationMode")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_ToggleSystemMenu, "Input.Action.ToggleSystemMenu")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_ObserveObject, "Input.Action.ObserveObject")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Media_Skip, "Input.Action.Media.Skip")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Dialogue_Next, "Input.Action.Dialogue.Next")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Dialogue_Previous, "Input.Action.Dialogue.Previous")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Dialogue_Exit, "Input.Action.Dialogue.Exit")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Gizbo_ControlsToggle, "Input.Action.Gizbo.ControlsToggle")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Gizbo_Follow, "Input.Action.Gizbo.Follow")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Gizbo_MoveTo, "Input.Action.Gizbo.MoveTo")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Gizbo_MoveToConfirm, "Input.Action.Gizbo.MoveToConfirm")

	UE_DEFINE_GAMEPLAY_TAG(SITag_Media, "Media")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Media_Cinematic, "Media.Cinematic")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Media_Video, "Media.Video")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Media_TitleCard, "Media.TitleCard")
	
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player, "Player")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State, "Player.State")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_Exploration, "Player.State.Exploration")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_Observation, "Player.State.Observation")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_Menu, "Player.State.Menu")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_Media, "Player.State.Media")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_Dialogue, "Player.State.Dialogue")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_Interrogation, "Player.State.Interrogation")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_Inactive, "Player.State.Inactive")
	
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Axis_1D_MoveForward, "Input.Axis.1D.MoveForward")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Axis_1D_MoveRight, "Input.Axis.1D.MoveRight")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Axis_1D_TurnRate, "Input.Axis.1D.TurnRate")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Axis_1D_LookUpRate, "Input.Axis.1D.LookUpRate")
	
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI, "UI")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_HUD, "UI.HUD")

	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu, "UI.Menu")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu_Map, "UI.Menu.Map")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu_System, "UI.Menu.System")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu_Game, "UI.Menu.Game")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu_Vendor, "UI.Menu.Vendor")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu_Interrogation, "UI.Menu.Interrogation")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu_Dialogue, "UI.Menu.Dialogue")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu_Validation, "UI.Prompt.Validation")

	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Screen, "UI.Screen")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Screen_Loading, "UI.Screen.Loading")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Screen_Video, "UI.Screen.Video")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Screen_TitleCard, "UI.Screen.TitleCard")

	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Prompt, "UI.Prompt")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Prompt_Interact, "UI.Prompt.Interact")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Prompt_Skip, "UI.Prompt.Skip")
}