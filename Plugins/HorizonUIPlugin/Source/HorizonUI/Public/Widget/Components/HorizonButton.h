// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#pragma once

#include "Components/Button.h"
#include "HorizonButton.generated.h"




/**
 * 
 */
UCLASS()
class HORIZONUI_API UHorizonButton : public UButton
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHorizonButtonEvent, UHorizonButton*, Button);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHorizonButtonEventNative, UHorizonButton*);

public: //delegate

	// for blueprint
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
	FOnHorizonButtonEvent OnClickedDelegate;
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
	FOnHorizonButtonEvent OnPressedDelegate;
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
	FOnHorizonButtonEvent OnReleasedDelegate;
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
	FOnHorizonButtonEvent OnHoveredDelegate;
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
	FOnHorizonButtonEvent OnUnhoveredDelegate;


	// for c++ callback binding
	FOnHorizonButtonEventNative OnClickedDelegateNative;
	FOnHorizonButtonEventNative OnPressedDelegateNative;
	FOnHorizonButtonEventNative OnReleasedDelegateNative;
	FOnHorizonButtonEventNative OnHoveredDelegateNative;
	FOnHorizonButtonEventNative OnUnhoveredDelegateNative;
public:

	virtual void OnWidgetRebuilt() override;
#if WITH_EDITOR
		//~ Begin UWidget Interface
		//#if (ENGINE_MAJOR_VERSION <= 4) && (ENGINE_MINOR_VERSION <= 12)
		//virtual const FSlateBrush* GetEditorIcon() override;
		//#endif
	virtual const FText GetPaletteCategory() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
protected:  //dynamic delegate
	UFUNCTION()
	virtual void OnPressedButton();
	UFUNCTION()
	virtual void OnReleasedButton();
	UFUNCTION()
	virtual void OnClickedButton();
	UFUNCTION()
	virtual void OnHoveredButton();
	UFUNCTION()
	virtual void OnUnhoveredButton();

	
	
};
