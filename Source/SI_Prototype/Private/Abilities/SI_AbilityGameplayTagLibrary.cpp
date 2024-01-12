// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/SI_AbilityGameplayTagLibrary.h"

namespace SI_AbilityGameplayTagLibrary
{	
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
}