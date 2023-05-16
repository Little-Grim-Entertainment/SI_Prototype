// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_UserWidget.h"
#include "Controllers/SI_PlayerController.h"

void USI_UserWidget::FadeOutComplete()
{
	GetWorld()->GetFirstPlayerController()->SetPause(false);
}

void USI_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OnNativeConstructionComplete.Broadcast();
}

void USI_UserWidget::NativePreConstruct()
{
	SetDefaults();
	Super::NativePreConstruct();
	OnNativePreConstructionComplete.Broadcast();
}

FColorDefaults USI_UserWidget::GetAllColors()
{
	if (!UIProjectDefaults)
	{
		const FColorDefaults NullColors;
		return NullColors;
	}
	return UIProjectDefaults->Colors;	
}

FFontStyles USI_UserWidget::GetAllFonts()
{
	if (!UIProjectDefaults)
	{
		const FFontStyles NullFonts;
		return NullFonts;
	}
	return UIProjectDefaults->Fonts;	
}

FSlateFontInfo USI_UserWidget::GetFontStyle(EFontStyle FontStyle, int FontSize = 0)
{
	if (!UIProjectDefaults)
	{
		const FSlateFontInfo NullFont;
		return NullFont;
	}
	
	switch (FontStyle)
	{
		case FS_Header:
			if (FontSize > 0) {UIProjectDefaults->Fonts.HeaderFontStyle.Size = FontSize;}
			return UIProjectDefaults->Fonts.HeaderFontStyle;
		case FS_HeaderHover:
			if (FontSize > 0) {UIProjectDefaults->Fonts.HoverHeaderFontStyle.Size = FontSize;}
			return UIProjectDefaults->Fonts.HoverHeaderFontStyle;
		case FS_Secondary:
			if (FontSize > 0) {UIProjectDefaults->Fonts.SecondaryFontStyle.Size = FontSize;}
			return UIProjectDefaults->Fonts.SecondaryFontStyle;
		case FS_SecondaryHover:
			if (FontSize > 0) {UIProjectDefaults->Fonts.HoverSecondaryFontStyle.Size = FontSize;}
			return UIProjectDefaults->Fonts.HoverSecondaryFontStyle;
		case FS_Paragraph:
			if (FontSize > 0) {UIProjectDefaults->Fonts.ParagraphFontStyle.Size = FontSize;}
			return UIProjectDefaults->Fonts.ParagraphFontStyle;
		default:
			if (FontSize > 0) {UIProjectDefaults->Fonts.ParagraphFontStyle.Size = FontSize;}
			return UIProjectDefaults->Fonts.ParagraphFontStyle;
	}
}



