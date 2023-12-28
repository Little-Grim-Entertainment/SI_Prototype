// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_NPC.h"

#include "LG_DebugMacros.h"
#include "GameplayTags/SI_NativeGameplayTagLibrary.h"
#include "Components/StateTreeComponent.h"
#include "SI_Prototype/SI_Prototype.h"


using namespace SI_NativeGameplayTagLibrary;

ASI_NPC::ASI_NPC()
{
	StateTreeComponent = CreateDefaultSubobject<UStateTreeComponent>(TEXT("State Tree Component"));
}

void ASI_NPC::SetCurrentBehavior(const FGameplayTag NewBehaviorTag)
{
	if (CurrentBehaviorTag != NewBehaviorTag)
	{
		CurrentBehaviorTag = NewBehaviorTag;
		OnBehaviorTagUpdated.Broadcast(CurrentBehaviorTag);
	}
	LG_LOG(LogLG_AI, Log, "ASI_NPC::SetCurrentBehavior %s", *CurrentBehaviorTag.ToString());
}

FGameplayTag& ASI_NPC::GetCurrentBehaviorTag()
{
	return CurrentBehaviorTag;
}

bool ASI_NPC::IsPerformingMainAction() const
{
	return CurrentBehaviorTag == SITag_Behavior_Default;
}

void ASI_NPC::BeginPlay()
{
	Super::BeginPlay();

	//StateTreeComponent->StartLogic();
}
