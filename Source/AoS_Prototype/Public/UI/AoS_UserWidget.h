// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/UI/AoS_UIProjectDefaults.h"
#include "AoS_UserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFadeOutComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNativeConstructionComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNativePreConstructionComplete);



UCLASS()
class AOS_PROTOTYPE_API UAoS_UserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	class AAoS_PlayerController* AOS_PlayerController;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ProjectDefaults")
	UAoS_UIProjectDefaults* UIProjectDefaults;
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
