// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SI_UserWidget.h"
#include "UI/SI_UITypes.h"
#include "SI_InterrogationDialogueBubble.generated.h"

class USI_InputOption;
class USI_InterrogationWidget;
class UBorder;
class UTextBlock;

enum ESI_InterrogationState : uint8;

UCLASS()
class SI_PROTOTYPE_API USI_InterrogationDialogueBubble : public USI_UserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputOptions")
	bool bShowInputOptions = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputOptions | Press")
	FSI_InputOptionSettings PressInputOptionSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputOptions | Present")
	FSI_InputOptionSettings PresentInputOptionSettings;
	
	UFUNCTION(BlueprintCallable)
	USI_InterrogationWidget* GetInterrogationWidget();

	UFUNCTION(BlueprintPure)
	USI_InputOption* GetPressInputOptionWidget();
	
	UFUNCTION(BlueprintPure)
	USI_InputOption* GetPresentInputOptionWidget();

	UFUNCTION(BlueprintNativeEvent)
	void PlayBubbleAnimation();
	
	void SetCharacterDialogue(const FText& InDialogue);
	void SetInterrogationWidget(USI_InterrogationWidget* InInterrogationWidget);
	void ShowPressInputOption(const bool& bInShouldShow);
	void ShowPresentInputOption(const bool& bInShouldShow);
	void HideAllInputOptions();
	void OnInterrogationStateUpdated(const ESI_InterrogationState& InInterrogationState);
	
	const FSI_InputOptionSettings& RequestInputOptionSettings(const USI_InputOption* InInputOptionWidget) const;
		
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UBorder* BG_DialogueBubble;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TXT_CharacterDialogue;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USI_InputOption* PressInputOption;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USI_InputOption* PresentInputOption;

	UPROPERTY(BlueprintReadOnly)
	USI_InterrogationWidget* InterrogationWidget;

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
