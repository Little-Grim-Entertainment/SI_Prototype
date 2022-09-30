//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Components/CheckBox.h"
//#include "HorizonUIPackage.h"
//#include "HorizonRadioButton.generated.h"
//
///**
// * 
// */
//UCLASS()
//class HORIZONUI_API UHorizonRadioButton : public UCheckBox
//{
//	GENERATED_BODY()
//	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHorizonRadioButtonEvent);
//	DECLARE_MULTICAST_DELEGATE(FOnHorizonRadioButtonEventNative);
//public:
//
//	virtual void OnWidgetRebuilt() override;
//#if WITH_EDITOR
//	//~ Begin UWidget Interface
//	//#if (ENGINE_MAJOR_VERSION <= 4) && (ENGINE_MINOR_VERSION <= 12)
//	//virtual const FSlateBrush* GetEditorIcon() override;
//	//#endif
//	virtual const FText GetPaletteCategory() override;
//
//	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
//#endif
//
//public:
//	virtual void SetChecked();
//private:
//	UFUNCTION()
//	virtual void NativeOnCheckStateChanged(bool bIsChecked);
//
//	void TryChecked();
//public:
//	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
//	FOnHorizonRadioButtonEvent OnCheckedDelegate;
//
//	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
//	FOnHorizonRadioButtonEvent OnUnCheckedDelegate;
//
//	// for c++ callback binding
//	FOnHorizonRadioButtonEventNative OnCheckedDelegateNative;
//	FOnHorizonRadioButtonEventNative OnUnCheckedDelegateNative;
//
//};
