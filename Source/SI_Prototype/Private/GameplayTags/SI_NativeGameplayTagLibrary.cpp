// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayTags/SI_NativeGameplayTagLibrary.h"

namespace SI_NativeGameplayTagLibrary
{
	UE_DEFINE_GAMEPLAY_TAG(SITag_None, "None")
	
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability, "Ability")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Cancel, "Ability.Cancel")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Confirm, "Ability.Confirm")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_HoldConfirm, "Ability.HoldConfirm")

	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_AI, "Ability.AI")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_AI_Follow, "Ability.AI.Follow")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_AI_MoveTo, "Ability.AI.MoveTo")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_AI_Wait, "Ability.AI.Wait")
	
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Gadget_UsePrimary, "Ability.Gadget.UsePrimary")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Gadget_UseSecondary, "Ability.Gadget.UseSecondary")
	
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Interact, "Ability.Interact")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Interact_Drop, "Ability.Interact.Drop")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Interact_Pickup, "Ability.Interact.Pickup")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Interact_Pull, "Ability.Interact.Pull")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Interact_Push, "Ability.Interact.Push")
		
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Nick, "Ability.Nick")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Nick_AdaptableAction, "Ability.Nick.AdaptableAction")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Nick_Observation, "Ability.Nick.Observation")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Nick_ObserveObject, "Ability.Nick.ObserveObject")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Nick_PossessMovable, "Ability.Nick.PossessMovable")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Nick_PossessIndicator, "Ability.Nick.PossessIndicator")

	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Gizbo, "Ability.Gizbo")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Gizbo_Construct_Flashlight, "Ability.Gizbo.Construct.Flashlight")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Gizbo_Construct_Lockpicks, "Ability.Gizbo.Construct.Lockpicks")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Gizbo_Construct, "Ability.Gizbo.Construct")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Ability_Gizbo_Deconstruct, "Ability.Gizbo.Deconstruct")
	
	UE_DEFINE_GAMEPLAY_TAG(SITag_Actor, "Actor")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Actor_Observable, "Actor.Observable")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Actor_Interactable, "Actor.Interactable")
	
	UE_DEFINE_GAMEPLAY_TAG(SITag_Audio, "Audio")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Audio_Music, "Audio.Music")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Audio_Music_Playing, "Audio.Music.Playing")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Audio_Music_Pause, "Audio.Music.Pause")

	UE_DEFINE_GAMEPLAY_TAG(SITag_Behavior, "Behavior")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Behavior_Default, "Behavior.Default")	
	UE_DEFINE_GAMEPLAY_TAG(SITag_Behavior_Following, "Behavior.Following")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Behavior_MoveTo, "Behavior.MoveTo")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Behavior_None, "Behavior.None")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Behavior_Patrolling, "Behavior.Patrolling")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Behavior_Waiting, "Behavior.Waiting")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Behavior_Wandering, "Behavior.Wandering")
	
	UE_DEFINE_GAMEPLAY_TAG(SITag_Camera, "Camera")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Camera_Mode, "Camera.Mode")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Camera_Mode_Dialogue, "Camera.Mode.Dialogue")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Camera_Mode_OutDoor, "Camera.Mode.OutDoor")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Camera_Mode_InDoor, "Camera.Mode.InDoor")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Camera_Mode_Observation, "Camera.Mode.Observation")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Camera_Mode_PossessMovable, "Camera.Mode.PossessMovable")

	UE_DEFINE_GAMEPLAY_TAG(SITag_Debug, "Debug")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Debug_DisableAllMedia, "Debug.DisableAllMedia")

	// Dialogue
	UE_DEFINE_GAMEPLAY_TAG(SITag_Dialogue, "Dialogue")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Dialogue_Struct, "Dialogue.Struct")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Dialogue_Struct_BubbleDialogue, "Dialogue.Struct.BubbleDialogue")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Dialogue_Struct_PrimaryDialogue, "Dialogue.Struct.PrimaryDialogue")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Dialogue_Struct_CorrectedDialogue, "Dialogue.Struct.CorrectedDialogue")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Dialogue_Struct_DefaultResponse, "Dialogue.Struct.DefaultResponse")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Dialogue_Struct_PressDialogue, "Dialogue.Struct.PressDialogue")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Dialogue_Struct_ResponseDialogue, "Dialogue.Struct.ResponseDialogue")
	
	UE_DEFINE_GAMEPLAY_TAG(SITag_Gadget, "Gadget")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Gadget_Flashlight, "Gadget.Flashlight")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Gadget_Lockpicks, "Gadget.Lockpicks")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Gadget_Camera, "Gadget.Camera")
	
	UE_DEFINE_GAMEPLAY_TAG(SITag_Game, "Game")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Game_State, "Game.State")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Game_State_Playing, "Game.State.Playing")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Game_State_Paused, "Game.State.Paused")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Game_State_Loading, "Game.State.Loading")

	UE_DEFINE_GAMEPLAY_TAG(SITag_Input, "Input")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action, "Input.Action")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Interact, "Input.Action.Interact")

	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_AdaptableAction, "Input.Action.AdaptableAction")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_CancelAbility, "Input.Action.CancelAbility")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_ConfirmAbility, "Input.Action.ConfirmAbility")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_HoldConfirmAbility, "Input.Action.HoldConfirmAbility")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Dialogue_Exit, "Input.Action.Dialogue.Exit")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Dialogue_Next, "Input.Action.Dialogue.Next")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Dialogue_Previous, "Input.Action.Dialogue.Previous")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Media_Skip, "Input.Action.Media.Skip")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_MultiOption_Down, "Input.Action.MultiOption.Down")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_MultiOption_Left, "Input.Action.MultiOption.Left")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_MultiOption_Right, "Input.Action.MultiOption.Right")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_MultiOption_Up, "Input.Action.MultiOption.Up")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_ObserveObject, "Input.Action.ObserveObject")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_ToggleGizboControls, "Input.Action.ToggleGizboControls")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_ToggleObservationMode, "Input.Action.ToggleObservationMode")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_ToggleSystemMenu, "Input.Action.ToggleSystemMenu")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_UseGadget, "Input.Action.UseGadget")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_UseGadgetSecondary, "Input.Action.UseGadgetSecondary")
	
	// Gizbo Commands
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Gizbo_Follow, "Input.Action.Gizbo.Follow")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Gizbo_MultiOption_Down, "Input.Action.Gizbo.MultiOption.Down")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Gizbo_MultiOption_Left, "Input.Action.Gizbo.MultiOption.Left")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Gizbo_MultiOption_Right, "Input.Action.Gizbo.MultiOption.Right")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Gizbo_MultiOption_Up, "Input.Action.Gizbo.MultiOption.Up")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Gizbo_UseGadget, "Input.Action.Gizbo.UseGadget");
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Action_Gizbo_UseGadgetSecondary, "Input.Action.Gizbo.UseGadgetSecondary");

	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Axis_1D_MoveForward, "Input.Axis.1D.MoveForward")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Axis_1D_MoveRight, "Input.Axis.1D.MoveRight")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Axis_1D_TurnRate, "Input.Axis.1D.TurnRate")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Input_Axis_1D_LookUpRate, "Input.Axis.1D.LookUpRate")

	UE_DEFINE_GAMEPLAY_TAG(SITag_Interaction_Activate,"Interaction.Activate")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Interaction_Deactivate,"Interaction.Deactivate")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Interaction_Pickup,"Interaction.Pickup")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Interaction_Drop,"Interaction.Drop")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Interaction_Push,"Interaction.Push")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Interaction_Pull,"Interaction.Pull")
	
	UE_DEFINE_GAMEPLAY_TAG(SITag_Media, "Media")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Media_Cinematic, "Media.Cinematic")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Media_TitleCard, "Media.TitleCard")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Media_Video, "Media.Video")

	// Player State
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player, "Player")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State, "Player.State")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_Dialogue, "Player.State.Dialogue")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_Exploration, "Player.State.Exploration")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_GizboActions, "Player.State.GizboActions")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_Inactive, "Player.State.Inactive")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_Interrogation, "Player.State.Interrogation")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_Menu, "Player.State.Menu")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_Media, "Player.State.Media")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_Observation, "Player.State.Observation")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_PossessIndicator, "Player.State.PossessIndicator")
	UE_DEFINE_GAMEPLAY_TAG(SITag_Player_State_PossessMovable, "Player.State.PossessMovable")

	// UI
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI, "UI")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_HUD, "UI.HUD")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_HUD_Dialogue, "UI.HUD.Dialogue")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_HUD_QuickAction, "UI.HUD.QuickAction")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_HUD_QuickAction_Movable, "UI.HUD.QuickAction.Movable")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_HUD_QuickAction_GadgetsOne, "UI.HUD.QuickAction.GadgetsOne")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_HUD_QuickAction_GadgetsTwo, "UI.HUD.QuickAction.GadgetsTwo")

	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu, "UI.Menu")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu_Map, "UI.Menu.Map")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu_System, "UI.Menu.System")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu_Game, "UI.Menu.Game")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu_Vendor, "UI.Menu.Vendor")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu_Interrogation, "UI.Menu.Interrogation")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Menu_Validation, "UI.Prompt.Validation")

	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Screen, "UI.Screen")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Screen_Loading, "UI.Screen.Loading")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Screen_Video, "UI.Screen.Video")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Screen_TitleCard, "UI.Screen.TitleCard")

	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Prompt, "UI.Prompt")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Prompt_Interact, "UI.Prompt.Interact")
	UE_DEFINE_GAMEPLAY_TAG(SITag_UI_Prompt_Skip, "UI.Prompt.Skip")
}