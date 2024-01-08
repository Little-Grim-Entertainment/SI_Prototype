// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "UI/SI_CaseTitleCard.h"

#include "SI_CaseData.generated.h"

//class USI_CaseTitleCard;
class USI_CaseManager;
class USI_PartData;
class USI_CharacterData;
class UTexture2D;

UCLASS(BlueprintType)
class SI_PROTOTYPE_API USI_CaseData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	USI_CaseData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CaseDetails")
	FGameplayTag CaseTag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CaseDetails")
	TArray<USI_PartData*> Parts;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CaseDetails")
	TArray<USI_CharacterData*> PeopleOfInterest;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleCard")
	TSubclassOf<USI_CaseTitleCard> TitleCardWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleCard", meta=(EditCondition="TitleCardWidget != nullptr", EditConditionHides))
	UTexture2D* TitleCardBackground = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleCard", meta=(EditCondition="TitleCardWidget != nullptr", EditConditionHides))
	USoundBase* TitleCardMusic = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleCard", meta=(EditCondition="TitleCardWidget != nullptr", EditConditionHides))
	float TitleCardLength = 7.0f;
	
	UFUNCTION(BlueprintPure)
	TArray<USI_PartData*> GetAllParts() const {return Parts;}
};
