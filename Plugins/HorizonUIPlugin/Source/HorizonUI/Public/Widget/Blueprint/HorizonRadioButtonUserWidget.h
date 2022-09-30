// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#pragma once

#include "CoreMinimal.h"
#include "Widget/Blueprint/HorizonDesignableUserWidget.h"
#include "HorizonRadioButtonUserWidget.generated.h"

class UCheckBox;
class UButton;
class UTextBlock;
/**
 *
 */
UCLASS()
class HORIZONUI_API UHorizonRadioButtonUserWidget : public UHorizonDesignableUserWidget
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHorizonRadioButtonEvent);
	DECLARE_MULTICAST_DELEGATE(FOnHorizonRadioButtonEventNative);
public:
	UHorizonRadioButtonUserWidget();
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void OnSynchronizeProperties_Implementation() override;

public:
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|RadioButton")
	virtual void SetChecked();
	virtual bool IsChecked();

protected:
	//virtual void SetUnchecked();
	UFUNCTION()
	virtual void NativeOnCheckStateChanged(bool bIsChecked);
	virtual void HandleOnCheckStateChanged(bool bIsChecked);
	UFUNCTION(BlueprintImplementableEvent, Category = "HorizonPlugin|UI|RadioButton")
	void BP_OnCheckStateChanged(bool bIsChecked);


	virtual void GatherAllRadioButton();
protected:



	// TryCheck is no other RadioButton checked
	virtual void TryChecked();
public:
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
		FOnHorizonRadioButtonEvent OnCheckedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
		FOnHorizonRadioButtonEvent OnUnCheckedDelegate;

	// for c++ callback binding
	FOnHorizonRadioButtonEventNative OnCheckedDelegateNative;
	FOnHorizonRadioButtonEventNative OnUnCheckedDelegateNative;
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "UI")
	UCheckBox* CheckBox_Main = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "UI")
	UTextBlock* TextBlock_Main = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content", meta = (MultiLine = true))
	FText Text_Main;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Content")
	bool bCheckedByDefault = false;

private:
	TArray<TWeakObjectPtr<UHorizonRadioButtonUserWidget>> AllRadioButtons;
};
