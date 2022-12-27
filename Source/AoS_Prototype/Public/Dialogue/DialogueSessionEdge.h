
#pragma once

#include "CoreMinimal.h"
#include "GenericGraphEdge.h"
#include "DialogueSessionEdge.generated.h"


// --- WARNING --- //
// MAY BREAK CURRENT DIALOGUE SESSIONS IN UPROJECT IF THIS IS MODIFIED!!

// TO DO: Add UpdatePart (with delegate) and GetAlternateDialogue
UENUM(BlueprintType)
enum class EEdgeType : uint8
{
    Next,
    Previous,
    Press,
    TextOption,
    ItemOption,
    SetNewStartNode,
    AngerIncrease,
    ChooseAlternateDialogue, // sets a bool in the dialogue session node to use the alternate dialogue instead
    UpdatePart // for updating the part of the case, should send this info to the case manager to deal with
};


UCLASS(Blueprintable)
class UDialogueSessionEdge : public UGenericGraphEdge
{
    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialogueSession")
    EEdgeType TypeOfEdge;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TextOptions")
    FText SelectionText;

private:

    // UObject should be replaced by the type of selectable objects later on
    UPROPERTY(EditDefaultsOnly, Category = "ItemOptions")
    UObject* ItemToCheck;
};