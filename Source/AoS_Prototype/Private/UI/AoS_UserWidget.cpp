// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_UserWidget.h"

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

FSlateFontInfo UAoS_UserWidget::GetFontStyle(EFontStyle FontStyle)
{
	if (!ProjectDefaults)
	{
		const FSlateFontInfo NullFont;
		return NullFont;
	}

	switch (FontStyle)
	{
		case FS_Header:
			return ProjectDefaults->Fonts.HeaderFontStyle;
		case FS_HeaderHover:
			return ProjectDefaults->Fonts.HoverHeaderFontStyle;
		case FS_Secondary:
			return ProjectDefaults->Fonts.SecondaryFontStyle;
		case FS_SecondaryHover:
			return ProjectDefaults->Fonts.HoverSecondaryFontStyle;
		case FS_Paragraph:
			return ProjectDefaults->Fonts.ParagraphFontStyle;
		default:
			return ProjectDefaults->Fonts.ParagraphFontStyle;
	}
}



