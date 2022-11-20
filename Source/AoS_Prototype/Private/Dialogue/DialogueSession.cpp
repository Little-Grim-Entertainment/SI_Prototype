
#include "Dialogue/DialogueSession.h"
#include "Dialogue/DialogueSessionNode.h"
#include "Dialogue/DialogueSessionEdge.h"

#define LOCTEXT_NAMESPACE "DialogueSession"

UDialogueSession::UDialogueSession()
{
    NodeType = UDialogueSessionNode::StaticClass();
    EdgeType = UDialogueSessionEdge::StaticClass();

    LeftDialoguerBgColor = FLinearColor::Black;
    RightDialoguerBgColor = FLinearColor(0.93f, 0.93f, 0.93f, 1.f);

    Name = "DialogueSession";
}

#undef LOCTEXT_NAMESPACE