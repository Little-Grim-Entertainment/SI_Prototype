// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_CaseManager.generated.h"

class UAoS_GameInstance;
class UAoS_Case;
class UAoS_Part;
class UAoS_Objective;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseAccepted, UAoS_Case*, AcceptedCase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseActivated, UAoS_Case*, ActivatedCase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseComplete, UAoS_Case*, CompletedCase);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPartActivated, UAoS_Part*, ActivatedPart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPartComplete, UAoS_Part*, CompletedPart);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveActivated, UAoS_Objective*, ActivatedObjective);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveComplete, UAoS_Objective*, CompletedObjective);

UCLASS()
class AOS_PROTOTYPE_API UAoS_CaseManager : public UGameInstanceSubsystem
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

	UFUNCTION(BlueprintCallable)
	void AcceptCase(UAoS_Case* CaseToAccept);
	UFUNCTION(BlueprintCallable)
	void SetActiveCase(UAoS_Case* CaseToSet);
	UFUNCTION(BlueprintCallable)
	void CompleteObjective(UAoS_Objective* ObjectiveToComplete);
	UFUNCTION(BlueprintCallable)
	void ResetAllCases();
	UFUNCTION(BlueprintCallable)
	void ResetCase(FString CaseToResetName);
	

	UFUNCTION(BlueprintPure)
	UAoS_Case* GetActiveCase() const;
	UFUNCTION(BlueprintPure)
	TArray<UAoS_Case*> GetAcceptedCases() const;
	UFUNCTION(BlueprintPure)
	TArray<UAoS_Case*> GetCompletedCases() const;
	UFUNCTION(BlueprintPure)
	UAoS_Part* GetActivePart() const;
	UFUNCTION(BlueprintPure)
	TArray<UAoS_Objective*> GetActiveObjectives() const;

	void SetActivePart(UAoS_Part* PartToSet);
	void SetActiveObjectives(TArray<UAoS_Objective*> ObjectivesToSet);
	
private:


	UPROPERTY()
	UWorld* World;
	UPROPERTY()
	UAoS_GameInstance* GameInstance;
	UPROPERTY()
	UAoS_Case* ActiveCase;
	UPROPERTY()
	TArray<UAoS_Case*> AcceptedCases;
	UPROPERTY()
	TArray<UAoS_Case*> CompletedCases;
	
	UPROPERTY()
	UAoS_Part* ActivePart;

	UPROPERTY()
	TArray<UAoS_Objective*> ActiveObjectives;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void ObjectiveCompleted(UAoS_Objective* CompletedObjective);
	void PartCompleted(UAoS_Part* CompletedPart);
	void CaseCompleted(UAoS_Case* CompletedCase);

	
	bool CheckForCompletedPart();
	bool CheckForCompletedCase();
};