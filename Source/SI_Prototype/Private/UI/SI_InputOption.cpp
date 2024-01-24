// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_InputOption.h"

#include "CommonTextBlock.h"
#include "InputMappingContext.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Dialogue/SI_DialogueManager.h"

void USI_InputOption::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateInputOptionSettings(true);
}

void USI_InputOption::NativeConstruct()
{
	Super::NativeConstruct();

	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if(!IsValid(DialogueManager)) {return;}

	bCanBeSelected = !DialogueManager->ActiveInputDelay();
	if(!bCanBeSelected)
	{
		DialogueManager->OnInputDelayEnd().AddUObject(this, &ThisClass::OnReadyForSelection);
	}
}

FInputOptionSettings USI_InputOption::GetInputOptionSettings() const
{
	return InputOptionSettings;
}

void USI_InputOption::UpdateInputOptionSettings(bool bInIsNativeCall)
{
	if(!InputOptionSettings.bOptionIsVisible)
	{
		SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	CurrentInputOptionSettings = InputOptionSettings;
	bIsTruncated = false;
	
	InitializeOptionText();

	FInputOptionStyleSettings StyleSettingsToUse = bIsSelected ? CurrentInputOptionSettings.SelectedStyleSettings : CurrentInputOptionSettings.DefaultStyleSettings;
	
#if WITH_EDITORONLY_DATA
	if(bPreviewSelectedState)
	{
		StyleSettingsToUse = CurrentInputOptionSettings.SelectedStyleSettings;
	}
#endif

	InitializeInputOptionStyle(StyleSettingsToUse);

	if(!bInIsNativeCall)
	{
		PostEditChange();
	}
}

void USI_InputOption::ScaleFont(UTextBlock* InTextBlock, const float& InScalePercentage)
{
	if(!IsValid(InTextBlock) || InScalePercentage <= 0) {return;}

	FSlateFontInfo TextBlockFont = InTextBlock->GetFont();
	TextBlockFont.Size *= InScalePercentage;

	InTextBlock->SetFont(TextBlockFont);
}

void USI_InputOption::CheckForQ(const FText& InInputText)
{
	if(!IsValid(TXT_Input)) {return;}
	
	const FString InputString = InInputText.ToString();
	InputString == "Q" ? TXT_Input->SetMargin(FMargin(0, -20, 0, 0)) : TXT_Input->SetMargin(FMargin(0, -5, 0, 0));

	TXT_Input->PostEditChange();
}

FText USI_InputOption::GetInputMappingText()
{
	const UInputMappingContext* TargetInputMappingPtr = CurrentInputOptionSettings.TargetInputMapping;
	const UInputAction* TargetInputActionPtr = CurrentInputOptionSettings.TargetInputAction;
	if(!IsValid(TargetInputMappingPtr) || !IsValid(TargetInputActionPtr)) {return FText();}

	TArray<FEnhancedActionKeyMapping> ActionKeyMappings = TargetInputMappingPtr->GetMappings();
	for(const FEnhancedActionKeyMapping& CurrentActionKeyMapping : ActionKeyMappings)
	{
		if(CurrentActionKeyMapping.Action == CurrentInputOptionSettings.TargetInputAction)
		{
			const FString KeyString = CurrentActionKeyMapping.Key.ToString();
			FText KeyText = FText::FromString(KeyString);
			if(KeyString.Len() > 3)
			{
				KeyText = TruncateInputText(KeyText);
			}
			return  KeyText;
		}
	}
	return FText();
}

void USI_InputOption::OnSelected()
{
	if(bIsSelected || !bCanBeSelected) {return;}

	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if(!IsValid(DialogueManager)) {return;}

	DialogueManager->OnInputDelayEnd().AddUObject(this, &ThisClass::OnReleased);
	DialogueManager->StartInputDelayTimer(CurrentInputOptionSettings.SelectedDelayTimer);
	
	bIsSelected = true;
	UpdateInputOptionSettings();
}

void USI_InputOption::OnReleased()
{
	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if(!IsValid(DialogueManager)) {return;}
	
	DialogueManager->OnInputDelayEnd().RemoveAll(this);

	bIsSelected = false;
	UpdateInputOptionSettings();
}

void USI_InputOption::OnReadyForSelection()
{
	bCanBeSelected = true;
}

FText USI_InputOption::TruncateInputText(const FText& InInputText)
{
	FString InputTextString = InInputText.ToString();

	InputTextString = InputTextString.LeftChop(3);
	bIsTruncated = true;
	return FText::FromString(InputTextString);
}

void USI_InputOption::SetOptionScale()
{
	if(!IsValid(OptionSize)) {return;}

	const float Width = CurrentInputOptionSettings.DefaultWidth * CurrentInputOptionSettings.OptionScalePercentage;
	const float Height = CurrentInputOptionSettings.DefaultHeight * CurrentInputOptionSettings.OptionScalePercentage;

	OptionSize->SetWidthOverride(Width);
	OptionSize->SetHeightOverride(Height);
}

void USI_InputOption::InitializeOptionText()
{
	// Label Text
	TXT_Label->SetText(CurrentInputOptionSettings.OptionLabel);


	//Input Text
	const FText& InputText = GetInputMappingText();
	if(InputText.IsEmpty()) {return;}

	CheckForQ(InputText);
	
	TXT_Input->SetText(InputText);
}

void USI_InputOption::InitializeInputOptionStyle(const FInputOptionStyleSettings& InStyleSettings)
{
	if(!IsValid(TXT_Label) || !IsValid(TXT_Input)) {return;}

	SetFonts(InStyleSettings);
	SetPadding();
	SetBackgroundColors(InStyleSettings);
	SetOptionScale();
}

void USI_InputOption::SetFonts(const FInputOptionStyleSettings& InStyleSettings)
{
	TXT_Label->SetColorAndOpacity(InStyleSettings.LabelTextColorAndOpacity);
	TXT_Label->SetFont(CurrentInputOptionSettings.LabelFont);

	TXT_Input->SetColorAndOpacity(InStyleSettings.InputTextColorAndOpacity);
	TXT_Input->SetFont(CurrentInputOptionSettings.InputFont);
	if(bIsTruncated)
	{
		ScaleFont(TXT_Input, CurrentInputOptionSettings.InputFontScalePercentage);
	}
}

void USI_InputOption::SetPadding()
{
	UBorderSlot* LabelBorderSlot = Cast<UBorderSlot>(TXT_Label->Slot);
	UBorderSlot* InputBorderSlot = Cast<UBorderSlot>(TXT_Input->Slot);
	if(!IsValid(InputBorderSlot) || !IsValid(LabelBorderSlot)) {return;}

	LabelBorderSlot->SetPadding(CurrentInputOptionSettings.LabelTextPadding);
	InputBorderSlot->SetPadding(CurrentInputOptionSettings.InputTextPadding);
}

void USI_InputOption::SetBackgroundColors(const FInputOptionStyleSettings& InStyleSettings)
{
	// Input Colors
	if(!IsValid(BG_OptionInput)|| !IsValid(InStyleSettings.InputMaterial)) {return;}
	
	UMaterialInstanceDynamic* InputMaterial = UMaterialInstanceDynamic::Create(InStyleSettings.InputMaterial, this) ;

	InputMaterial->SetVectorParameterValue("BackgroundColor", InStyleSettings.InputBackgroundColor);
	InputMaterial->SetVectorParameterValue("BorderColor", InStyleSettings.InputBorderColor);
	BG_OptionInput->SetBrushFromMaterial(InputMaterial);

	// Label Colors
	if(!IsValid(BG_OptionLabel) || !IsValid(InStyleSettings.LabelMaterial)) {return;}
	
	if(!CurrentInputOptionSettings.bShouldShowBackground)
	{
		const FLinearColor LabelBrushColor = FLinearColor(0,0,0,0);
		BG_OptionLabel->SetBrushColor(LabelBrushColor);
		return;
	}
	
	UMaterialInstanceDynamic* LabelMaterial = UMaterialInstanceDynamic::Create(InStyleSettings.LabelMaterial, this) ;

	LabelMaterial->SetVectorParameterValue("BackgroundColor", InStyleSettings.LabelBackgroundColor);
	LabelMaterial->SetVectorParameterValue("BorderColor", InStyleSettings.LabelBorderColor);
	BG_OptionLabel->SetBrushFromMaterial(LabelMaterial);
}
