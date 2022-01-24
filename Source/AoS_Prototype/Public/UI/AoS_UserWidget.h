// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/AoS_Defaults.h"
#include "AoS_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AOS_PROTOTYPE_API UAoS_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ProjectDefaults")
	class UAoS_Defaults* ProjectDefaults;


	// Getters
	UFUNCTION(BlueprintPure)
	FColorDefaults GetAllColors();
	UFUNCTION(BlueprintPure)
	FFontStyles GetAllFonts();
	UFUNCTION(BlueprintPure)
	FSlateFontInfo GetFontStyle(EFontStyle FontStyle);
};
