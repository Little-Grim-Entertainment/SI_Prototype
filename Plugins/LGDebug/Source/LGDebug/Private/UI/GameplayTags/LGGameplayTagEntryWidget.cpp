// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameplayTags/LGGameplayTagEntryWidget.h"
#include "Components/TextBlock.h"

void ULGGameplayTagEntryWidget::SetGameplayTagText(const FGameplayTag& InGameplayTag)
{
	if(!IsValid(GameplayTagText) || !InGameplayTag.IsValid()) {return;}
	
	const FString GameplayTagString = InGameplayTag.ToString();
	
	GameplayTagText->SetText(FText::FromString(GameplayTagString));
	EntryTag = InGameplayTag;
}
