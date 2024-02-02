// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Data/SI_UIProjectDefaults.h"
#include "SI_UserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFadeOutComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNativeConstructionComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNativePreConstructionComplete);



UCLASS(editinlinenew, BlueprintType, Blueprintable)
class SI_PROTOTYPE_API USI_UserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	class ASI_PlayerController* SI_PlayerController;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ProjectDefaults")
	USI_UIProjectDefaults* UIProjectDefaults;
	UPROPERTY(BlueprintCallable)
	FOnFadeOutComplete OnFadeOutComplete;
	UPROPERTY(BlueprintAssignable)
	FOnNativeConstructionComplete OnNativeConstructionComplete;
	UPROPERTY(BlueprintAssignable)
	FOnNativePreConstructionComplete OnNativePreConstructionComplete;
	
	UFUNCTION(BlueprintImplementableEvent)
	void FadeInWidget();
	UFUNCTION(BlueprintImplementableEvent)
	void FadeOutWidget();

	void FadeOutComplete();

	USI_UserWidget* GetOutermostWidget() const;

protected:

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool SetDefaults();
	
	// Getters
	UFUNCTION(BlueprintPure)
	FColorDefaults GetAllColors();
	UFUNCTION(BlueprintPure)
	FFontStyles GetAllFonts();
	UFUNCTION(BlueprintPure)
	FSlateFontInfo GetFontStyle(EFontStyle FontStyle, int FontSize);
};
