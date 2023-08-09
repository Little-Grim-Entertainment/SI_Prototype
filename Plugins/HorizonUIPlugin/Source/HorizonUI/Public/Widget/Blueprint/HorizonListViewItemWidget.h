// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


// Core
#include "CoreMinimal.h"


// UMG
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"


// HorizonUI
#include "HorizonListViewItemWidget.generated.h"


class UButton;




UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class HORIZONUI_API UHorizonListViewItemObject : public UObject
{
	GENERATED_BODY()

};


/**
 * 
 */
UCLASS()
class HORIZONUI_API UHorizonListViewItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	UHorizonListViewItemWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnListItemObjectSet(UObject* InListItemObject) override;

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|TileView")
	virtual void SynchronizeProperties() override;


	virtual bool IsHovered() const override;

	UFUNCTION(BlueprintNativeEvent, Category = "HorizonPlugin|UI|TileView")
	void OnSynchronizeProperties();
	virtual void OnSynchronizeProperties_Implementation() {};


#if 1 // button event
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HorizonPlugin|UI|ListView|Item")
		void OnListItemObjectHovered();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HorizonPlugin|UI|ListView|Item")
		void OnListItemObjectUnhovered();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HorizonPlugin|UI|ListView|Item")
		void OnListItemObjectPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HorizonPlugin|UI|ListView|Item")
		void OnListItemObjectReleased();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HorizonPlugin|UI|ListView|Item")
		void OnListItemObjectClicked();

#endif // button event

#if 1 // reroute button event for mouse
protected:
	UFUNCTION()
	virtual void OnListItemObjectButtonHovered();
	UFUNCTION()
	virtual void OnListItemObjectButtonUnhovered();
	UFUNCTION()
	virtual void OnListItemObjectButtonPressed();
	UFUNCTION()
	virtual void OnListItemObjectButtonReleased();
	UFUNCTION()
	virtual void OnListItemObjectButtonClicked();
#endif // reroute button event for mouse
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional), Category = "Content")
	UButton* Button_ClickArea = nullptr;


};
