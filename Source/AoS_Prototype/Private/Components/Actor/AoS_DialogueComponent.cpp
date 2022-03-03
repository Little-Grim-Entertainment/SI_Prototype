// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actor/AoS_DialogueComponent.h"

//DELETE THESE WHEN INTERACT WORKING
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UAoS_DialogueComponent::UAoS_DialogueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAoS_DialogueComponent::BeginPlay()
{
	Super::BeginPlay();



	//Have this when actor beginOverlap + press interact
	bRunConversation = true;
	bStartInterrogation = false;
	PlayerProgression = "1";
	InterrogationProgression = "1";

}
// Called every frame
void UAoS_DialogueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//THIS CONDITIONA TEMP UNTIL INTERACT KEY IS READY

	/*if (InterrogationData && bStartInterrogation)
	{
		StartInterrogation();
	}

	else if (ConversationData && bRunConversation)
	{
		if (!bRunConversation)
			bRunConversation = true;
		StartConversation();

	}*/


	//if (GetOwner() && !GetOwner()->EndOver))
	//{
	//	ConversationCount = 0;
	//	bRunConversation = false;
	//}


}

void UAoS_DialogueComponent::StartConversation()
{
	if (!ConversationData || !InterrogationData) { return; }
	if (ConversationCount < ConversationData->GetRowNames().Num())
	{
		//If ConversationCount == 0 then get first line
		GetFirstConversationLine();

		//if End is qued then end
		EndConversation();

		//PlayConversation
		PlayConversation();

	}
}

void UAoS_DialogueComponent::PlayConversation()
{
	if (ConversationData)
	{
		FString Local_Dialogue;
		FString Local_TagAnswerA;
		FString Local_TagAnswerB;
		FString Local_TagAnswerC;
		FString Local_TagAnswerD;

		static const FString ContextString(TEXT("ConversationDataContext"));
		FAOS_ConversationData* ConversationRow = ConversationData->FindRow<FAOS_ConversationData>(RowNameToSearch, ContextString, true);

		//Broadcast Current Character Speaking
		OnCharacterSpeakingChange.Broadcast(ConversationRow->Character);


		if (ConversationRow && ConversationRow->Character != "NickMulti")
		{

			//Setting Dialog Text
			Local_Dialogue = ConversationRow->Dialogue;

			//Broadcast Dialog for Display
			OnDialogDisplayed.Broadcast(Local_Dialogue);

			//Displaying Text (Debug)
			//DebugSimpleConversationLines(ConversationRow, Local_Dialogue);

			//Wait for Player Input
			SetComponentTickEnabled(false);

			//Get Next Line:
			GetNewSimpleConversationLine(ConversationRow);

			//Add Counter 
			ConversationCount++;

		}

		else if (ConversationRow && ConversationRow->Character == "NickMulti")
		{
			if (bNPC_Talking)
			{
				//Set Dialog and Answer Tags
				Local_Dialogue = ConversationRow->Dialogue;

				SetConversationMultipleAnswerTags(ConversationRow, &Local_TagAnswerA, &Local_TagAnswerB, &Local_TagAnswerC, &Local_TagAnswerD);

				//Broadcast Dialog for Display AND Multichoice
				OnDialogDisplayed.Broadcast(Local_Dialogue);
				OnMultiChoiceDisplayed.Broadcast(Local_TagAnswerA, Local_TagAnswerB, Local_TagAnswerC, Local_TagAnswerD);

				//Displaying Answer Option to Player
				//DebugMultiConversationLines(Local_Dialogue, Local_TagAnswerA, Local_TagAnswerB, Local_TagAnswerC, Local_TagAnswerD);

				//bNPC_Talking to keep conversation flowing
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindLambda([&] { bNPC_Talking = false; });
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.5f, false);

				//Pause Program
				SetComponentTickEnabled(false);
			}
			else
			{
				//Player Inputs his choice (if only one defaults to A)
				GetMultiConversationPlayerInput();

				//Display Player's Answer
				//DebugMultiConversationPlayerAnswers(ConversationRow);

				//Selecting New Dialog
				GetNewMultiConversationLine(ConversationRow);

				//Add Count
				ConversationCount++;


				FTimerDelegate TimerDelegate;
				TimerDelegate.BindLambda([&] { bNPC_Talking = true;});
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.5f, false);

				//Pause Program
				SetComponentTickEnabled(false);
			}
		}

		else if (!ConversationRow)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Conversation Not Found")));
			}
		}

	}


}

void UAoS_DialogueComponent::StartInterrogation()
{
	if (!ConversationData || !InterrogationData) { return; }
	if (InterrogationCount < InterrogationData->GetRowNames().Num())
	{
		//If InterrogationCount == 0 then get first line
		GetFirstInterrogationLine();

		//if End is qued then end
		EndInterrogation();

		//If starting loop get proper line
		StartInterrogationNewLoop();

		//Play Interrogation
		PlayInterrogation();
	}
}

void UAoS_DialogueComponent::PlayInterrogation()
{
	if (InterrogationData)
	{
		FString Local_Dialogue;

		static const FString ContextString(TEXT("InterrogationDataContext"));
		FAOS_InterrogationData* InterrogationRow = InterrogationData->FindRow<FAOS_InterrogationData>(RowNameToSearch, ContextString, true);

		//Broadcast Current Character Speaking
		OnCharacterSpeakingChange.Broadcast(InterrogationRow->Character);

		if (InterrogationRow && !InterrogationRow->Allow_Evidence && !InterrogationRow->Allow_Scrutiny && InterrogationRow->Line_Order < 1)
		{
			if (!bHasSelectedEvidence)
			{
				//Setting Dialog Text
				Local_Dialogue = InterrogationRow->Dialogue;

				//Broadcast Dialog for Display
				OnDialogDisplayed.Broadcast(Local_Dialogue);

				//Displaying Text (Debug)
				DebugInterrogationLinesNoEvidence(InterrogationRow, Local_Dialogue);

				//bSelectedEvidence to keep conversation flowing
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindLambda([&] {bHasSelectedEvidence = true;});
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.5f, false);

				//Wait for Player Input
				SetComponentTickEnabled(false);
			}
			else
			{
				//Get Next Line:
				GetNewInterrogationLine(InterrogationRow);

				//Check if pissed off 
				AddInterrogationIrritation(InterrogationRow);

				//Adds progression
				AddInterrogationProgression(InterrogationRow);

				//Add Counter 
				InterrogationCount++;

				//Keep Flow
				bHasSelectedEvidence = false;
			}	

		}
		else if (InterrogationRow && !InterrogationRow->Allow_Evidence && !InterrogationRow->Allow_Scrutiny && InterrogationRow->Line_Order > 0)
		{


			if (!bHasSelectedEvidence)
			{
				//Check if it belong to main tree and register it
				UpdateInterrogationRegister(InterrogationRow);

				//Setting Dialog Text
				Local_Dialogue = InterrogationRow->Dialogue;

				//Broadcast Dialog for Display
				OnDialogDisplayed.Broadcast(Local_Dialogue);

				//Displaying Text (Debug)
				DebugInterrogationLinesNoEvidence(InterrogationRow, Local_Dialogue);

				//bSelectedEvidence to keep conversation flowing
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindLambda([&] {bHasSelectedEvidence = true;});
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.5f, false);

				//Wait for Player Input
				SetComponentTickEnabled(false);
			}
			else
			{
				//Check for new line
				GetNewInterrogationLine(InterrogationRow);
	
				//Check if pissed off or Adds progression
				AddInterrogationIrritation(InterrogationRow);

				AddInterrogationProgression(InterrogationRow);

				//Add Counter
				InterrogationCount++;
					
				//bSelectedEvidence to keep conversation flowing
				bHasSelectedEvidence = false;

				/*
				* THIS CREATES A DELAY THAT DOES NOT WORK
				* LEFT HERE FOR REFERENCE
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindLambda([&] {bHasSelectedEvidence = false;});
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.5f, false);*/
			}


			
		}

		else if (InterrogationRow && InterrogationRow->Allow_Evidence && !InterrogationRow->Allow_Scrutiny)
		{
			if (!bHasSelectedEvidence)
			{
				//update if main tree
				UpdateInterrogationRegister(InterrogationRow);

				//Setting Dialog Text
				Local_Dialogue = InterrogationRow->Dialogue;

				//Broadcast Dialog for Display
				OnDialogDisplayed.Broadcast(Local_Dialogue);

				//Displaying Text (Debug)
				//DebugInterrogationLinesWithEvidence(InterrogationRow, Local_Dialogue);

				//bSelectedEvidence to keep conversation flowing
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindLambda([&] {bHasSelectedEvidence = true;});
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.5f, false);

				//Pause Program
				SetComponentTickEnabled(false);

			}
			else
			{
				//Make this decodification it's own function
				DecodePlayerEvidenceAnswer(PlayerAnswerChoice);

				//if selects a proper evidence
				//Checks if the array has a slot for selected player input
				if (TempEvidence.IsValidIndex(FCString::Atoi(*PlayerAnswerChoice) - 1) || PlayerAnswerChoice == "0")
				{
					GetInterrogationLineWithEvidence(InterrogationRow);
				}
				//Else or if presses 0 then do usual
				else
				{
					//Check if pissed off or Adds progression
					GetNewInterrogationLine(InterrogationRow);

				}

				//Check if pissed off or Adds progression
				AddInterrogationIrritation(InterrogationRow);

				AddInterrogationProgression(InterrogationRow);

				//Add Counter
				InterrogationCount++;

				//Reset Conversation Flow
				bHasSelectedEvidence = false;

			}
		}
		else if (InterrogationRow && !InterrogationRow->Allow_Evidence && InterrogationRow->Allow_Scrutiny)
		{

			if (!bHasSelectedEvidence)
			{

				//Check if it belong to main tree and register it
				UpdateInterrogationRegister(InterrogationRow);

				//Setting Dialog Text
				Local_Dialogue = InterrogationRow->Dialogue;

				//Broadcast Dialog for Display
				OnDialogDisplayed.Broadcast(Local_Dialogue);

				//Displaying Text (Debug)
				//DebugInterrogationLinesNoEvidence(InterrogationRow, Local_Dialogue);

				//bSelectedEvidence to keep conversation flowing
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindLambda([&] {bHasSelectedEvidence = true;});
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.5f, false);

				//Pause Program
				SetComponentTickEnabled(false);

			}
			else
			{
				//Get Next line, it includes Scruitny 
				GetNewInterrogationLine(InterrogationRow);

				//Check if pissed off or Adds progression
				AddInterrogationIrritation(InterrogationRow);

				AddInterrogationProgression(InterrogationRow);

				//Add Counter
				InterrogationCount++;

				bHasSelectedEvidence = false;

			}
		}
		else if (!InterrogationRow)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Interrogation Line Not Found")));
			}
		}




	}
}

void UAoS_DialogueComponent::DebugSimpleConversationLines(FAOS_ConversationData* Conversation_Row, FString LocalDialog)
{
	if (GEngine)
	{
		GEngine->ClearOnScreenDebugMessages();
		if (Conversation_Row->Character == "NPC")
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("%s: %s"), *GetOwner()->GetName(), *LocalDialog), false, FVector2D(3.f, 3.f));
		if (Conversation_Row->Character == "Nick")
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Nick: %s"), *LocalDialog), false, FVector2D(3.f, 3.f));
	}
}

void UAoS_DialogueComponent::DebugMultiConversationLines(FString LocalDialog, FString LocalTagA, FString LocalTagB, FString LocalTagC, FString LocalTagD)
{
	if (GEngine)
	{
		GEngine->ClearOnScreenDebugMessages();



		if (!bSkipAnswerSelection)
		{

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("%s: %s"), *GetOwner()->GetName(), *LocalDialog), false, FVector2D(3.f, 3.f));

			if (LocalTagA != "")
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Tag Answer A: %s"), *LocalTagA), false, FVector2D(3.f, 3.f));
			}

			if (LocalTagB != "")
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Tag Answer B: %s"), *LocalTagB), false, FVector2D(3.f, 3.f));
			}
			if (LocalTagC != "")
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Tag Answer C: %s"), *LocalTagC), false, FVector2D(3.f, 3.f));
			}
			if (LocalTagD != "")
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Tag Answer D: %s"), *LocalTagD), false, FVector2D(3.f, 3.f));
			}


		}


	}
}

void UAoS_DialogueComponent::DebugMultiConversationPlayerAnswers(FAOS_ConversationData* Conversation_Row)
{

	if (bSkipAnswerSelection)
	{
		FString Local_AnswerA = Conversation_Row->Answer_A;

		GEngine->ClearOnScreenDebugMessages();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Nick: %s"), *Local_AnswerA), false, FVector2D(3.f, 3.f));
	}

	else
	{
		FString Local_AnswerA;
		FString Local_AnswerB;
		FString Local_AnswerC;
		FString Local_AnswerD;

		GEngine->ClearOnScreenDebugMessages();
		switch (PlayerAnswer)
		{
		case AnswerA:
			Local_AnswerA = Conversation_Row->Answer_A;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Nick: %s"), *Local_AnswerA), false, FVector2D(3.f, 3.f));
			break;
		case AnswerB:
			Local_AnswerB = Conversation_Row->Answer_B;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Nick: %s"), *Local_AnswerB), false, FVector2D(3.f, 3.f));
			break;
		case AnswerC:
			Local_AnswerC = Conversation_Row->Answer_C;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Nick: %s"), *Local_AnswerC), false, FVector2D(3.f, 3.f));
			break;
		case AnswerD:
			Local_AnswerD = Conversation_Row->Answer_D;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Nick: %s"), *Local_AnswerD), false, FVector2D(3.f, 3.f));
			break;
		default:
			Local_AnswerA = Conversation_Row->Answer_A;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Nick: %s"), *Local_AnswerA), false, FVector2D(3.f, 3.f));
			break;
		}

	}
}

void UAoS_DialogueComponent::SetConversationMultipleAnswerTags(FAOS_ConversationData* Conversation_Row, FString* LocalTagA, FString* LocalTagB, FString* LocalTagC, FString* LocalTagD)
{
	if (Conversation_Row->TagFor_A != "")
	{
		*LocalTagA = Conversation_Row->TagFor_A;
		bSkipAnswerSelection = true;
	}

	if (Conversation_Row->TagFor_B != "")
	{
		*LocalTagB = Conversation_Row->TagFor_B;
		bSkipAnswerSelection = false;
	}

	if (Conversation_Row->TagFor_C != "")
	{
		*LocalTagC = Conversation_Row->TagFor_C;
		bSkipAnswerSelection = false;
	}

	if (Conversation_Row->TagFor_D != "")
	{
		*LocalTagD = Conversation_Row->TagFor_D;
		bSkipAnswerSelection = false;
	}
}

void UAoS_DialogueComponent::GetNewSimpleConversationLine(FAOS_ConversationData* Conversation_Row)
{

		if (Conversation_Row->TransitionOverride)
		{
			RowNameToSearch = FName(*Conversation_Row->IF_Dialog);
		}

		else
		{
			//Automatically based on this Line Number (Ex: Line01)
			FString NewRowName = RowNameToSearch.ToString();
			FString StringToInt = NewRowName;

			int32 n1 = FCString::Atoi(*StringToInt.RightChop(StringToInt.Len() - 1));
			StringToInt.RemoveAt(StringToInt.Len() - 1);
			int32 n2 = FCString::Atoi(*(StringToInt.RightChop(StringToInt.Len() - 1)));

			if (n1 < 9)
			{
				n1++;
			}
			else if (n1 >= 9)
			{
				n1 = 0;
				n2++;
			}

			//If this line is bigger than Array End Conversation
			int32 ControlNumber = n2 * 10 + n1;
			if (ControlNumber > ConversationData->GetRowNames().Num())
			{
				RowNameToSearch = FName("End");
				return;
			}

			NewRowName.RemoveAt(NewRowName.Len() - 1);
			NewRowName.RemoveAt(NewRowName.Len() - 1);
			NewRowName.AppendInt(n2);
			NewRowName.AppendInt(n1);
			RowNameToSearch = FName(*NewRowName);

		}
	

}

void UAoS_DialogueComponent::GetNewMultiConversationLine(FAOS_ConversationData* Conversation_Row)
{
	if (!Conversation_Row->TransitionOverride)
	{
		//Go to next line
		FString NewRowName = RowNameToSearch.ToString();
		FString StringToInt = NewRowName;

		int32 n1 = FCString::Atoi(*StringToInt.RightChop(StringToInt.Len() - 1));
		StringToInt.RemoveAt(StringToInt.Len() - 1);
		int32 n2 = FCString::Atoi(*(StringToInt.RightChop(StringToInt.Len() - 1)));

		if (n1 < 9)
		{
			n1++;
		}
		else if (n1 >= 9)
		{
			n1 = 0;
			n2++;
		}

		//If this line is bigger than Array End Conversation
		int32 ControlNumber = n2 * 10 + n1;
		if (ControlNumber > ConversationData->GetRowNames().Num())
		{
			RowNameToSearch = FName("End");
			return;
		}

		NewRowName.RemoveAt(NewRowName.Len() - 1);
		NewRowName.RemoveAt(NewRowName.Len() - 1);
		NewRowName.AppendInt(n2);
		NewRowName.AppendInt(n1);
		RowNameToSearch = FName(*NewRowName);

		//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s"), *RowNameToSearch.ToString()));
		//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s"), *FString::FromInt(n)));
	}

	else
	{
		//Go to line depending on IF_Dialog/A/B/C/D
		switch (PlayerAnswer)
		{
		case AnswerA:
			RowNameToSearch = FName(*Conversation_Row->IF_A);
			break;
		case AnswerB:
			RowNameToSearch = FName(*Conversation_Row->IF_B);
			break;
		case AnswerC:
			RowNameToSearch = FName(*Conversation_Row->IF_C);
			break;
		case AnswerD:
			RowNameToSearch = FName(*Conversation_Row->IF_D);
			break;
		default:
			RowNameToSearch = FName(*Conversation_Row->IF_A);
			break;
		}

	}
}

void UAoS_DialogueComponent::GetMultiConversationPlayerInput()
{
	if (!bSkipAnswerSelection)
	{
		PlayerAnswer = EAOS_ConversationAnswerSelection::AnswerA;

		if (PlayerAnswerChoice == "B")
		{
			PlayerAnswer = EAOS_ConversationAnswerSelection::AnswerB;
		}

		else if (PlayerAnswerChoice == "C")
		{
			PlayerAnswer = EAOS_ConversationAnswerSelection::AnswerC;
		}

		else if (PlayerAnswerChoice == "D")
		{
			PlayerAnswer = EAOS_ConversationAnswerSelection::AnswerD;
		}
	}

}

void UAoS_DialogueComponent::GetFirstConversationLine()
{
	if (ConversationCount == 0)
	{
		//Search of progression
		if (PlayerProgression != "")
		{
			TArray<FAOS_ConversationData*> TempArr;
			static const FString ContextString(TEXT("ConversationDataContext"));
			ConversationData->GetAllRows(ContextString, TempArr);

			for (int i = 0; i < TempArr.Num(); i++)
			{
				if (TempArr.IsValidIndex(i))
				{
					if (TempArr[i]->Progression == PlayerProgression)
					{

						if (i < 9)
						{
							FString NameToSearch = "Line0" + FString::FromInt(i + 1);
							RowNameToSearch = *NameToSearch;
						}
						else
						{
							FString NameToSearch = "Line" + FString::FromInt(i + 1);
							RowNameToSearch = *NameToSearch;
						}

					}
				}

			}
		}

		//If not found populate generic
		if (RowNameToSearch == "")
		{
			RowNameToSearch = TEXT("Line01");
		}


		//Search Player Progression to set this.
		//ConversationData;



	}
}

void UAoS_DialogueComponent::EndConversation()
{
	if (RowNameToSearch == "End")
	{
		ConversationCount = 0;
		bRunConversation = false;
		OnConversationEnd.Broadcast();
		//GEngine->ClearOnScreenDebugMessages();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Conversation Ended")), false, FVector2D(3.f, 3.f));
		return;
	}
}

void UAoS_DialogueComponent::DebugInterrogationLinesNoEvidence(FAOS_InterrogationData* Interrogation_Row, FString LocalDialog)
{
	if (GEngine)
	{
		GEngine->ClearOnScreenDebugMessages();
		if (Interrogation_Row->Character == "NPC")
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("%s: %s"), *GetOwner()->GetName(), *LocalDialog), false, FVector2D(2.f, 2.f));
		if (Interrogation_Row->Character == "Nick")
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Nick: %s"), *LocalDialog), false, FVector2D(2.f, 2.f));
	}
}

void UAoS_DialogueComponent::DebugInterrogationLinesWithEvidence(FAOS_InterrogationData* Interrogation_Row, FString LocalDialog)
{
	if (GEngine)
	{
		GEngine->ClearOnScreenDebugMessages();
		if (Interrogation_Row->Character == "NPC")
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("%s: %s"), *GetOwner()->GetName(), *LocalDialog), false, FVector2D(3.f, 3.f));
		if (Interrogation_Row->Character == "Nick")
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Nick: %s"), *LocalDialog), false, FVector2D(3.f, 3.f));

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("0.Don't Show Evidence")), false, FVector2D(3.f, 3.f));

		for (int i = 0; i < TempEvidence.Num(); i++)
		{
			if (TempEvidence.IsValidIndex(i))
			{
				FString Message = FString::Printf(TEXT("%s.Evidence: %s"), *FString::FromInt(i + 1), *TempEvidence[i].Evidence);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, Message, false, FVector2D(3.f, 3.f));
			}
		}
	}
}

void UAoS_DialogueComponent::AddInterrogationProgression(FAOS_InterrogationData* Interrogation_Row)
{
	if (Interrogation_Row->AddProgression)
	{
		int32 LocalPorgression = FCString::Atoi(*InterrogationProgression) + 1;
		InterrogationProgression = FString::FromInt(LocalPorgression);

		if (!Interrogation_Row->Override_Text_In.IsEmpty())
		{
			//Override TempInterrogationRow Dialog with InterrogationRow Dialog
			//This is a bit aggresive but may work. Needs test since it override the text from the Data Table
			static const FString TempContextString(TEXT("InterrogationDataContext"));
			FAOS_InterrogationData* TempInterrogationRow = InterrogationData->FindRow<FAOS_InterrogationData>(FName(Interrogation_Row->Override_Text_In), TempContextString, true);

			TempInterrogationRow->Dialogue = Interrogation_Row->Dialogue;
			TempInterrogationRow->Allow_Scrutiny = false;
		}
	}

	//Check if player has finished all clues
	TArray<FAOS_InterrogationData*> TempArr;
	static const FString TempContextString(TEXT("InterrogationDataContext"));
	InterrogationData->GetAllRows(TempContextString, TempArr);

	for (int i = 0; i < TempArr.Num(); i++)
	{
		if (TempArr.IsValidIndex(i) && TempArr[i]->Allow_Scrutiny)
		{
			return;
			break;
		}

	}
	//if no allow scrutiny left player has finished
	RowNameToSearch = "EndWithSucess";


}

void UAoS_DialogueComponent::GetInterrogationLineWithEvidence(FAOS_InterrogationData* Interrogation_Row)
{

	if (TempEvidence.IsValidIndex(FCString::Atoi(*PlayerAnswerChoice) - 1))
	{
		if (TempEvidence[FCString::Atoi(*PlayerAnswerChoice) - 1].EvidenceID == Interrogation_Row->Evidence_ID)
		{
			RowNameToSearch = FName(Interrogation_Row->If_Correct_To);
		}
		else
		{
			RowNameToSearch = FName(Interrogation_Row->If_Incorrect_To);
		}
	}
	else if (PlayerAnswerChoice == "0")
	{
		RowNameToSearch = FName(Interrogation_Row->If_Incorrect_To);
	}
}

void UAoS_DialogueComponent::GetNewInterrogationLine(FAOS_InterrogationData* Interrogation_Row)
{

	if (Interrogation_Row->Line_Order > 0 && PlayerAnswerChoice == "Backward")
	{
		//Check if the previous line actually exists
		//Location 2 would be in Arr[1] so that's why we substract -2
		if (InterrogationRegister.IsValidIndex(InterrogationMainTreeLocation - 2))
		{
			TArray<FAOS_InterrogationData*> TempArr;
			static const FString TempContextString(TEXT("InterrogationDataContext"));
			InterrogationData->GetAllRows(TempContextString, TempArr);

			for (int i = 0; i < TempArr.Num(); i++)
			{
				if (TempArr.IsValidIndex(i) && TempArr[i]->Line_Order == InterrogationMainTreeLocation - 1)
				{
					if (i < 9)
					{
						//Need to add +1 since index is -1
						FString NameToSearch = "Line0" + FString::FromInt(i + 1);
						RowNameToSearch = *NameToSearch;
					}
					else
					{
						FString NameToSearch = "Line" + FString::FromInt(i + 1);
						RowNameToSearch = *NameToSearch;
					}
					break;
				}
			}

			return;
		}
		else
		{
			//Check if the previous line actually exists
//Location 2 would be in Arr[1] so that's why we substract -2
			if (InterrogationRegister.IsValidIndex(InterrogationMainTreeLocation - 2))
			{
				TArray<FAOS_InterrogationData*> TempArr;
				static const FString TempContextString(TEXT("InterrogationDataContext"));
				InterrogationData->GetAllRows(TempContextString, TempArr);

				for (int i = 0; i < TempArr.Num(); i++)
				{
					if (TempArr.IsValidIndex(i) && TempArr[i]->Line_Order == InterrogationMainTreeLocation - 1)
					{
						if (i < 9)
						{
							//Need to add +1 since index is -1
							FString NameToSearch = "Line0" + FString::FromInt(i + 1);
							RowNameToSearch = *NameToSearch;
						}
						else
						{
							FString NameToSearch = "Line" + FString::FromInt(i + 1);
							RowNameToSearch = *NameToSearch;
						}
						break;
					}
				}

				return;
			}
			//If not valid then stay in the same line
			else
			{
				TArray<FAOS_InterrogationData*> TempArr;
				static const FString TempContextString(TEXT("InterrogationDataContext"));
				InterrogationData->GetAllRows(TempContextString, TempArr);

				for (int i = 0; i < TempArr.Num(); i++)
				{
					if (TempArr.IsValidIndex(i) && TempArr[i]->Line_Order == InterrogationMainTreeLocation)
					{
						if (i < 9)
						{
							//Need to add +1 since index is -1
							FString NameToSearch = "Line0" + FString::FromInt(i + 1);
							RowNameToSearch = *NameToSearch;
						}
						else
						{
							FString NameToSearch = "Line" + FString::FromInt(i + 1);
							RowNameToSearch = *NameToSearch;
						}
						break;
					}
				}

				return;
			}
		}
	}

	if (Interrogation_Row->Allow_Scrutiny && PlayerAnswerChoice == "Scrutiny")
	{
		RowNameToSearch = FName(*Interrogation_Row->If_Scrutiny_To);
		return;

	}

	else if (PlayerAnswerChoice == "Forward" && Interrogation_Row->TransitionOverride)
	{

		RowNameToSearch = FName(*Interrogation_Row->OverrideTo);
		return;

	}

	else if (PlayerAnswerChoice == "Forward" && !Interrogation_Row->TransitionOverride)
	{
		//Automatically based on this Line Number (Ex: Line01)
		FString NewRowName = RowNameToSearch.ToString();
		FString StringToInt = NewRowName;

		int32 n1 = FCString::Atoi(*StringToInt.RightChop(StringToInt.Len() - 1));
		StringToInt.RemoveAt(StringToInt.Len() - 1);
		int32 n2 = FCString::Atoi(*(StringToInt.RightChop(StringToInt.Len() - 1)));

		if (n1 < 9)
		{
			n1++;
		}
		else if (n1 >= 9)
		{
			n1 = 0;
			n2++;
		}

		//If this line is bigger than Array End Conversation
		int32 ControlNumber = n2 * 10 + n1;
		if (ControlNumber > InterrogationData->GetRowNames().Num())
		{
			RowNameToSearch = FName("End");
			return;
		}

		NewRowName.RemoveAt(NewRowName.Len() - 1);
		NewRowName.RemoveAt(NewRowName.Len() - 1);
		NewRowName.AppendInt(n2);
		NewRowName.AppendInt(n1);
		RowNameToSearch = FName(*NewRowName);

	}
	
}

void UAoS_DialogueComponent::GetFirstInterrogationLine()
{
	if (InterrogationCount == 0)
	{
		//Search for starting point
		TArray<FAOS_InterrogationData*> TempArr;
		static const FString ContextString(TEXT("InterrogationDataContext"));
		InterrogationData->GetAllRows(ContextString, TempArr);

		for (int i = 0; i < TempArr.Num(); i++)
		{
			if (TempArr.IsValidIndex(i))
			{
				if (i < 9)
				{
					//Need to add +1 since index is -1
					FString NameToSearch = "Line0" + FString::FromInt(i + 1);
					RowNameToSearch = *NameToSearch;
				}
				else
				{
					FString NameToSearch = "Line" + FString::FromInt(i + 1);
					RowNameToSearch = *NameToSearch;
				}
				break;
			}
		}

		//If not found populate generic
		if (RowNameToSearch == "")
		{

			RowNameToSearch = TEXT("Line01");
		}
	}
}

void UAoS_DialogueComponent::StartInterrogationNewLoop()
{
	if (RowNameToSearch == "Start")
	{
		TArray<FAOS_InterrogationData*> TempArr;
		static const FString ContextString(TEXT("InterrogationDataContext"));
		InterrogationData->GetAllRows(ContextString, TempArr);

		for (int i = 0; i < TempArr.Num(); i++)
		{

			if (TempArr.IsValidIndex(i))
			{
				if (i < 9)
				{
					FString NameToSearch = "Line0" + FString::FromInt(i + 1);
					RowNameToSearch = *NameToSearch;
				}
				else
				{
					FString NameToSearch = "Line" + FString::FromInt(i + 1);
					RowNameToSearch = *NameToSearch;
				}
				break;
			}
		}
	}
}

void UAoS_DialogueComponent::EndInterrogation()
{
	if (RowNameToSearch == "End")
	{

		ConversationCount = 0;
		bRunConversation = false;
		bStartInterrogation = false;
		OnInterrogationEnd.Broadcast();
		//GEngine->ClearOnScreenDebugMessages();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Interrogation Ended")), false, FVector2D(3.f, 3.f));
		return;
	}
	else if (RowNameToSearch == "EndWithSucess")
	{
		ConversationCount = 0;
		bRunConversation = false;
		bStartInterrogation = false;
		OnInterrogationEnd.Broadcast();
		//GEngine->ClearOnScreenDebugMessages();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Interrogation Ended Sucessfully")), false, FVector2D(3.f, 3.f));
		return;
	}
	else if (RowNameToSearch == "EndFatal")
	{
		ConversationCount = 0;
		bRunConversation = false;
		bStartInterrogation = false;
		OnInterrogationEnd.Broadcast();
		//GEngine->ClearOnScreenDebugMessages();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Interrogation Ended Fatally")), false, FVector2D(3.f, 3.f));
		return;
	}

}

void UAoS_DialogueComponent::AddInterrogationIrritation(FAOS_InterrogationData* Interrogation_Row)
{
	if (Interrogation_Row->PissedOf)
	{
		AnnoyanceMeter = AnnoyanceMeter + AnnoyanceAmountPerMiss;

		if (AnnoyanceMeter >= MaxAmountAnnoyanceAllowed)
		{
			InterrogationProgression = "-1";
			RowNameToSearch = "EndFatal";
		}
	}
}
void UAoS_DialogueComponent::UpdateInterrogationRegister(FAOS_InterrogationData* Interrogation_Row)
{
	if (!InterrogationRegister.IsValidIndex(Interrogation_Row->Line_Order - 1))
	{
		InterrogationRegister.Add(Interrogation_Row);
	}
	else
	{
		InterrogationRegister[Interrogation_Row->Line_Order - 1] = Interrogation_Row;
	}

	//Logs location in the main tree
	InterrogationMainTreeLocation = Interrogation_Row->Line_Order;

	//UE_LOG(LogTemp, Warning, TEXT("Inter Location: %s"), *FString::FromInt(InterrogationMainTreeLocation));
	
}

void UAoS_DialogueComponent::DecodePlayerEvidenceAnswer(FString PlayerChoice)
{

	if (PlayerChoice == "A")
	{
		PlayerAnswerChoice = "1";
	}
	else if (PlayerChoice == "B")
	{
		PlayerAnswerChoice = "2";
	}
	else if (PlayerChoice == "C")
	{
		PlayerAnswerChoice = "3";
	}
	else if (PlayerChoice == "D")
	{
		PlayerAnswerChoice = "4";
	}
	else
	{
		PlayerAnswerChoice = "0";
	}
}

void UAoS_DialogueComponent::SetPlayerAnswer(FString Answer)
{
	PlayerAnswerChoice = Answer;

	SetComponentTickEnabled(true);
}

void UAoS_DialogueComponent::SetInterrogation(bool Start)
{
	bStartInterrogation = Start;
	SetComponentTickEnabled(true);
}