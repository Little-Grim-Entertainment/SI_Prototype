// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_NPC.h"

#include "LG_DebugMacros.h"
#include "SI_NativeGameplayTagLibrary.h"


using namespace SI_NativeGameplayTagLibrary;

ASI_NPC::ASI_NPC()
{
}

void ASI_NPC::SetCurrentBehavior(const FGameplayTag NewBehaviorTag)
{
	if (CurrentBehaviorTag != NewBehaviorTag)
	{
		CurrentBehaviorTag = NewBehaviorTag;
	}
	LG_PRINT(5.0f, Black , "ASI_NPC::SetCurrentBehavior %s", *CurrentBehaviorTag.ToString());
}

FGameplayTag& ASI_NPC::GetCurrentBehaviorTag()
{
	return CurrentBehaviorTag;
}

bool ASI_NPC::IsPerformingMainAction() const
{
	return CurrentBehaviorTag == SITag_Behavior_Default;
}