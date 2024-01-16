// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_UserWidget.h"
#include "SI_InterrogationDialogueBubble.generated.h"


class USI_InterrogationWidget;
class UBorder;
class UTextBlock;

UCLASS()
class SI_PROTOTYPE_API USI_InterrogationDialogueBubble : public USI_UserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	USI_InterrogationWidget* GetInterrogationWidget();

	UFUNCTION(BlueprintNativeEvent)
	void PlayBubbleAnimation();
	
	void SetCharacterDialogue(const FText& InDialogue);
	void SetInterrogationWidget(USI_InterrogationWidget* InInterrogationWidget);

protected:
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UBorder* BG_DialogueBubble;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TXT_CharacterDialogue;

	UPROPERTY(BlueprintReadOnly)
	USI_InterrogationWidget* InterrogationWidget;
	
};
