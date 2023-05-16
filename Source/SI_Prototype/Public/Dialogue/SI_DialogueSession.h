
#pragma once

#include "CoreMinimal.h"
#include "GenericGraph.h"
#include "SI_DialogueSessionEdge.h"
#include "SI_DialogueSession.generated.h"

class USI_CharacterData;
class UDialogueSessionNode;
class UDialogueSessionEdge;
class USI_DialogueManager;
class USI_CaseManager;

UCLASS(Blueprintable)
class SI_PROTOTYPE_API UDialogueSession : public UGenericGraph
{
    GENERATED_BODY()

public:
    UDialogueSession();

    UPROPERTY(EditDefaultsOnly, Category = "DialogueType")
    bool bIsInterrogationDialogue = true;
    

    // --- FUNCTIONS TO CALL FOR CHANGING DIALOGUE STATE --- //
    // UObject should be replaced by the type of selectable objects later on
    void SelectEdgeOfType(EEdgeType Type, UObject* ItemToCheck = nullptr, FText TextToCheck = FText());

    // Functions that determine which buttons should be displayed
    bool HasEdgeOfType(EEdgeType Type);

    // --- FUNCTIONS TO BEGIN OR RESET DIALOGUE --- //

    // If SavedNode of CharacterData is not null, just sets CurrentNode equal to it
    // Otherwise, it searches for the default starting node
    void StartDialogue(USI_CharacterData* InCharacterData, USI_DialogueManager* InDialogueManager, USI_CaseManager* InCaseManager);

    // Sets CurrentNode and NodeToSave to the default start node
    // Sets CurrentAngerLevel = 0
    void ResetDialogue();

    
    // --- FUNCTIONS TO CALL FROM UI --- //

    // Functions that determine what text should be displayed
    UFUNCTION(BlueprintCallable)
    FText GetName() const;
    UFUNCTION(BlueprintCallable)
    FText GetText() const;

    // Should update CharacterData
    // Only time that CharacterData gets updated
    void ExitDialogue();


private:

    USI_DialogueManager* DialogueManagerRef;

    UDialogueSessionNode* CurrentNode;
    // Info to save
    UDialogueSessionNode* NodeToSave;
    int32 CurrentAngerLevel = 0;

    FText CharacterDisplayName;
    
    // Used every time that CurrentNode is update to check whether there is a new saved node
    void UpdateCurrentNode(UDialogueSessionNode* NewNode);
    // Used to make sure the current node is valid; otherwise, relevant errors are printed
    bool CheckCurrentNode(FString ErrorText);
    void PrintErrorText(FString ErrorText, bool bShouldExit);

    // Returns an edge of the given type if there is exactly one such edge from CurrentNode
    // Otherwise, returns nullptr
    // NOTE: should not be called for TextOption or other types of edges that can have multiple edges eminating from the current node
    UDialogueSessionEdge* FindEdgeOfType(EEdgeType Type, bool bShouldExitForMultipleEdges);

    // Returns all edges of the given type
    // May be empty
    TArray<UDialogueSessionEdge*> FindAllEdgesOfType(EEdgeType Type);
};