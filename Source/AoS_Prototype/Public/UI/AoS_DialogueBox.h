// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/AoS_UserWidget.h"
#include "AoS_DialogueBox.generated.h"

class UTextBlock;
class UDlgContext;

UCLASS()
class AOS_PROTOTYPE_API UAoS_DialogueBox : public UAoS_UserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetCharacterName(FText InCharacterName);
	UFUNCTION(BlueprintCallable)
	void SetCharacterDialogue(FText InCharacterDialogue);
	UFUNCTION(BlueprintCallable)
	void UpdateDialogueBox(UDlgContext* DlgContext);
	UFUNCTION(BlueprintCallable)
	FText GetCurrentSpeaker() const;
	UFUNCTION(BlueprintCallable)
	FText GetCurrentDialogue() const;
	
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TXT_CharacterName;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TXT_CharacterDialogue;

private:
	
	FText CurrentSpeaker;
	FText CurrentDialogue;
	
};
