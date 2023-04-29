// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UI/AoS_CaseTitleCard.h"

#include "AoS_CaseData.generated.h"

//class UAoS_CaseTitleCard;
class UAoS_CaseManager;
class UAoS_PartData;
class UAoS_CharacterData;
class UTexture2D;

UCLASS(BlueprintType)
class AOS_PROTOTYPE_API UAoS_CaseData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UAoS_CaseData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CaseDetails")
	FText CaseName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CaseDetails")
	TArray<UAoS_PartData*> Parts;
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
	TArray<UAoS_PartData*> GetAllParts() const {return Parts;}
};
