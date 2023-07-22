// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SI_InteractionWidget.h"
#include "SI_QuickActionWidget.generated.h"

class UInputAction;
class USI_OptionWidget;
class UDataTable;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS()
class SI_PROTOTYPE_API USI_QuickActionWidget : public USI_InteractionWidget
{
	GENERATED_BODY()

public:

	void RefreshQuickActionWidget();
	
protected:

	virtual void NativeConstruct() override;
	void UpdateQuickActionUp(FGameplayTag InOptionTag);
	void UpdateQuickActionDown(FGameplayTag InOptionTag);
	void UpdateQuickActionLeft(FGameplayTag InOptionTag);
	void UpdateQuickActionRight(FGameplayTag InOptionTag);
	void UpdateActionByTag(USI_OptionWidget* InOptionWidget, FGameplayTag InOptionTag, UInputAction* InInputAction);
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* OptionListDataTable;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USI_OptionWidget* QuickActionOption_Down;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USI_OptionWidget* QuickActionOption_Left;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USI_OptionWidget* QuickActionOption_Right;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USI_OptionWidget* QuickActionOption_Up;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag QuickActionUpTag;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* QuickActionUpInputAction;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag QuickActionDownTag;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* QuickActionDownInputAction;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag QuickActionLeftTag;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* QuickActionLeftInputAction;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag QuickActionRightTag;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* QuickActionRightInputAction;

	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLPS;
};
