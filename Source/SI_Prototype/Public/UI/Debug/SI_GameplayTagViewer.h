// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/GameplayTags/LGGameplayTagViewer.h"

#include "SI_GameplayTagViewer.generated.h"

class USI_GameplayTagManager;

UCLASS()
class SI_PROTOTYPE_API USI_GameplayTagViewer : public ULGGameplayTagViewer
{
	GENERATED_BODY()

public:
	
	USI_GameplayTagViewer();
	
protected:

	virtual void InitializeTagCategories() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	bool bCategoriesInitialized;

	void UpdateTagEntries();

	UPROPERTY()
	USI_GameplayTagManager* SITagManager;
	
	UPROPERTY()
	ULGGameplayTagCategoryWidget* CameraTags;
	
	UPROPERTY()
	ULGGameplayTagCategoryWidget* DebugTags;

	UPROPERTY()
	ULGGameplayTagCategoryWidget* GadgetTags;

	UPROPERTY()
	ULGGameplayTagCategoryWidget* GameStateTags;

	UPROPERTY()
	ULGGameplayTagCategoryWidget* LevelTags;

	UPROPERTY()
	ULGGameplayTagCategoryWidget* MediaTags;

	UPROPERTY()
	ULGGameplayTagCategoryWidget* MusicTags;

	UPROPERTY()
	ULGGameplayTagCategoryWidget* PlayerStateTags;

	UPROPERTY()
	ULGGameplayTagCategoryWidget* UITags;		
};
