// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_UITypes.h"
#include "SI_UserWidget.h"
#include "SI_InputOption.generated.h"

class USizeBox;
class UBorder;
class UCommonTextBlock;
class UTextBlock;

UCLASS(editinlinenew, BlueprintType, Blueprintable)
class SI_PROTOTYPE_API USI_InputOption : public USI_UserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure, Category = "Widget")
	const FSI_InputOptionSettings& GetInputOptionSettings() const;
	
	FSI_InputOptionSettings& GetInputOptionSettings();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void UpdateInputOptionSettings();

	void SetInputOptionSettings(const FSI_InputOptionSettings& InInputOptionSettings);

protected:

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails")
	bool bPreviewSelectedState = false;
#endif
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionDetails")
	FSI_InputOptionSettings InputOptionSettings;
	
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
	void InitializeInputOptionStyle(const FSI_InputOptionStyleSettings& InStyleSettings);
	void SetFonts(const FSI_InputOptionStyleSettings& InStyleSettings);
	void SetPadding();
	void SetBackgroundColors(const FSI_InputOptionStyleSettings& InStyleSettings);

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:

	FSI_InputOptionSettings CurrentInputOptionSettings;
	
	bool bCanBeSelected;
	bool bIsSelected = false;
	bool bIsTruncated = false;
};
