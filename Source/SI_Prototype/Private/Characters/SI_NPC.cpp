// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_NPC.h"
#include "LG_DebugMacros.h"
#include "SI_GameInstance.h"
#include "Characters/SI_CharacterManager.h"
#include "Components/StateTreeComponent.h"
#include "Characters/Data/SI_CharacterData.h"
#include "LGBlueprintFunctionLibrary.h"
#include "SI_Prototype/SI_Prototype.h"
#include "Dialogue/SI_DialogueTypes.h"
#include "Cases/SI_CaseManager.h"
#include "Cases/Data/SI_PartData.h"
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

FSI_CharacterState* ASI_NPC::GetCharacterState()
{
	return CharacterState;
}

void ASI_NPC::BeginPlay()
{
	Super::BeginPlay();

	//StateTreeComponent->StartLogic();

	InitializeCharacterState();
}

void ASI_NPC::InitializeCharacterState()
{
	const UWorld* World = GetWorld();
	const USI_GameInstance* GameInstance = Cast<USI_GameInstance>(GetGameInstance());

	if(!IsValid(World) || !IsValid(GameInstance) || !IsValid(CharacterData)) {return;}

	USI_CharacterManager* CharacterManager = World->GetSubsystem<USI_CharacterManager>();
	if(!IsValid(CharacterManager) || !CharacterManager->IsActiveCharacter(CharacterData)) {return;}

	CharacterState = CharacterManager->GetCharacterStateByTag(CharacterData->CharacterTag);
	if(!CharacterState) {return;}

	USI_CaseManager* CaseManager = GameInstance->GetSubsystem<USI_CaseManager>();
	if(!IsValid(CaseManager)) {return;}

	USI_CaseData* CurrentCase = CaseManager->GetActiveCase();
	if(!IsValid(CurrentCase)) {return;}

	const FSI_CharacterCaseState* CaseState = CharacterState->GetCaseStateByTag(CurrentCase->CaseTag);
	if(!CaseState)
	{
		CaseState = CharacterState->AddNewCaseState(CurrentCase);
		if(!CaseState)
		{
			return;
		}
	}
	
	const FSI_DialogueState* DialogueState = CharacterState->GetDialogueStateByCaseTag(CurrentCase->CaseTag);
	if(!DialogueState)
	{
		const USI_DialogueManager* DialogueManager = World->GetSubsystem<USI_DialogueManager>();
		if(!IsValid(DialogueManager)) {return;}

		const FString CaseName = ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(CurrentCase->CaseTag);
		const FString DialogueLabel = CaseName + "_" + "P" + CaseManager->GetActivePart()->PartName.ToString();

		/*FSI_PrimaryDialogueArray* PrimaryDialogueArray = CharacterData->CharacterDialogue->GetDialogueArrayStructByCaseAndLabel<FSI_PrimaryDialogueArray>(CurrentCase->CaseTag, DialogueLabel);
		FSI_DialogueState* NewDialogueState = new FSI_DialogueState(PrimaryDialogueArray);

		CharacterState->AddNewDialogueState(CurrentCase->CaseTag, NewDialogueState);*/
	}
}
