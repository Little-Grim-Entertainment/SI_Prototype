// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "SI_DialogueComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConversationEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInterrogationEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSpeaking, FString, CharacterCurrentlySpeaking);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogText, FString, CurrentDialogText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnMultiText, FString, OptionA, FString, OptionB, FString, OptionC, FString, OptionD);

USTRUCT(BlueprintType)
struct FSI_ConversationData : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Dialogue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Character;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Progression;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Answer_A;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString TagFor_A;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Answer_B;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString TagFor_B;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Answer_C;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString TagFor_C;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Answer_D;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString TagFor_D;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool TransitionOverride;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString IF_Dialog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString IF_A;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString IF_B;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString IF_C;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString IF_D;
};

USTRUCT(BlueprintType)
struct FSI_InterrogationData : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Dialogue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Character;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Line_Order;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool Allow_Scrutiny;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString If_Scrutiny_To;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool Allow_Evidence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Evidence_ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString If_Correct_To;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString If_Incorrect_To;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool TransitionOverride;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString OverrideTo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool PissedOf;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool AddProgression;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Override_Text_In;
};

UENUM(BlueprintType)
enum ESI_ConversationAnswerSelection
{
	DialogOnly,
	AnswerA,
	AnswerB,
	AnswerC,
	AnswerD,
	NoAnwser,
};

//TEMP EVIDENCE STRUCT (DELETE). For DEBUG
USTRUCT(BlueprintType)
struct FSI_TempEvidenceStruct
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Evidence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString EvidenceID;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SI_PROTOTYPE_API USI_DialogueComponent : public UActorComponent
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = "Data")
		class UDataTable* ConversationData;
	UPROPERTY(EditAnywhere, Category = "Data")
		class UDataTable* InterrogationData;

public:
	// Sets default values for this component's properties
	USI_DialogueComponent();

	UPROPERTY(BlueprintAssignable, Category = "Overlap")
		FOnConversationEnd OnConversationEnd;
	UPROPERTY(BlueprintAssignable, Category = "Overlap")
		FOnInterrogationEnd OnInterrogationEnd;
	UPROPERTY(BlueprintAssignable, Category = "Conversation")
		FOnCharacterSpeaking OnCharacterSpeakingChange;
	UPROPERTY(BlueprintAssignable, Category = "Dialog")
		FOnDialogText OnDialogDisplayed;
	UPROPERTY(BlueprintAssignable, Category = "Dialog")
		FOnMultiText OnMultiChoiceDisplayed;

protected:

	ESI_ConversationAnswerSelection PlayerAnswer;

	FName RowNameToSearch;

	bool bRunConversation = true;
	bool bSkipAnswerSelection = true;
	bool bNPC_Talking = true;

	bool bHasSelectedEvidence = false;

	//Start interrogation
	bool bStartInterrogation = false;

	FString PlayerAnswerChoice;

	int32 ConversationCount = 0;
	int32 InterrogationCount = 0;

	//Logs which position of main tree are we in
	int32 InterrogationMainTreeLocation = 0;

	//Registers Interrogation Text to toggle through it
	TArray< FSI_InterrogationData*> InterrogationRegister;

	FString PlayerProgression;
	FString InterrogationProgression;

	int8 AnnoyanceMeter = 0;

	//This is Temp for Debug
	UPROPERTY(EditAnywhere)
		TArray<FSI_TempEvidenceStruct> TempEvidence;

	//Annoyance Rate
	UPROPERTY(EditAnywhere, Category = "Annoyace Meter")
		int32 AnnoyanceAmountPerMiss = 10.f;
	UPROPERTY(EditAnywhere, Category = "Annoyace Meter")
		int32 MaxAmountAnnoyanceAllowed = 40.f;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Bind to key when player overlaps actor
	UFUNCTION(BlueprintCallable)
		void StartConversation();
	UFUNCTION(BlueprintCallable)
		void PlayConversation();
	UFUNCTION(BlueprintCallable)
		void StartInterrogation();
	UFUNCTION(BlueprintCallable)
		void PlayInterrogation();

	void DebugSimpleConversationLines(FSI_ConversationData* Conversation_Row, FString LocalDialog);

	void DebugMultiConversationLines(FString LocalDialog, FString LocalTagA, FString LocalTagB, FString LocalTagC, FString LocalTagD);

	void DebugMultiConversationPlayerAnswers(FSI_ConversationData* Conversation_Row);

	void SetConversationMultipleAnswerTags(FSI_ConversationData* Conversation_Row, FString* LocalTagA, FString* LocalTagB, FString* LocalTagC, FString* LocalTagD);

	void GetNewSimpleConversationLine(FSI_ConversationData* Conversation_Row);

	void GetNewMultiConversationLine(FSI_ConversationData* Conversation_Row);

	void GetMultiConversationPlayerInput();

	void GetFirstConversationLine();

	void EndConversation();

	void DebugInterrogationLinesNoEvidence(FSI_InterrogationData* Interrogation_Row, FString LocalDialog);

	void DebugInterrogationLinesWithEvidence(FSI_InterrogationData* Interrogation_Row, FString LocalDialog);

	void AddInterrogationProgression(FSI_InterrogationData* Interrogation_Row);

	void GetInterrogationLineWithEvidence(FSI_InterrogationData* Interrogation_Row);

	void GetNewInterrogationLine(FSI_InterrogationData* Interrogation_Row);

	void GetFirstInterrogationLine();

	void StartInterrogationNewLoop();

	void EndInterrogation();

	void AddInterrogationIrritation(FSI_InterrogationData* Interrogation_Row);

	void UpdateInterrogationRegister(FSI_InterrogationData* Interrogation_Row);

	void DecodePlayerEvidenceAnswer(FString PlayerChoice);

	UFUNCTION(BlueprintCallable)
		void SetPlayerAnswer(FString Answer);
	UFUNCTION(BlueprintCallable)
		void SetInterrogation(bool Start);


};
