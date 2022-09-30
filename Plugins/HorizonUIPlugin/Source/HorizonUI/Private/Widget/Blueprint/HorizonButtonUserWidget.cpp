// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#include "Widget/Blueprint/HorizonButtonUserWidget.h"
#include "HorizonUIPrivate.h"
#include "Widget/Components/HorizonButton.h"
UHorizonButtonUserWidget::UHorizonButtonUserWidget()
{
	Text_Main = FText::FromString(TEXT("Text Block"));
	bIsFocusable = true;
	Visibility = ESlateVisibility::Visible;
}

void UHorizonButtonUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Button_Main)
	{
		Button_Main->OnPressed.AddDynamic(this, &ThisClass::NativeOnButtonPressed);
		Button_Main->OnReleased.AddDynamic(this, &ThisClass::NativeOnButtonReleased);
		Button_Main->OnClicked.AddDynamic(this, &ThisClass::NativeOnButtonClicked);
		Button_Main->OnHovered.AddDynamic(this, &ThisClass::NativeOnButtonHovered);
		Button_Main->OnUnhovered.AddDynamic(this, &ThisClass::NativeOnButtonUnhovered);
	}
}

void UHorizonButtonUserWidget::NativeConstruct()
{
	Super::NativeConstruct();


}


void UHorizonButtonUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UHorizonButtonUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UHorizonButtonUserWidget::OnSynchronizeProperties_Implementation()
{
	if (TextBlock_Main)
	{
		TextBlock_Main->SetText(FText::AsCultureInvariant(Text_Main));
	}

	if (Image_Main)
	{
		Image_Main->SetBrush(SlateBrush_ImageMain);
	}
	
}



void UHorizonButtonUserWidget::SetIsEnabled(bool bInIsEnabled)
{
	Super::SetIsEnabled(bInIsEnabled);

	if (Button_Main)
	{
		Button_Main->SetIsEnabled(bInIsEnabled);
	}

	if (TextBlock_Main)
	{
		TextBlock_Main->SetIsEnabled(bInIsEnabled);
	}

	if (Image_Main)
	{
		Image_Main->SetIsEnabled(bInIsEnabled);
	}

}

#if 1 // Button Delegate
void UHorizonButtonUserWidget::NativeOnButtonPressed()
{
	OnButtonPressedDelegate.Broadcast(this);
	OnButtonPressedDelegateNative.Broadcast(this);
	ReceiveOnButtonPressed();
}

void UHorizonButtonUserWidget::NativeOnButtonReleased()
{
	OnButtonReleasedDelegate.Broadcast(this);
	OnButtonReleasedDelegateNative.Broadcast(this);
	ReceiveOnButtonReleased();
}

void UHorizonButtonUserWidget::NativeOnButtonClicked()
{
	OnButtonClickedDelegate.Broadcast(this);
	OnButtonClickedDelegateNative.Broadcast(this);
	ReceiveOnButtonClicked();
}

void UHorizonButtonUserWidget::NativeOnButtonHovered()
{
	if (Button_Main)
	{
		auto pOwningPlayer = GetOwningPlayer();
		if (bFocusOnHovered && Button_Main->IsFocusable)
		{
			//bButtonFocused = true;

			if (!Button_Main->HasUserFocus(pOwningPlayer))
			{
				Button_Main->SetUserFocus(pOwningPlayer);
			}
			OnButtonHoveredDelegate.Broadcast(this);
			OnButtonHoveredDelegateNative.Broadcast(this);
			ReceiveOnButtonHovered();
			
		}
		else
		{
			OnButtonHoveredDelegate.Broadcast(this);
			OnButtonHoveredDelegateNative.Broadcast(this);
			ReceiveOnButtonHovered();
		}
	}
}

void UHorizonButtonUserWidget::NativeOnButtonUnhovered()
{
	if (Button_Main)
	{
		auto pOwningPlayer = GetOwningPlayer();
		if (bFocusOnHovered && Button_Main->IsFocusable)
		{
			//bButtonFocused = false;
			if (Button_Main->HasUserFocus(pOwningPlayer))
			{
				OnButtonUnhoveredDelegate.Broadcast(this);
				OnButtonUnhoveredDelegateNative.Broadcast(this);
				ReceiveOnButtonUnhovered();
			}
		}
		else
		{
			OnButtonUnhoveredDelegate.Broadcast(this);
			OnButtonUnhoveredDelegateNative.Broadcast(this);
			ReceiveOnButtonUnhovered();
		}
	}
	
}



void UHorizonButtonUserWidget::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	if (false == bButtonFocused)
	{
		OnButtonFocusDelegate.Broadcast(this, InFocusEvent);
		OnButtonFocusDelegateNative.Broadcast(this, InFocusEvent);
		ReceiveOnButtonFocus(InFocusEvent);
	}
	bButtonFocused = true;
	Super::NativeOnAddedToFocusPath(InFocusEvent);
}

void UHorizonButtonUserWidget::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	if (bButtonFocused)
	{
		OnButtonFocusLostDelegate.Broadcast(this, InFocusEvent);
		OnButtonFocusLostDelegateNative.Broadcast(this, InFocusEvent);
		ReceiveOnOnButtonFocusLost(InFocusEvent);
	}
	bButtonFocused = false;
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
}

FReply UHorizonButtonUserWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	FReply reply = FReply::Handled();//Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

	if (InFocusEvent.GetCause() != EFocusCause::Cleared)
	{
		auto pOwningPlayer = GetOwningPlayer();
		if (Button_Main && !Button_Main->HasUserFocus(pOwningPlayer))
		{
			TSharedPtr<SWidget> safeWidget = Button_Main->GetCachedWidget();
			if (safeWidget.IsValid())
			{
				reply.SetUserFocus(safeWidget.ToSharedRef(), InFocusEvent.GetCause());
			}
		}
	}

	return reply;
}

#endif // Button Delegate