// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#include "Widget/Components/HorizonButton.h"
#include "HorizonUIPrivate.h"
void UHorizonButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	if (!IsDesignTime())
	{

		OnPressed.RemoveDynamic(this, &ThisClass::OnPressedButton);
		OnReleased.RemoveDynamic(this, &ThisClass::OnReleasedButton);
		OnClicked.RemoveDynamic(this, &ThisClass::OnClickedButton);
		OnHovered.RemoveDynamic(this, &ThisClass::OnHoveredButton);
		OnUnhovered.RemoveDynamic(this, &ThisClass::OnUnhoveredButton);
		OnPressed.AddDynamic(this, &ThisClass::OnPressedButton);
		OnReleased.AddDynamic(this, &ThisClass::OnReleasedButton);
		OnClicked.AddDynamic(this, &ThisClass::OnClickedButton);
		OnHovered.AddDynamic(this, &ThisClass::OnHoveredButton);
		OnUnhovered.AddDynamic(this, &ThisClass::OnUnhoveredButton);
	}

}



void UHorizonButton::OnPressedButton()
{
	OnPressedDelegate.Broadcast(this);
	OnPressedDelegateNative.Broadcast(this);
	
}

void UHorizonButton::OnReleasedButton()
{
	OnReleasedDelegate.Broadcast(this);
	OnReleasedDelegateNative.Broadcast(this);
}

void UHorizonButton::OnClickedButton()
{
	OnClickedDelegate.Broadcast(this);
	OnClickedDelegateNative.Broadcast(this);

}


void UHorizonButton::OnHoveredButton()
{
	OnHoveredDelegate.Broadcast(this);
	OnHoveredDelegateNative.Broadcast(this);

}

void UHorizonButton::OnUnhoveredButton()
{
	OnUnhoveredDelegate.Broadcast(this);
	OnUnhoveredDelegateNative.Broadcast(this);
}



#if WITH_EDITOR

const FText UHorizonButton::GetPaletteCategory()
{
	return NSLOCTEXT("HorizonPlugin", "HorizonPlugin", "HorizonPlugin");
}





void UHorizonButton::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	Super::PostEditChangeProperty(PropertyChangedEvent);

}
#endif //#if WITH_EDITOR

