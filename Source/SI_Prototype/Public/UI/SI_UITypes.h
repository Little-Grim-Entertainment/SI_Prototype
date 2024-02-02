// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTags/SI_GameplayTagTypes.h"
#include "SI_UITypes.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FSI_InputOptionStyleSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* InputMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor InputBackgroundColor = FLinearColor::White;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor InputBorderColor = FLinearColor::Black;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateColor InputTextColorAndOpacity = FSlateColor(FLinearColor::White);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* LabelMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor LabelBackgroundColor = FLinearColor::White;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor LabelBorderColor = FLinearColor::Black;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateColor LabelTextColorAndOpacity = FSlateColor(FLinearColor::Black);
};


USTRUCT(BlueprintType)
struct FSI_InputOptionSettings
{
	GENERATED_BODY()

	FSI_InputOptionSettings() {}

	// General Widget Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0, ClampMax=1, UIMin=0, UIMax=1))
	float OptionScalePercentage = 1.0f;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldShowBackground = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultWidth = 380.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultHeight = 156.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SelectedDelayTimer = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMargin InputOptionPadding = FMargin(0,0,0,0);

	// Input Display Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails | Input")
	UInputMappingContext* TargetInputMapping = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails | Input")
	UInputAction* TargetInputAction = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails | Input")
	FSlateFontInfo InputFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails | Input")
	float InputFontScalePercentage = 0.8f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMargin InputTextPadding = FMargin(0,0,0,0);

	// Label Display Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails | Label")
	FText OptionLabel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails | Label")
	FSlateFontInfo LabelFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails | Label")
	FMargin LabelTextPadding = FMargin(0,0,0,0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails | Style")
	FSI_InputOptionStyleSettings DefaultStyleSettings = FSI_InputOptionStyleSettings();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails | Style")
	FSI_InputOptionStyleSettings SelectedStyleSettings  = FSI_InputOptionStyleSettings();

	bool IsValid() const;
	
	bool operator==(const FSI_InputOptionSettings& OtherInputOptionSettings) const;
	bool operator!=(const FSI_InputOptionSettings& OtherInputOptionSettings) const;
};
