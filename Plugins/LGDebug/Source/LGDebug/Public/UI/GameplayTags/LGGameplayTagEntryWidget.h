// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "LGGameplayTagEntryWidget.generated.h"

class UTextBlock;

UCLASS(BlueprintType)
class LGDEBUG_API ULGGameplayTagEntryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "GameplayTagDebug")
	void SetGameplayTagText(const FGameplayTag& InGameplayTag);
	
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameplayTagText;
};
