
#include "Dialogue/DialogueSessionNode.h"
#include "Dialogue/DialogueSession.h"
#include "Data/Characters/AoS_CharacterData.h"

#define LOCTEXT_NAMESPACE "DialogueSessionNode"

#define NUM_CHARS_SHOWN 15

UDialogueSessionNode::UDialogueSessionNode()
{
#if WITH_EDITORONLY_DATA
    CompatibleGraphType = UDialogueSession::StaticClass();

    ContextMenuName = LOCTEXT("ConextMenuName", "Dialogue Session Node");
#endif

}

UDialogueSessionNode::~UDialogueSessionNode()
{
}

#if WITH_EDITOR

FText UDialogueSessionNode::GetNodeTitle() const
{
    // TO DO: Change to display only first 10 (or so) letters of dialogue
    return Dialogue.IsEmpty() ? LOCTEXT("", "") : FText::FromString(Dialogue.ToString().Mid(0, NUM_CHARS_SHOWN));
}

void UDialogueSessionNode::SetNodeTitle(const FText& NewTitle)
{
    Dialogue = NewTitle;
}
#endif

#undef LOCTEXT_NAMESPACE