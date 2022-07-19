// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_Case.generated.h"


class UAoS_Part;
class AAoS_Character;

UCLASS(BlueprintType)
class AOS_PROTOTYPE_API UAoS_Case : public UDataAsset
{
	GENERATED_BODY()

public:

	UAoS_Case();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CaseDetails")
	FText CaseName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CaseDetails")
	TArray<UAoS_Part*> Parts;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CaseDetails")
	TArray<TSubclassOf<AAoS_Character>> PeopleOfInterest;

	UFUNCTION(BlueprintPure)
	bool GetCaseIsComplete() const {return bIsComplete;}
	UFUNCTION(BlueprintPure)
	UAoS_Part* GetActivePart() const;
	UFUNCTION(BlueprintPure)
	TArray<UAoS_Part*> GetAllParts() const {return Parts;}

	void ResetCase();	
	void SetCaseComplete(bool bCaseCompleted);
	void SetCaseIsActive(bool bCaseIsActive);
	void ActivatePart();
	void DeactivatePart();
	
private:

	bool bIsActive;
	bool bIsComplete;
	
};
