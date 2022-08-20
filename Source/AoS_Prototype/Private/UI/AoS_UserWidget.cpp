// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_UserWidget.h"
#include "Controllers/AoS_PlayerController.h"

void UAoS_UserWidget::FadeOutComplete()
{
	GetWorld()->GetFirstPlayerController()->SetPause(false);
}

void UAoS_UserWidget::NativePreConstruct()
{
	SetDefaults();
	Super::NativePreConstruct();
}

FColorDefaults UAoS_UserWidget::GetAllColors()
{
	if (!ProjectDefaults)
	{
		const FColorDefaults NullColors;
		return NullColors;
	}
	return ProjectDefaults->Colors;	
}

FFontStyles UAoS_UserWidget::GetAllFonts()
{
	if (!ProjectDefaults)
	{
		const FFontStyles NullFonts;
		return NullFonts;
	}
	return ProjectDefaults->Fonts;	
}

FSlateFontInfo UAoS_UserWidget::GetFontStyle(EFontStyle FontStyle, int FontSize = 0)
{
	if (!ProjectDefaults)
	{
		const FSlateFontInfo NullFont;
		return NullFont;
	}
	
	switch (FontStyle)
	{
		case FS_Header:
			if (FontSize > 0) {ProjectDefaults->Fonts.HeaderFontStyle.Size = FontSize;}
			return ProjectDefaults->Fonts.HeaderFontStyle;
		case FS_HeaderHover:
			if (FontSize > 0) {ProjectDefaults->Fonts.HoverHeaderFontStyle.Size = FontSize;}
			return ProjectDefaults->Fonts.HoverHeaderFontStyle;
		case FS_Secondary:
			if (FontSize > 0) {ProjectDefaults->Fonts.SecondaryFontStyle.Size = FontSize;}
			return ProjectDefaults->Fonts.SecondaryFontStyle;
		case FS_SecondaryHover:
			if (FontSize > 0) {ProjectDefaults->Fonts.HoverSecondaryFontStyle.Size = FontSize;}
			return ProjectDefaults->Fonts.HoverSecondaryFontStyle;
		case FS_Paragraph:
			if (FontSize > 0) {ProjectDefaults->Fonts.ParagraphFontStyle.Size = FontSize;}
			return ProjectDefaults->Fonts.ParagraphFontStyle;
		default:
			if (FontSize > 0) {ProjectDefaults->Fonts.ParagraphFontStyle.Size = FontSize;}
			return ProjectDefaults->Fonts.ParagraphFontStyle;
	}
}



