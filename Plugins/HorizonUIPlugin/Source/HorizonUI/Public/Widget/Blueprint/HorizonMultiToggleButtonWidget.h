// Created by horizon-studio, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widget/Blueprint/HorizonDesignableUserWidget.h"
#include "HorizonMultiToggleButtonWidget.generated.h"


class UButton;
class UTextBlock;
class UImage;

USTRUCT(BlueprintType)
struct HORIZONUI_API FHorizonMultiToggleButtonState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
	FLinearColor TextColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
	FSlateBrush Brush;
};

/**
 * Multi Option Toggle Button
 */
UCLASS()
class HORIZONUI_API UHorizonMultiToggleButtonWidget : public UHorizonDesignableUserWidget
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHorizonMultiToggleButtonSyncEvent, int32, InCurrentStateIndex);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHorizonMultiToggleButtonSyncEventNative, int32);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHorizonMultiToggleButtonEvent, int32, InCurrentStateIndex, int32, InToStateIndex);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHorizonMultiToggleButtonEventNative, int32, int32);
public:
	UHorizonMultiToggleButtonWidget();
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void OnSynchronizeProperties_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|MultiToggleButton")
	virtual void ToggleState_Prev();
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|MultiToggleButton")
	virtual void ToggleState_Next();


	UFUNCTION(BlueprintSetter)
	virtual void SetCurrentStateIndex(int32 InStateIndex);

	UFUNCTION(BlueprintGetter)
	virtual int32 GetCurrentStateIndex(){return CurrentStateIndex;};


	UFUNCTION(BlueprintSetter)
	virtual void SetLoopToggleState(bool InLoopToggleState){ bLoopToggleState = InLoopToggleState;};

	UFUNCTION(BlueprintGetter)
	virtual bool GetLoopToggleState() { return bLoopToggleState; };


	UFUNCTION(BlueprintPure, Category = "HorizonPlugin|UI|MultiToggleButton")
	virtual int32 GetToggleState_PrevIndex();

	UFUNCTION(BlueprintPure, Category = "HorizonPlugin|UI|MultiToggleButton")
	virtual int32 GetToggleState_NextIndex();


	virtual FHorizonMultiToggleButtonState& GetState(int32 InStateIndex);
public:

	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
	FOnHorizonMultiToggleButtonSyncEvent OnStateSyncDelegate;

	// for c++ callback binding
	FOnHorizonMultiToggleButtonSyncEventNative OnStateSyncDelegateNative;

	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Delegate")
	FOnHorizonMultiToggleButtonEvent OnStateChangedDelegate;

	// for c++ callback binding
	FOnHorizonMultiToggleButtonEventNative OnStateChangedDelegateNative;

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "UI")
	UButton* Button_ToggleState_Prev = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "UI")
	UButton* Button_ToggleState_Next = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "UI")
	UTextBlock* TextBlock_CurrentState = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "UI")
	UImage* Image_CurrentState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
	TArray<FHorizonMultiToggleButtonState> StateList;

private:
	// LoopState when ToggleState
	UPROPERTY(EditAnywhere, BlueprintSetter=SetLoopToggleState, BlueprintGetter=GetLoopToggleState, Category = "Content")
	bool bLoopToggleState = false;

	UPROPERTY(EditAnywhere, BlueprintSetter=SetCurrentStateIndex, BlueprintGetter=GetCurrentStateIndex, Category = "Content")
	int32 CurrentStateIndex = -1;
};
