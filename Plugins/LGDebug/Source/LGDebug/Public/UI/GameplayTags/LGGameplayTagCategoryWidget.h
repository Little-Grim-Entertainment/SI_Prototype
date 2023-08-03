// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "LGGameplayTagCategoryWidget.generated.h"

class UTextBlock;
class ULGGameplayTagEntryWidget;
class UPanelWidget;

UCLASS(BlueprintType)
class LGDEBUG_API ULGGameplayTagCategoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "GameplayTagDebug")
	void AddTagEntry(const FGameplayTag& InGameplayTag);

	void SetCategoryLabel(const FString& InCategoryLabel);
	void SetTagEntryClass(const TSubclassOf<ULGGameplayTagEntryWidget>& InGameplayTagEntryClass);

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_CategoryLabel;	
	
	UPROPERTY(meta = (BindWidget))
	UPanelWidget* TagEntriesContainer;

private:
	
	TSubclassOf<ULGGameplayTagEntryWidget> GameplayTagEntryClass;
};
