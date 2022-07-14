// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_CaseManager.generated.h"

class UAoS_Case;
class UAoS_Part;
class UAoS_Objective;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseAccepted, UAoS_Case*, AcceptedCase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveComplete, UAoS_Objective*, CompletedObjective);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPartComplete, UAoS_Part*, CompletedPart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseComplete, UAoS_Case*, CompletedCase);

UCLASS()
class AOS_PROTOTYPE_API UAoS_CaseManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UAoS_CaseManager();

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveComplete OnObjectiveComplete;
	UPROPERTY(BlueprintAssignable)
	FOnPartComplete OnPartComplete;
	UPROPERTY(BlueprintAssignable)
	FOnCaseComplete OnCaseComplete;
	UPROPERTY(BlueprintAssignable)
	FOnCaseAccepted OnCaseAccepted;

	UFUNCTION(BlueprintCallable)
	void AcceptCase(UAoS_Case* CaseToAccept);
	UFUNCTION(BlueprintCallable)
	void SetActiveCase(UAoS_Case* CaseToSet);
	UFUNCTION(BlueprintCallable)
	void CompleteObjective(UAoS_Objective* ObjectiveToComplete);


	UFUNCTION(BlueprintPure)
	UAoS_Case* GetActiveCase() const;
	UFUNCTION(BlueprintPure)
	TArray<UAoS_Case*> GetAcceptedCases() const;
	UFUNCTION(BlueprintPure)
	UAoS_Part* GetActivePart() const;
	UFUNCTION(BlueprintPure)
	TArray<UAoS_Objective*> GetActiveObjectives() const;
	
private:

	UPROPERTY()
	UAoS_Case* ActiveCase;
	UPROPERTY()
	TArray<UAoS_Case*> AcceptedCases;

	void ObjectiveCompleted(UAoS_Objective* CompletedObjective);
	void PartCompleted(UAoS_Part* CompletedPart);
	void CaseCompleted(UAoS_Case* CompletedCase);
	
	bool CheckForCompletedPart();
	bool CheckForCompletedCase();
};
