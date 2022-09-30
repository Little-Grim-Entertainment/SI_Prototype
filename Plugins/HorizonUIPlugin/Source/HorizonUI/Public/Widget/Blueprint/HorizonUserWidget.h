// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#pragma once
#include "Blueprint/UserWidget.h"
#include "HorizonUserWidget.generated.h"


UCLASS()
class HORIZONUI_API UHorizonUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UHorizonUserWidget(const FObjectInitializer& ObjectInitializer);


	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;
};

