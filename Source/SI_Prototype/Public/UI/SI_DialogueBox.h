// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dialogue/SI_DialogueTypes.h"
#include "UI/SI_UserWidget.h"
#include "SI_DialogueBox.generated.h"

class UButton;
class UTextBlock;
class USI_DialogueManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextClickedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextHoveredDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextUnhoveredDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreviousClickedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreviousHoveredDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreviousUnhoveredDelegate);


UCLASS()
class SI_PROTOTYPE_API USI_DialogueBox : public USI_UserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	FText GetCurrentSpeaker() const;
	UFUNCTION(BlueprintCallable)
	FText GetCurrentDialogue() const;
	UFUNCTION(BlueprintCallable)
	void RefreshDialogueBox();

	UFUNCTION()
	void OnNextClicked();
	UFUNCTION()
	void OnPreviousClicked();

	FOnNextClickedDelegate& GetOnNextClickedDelegate();
	FOnNextHoveredDelegate& GetOnNextHoveredDelegate();
	FOnNextUnhoveredDelegate& GetOnNextUnhoveredDelegate();

	FOnPreviousClickedDelegate& GetOnPreviousClickedDelegate();
	FOnPreviousHoveredDelegate& GetOnPreviousHoveredDelegate();
	FOnPreviousUnhoveredDelegate& GetOnPreviousUnhoveredDelegate();
	
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TXT_CharacterName;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TXT_CharacterDialogue;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* BTN_Next;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* BTN_Previous;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	
	FSI_PrimaryDialogue CurrentPrimaryDialogue;

	FOnNextClickedDelegate OnNextClickedDelegate;
	FOnNextHoveredDelegate OnNextHoveredDelegate;
	FOnNextUnhoveredDelegate OnNextUnhoveredDelegate;

	FOnPreviousClickedDelegate OnPreviousClickedDelegate;
	FOnPreviousHoveredDelegate OnPreviousHoveredDelegate;
	FOnPreviousUnhoveredDelegate OnPreviousUnhoveredDelegate;


	UFUNCTION()
	void OnNextHovered();
	UFUNCTION()
	void OnNextUnhovered();
	
	UFUNCTION()
	void OnPreviousHovered();
	UFUNCTION()
	void OnPreviousUnhovered();

	void ShowNextButton(USI_DialogueManager* InDialogueManager);
	void ShowPreviousButton(USI_DialogueManager* InDialogueManager);

};
