// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#pragma once

// Engine
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/EngineBaseTypes.h"

// MovieScene
#include "MovieScene.h"

// UMG 
#include "Animation/WidgetAnimation.h"

// HorizonUI
#include "Widget/Components/HorizonDialogueMsgTextBlock.h"
#include "Widget/HorizonDialogueStyleInfo.h"
#include "HorizonWidgetFunctionLibrary.generated.h"


UENUM(BlueprintType)
enum class EHorizonUIInputMode : uint8
{
	Invalidated,
	GameAndUI,
	UIOnly,
	GameOnly
};




class UPaperFlipbook;
class UUserWidget;
UCLASS()
class HORIZONUI_API UHorizonWidgetFunctionLibrary : public UBlueprintFunctionLibrary {
private:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Library")
	static UCanvasPanelSlot* GetParentCanvasPanelSlot(UWidget* pWidget);


#if WITH_EDITOR
	//UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Library")
	static void RebuildFlipbook(const UPaperFlipbook* PaperFlipbook, 
			TArray<FVector2D>& OutSourceUV, 
			TArray<FVector2D>& OutSourceSize);
#endif //#if WITH_EDITOR


	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Library")
	static UWidgetAnimation* GetUserWidgetAnimation(UUserWidget* pUserWidget, 
		const FName& animeName);


	static UWidgetAnimation* GetUserWidgetAnimation(
		UWidgetBlueprintGeneratedClass* pBGClass,
		const FName& animeName);


	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Library")
	static UWidget* GetWidgetFromNameRecursively(UUserWidget* pUserWidget, const FName& InWidgetName);


	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Library")
	static UWidget* SetWidgetVisibility(UUserWidget* UserWidget, FName WidgetName, UPARAM(DisplayName = "SlateVisibility") ESlateVisibility eVisiblity);


	static int32 FindCharIndexFromStr(int32 startIndex, TCHAR aChar, const FString& str);
	static int32 FindCharIndexFromStr(int32 startIndex, const TArray<TCHAR>& charList, const FString& str);


	static FString NormalizeBlueprintClassFilePath(const FString& filePath);


	// check if InWidget is InUserWidget's child
	static bool IsChildWidget(UUserWidget* InUserWidget, const TSharedRef<SWidget>& InWidget);


	// check if InWidget contain InTargetWidgt in WidgetPath
	static bool ContainWidgetType(const TSharedRef<SWidget>& InWidget, const TSharedRef<SWidget>& InTargetWidgt, bool bIsSearchFromEnd = true);


	static bool ContainWidgetType(const FWidgetPath& InNewWidgetPath, const FName& InWidgetTypeName, bool bIsSearchFromEnd = true);

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Library")
	static EHorizonUIInputMode GetInputMode(const APlayerController* InPC);

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|Library")
	static void SetInputMode(APlayerController* InPC, 
			EHorizonUIInputMode InInputMode, UWidget* InWidgetToFocus = nullptr, 
			EMouseLockMode InMouseLockMode = EMouseLockMode::DoNotLock, bool bInHideCursorDuringCapture = true);


	UFUNCTION(BlueprintPure, Category = "HorizonPlugin|UI|Library")
	static int32 GetUserIndex(UWidget* InWidget);
};