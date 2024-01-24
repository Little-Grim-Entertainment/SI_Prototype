// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_UserWidget.h"
#include "SI_InputOption.generated.h"

class USizeBox;
class UBorder;
class UCommonTextBlock;
class UInputAction;
class UInputMappingContext;
class UTextBlock;

USTRUCT(BlueprintType)
struct FInputOptionStyleSettings
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
struct FInputOptionSettings
{
	GENERATED_BODY()

	// General Widget Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0, ClampMax=1, UIMin=0, UIMax=1))
	bool bOptionIsVisible = true;	
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

	// Input Display Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails | Input")
	UInputMappingContext* TargetInputMapping;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails | Input")
	UInputAction* TargetInputAction;
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
	FInputOptionStyleSettings DefaultStyleSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails | Style")
	FInputOptionStyleSettings SelectedStyleSettings;
};

UCLASS()
class SI_PROTOTYPE_API USI_InputOption : public USI_UserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure, Category = "Widget")
	FInputOptionSettings GetInputOptionSettings() const;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void UpdateInputOptionSettings(bool bInIsNativeCall = false);

protected:

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails")
	bool bPreviewSelectedState = false;
#endif
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails")
	FInputOptionSettings InputOptionSettings;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "Widgets")
	UCommonTextBlock* TXT_Input;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "Widgets")
	UTextBlock* TXT_Label;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "Widgets")
	UBorder* BG_OptionLabel;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "Widgets")
	UBorder* BG_OptionInput;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "Widgets")
	USizeBox* OptionSize;
	
	UFUNCTION(BlueprintCallable, Category = "Font")
	void ScaleFont(UTextBlock* InTextBlock, const float& InScalePercentage);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void CheckForQ(const FText& InInputText);
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	FText GetInputMappingText();
	
	UFUNCTION(BlueprintCallable, Category = "Font")
	void OnSelected();

	UFUNCTION()
	void OnReleased();

	UFUNCTION()
	void OnReadyForSelection();
	
	FText TruncateInputText(const FText& InInputText);

	void SetOptionScale();
	
	void InitializeOptionText();
	void InitializeInputOptionStyle(const FInputOptionStyleSettings& InStyleSettings);
	void SetFonts(const FInputOptionStyleSettings& InStyleSettings);
	void SetPadding();
	void SetBackgroundColors(const FInputOptionStyleSettings& InStyleSettings);

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:

	UPROPERTY()
	FInputOptionSettings CurrentInputOptionSettings;

	bool bCanBeSelected;
	bool bIsSelected = false;
	bool bIsTruncated = false;
};
