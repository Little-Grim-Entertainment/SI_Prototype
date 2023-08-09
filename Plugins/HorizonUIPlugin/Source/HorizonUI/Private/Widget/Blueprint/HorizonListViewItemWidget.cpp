// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Blueprint/HorizonListViewItemWidget.h"
#include "HorizonUIPrivate.h"
#include "Widget/Components/HorizonTileView.h"






UHorizonListViewItemWidget::UHorizonListViewItemWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if UE_VERSION_OLDER_THAN(5,2,0)
	bIsFocusable = true;
#else
	SetIsFocusable(true);
#endif
}

void UHorizonListViewItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Button_ClickArea)
	{
		Button_ClickArea->OnHovered.AddDynamic(this, &ThisClass::OnListItemObjectButtonHovered);
		Button_ClickArea->OnUnhovered.AddDynamic(this, &ThisClass::OnListItemObjectButtonUnhovered);

		Button_ClickArea->OnPressed.AddDynamic(this, &ThisClass::OnListItemObjectButtonPressed);
		Button_ClickArea->OnReleased.AddDynamic(this, &ThisClass::OnListItemObjectButtonReleased);
		Button_ClickArea->OnClicked.AddDynamic(this, &ThisClass::OnListItemObjectButtonClicked);
		
	}
}

FReply UHorizonListViewItemWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	FReply reply = Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

#if UE_VERSION_OLDER_THAN(5,2,0)
	if (Button_ClickArea && Button_ClickArea->IsFocusable)
#else
	if (Button_ClickArea && Button_ClickArea->GetIsFocusable())
#endif
	{
		Button_ClickArea->SetFocus();
		reply = FReply::Handled();
	}


	return reply;
}

void UHorizonListViewItemWidget::NativeOnListItemObjectSet(UObject* InListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(InListItemObject);

}




void UHorizonListViewItemWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	NativeOnListItemObjectSet(GetListItem());
	OnSynchronizeProperties();
}

bool UHorizonListViewItemWidget::IsHovered() const
{
	bool bResult = Super::IsHovered();
	if(Button_ClickArea)
	{
		TSharedPtr<SWidget> safeWidget = Button_ClickArea->GetCachedWidget();
		TOptional<EFocusCause> focusCause = safeWidget.IsValid() ? safeWidget->HasAnyUserFocus() : NullOpt;
		bResult = focusCause.IsSet() ? true : false;
	}
	return bResult;
}

void UHorizonListViewItemWidget::OnListItemObjectHovered_Implementation()
{

}

void UHorizonListViewItemWidget::OnListItemObjectUnhovered_Implementation()
{

}

void UHorizonListViewItemWidget::OnListItemObjectPressed_Implementation()
{

}

void UHorizonListViewItemWidget::OnListItemObjectReleased_Implementation()
{

}

void UHorizonListViewItemWidget::OnListItemObjectClicked_Implementation()
{

}

#if 1 // reroute button event for mouse


void UHorizonListViewItemWidget::OnListItemObjectButtonHovered()
{
	auto pItem = GetListItem<UObject>();
	if (pItem)
	{
		auto pListView = Cast<UListView>(pItem->GetOuter());
		if(pListView)
		{
			pListView->SetSelectedItem(pItem);
		}

		auto pTileView = Cast<UHorizonTileView>(pItem->GetOuter());
		if (pTileView)
		{
			pTileView->RerouteItemHovered(pItem);
		}
	}
}

void UHorizonListViewItemWidget::OnListItemObjectButtonUnhovered()
{
	auto pItem = GetListItem<UObject>();
	if (pItem)
	{
		auto pTileView = Cast<UHorizonTileView>(pItem->GetOuter());
		if (pTileView)
		{
			pTileView->RerouteItemUnhovered(pItem);
		}
	}
}

void UHorizonListViewItemWidget::OnListItemObjectButtonPressed()
{
	auto pItem = GetListItem<UObject>();
	if (pItem)
	{
		auto pTileView = Cast<UHorizonTileView>(pItem->GetOuter());
		if (pTileView)
		{
			pTileView->RerouteItemPressed(pItem);
		}
	}
}

void UHorizonListViewItemWidget::OnListItemObjectButtonReleased()
{
	auto pItem = GetListItem<UObject>();
	if (pItem)
	{
		auto pTileView = Cast<UHorizonTileView>(pItem->GetOuter());
		if (pTileView)
		{
			pTileView->RerouteItemReleased(pItem);
		}
	}
}

void UHorizonListViewItemWidget::OnListItemObjectButtonClicked()
{
	auto pItem = GetListItem<UObject>();
	if (pItem)
	{
		auto pTileView = Cast<UHorizonTileView>(pItem->GetOuter());
		if (pTileView)
		{
			pTileView->RerouteItemClicked(pItem);
		}
	}
}

#endif // reroute button event for mouse