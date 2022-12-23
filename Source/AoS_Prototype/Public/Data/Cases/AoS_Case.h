// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UI/AoS_CaseTitleCard.h"

#include "AoS_Case.generated.h"



//class UAoS_CaseTitleCard;
class UAoS_CaseManager;
class UAoS_Part;
class UAoS_CharacterData;
class UTexture2D;

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
	TArray<UAoS_CharacterData*> PeopleOfInterest;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleCard")
	TSubclassOf<UAoS_CaseTitleCard> TitleCardWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleCard", meta=(EditCondition="TitleCardWidget != nullptr", EditConditionHides))
	UTexture2D* TitleCardBackground;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleCard", meta=(EditCondition="TitleCardWidget != nullptr", EditConditionHides))
	USoundBase* TitleCardMusic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleCard", meta=(EditCondition="TitleCardWidget != nullptr", EditConditionHides))
	float TitleCardLength = 7.0f;
	

	UFUNCTION(BlueprintPure)
	bool GetCaseIsComplete() const {return bIsComplete;}
	UFUNCTION(BlueprintPure)
	bool GetCaseIsActive() const {return bIsActive;}
	UFUNCTION(BlueprintPure)
	UAoS_Part* GetActivePart() const;
	UFUNCTION(BlueprintPure)
	TArray<UAoS_Part*> GetAllParts() const {return Parts;}
	
	void ResetCase();	
	void SetCaseComplete(bool bCaseCompleted);
	void SetCaseIsActive(bool bCaseIsActive, UAoS_CaseManager* CaseManagerRef);
	void ActivatePart(UAoS_CaseManager* CaseManagerRef);
	void DeactivatePart(UAoS_CaseManager* CaseManagerRef);
	
private:

	UPROPERTY()
	UAoS_CaseTitleCard* CaseTitleCard;
	
	bool bIsActive;
	bool bIsComplete;
	
};
