
#include "Dialogue/DialogueSession.h"
#include "Dialogue/DialogueSessionNode.h"
#include "Dialogue/DialogueSessionEdge.h"
#include "Dialogue/AoS_DialogueManager.h"
#include "Data/Characters/AoS_CharacterData.h"

#define LOCTEXT_NAMESPACE "DialogueSession"

#define MAX_ANGER 3
#define NICK_DISPLAY_NAME TEXT("Nick Spade")

UDialogueSession::UDialogueSession()
{
    NodeType = UDialogueSessionNode::StaticClass();
    EdgeType = UDialogueSessionEdge::StaticClass();

    Name = "DialogueSession";

#if WITH_EDITORONLY_DATA
    bCanBeCyclical = true;
#endif
}

void UDialogueSession::StartDialogue(FText CharacterName, UDialogueSessionNode* SaveNode, int32 StartingAnger)
{
    if (GetWorld())
    {
        DialogueManagerRef = GetWorld()->GetSubsystem<UAoS_DialogueManager>();
        if (!DialogueManagerRef)
        {
            UE_LOG(LogTemp, Error, TEXT("Can't find reference to the DialogueManager."));
        }
    }

    CharacterDisplayName = CharacterName;

    // if a node is saved in CurrentDialogueData, then start with the saved info
    if (SaveNode)
    {
        CurrentNode = SaveNode;
        NodeToSave = SaveNode;
        CurrentAngerLevel = StartingAnger;
    }
    else
    {
        ResetDialogue();
    }
}

void UDialogueSession::ResetDialogue()
{
    CurrentNode = nullptr;
    NodeToSave = nullptr;
    CurrentAngerLevel = 0;

    // Search for starting node
    for (auto& NodeToCheck : AllNodes)
    {
        UDialogueSessionNode* TempNode = Cast<UDialogueSessionNode>(NodeToCheck);
        if (TempNode && TempNode->bIsDefaultStartingNode)
        {
            if (CurrentNode)
            {
                UE_LOG(LogTemp, Error, TEXT("Multiple default starting nodes set for dialogue %s. Dialogue will not start."), *Name);
                CurrentNode = nullptr;
                NodeToSave = nullptr;
                return;
            }
            else
            {
                CurrentNode = TempNode;
                NodeToSave = TempNode;
            }
        }
    }

    if (!CurrentNode)
    {
        UE_LOG(LogTemp, Error, TEXT("No default starting node set in dialogue %s. Dialogue will not start."), *Name);
    }
}

void UDialogueSession::ExitDialogue()
{
    if (!DialogueManagerRef)
    {
        UE_LOG(LogTemp, Error, TEXT("No reference to DialogueManager found in dialogue %s, will be unable to save progress."), *Name);
    }
    else
    {
        DialogueManagerRef->ExitDialogue(NodeToSave, CurrentAngerLevel);
    }

    CurrentNode = nullptr;
    NodeToSave = nullptr;
}

// As of now (11/26/22), this only updates the current node in the graph; doesn't change text anywhere
void UDialogueSession::SelectEdgeOfType(EEdgeType Type, UObject* ItemToCheck)
{
    if (!CheckCurrentNode(TEXT("CurrentNode not set in dialogue!")))
    {
        return;
    }

    UDialogueSessionEdge* NewEdge = FindEdgeOfType(Type, true);

    if (!NewEdge)
    {
        PrintErrorText(TEXT("No such edge found in dialogue graph."), true);
        return;
    }

    if (Type == EEdgeType::AngerIncrease)
    {
        CurrentAngerLevel++;
    }

    if (CurrentAngerLevel < MAX_ANGER)
    {
        UpdateCurrentNode(Cast<UDialogueSessionNode>(NewEdge->EndNode));
    }
    else
    {
        // deal with anger reaching max

    }
}

// Sets CurrentNode to the new node and checks if there should vbe 
void UDialogueSession::UpdateCurrentNode(UDialogueSessionNode* NewNode)
{
    CurrentNode = NewNode;
    if (!CheckCurrentNode(TEXT("Next node in the dialogue graph unable to be converted to type UDialogueSessionNode.")))
    {
        return;
    }

    UDialogueSessionEdge* SaveEdge = FindEdgeOfType(EEdgeType::SetNewStartNode, true);

    if (SaveEdge && Cast<UDialogueSessionNode>(SaveEdge->EndNode))
    {
        NodeToSave = Cast<UDialogueSessionNode>(SaveEdge->EndNode);
    }
}

FText UDialogueSession::GetName() const
{
    if (!CurrentNode)
    {
        return FText();
    }
    return CurrentNode->bIsNickSpeaking ? FText::FromString(FString(NICK_DISPLAY_NAME)) : CharacterDisplayName;
}

FText UDialogueSession::GetText() const
{
    return CurrentNode ? CurrentNode->GetDialogueText() : FText();
}

bool UDialogueSession::HasEdgeOfType(EEdgeType Type)
{
    return (FindEdgeOfType(Type, false) != nullptr);
}

// returns CurrentNode != nullptr
bool UDialogueSession::CheckCurrentNode(FString ErrorText)
{
    if (!CurrentNode)
    {
        PrintErrorText(ErrorText, true);
        return false;
    }
    return true;
}

void UDialogueSession::PrintErrorText(FString ErrorText, bool bShouldExit)
{
    UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorText);
    if (bShouldExit)
    {
        ExitDialogue();
    }
}

UDialogueSessionEdge* UDialogueSession::FindEdgeOfType(EEdgeType Type, bool bShouldExitForMultipleEdges)
{
    // Search for edges indicating new save location
    UDialogueSessionEdge* CurrEdge;
    UDialogueSessionEdge* NewEdge = nullptr;
    for (auto& ChildNode : CurrentNode->ChildrenNodes)
    {
        CurrEdge = Cast<UDialogueSessionEdge>(CurrentNode->Edges[ChildNode]);
        if (CurrEdge && CurrEdge->TypeOfEdge == Type)
        {
            if (NewEdge)
            {
                PrintErrorText(TEXT("Multiple edges of same type given in dialogue. Cannot determine new node."), bShouldExitForMultipleEdges);
                break;
            }
            NewEdge = CurrEdge;
        }
    }

    return NewEdge;
}

TArray<UDialogueSessionEdge*> UDialogueSession::FindAllEdgesOfType(EEdgeType Type)
{
    return TArray<UDialogueSessionEdge*>();
}

#undef LOCTEXT_NAMESPACE