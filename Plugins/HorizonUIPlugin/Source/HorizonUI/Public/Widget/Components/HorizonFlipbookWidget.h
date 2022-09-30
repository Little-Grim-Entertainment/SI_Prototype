// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#pragma once
#include "Widget/Components/HorizonImage.h"
#include "Components/Image.h"
#include "Tickable.h"
#include "HorizonFlipbookWidget.generated.h"
class UPaperFlipbookComponent;
class UPaperFlipbook;
UCLASS()
class HORIZONUI_API UHorizonFlipbookWidget :
	public UImage,
	public FTickableGameObject
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHorizonFlipbookEvent);
	DECLARE_MULTICAST_DELEGATE(FOnHorizonFlipbookEventNative);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHorizonFlipbookStartEvent, int32, InCurrentNumOfLoop);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHorizonFlipbookEventStartNative, int32);

	GENERATED_BODY()
public:


#if WITH_EDITOR
	//~ Begin UWidget Interface
	//#if (ENGINE_MAJOR_VERSION <= 4) && (ENGINE_MINOR_VERSION <= 12)
	//virtual const FSlateBrush* GetEditorIcon() override;
	//#endif
	virtual const FText GetPaletteCategory() override;


#endif

#if 1 // override
protected:
	//~ Begin UWidget Interface
	virtual void OnWidgetRebuilt() override;
	//~ End UWidget Interface

public://FTickableGameObject implement
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UHorizonFlipbookWidget, STATGROUP_Tickables); }
	virtual bool IsTickable() const override { return bIsStartTick && !bAnimationFinished; }
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickableInEditor() const override {return true;}

#endif // override

#if 1 // Functions
public:

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Flipbook|Appearance")
	void SetFlipbook(UPaperFlipbook* InFlipbook);

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Flipbook|Behavior")
	void ResetAnimation();
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Flipbook|Behavior")
	void PlayAnimation();
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Flipbook|Behavior")
	void StopAnimation();
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Flipbook|Behavior")
	void PauseAnimation();
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Flipbook|Behavior")
	void ResumeAnimation();
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Flipbook|Behavior")
	void SetCurrentAnimationDuration(float InDuration);
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Flipbook|Behavior")
	float GetCurrentAnimationDuration();
private:
	void SetCurrentImage(float currentDuration);

#endif // Functions
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HorizonPlugin|UI|Flipbook|Behavior")
	bool bIsStartTick = true;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HorizonPlugin|UI|Flipbook|Behavior")
	int32 NumOfLoop = 0;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HorizonPlugin|UI|Flipbook|Behavior")
	bool bAnimationFinished = false;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HorizonPlugin|UI|Flipbook|Brush", meta = (DisplayThumbnail = "true", DisplayName = "PaperFlipbook", AllowedClasses = "PaperFlipbook"))
	UPaperFlipbook* PaperFlipbook = nullptr;


	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Flipbook")
	FOnHorizonFlipbookStartEvent OnAnimationStart;
	FOnHorizonFlipbookEventStartNative OnAnimationStartNative;

	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|Flipbook")
	FOnHorizonFlipbookEvent OnAnimationFinished;
	FOnHorizonFlipbookEventNative OnAnimationFinishedNative;
private:
	float CurrentDuration = 0.0f;
	int32 CurrentNumOfLoop = 0;
	int32 CurrentSpriteIndex = -1;

};