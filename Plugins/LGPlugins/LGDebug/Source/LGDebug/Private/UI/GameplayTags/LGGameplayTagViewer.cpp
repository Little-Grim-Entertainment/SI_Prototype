// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameplayTags/LGGameplayTagViewer.h"

#include "Components/PanelWidget.h"
#include "UI/GameplayTags/LGGameplayTagCategoryWidget.h"
#include "UI/GameplayTags/LGGameplayTagEntryWidget.h"

ULGGameplayTagCategoryWidget* ULGGameplayTagViewer::CreateTagCategory(const FString& InCategoryLabel)
{
	ULGGameplayTagCategoryWidget* NewCategoryWidget = Cast<ULGGameplayTagCategoryWidget>(CreateWidget(GetWorld()->GetFirstPlayerController(), TagCategoryWidgetClass));
	if(!IsValid(NewCategoryWidget)) {return nullptr;}

	NewCategoryWidget->SetCategoryLabel(InCategoryLabel);
	NewCategoryWidget->SetTagEntryClass(TagEntryWidgetClass);
	
	TagListContainer->AddChild(NewCategoryWidget);
	TagCategoryWidgets.AddUnique(NewCategoryWidget);

	return NewCategoryWidget;
}

void ULGGameplayTagViewer::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeTagCategories();
	UpdateCategoriesVisibility();
}

void ULGGameplayTagViewer::InitializeTagCategories()
{
}

void ULGGameplayTagViewer::GenerateEntriesFromTagContainer(ULGGameplayTagCategoryWidget* InCategoryWidget, const FGameplayTagContainer& InTagContainer)
{	
	TArray<FGameplayTag> GameplayTags;
	InTagContainer.GetGameplayTagArray(GameplayTags);
	
	for(const FGameplayTag& CurrentTag : GameplayTags)
	{
		if(InCategoryWidget->HasTagEntry(CurrentTag)) {continue;}
		
		InCategoryWidget->AddTagEntry(CurrentTag);
	}

	TArray<ULGGameplayTagEntryWidget*> TagEntriesCopy = InCategoryWidget->TagEntries;
	
	for(ULGGameplayTagEntryWidget* CurrentEntry : TagEntriesCopy)
	{
		if(!IsValid(CurrentEntry)) {continue;}

		if(!InTagContainer.HasTagExact(CurrentEntry->EntryTag))
		{
			InCategoryWidget->TagEntriesContainer->RemoveChild(CurrentEntry);
			InCategoryWidget->TagEntries.RemoveSingle(CurrentEntry);
		}
	}
}

void ULGGameplayTagViewer::UpdateCategoriesVisibility()
{
	for(ULGGameplayTagCategoryWidget* CurrentCategoryWidget : TagCategoryWidgets)
	{
		if(!IsValid(CurrentCategoryWidget)) { continue;}

		if(CurrentCategoryWidget->TagEntriesContainer->GetChildrenCount() <= 0)
		{
			CurrentCategoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
		else if(CurrentCategoryWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			CurrentCategoryWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
