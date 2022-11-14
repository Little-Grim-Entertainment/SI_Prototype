// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/AoS_DialogueManager.h"
#include "DlgDialogue.h"
#include "DlgManager.h"
#include "AoS_GameInstance.h"
#include "UI/AoS_UIManager.h"


void UAoS_DialogueManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	if(GameInstance)
	{
		UAoS_UIManager* UIManager = Cast<UAoS_UIManager>(GameInstance->GetUIManager());
		if (IsValid(UIManager))
		{
			;
		}
	}
}


FOnBeginDialogue& UAoS_DialogueManager::GetOnBeginDialogue()
{
	return OnBeginDialogueDelegate;
}
