// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameplayTags/LGGameplayTagViewer.h"

#include "Components/PanelWidget.h"
#include "UI/GameplayTags/LGGameplayTagCategoryWidget.h"
#include "UI/GameplayTags/LGGameplayTagEntryWidget.h"

void ULGGameplayTagViewer::CreateTagCategory(const FString& InCategoryLabel)
{
	ULGGameplayTagCategoryWidget* NewCategoryWidget = Cast<ULGGameplayTagCategoryWidget>(CreateWidget(GetWorld()->GetFirstPlayerController(), TagCategoryWidgetClass));
	if(!IsValid(NewCategoryWidget)) {return;}

	NewCategoryWidget->SetCategoryLabel(InCategoryLabel);
	NewCategoryWidget->SetTagEntryClass(TagEntryWidgetClass);
	
	TagListContainer->AddChild(NewCategoryWidget);
	TagCategoryWidgets.AddUnique(NewCategoryWidget);
}

void ULGGameplayTagViewer::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeTagCategories();
	CollapseEmptyCategories();
}

void ULGGameplayTagViewer::InitializeTagCategories()
{
}

void ULGGameplayTagViewer::CollapseEmptyCategories()
{
	for(ULGGameplayTagCategoryWidget* CurrentCategoryWidget : TagCategoryWidgets)
	{
		if(!IsValid(CurrentCategoryWidget)) { continue;}

		if(CurrentCategoryWidget->TagEntriesContainer->GetChildrenCount() <= 0)
		{
			CurrentCategoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}
