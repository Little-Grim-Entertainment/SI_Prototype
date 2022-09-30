// Created by horizon-studio, All Right Reserved


#include "Widget/Components/HorizonTileView.h"
#include "HorizonUIPrivate.h"



void UHorizonTileView::NavigateToAndSelectIndex(int32 InIndex)
{
	ScrollIndexIntoView(InIndex);
	NavigateToIndex(InIndex);
	SetSelectedIndex(InIndex);
}

void UHorizonTileView::HandleListEntryHovered(UUserWidget& EntryWidget)
{
	Super::HandleListEntryHovered(EntryWidget);
	EntryWidget.SetFocus();
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
#endif


void UHorizonTileView::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	RequestRefresh();
	ScrollToBottom();
}


UUserWidget& UHorizonTileView::OnGenerateEntryWidgetInternal(UObject* Item,
	TSubclassOf<UUserWidget> DesiredEntryClass,
	const TSharedRef<STableViewBase>& OwnerTable)
{
	auto& entryWidget = Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);

	return entryWidget;
}
#if WITH_EDITORONLY_DATA
void UHorizonTileView::OnRefreshDesignerItems()
{
	RefreshDesignerItems<UObject*>(ListItems, [this]() {
		UObject* pObj = NewObject<UObject>(this);
		return pObj;
	});

}
#endif //#if WITH_EDITORONLY_DATA