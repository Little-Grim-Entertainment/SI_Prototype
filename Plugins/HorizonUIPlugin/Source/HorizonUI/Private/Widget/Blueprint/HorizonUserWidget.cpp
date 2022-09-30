// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#include "Widget/Blueprint/HorizonUserWidget.h"
#include "HorizonUIPrivate.h"

UHorizonUserWidget::UHorizonUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITORONLY_DATA
	PaletteCategory = NSLOCTEXT("HorizonPlugin", "HorizonPlugin", "HorizonPlugin");
#endif
}

void UHorizonUserWidget::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);
}

void UHorizonUserWidget::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
}

FReply UHorizonUserWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UHorizonUserWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);
}
