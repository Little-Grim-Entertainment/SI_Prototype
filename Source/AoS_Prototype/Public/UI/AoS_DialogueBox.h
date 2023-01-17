// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/AoS_UserWidget.h"
#include "AoS_DialogueBox.generated.h"

class UButton;
class UTextBlock;
class UAoS_DialogueManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextClickedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextHoveredDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextUnhoveredDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreviousClickedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreviousHoveredDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreviousUnhoveredDelegate);


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
	
	FText CurrentSpeaker;
	FText CurrentDialogue;

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

	void ShowNextButton(UAoS_DialogueManager* InDialogueManager);
	void ShowPreviousButton(UAoS_DialogueManager* InDialogueManager);

};
