// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#pragma once

#include "CoreMinimal.h"
#include "Widget/Blueprint/HorizonDesignableUserWidget.h"
#include "HorizonButtonUserWidget.generated.h"

class UTextBlock;
class UButton;
class UImage;
/**
 * 
 */
UCLASS()
class HORIZONUI_API UHorizonButtonUserWidget : public UHorizonDesignableUserWidget
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHorizonButtonEvent, UHorizonButtonUserWidget*, InButton);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHorizonButtonEventNative, UHorizonButtonUserWidget*);


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHorizonButtonFocusEvent, UHorizonButtonUserWidget*, InButton, const FFocusEvent&, InFocusEvent);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHorizonButtonFocusEventNative, UHorizonButtonUserWidget*, const FFocusEvent& /*InFocusEvent*/);
public:
	UHorizonButtonUserWidget();
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void OnSynchronizeProperties_Implementation() override;
	virtual void SetIsEnabled(bool bInIsEnabled) override;



#if 1 // Button Delegate
protected:

	UFUNCTION()
	virtual void NativeOnButtonPressed();
	UFUNCTION()
	virtual void NativeOnButtonReleased();
	UFUNCTION()
	virtual void NativeOnButtonClicked();
	UFUNCTION()
	virtual void NativeOnButtonHovered();
	UFUNCTION()
	virtual void NativeOnButtonUnhovered();
	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "HorizonPlugin|UI", meta = (DisplayName = "OnButtonPressed"))
	void ReceiveOnButtonPressed();
	UFUNCTION(BlueprintImplementableEvent, Category = "HorizonPlugin|UI", meta = (DisplayName = "OnButtonReleased"))
	void ReceiveOnButtonReleased();
	UFUNCTION(BlueprintImplementableEvent, Category = "HorizonPlugin|UI", meta = (DisplayName = "OnButtonClicked"))
	void ReceiveOnButtonClicked();
	UFUNCTION(BlueprintImplementableEvent, Category = "HorizonPlugin|UI", meta = (DisplayName = "OnButtonHovered"))
	void ReceiveOnButtonHovered();
	UFUNCTION(BlueprintImplementableEvent, Category = "HorizonPlugin|UI", meta = (DisplayName = "OnButtonUnhovered"))
	void ReceiveOnButtonUnhovered();
	UFUNCTION(BlueprintImplementableEvent, Category = "HorizonPlugin|UI", meta = (DisplayName = "OnButtonFocus"))
	void ReceiveOnButtonFocus(const FFocusEvent& InFocusEvent);
	UFUNCTION(BlueprintImplementableEvent, Category = "HorizonPlugin|UI", meta = (DisplayName = "OnButtonFocusLost"))
	void ReceiveOnOnButtonFocusLost(const FFocusEvent& InFocusEvent);
#endif // Button Delegate

public:

	// for blueprint
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
	FOnHorizonButtonEvent OnButtonClickedDelegate;
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
	FOnHorizonButtonEvent OnButtonPressedDelegate;
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
	FOnHorizonButtonEvent OnButtonReleasedDelegate;
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
	FOnHorizonButtonEvent OnButtonHoveredDelegate;
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
	FOnHorizonButtonEvent OnButtonUnhoveredDelegate;
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
	FOnHorizonButtonFocusEvent OnButtonFocusDelegate;
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
	FOnHorizonButtonFocusEvent OnButtonFocusLostDelegate;


	// for c++ callback binding
	FOnHorizonButtonEventNative OnButtonClickedDelegateNative;
	FOnHorizonButtonEventNative OnButtonPressedDelegateNative;
	FOnHorizonButtonEventNative OnButtonReleasedDelegateNative;
	FOnHorizonButtonEventNative OnButtonHoveredDelegateNative;
	FOnHorizonButtonEventNative OnButtonUnhoveredDelegateNative;
	FOnHorizonButtonFocusEventNative OnButtonFocusDelegateNative;
	FOnHorizonButtonFocusEventNative OnButtonFocusLostDelegateNative;

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "UI")
	UButton* Button_Main = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "UI")
	UTextBlock* TextBlock_Main = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "UI")
	UImage* Image_Main = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content", meta = (MultiLine = true))
	FText Text_Main;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
	FSlateBrush SlateBrush_ImageMain;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content", meta = (AllowPrivateAccess = "true", DisplayThumbnail = "true", DisplayName = "Image", AllowedClasses = "Texture,MaterialInterface,SlateTextureAtlasInterface", DisallowedClasses = "MediaTexture"))
	//FSoftObjectPath* Image_SoftResourceObjectMain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	bool bFocusOnHovered = true;


	UPROPERTY(BlueprintReadOnly, Category = "UI")
	bool bButtonFocused = false;
};
