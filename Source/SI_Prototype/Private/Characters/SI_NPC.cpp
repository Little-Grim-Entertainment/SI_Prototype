// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_NPC.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "AI/SI_StateTreeComponent.h"

using namespace SI_NativeGameplayTagLibrary;

ASI_NPC::ASI_NPC()
{
	StateTreeComponent = CreateDefaultSubobject<USI_StateTreeComponent>(TEXT("StateTreeComponent"));
}

void ASI_NPC::SetCurrentBehavior(const FGameplayTag NewBehaviorTag)
{
	if (CurrentBehaviorTag != NewBehaviorTag)
	{
		CurrentBehaviorTag = NewBehaviorTag;
	}
}

FGameplayTag& ASI_NPC::GetCurrentBehaviorTag()
{
	return CurrentBehaviorTag;
}

bool ASI_NPC::IsPerformingMainAction() const
{
	return CurrentBehaviorTag == SITag_Behavior_Default;
}