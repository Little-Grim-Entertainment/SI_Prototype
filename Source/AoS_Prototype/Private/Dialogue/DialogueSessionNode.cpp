
#include "Dialogue/DialogueSessionNode.h"
#include "Dialogue/DialogueSession.h"

#define LOCTEXT_NAMESPACE "DialogueSessionNode"

UDialogueSessionNode::UDialogueSessionNode()
{
#if WITH_EDITORONLY_DATA
    CompatibleGraphType = UDialogueSession::StaticClass();

    ContextMenuName = LOCTEXT("ConextMenuName", "Dialogue Session Node");
#endif
}

#if WITH_EDITOR

FText UDialogueSessionNode::GetNodeTitle() const
{
    return Paragraph.IsEmpty() ? LOCTEXT("EmptyParagraph", "(Empty paragraph)") : Paragraph;
}

void UDialogueSessionNode::SetNodeTitle(const FText& NewTitle)
{
    Paragraph = NewTitle;
}

FLinearColor UDialogueSessionNode::GetBackgroundColor() const
{
    UDialogueSession* CurrGraph = Cast<UDialogueSession>(GetGraph());

    if (CurrGraph == nullptr)
        return Super::GetBackgroundColor();

    switch (DialoguerPostion)
    {
    case EDialoguerPostion::Left:
        return CurrGraph->LeftDialoguerBgColor;
    case EDialoguerPostion::Right:
        return CurrGraph->RightDialoguerBgColor;
    default:
        return FLinearColor::Black;
    }
}

#endif

#undef LOCTEXT_NAMESPACE