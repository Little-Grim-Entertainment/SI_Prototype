// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_NPC.h"
#include "LG_DebugMacros.h"
#include "SI_GameInstance.h"
#include "Characters/SI_CharacterManager.h"
#include "Components/StateTreeComponent.h"
#include "Characters/Data/SI_CharacterData.h"
#include "SI_Prototype/SI_Prototype.h"
#include "Dialogue/SI_DialogueTypes.h"
#include "Cases/SI_CaseManager.h"
#include "Dialogue/SI_DialogueManager.h"
#include "Dialogue/Data/SI_DialogueDataAsset.h"

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

	CharacterManager = GetWorld()->GetSubsystem<USI_CharacterManager>();
	if(!IsValid(CharacterManager.Get())) {return;}

	InitializeCharacterState();

	//StateTreeComponent->StartLogic();
}

void ASI_NPC::InitializeCharacterState()
{
	if(!IsValid(CharacterManager.Get()) || !IsValid(CharacterData)) {return;}

	CharacterState = CharacterManager->GetCharacterStateByTag(CharacterData->CharacterTag, this);
	if(CharacterState)
	{
		InitializeCharacterDialogueState();
	}
}

void ASI_NPC::InitializeCharacterDialogueState()
{
	const USI_GameInstance* GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	if(!IsValid(GameInstance) || !CharacterState  || !IsValid(CharacterManager.Get())) {return;}
	
	const USI_CaseManager* CaseManager = GameInstance->GetSubsystem<USI_CaseManager>();
	const USI_DialogueDataAsset* CharacterDialogue = CharacterData->CharacterDialogue;
	if(!IsValid(CaseManager) || !IsValid(CharacterDialogue)) {return;}
	
	const USI_CaseData* ActiveCase = CaseManager->GetActiveCase();
	if(!IsValid(ActiveCase) || !CharacterManager->IsActiveCharacter(CharacterData))
	{
		return;
	}
	
	if(CharacterState->CharacterCaseStates.IsEmpty() || !HasCharacterStateForCase(ActiveCase->CaseTag))
	{
		const UDataTable* PrimaryDialogueDataTable = CharacterDialogue->GetDialogueDataTableByType(SITag_Dialogue_Struct_PrimaryDialogue);
		CharacterState->AddNewCaseState(ActiveCase, PrimaryDialogueDataTable);
	}
}

bool ASI_NPC::HasCharacterStateForCase(const FGameplayTag& InCaseTag) const
{
	const FSI_CharacterCaseState* CharacterCaseState = CharacterState->CharacterCaseStates.Find(InCaseTag);
	return CharacterCaseState != nullptr;
}

FSI_CharacterState* ASI_NPC::GetCharacterState() const
{
	return CharacterState;
}

FSI_CharacterState* ASI_NPC::GetCharacterState()
{
	return CharacterState;
}

FSI_DialogueState* ASI_NPC::GetActiveDialogueState() const
{
	const USI_GameInstance* GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	if(!IsValid(GameInstance) || !CharacterState) {return nullptr;}

	const USI_CaseManager* CaseManager = GameInstance->GetSubsystem<USI_CaseManager>();
	if(!IsValid(CaseManager)) {return nullptr;}

	if(HasCharacterStateForCase(CaseManager->GetActiveCaseTag()))
	{
		return CharacterState->GetDialogueStateByCaseTag(CaseManager->GetActiveCaseTag());
	}

	return &CharacterState->DefaultDialogueState;
}

FSI_DialogueState* ASI_NPC::GetActiveDialogueState()
{
	const USI_GameInstance* GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	if(!IsValid(GameInstance) || !CharacterState) {return nullptr;}

	const USI_CaseManager* CaseManager = GameInstance->GetSubsystem<USI_CaseManager>();
	if(!IsValid(CaseManager)) {return nullptr;}

	if(HasCharacterStateForCase(CaseManager->GetActiveCaseTag()))
	{
		return CharacterState->GetDialogueStateByCaseTag(CaseManager->GetActiveCaseTag());
	}

	return &CharacterState->DefaultDialogueState;
}
