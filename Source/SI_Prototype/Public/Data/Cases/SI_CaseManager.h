// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SI_GameInstanceSubsystem.h"
#include "SI_Types.h"
#include "SI_CaseManager.generated.h"

class USI_CaseData;
class USI_PartData;
class USI_ObjectiveData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseAccepted, USI_CaseData*, AcceptedCase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseActivated, USI_CaseData*, ActivatedCase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseDeactivated, USI_CaseData*, DeactivatedCase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseComplete, USI_CaseData*, CompletedCase);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPartActivated, USI_PartData*, ActivatedPart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPartComplete, USI_PartData*, CompletedPart);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveActivated, USI_ObjectiveData*, ActivatedObjective);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveComplete, USI_ObjectiveData*, CompletedObjective);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCaseTitleCardComplete);

// This system is responsible for handling the receiving, completing, and updating of cases

DECLARE_LOG_CATEGORY_EXTERN(LogSI_CaseManager, Log, All);

UCLASS()
class SI_PROTOTYPE_API USI_CaseManager : public USI_GameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USI_CaseManager();

	UFUNCTION(BlueprintCallable)
	void AcceptCase(USI_CaseData* CaseToAccept);
	UFUNCTION(BlueprintCallable)
	void SetActiveCase(USI_CaseData* CaseToSet);
	UFUNCTION(BlueprintCallable)
	void DeactivateCase(USI_CaseData* CaseToDeactivate);
	UFUNCTION(BlueprintCallable)
	void ResetAllCases();
	UFUNCTION(BlueprintCallable)
	void ResetCase(USI_CaseData* CaseToReset);
	
	UFUNCTION(BlueprintCallable)
	void CompleteObjective(USI_ObjectiveData* ObjectiveToComplete);

	void AssignMedia();

	void PlayIntroMedia();

	UFUNCTION(BlueprintPure)
	USI_CaseData* GetActiveCase();
	UFUNCTION(BlueprintPure)
	USI_PartData* GetActivePart();
	UFUNCTION(BlueprintPure)
	TArray<USI_ObjectiveData*> GetActiveObjectives();
	
	UFUNCTION(BlueprintPure)
	USI_CaseData* GetCaseByName(const FString& InCaseName);
	UFUNCTION(BlueprintPure)
	TArray<USI_CaseData*> GetAcceptedCases();
	UFUNCTION(BlueprintPure)
	TArray<USI_CaseData*> GetCompletedCases();

	FSI_CaseDetails* GetCaseDetails(const USI_CaseData* InCaseData);
	
	FSI_PartDetails* GetPartDetails(const USI_PartData* InPartData);
	FSI_ObjectiveDetails* GetObjectiveDetails(const USI_ObjectiveData* InObjectiveData);

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

	TMap<USI_CaseData*, FSI_CaseDetails*> AllCases;
	
	UPROPERTY()
	USI_CaseData* ActiveCase;
	UPROPERTY()
	TArray<USI_CaseData*> AcceptedCases;
	UPROPERTY()
	TArray<USI_CaseData*> CompletedCases;

	void InitializeCases();
	void InitializeParts();
	void InitializeObjectives();

	bool CompleteCase(USI_CaseData* InCaseToComplete);
	
	void PostCaseActivated(const USI_CaseData* ActivatedCase);
	void PostCaseCompleted(USI_CaseData* CompletedCase);

	void ActivatePart();
	void PostPartActivated(const USI_PartData* ActivatedPart);
	bool CompletePart(USI_PartData* InPartToComplete);
	void PostPartCompleted(const USI_PartData* CompletedPart);

	void ActivateObjectives();
	void PostObjectiveCompleted(const USI_ObjectiveData* CompletedObjective);
	
	bool CheckForCompletedPart();
	bool CheckForCompletedCase();

	bool bCasesInitialized;
};
