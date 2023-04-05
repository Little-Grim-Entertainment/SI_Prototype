// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_NativeGameplayTagLibrary.h"

namespace AoS_NativeGameplayTagLibrary
{
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Game, "Game")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Game_State, "Game.State")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Game_State_Playing, "Game.State.Playing")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Game_State_Paused, "Game.State.Paused")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Game_State_Loading, "Game.State.Loading")
<<<<<<< Updated upstream
	
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_Mode_Exploration, "Player.Mode.Exploration")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_Mode_Observation, "Player.Mode.Observation")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_Mode_Menu, "Player.Mode.Menu")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_Mode_Media, "Player.Mode.Media")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_Mode_Dialogue, "Player.Mode.Dialogue")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_Mode_Interrogation, "Player.Mode.Interrogation")
	
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Interact, "Input.Action.Interact")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_ToggleObservationMode, "Input.Action.ToggleObservationMode")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_ToggleSystemMenu, "Input.Action.ToggleSystemMenu")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_ObserveObject, "Input.Action.ObserveObject")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Media_Skip, "Input.Action.Media.Skip")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Dialogue_Next, "Input.Action.Dialogue.Next")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Dialogue_Previous, "Input.Action.Dialogue.Previous")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Dialogue_Exit, "Input.Action.Dialogue.Exit")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Gizbo_Follow, "Input.Action.Gizbo.Follow")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Gizbo_MoveTo, "Input.Action.Gizbo.MoveTo")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Gizbo_MoveToConfirm, "Input.Action.Gizbo.MoveToConfirm")

	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Axis_1D_MoveForward, "Input.Axis.1D.MoveForward")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Axis_1D_MoveRight, "Input.Axis.1D.MoveRight")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Axis_1D_TurnRate, "Input.Axis.1D.TurnRate")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Axis_1D_LookUpRate, "Input.Axis.1D.LookUpRate")
	
=======

	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player, "Player")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_Mode, "Player.Mode")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_Mode_Exploration, "Player.Mode.Exploration")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_Mode_Observation, "Player.Mode.Observation")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_Mode_Menu, "Player.Mode.Menu")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_Mode_Media, "Player.Mode.Media")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_Mode_Dialogue, "Player.Mode.Dialogue")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Player_Mode_Interrogation, "Player.Mode.Interrogation")
	
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Interact, "Input.Action.Interact")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_ToggleObservationMode, "Input.Action.ToggleObservationMode")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_ToggleSystemMenu, "Input.Action.ToggleSystemMenu")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_ObserveObject, "Input.Action.ObserveObject")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Media_Skip, "Input.Action.Media.Skip")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Dialogue_Next, "Input.Action.Dialogue.Next")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Dialogue_Previous, "Input.Action.Dialogue.Previous")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Dialogue_Exit, "Input.Action.Dialogue.Exit")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Gizbo_Follow, "Input.Action.Gizbo.Follow")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Gizbo_MoveTo, "Input.Action.Gizbo.MoveTo")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Action_Gizbo_MoveToConfirm, "Input.Action.Gizbo.MoveToConfirm")

	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Axis_1D_MoveForward, "Input.Axis.1D.MoveForward")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Axis_1D_MoveRight, "Input.Axis.1D.MoveRight")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Axis_1D_TurnRate, "Input.Axis.1D.TurnRate")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Input_Axis_1D_LookUpRate, "Input.Axis.1D.LookUpRate")

	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Menu, "Menu")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Menu_Type, "Menu.Type")
>>>>>>> Stashed changes
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Menu_Type_Main, "Menu.Type.Main")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Menu_Type_System, "Menu.Type.System")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Menu_Type_Game, "Menu.Type.Game")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Menu_Type_Vendor, "Menu.Type.Vendor")

	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Media, "Media")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Media_Type, "Media.Type")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Media_Type_Cinematic, "Media.Type.Cinematic")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Media_Type_Video, "Media.Type.Video")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Media_Type_TitleCard, "Media.Type.TitleCard")
	
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Camera, "Camera")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Camera_Mode, "Camera.Mode")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Camera_Mode_OutDoor, "Camera.Mode.OutDoor")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Camera_Mode_InDoor, "Camera.Mode.InDoor")
	UE_DEFINE_GAMEPLAY_TAG(AOSTag_Camera_Mode_Observation, "Camera.Mode.Observation")
}