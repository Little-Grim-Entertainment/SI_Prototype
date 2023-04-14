// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_GameInstanceSubsystem.h"
#include "AoS_CaseManager.generated.h"

class UAoS_CaseData;
class UAoS_PartData;
class UAoS_ObjectiveData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseAccepted, UAoS_CaseData*, AcceptedCase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseActivated, UAoS_CaseData*, ActivatedCase);
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

	UPROPERTY(BlueprintAssignable)
	FOnCaseAccepted OnCaseAccepted;
	UPROPERTY(BlueprintAssignable)
	FOnCaseActivated OnCaseActivated;
	UPROPERTY(BlueprintAssignable)
	FOnCaseComplete OnCaseComplete;

	UPROPERTY(BlueprintAssignable)
	FOnPartActivated OnPartActivated;
	UPROPERTY(BlueprintAssignable)
	FOnPartComplete OnPartComplete;
	
	UPROPERTY(BlueprintAssignable)
	FOnObjectiveActivated OnObjectiveActivated;	
	UPROPERTY(BlueprintAssignable)
	FOnObjectiveComplete OnObjectiveComplete;

	UPROPERTY(BlueprintAssignable)
	FOnCaseTitleCardComplete OnCaseTitleCardComplete;

	UFUNCTION(BlueprintCallable)
	void AcceptCase(UAoS_CaseData* CaseToAccept);
	UFUNCTION(BlueprintCallable)
	void SetActiveCase(UAoS_CaseData* CaseToSet);
	UFUNCTION(BlueprintCallable)
	void CompleteObjective(UAoS_ObjectiveData* ObjectiveToComplete);
	UFUNCTION(BlueprintCallable)
	void ResetAllCases();
	UFUNCTION(BlueprintCallable)
	void ResetCase(FString CaseToResetName);

	UFUNCTION(BlueprintPure)
	UAoS_CaseData* GetActiveCase() const;
	UFUNCTION(BlueprintPure)
	TArray<UAoS_CaseData*> GetAcceptedCases() const;
	UFUNCTION(BlueprintPure)
	TArray<UAoS_CaseData*> GetCompletedCases() const;
	UFUNCTION(BlueprintPure)
	UAoS_PartData* GetActivePart() const;
	UFUNCTION(BlueprintPure)
	TArray<UAoS_ObjectiveData*> GetActiveObjectives() const;

	void SetActivePart(UAoS_PartData* PartToSet);
	void SetActiveObjectives(TArray<UAoS_ObjectiveData*> ObjectivesToSet);

protected:

	virtual void OnGameInstanceInit() override;
	
private:

	UPROPERTY()
	UAoS_CaseData* ActiveCase;
	UPROPERTY()
	TArray<UAoS_CaseData*> AcceptedCases;
	UPROPERTY()
	TArray<UAoS_CaseData*> CompletedCases;
	

	
	void ObjectiveCompleted(UAoS_ObjectiveData* CompletedObjective);
	void PartCompleted(UAoS_PartData* CompletedPart);
	void CaseCompleted(UAoS_CaseData* CompletedCase);
	void SkipVideoRequested();
	void SkipVideoCanceled();
	void SkipVideoComplete(); 

	
	bool CheckForCompletedPart();
	bool CheckForCompletedCase();
};
