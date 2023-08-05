// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameplayTags/LGGameplayTagCategoryWidget.h"

#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "UI/GameplayTags/LGGameplayTagEntryWidget.h"

void ULGGameplayTagCategoryWidget::AddTagEntry(const FGameplayTag& InGameplayTag)
{
	ULGGameplayTagEntryWidget* NewEntryWidget = Cast<ULGGameplayTagEntryWidget>(CreateWidget(GetWorld()->GetFirstPlayerController(), GameplayTagEntryClass));
	if(!IsValid(NewEntryWidget)) {return;}

	NewEntryWidget->SetGameplayTagText(InGameplayTag);

	TagEntriesContainer->AddChild(NewEntryWidget);
	TagEntries.AddUnique(NewEntryWidget);
}

bool ULGGameplayTagCategoryWidget::HasTagEntry(const FGameplayTag& InGameplayTag)
{
	for(const ULGGameplayTagEntryWidget* CurrentTagEntry : TagEntries)
	{
		if(CurrentTagEntry->EntryTag == InGameplayTag)
		{
			return true;
		}
	}

	return false;
}

void ULGGameplayTagCategoryWidget::SetCategoryLabel(const FString& InCategoryLabel)
{
	if(!IsValid(TXT_CategoryLabel)) {return;}
	
	TXT_CategoryLabel->SetText(FText::FromString(InCategoryLabel));
}

void ULGGameplayTagCategoryWidget::SetTagEntryClass(const TSubclassOf<ULGGameplayTagEntryWidget>& InGameplayTagEntryClass)
{
	GameplayTagEntryClass = InGameplayTagEntryClass;
}
