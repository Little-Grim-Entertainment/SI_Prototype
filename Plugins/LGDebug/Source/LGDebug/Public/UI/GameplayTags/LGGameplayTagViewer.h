// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LGGameplayTagViewer.generated.h"

class ULGGameplayTagCategoryWidget;
class ULGGameplayTagEntryWidget;
/**
 * 
 */
UCLASS(BlueprintType)
class LGDEBUG_API ULGGameplayTagViewer : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "GameplayTagDebug")
	void CreateTagCategory(const FString& InCategoryLabel);

protected:

	virtual void NativeConstruct() override;
	
	virtual void InitializeTagCategories();

	void CollapseEmptyCategories();
	
private:

	UPROPERTY(EditAnywhere, Category = "GameplayTagDebug")
	TSubclassOf<ULGGameplayTagCategoryWidget> TagCategoryWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "GameplayTagDebug")
	TSubclassOf<ULGGameplayTagEntryWidget> TagEntryWidgetClass;
		
	UPROPERTY(meta = (BindWidget))
	UPanelWidget* TagListContainer;

	TArray<ULGGameplayTagCategoryWidget*> TagCategoryWidgets;
};
