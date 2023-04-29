// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_GameInstanceSubsystem.h"
#include "AoS_Types.h"
#include "AoS_CaseManager.generated.h"

class UAoS_CaseData;
class UAoS_PartData;
class UAoS_ObjectiveData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseAccepted, UAoS_CaseData*, AcceptedCase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseActivated, UAoS_CaseData*, ActivatedCase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseDeactivated, UAoS_CaseData*, DeactivatedCase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseComplete, UAoS_CaseData*, CompletedCase);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPartActivated, UAoS_PartData*, ActivatedPart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPartComplete, UAoS_PartData*, CompletedPart);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveActivated, UAoS_ObjectiveData*, ActivatedObjective);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveComplete, UAoS_ObjectiveData*, CompletedObjective);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCaseTitleCardComplete);

// This system is responsible for handling the receiving, completing, and updating of cases

UCLASS()
class AOS_PROTOTYPE_API UAoS_CaseManager : public UAoS_GameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UAoS_CaseManager();

	UFUNCTION(BlueprintCallable)
	void AcceptCase(UAoS_CaseData* CaseToAccept);
	UFUNCTION(BlueprintCallable)
	void SetActiveCase(UAoS_CaseData* CaseToSet);
	UFUNCTION(BlueprintCallable)
	void DeactivateCase(UAoS_CaseData* CaseToDeactivate);
	UFUNCTION(BlueprintCallable)
	void ResetAllCases();
	UFUNCTION(BlueprintCallable)
	void ResetCase(UAoS_CaseData* CaseToReset);
	
	UFUNCTION(BlueprintCallable)
	void CompleteObjective(UAoS_ObjectiveData* ObjectiveToComplete);

	UFUNCTION(BlueprintPure)
	FAoS_CaseDetails& GetCaseDetails(const UAoS_CaseData* InCaseData);
	UFUNCTION(BlueprintPure)
	UAoS_CaseData* GetActiveCase();
	UFUNCTION(BlueprintPure)
	UAoS_CaseData* GetCaseByName(const FString InCaseName);
	UFUNCTION(BlueprintPure)
	TArray<UAoS_CaseData*> GetAcceptedCases();
	UFUNCTION(BlueprintPure)
	TArray<UAoS_CaseData*> GetCompletedCases();

	UFUNCTION(BlueprintPure)
	FAoS_PartDetails& GetPartDetails(const UAoS_PartData* InPartData);
	UFUNCTION(BlueprintPure)
	UAoS_PartData* GetActivePart();

	UFUNCTION(BlueprintPure)
	FAoS_ObjectiveDetails& GetObjectiveDetails(const UAoS_ObjectiveData* InObjectiveData);
	UFUNCTION(BlueprintPure)
	TArray<UAoS_ObjectiveData*> GetActiveObjectives();

	FOnCaseAccepted& OnCaseAccepted();
	FOnCaseActivated& OnCaseActivated();
	FOnCaseDeactivated& OnCaseDeactivated();
	FOnCaseComplete& OnCaseComplete();

	FOnPartActivated& OnPartActivated();
	FOnPartComplete& OnPartComplete();
	
	FOnObjectiveActivated& OnObjectiveActivated();	
	FOnObjectiveComplete& OnObjectiveComplete();

	FOnCaseTitleCardComplete& OnCaseTitleCardComplete();

protected:

	virtual void OnGameModeBeginPlay() override;
	
private:

	FOnCaseAccepted OnCaseAcceptedDelegate;
	FOnCaseActivated OnCaseActivatedDelegate;
	FOnCaseDeactivated OnCaseDeactivatedDelegate;
	FOnCaseComplete OnCaseCompleteDelegate;

	FOnPartActivated OnPartActivatedDelegate;
	FOnPartComplete OnPartCompleteDelegate;
	
	FOnObjectiveActivated OnObjectiveActivatedDelegate;	
	FOnObjectiveComplete OnObjectiveCompleteDelegate;

	FOnCaseTitleCardComplete OnCaseTitleCardCompleteDelegate;

	TMap<UAoS_CaseData*, FAoS_CaseDetails> AllCases;
	
	UPROPERTY()
	UAoS_CaseData* ActiveCase;
	UPROPERTY()
	TArray<UAoS_CaseData*> AcceptedCases;
	UPROPERTY()
	TArray<UAoS_CaseData*> CompletedCases;

	void InitializeCases();
	void InitializeParts();
	void InitializeObjectives();

	bool CompleteCase(UAoS_CaseData* InCaseToComplete);
	
	void PostCaseActivated(const UAoS_CaseData* ActivatedCase);
	void PostCaseCompleted(UAoS_CaseData* CompletedCase);

	void ActivatePart();
	void PostPartActivated(const UAoS_PartData* ActivatedPart);
	bool CompletePart(UAoS_PartData* InPartToComplete);
	void PostPartCompleted(const UAoS_PartData* CompletedPart);

	void ActivateObjectives();
	void AssignObjectiveMedia(UAoS_LevelManager* InLevelManager);
	void PostObjectiveCompleted(const UAoS_ObjectiveData* CompletedObjective);
	
	bool CheckForCompletedPart();
	bool CheckForCompletedCase();
};
