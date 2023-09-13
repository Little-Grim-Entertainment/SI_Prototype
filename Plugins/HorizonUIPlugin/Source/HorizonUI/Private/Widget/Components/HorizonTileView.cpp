// Created by horizon-studio, All Right Reserved


#include "Widget/Components/HorizonTileView.h"
#include "Widget/Blueprint/HorizonListViewItemWidget.h"


UHorizonTileView::UHorizonTileView(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsFocusable = false;
}

void UHorizonTileView::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	RequestRefresh();
	ScrollToBottom();
}




bool UHorizonTileView::IsTickable() const
{
	return RequestedItemSelectionIndex >= 0;
}

bool UHorizonTileView::IsTickableInEditor() const
{
	return RequestedItemSelectionIndex >= 0;
}

void UHorizonTileView::Tick(float DeltaTime)
{
	if(RequestedItemSelectionIndex >= 0)
	{
		auto pEntryWidget = GetEntryWidgetFromItem<UUserWidget>(GetItemAt(RequestedItemSelectionIndex));
		if(pEntryWidget)
		{ 
			SetSelectedIndex(RequestedItemSelectionIndex);
			RequestedItemSelectionIndex = -1;
		}
	}
	
}

void UHorizonTileView::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	InitListItem();
	switch (RefreshBehavior)
	{
	case EHorizonTileViewRefreshBehavior::ScrollToTop:
		ScrollToTop();
		break;
	case EHorizonTileViewRefreshBehavior::ScrollToBottom:
		ScrollToBottom();
		break;
	default:
		break;
	}

}



void UHorizonTileView::OnSelectionChangedInternal(UObject* InFirstSelectedItem)
{
	Super::OnSelectionChangedInternal(InFirstSelectedItem);

	if (PreviousSelectedItem.IsValid())
	{
		if (PreviousSelectedItem != InFirstSelectedItem)
		{
			RerouteItemUnhovered(PreviousSelectedItem.Get());
		}
	}
	RerouteItemHovered(InFirstSelectedItem);
	PreviousSelectedItem = InFirstSelectedItem;

}



void UHorizonTileView::HandleListEntryHovered(UUserWidget& EntryWidget)
{
	Super::HandleListEntryHovered(EntryWidget);
	EntryWidget.SetFocus();
}



void UHorizonTileView::NavigateToAndSelectIndex(int32 InIndex)
{
	ScrollIndexIntoView(InIndex);
	NavigateToIndex(InIndex);
	RequestedItemSelectionIndex = InIndex;
	if(RequestedItemSelectionIndex < 0)
	{
		// Remove PreviousSelectedItem from selection
		SetItemSelection(PreviousSelectedItem.Get(), false);
	}

}




bool UHorizonTileView::IsFocusable()
{
	return bIsFocusable;
}

bool UHorizonTileView::IsPendingRefresh()
{
	bool bResult = false;
	TSharedPtr<STileView<UObject*>> listViewPtr = StaticCastSharedPtr<STileView<UObject*>>(GetCachedWidget());
	if(listViewPtr.IsValid())
	{
		bResult = listViewPtr->IsPendingRefresh();
	}
	return bResult;
}

int32 UHorizonTileView::GetNumGeneratedChildren()
{
	TSharedPtr<SListView<UObject*>> listViewPtr = StaticCastSharedPtr<SListView<UObject*>>(GetCachedWidget());
	return listViewPtr->GetNumGeneratedChildren();
}



void UHorizonTileView::OnItemClickedInternal(UObject* InItem)
{
	SetSelectedItem(InItem);
	Super::OnItemClickedInternal(InItem);
}

UUserWidget& UHorizonTileView::OnGenerateEntryWidgetInternal(UObject* InItem,
	TSubclassOf<UUserWidget> InDesiredEntryClass,
	const TSharedRef<STableViewBase>& InOwnerTable)
{
	auto& entryWidget = Super::OnGenerateEntryWidgetInternal(InItem, InDesiredEntryClass, InOwnerTable);

#if WITH_EDITOR
	if (IsDesignTime())
	{
		UHorizonListViewItemWidget* pItemWidget = Cast<UHorizonListViewItemWidget>(&entryWidget);
		if (pItemWidget)
		{
			pItemWidget->NativeOnListItemObjectSet(InItem);
		}
	}
#endif
	return entryWidget;
}



void UHorizonTileView::RerouteItemPressed(UObject* InItem)
{
	auto pItemWidget = GetEntryWidgetFromItem<UHorizonListViewItemWidget>(InItem);
	if (pItemWidget)
	{
		pItemWidget->OnListItemObjectPressed();
		OnItemPressedEvent.Broadcast(InItem);
		OnItemPressedEventNative.Broadcast(InItem);
	}
}


void UHorizonTileView::RerouteItemReleased(UObject* InItem)
{
	auto pItemWidget = GetEntryWidgetFromItem<UHorizonListViewItemWidget>(InItem);
	if (pItemWidget)
	{
		pItemWidget->OnListItemObjectReleased();
		OnItemReleasedEvent.Broadcast(InItem);
		OnItemReleasedEventNative.Broadcast(InItem);
	}
}

void UHorizonTileView::RerouteItemHovered(UObject* InItem)
{

	auto pItemWidget = GetEntryWidgetFromItem<UHorizonListViewItemWidget>(InItem);
	if (pItemWidget)
	{
		pItemWidget->SetFocus();
		pItemWidget->OnListItemObjectHovered();
		OnItemHoveredEvent.Broadcast(InItem);
		OnItemHoveredEventNative.Broadcast(InItem);
	}
}

void UHorizonTileView::RerouteItemUnhovered(UObject* InItem)
{
	auto pItemWidget = GetEntryWidgetFromItem<UHorizonListViewItemWidget>(InItem);
	if (pItemWidget)
	{
		pItemWidget->OnListItemObjectUnhovered();
		OnItemUnhoveredEvent.Broadcast(InItem);
		OnItemUnhoveredEventNative.Broadcast(InItem);
	}

}

void UHorizonTileView::RerouteItemClicked(UObject* InItem)
{
	OnItemClickedInternal(InItem);
	auto pItemWidget = GetEntryWidgetFromItem<UHorizonListViewItemWidget>(InItem);
	if (pItemWidget)
	{
		pItemWidget->SetFocus();
		pItemWidget->OnListItemObjectClicked();
		OnItemClickedEvent.Broadcast(InItem);
		OnItemClickedEventNative.Broadcast(InItem);
	}
}


void UHorizonTileView::RequestListRefresh()
{
	InitListItem();
	RequestRefresh();
}

void UHorizonTileView::InitListItem()
{
	OnInitListItemEvent.Broadcast(this);
	OnInitListItemEventNative.Broadcast(this);
}

UHorizonListViewItemWidget* UHorizonTileView::BP_GetEntryWidgetFromItem(UObject* InItem)
{
	return GetEntryWidgetFromItem<UHorizonListViewItemWidget>(InItem);
}


void UHorizonTileView::RemoveItemAndKeepSelectedIndex(UObject* InItem)
{
	int32 currentSelectedIndex = GetIndexForItem(GetSelectedItem());
	RemoveItem(InItem);
	if (currentSelectedIndex >= GetNumItems())
	{
		currentSelectedIndex = GetNumItems() - 1;
	}
	SetSelectedIndex(currentSelectedIndex);
}


#if WITH_EDITOR


void UHorizonTileView::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	//if ((PropertyName == GET_MEMBER_NAME_CHECKED(UListViewBase, EntryWidgetClass)))
	if (PropertyName == TEXT("EntryWidgetClass"))
	{
		CalculateItemSize();
	}
}

void UHorizonTileView::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

}

void UHorizonTileView::CalculateItemSize()
{
	auto entryWidgetClass = GetEntryWidgetClass();
	if (entryWidgetClass)
	{
		auto defaultItem = Cast<UUserWidget>(entryWidgetClass->GetDefaultObject());
		if (defaultItem)
		{
			SetEntryWidth(defaultItem->DesignTimeSize.X);
			SetEntryHeight(defaultItem->DesignTimeSize.Y);

		}
	}


}


void UHorizonTileView::OnRefreshDesignerItems()
{
	RefreshDesignerItems<UObject*>(ListItems, [this]() {
		UObject* pObj = NewObject<UHorizonListViewItemObject>(this);
		return pObj;
	});

}

#endif