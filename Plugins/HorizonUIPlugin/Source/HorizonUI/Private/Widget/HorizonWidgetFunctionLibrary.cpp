// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#include "Widget/HorizonWidgetFunctionLibrary.h"
#include "HorizonUIPrivate.h"
#include "Slate/SObjectWidget.h"

UCanvasPanelSlot* UHorizonWidgetFunctionLibrary::GetParentCanvasPanelSlot(UWidget* pWidget){
	UCanvasPanelSlot* pPanelSlot = nullptr;
	//try to find out UCanvasPanelSlot, search from current widget
	UWidget* pTargetWidget = pWidget;
	do {
		if (pTargetWidget) {
			pPanelSlot = Cast<UCanvasPanelSlot>(pTargetWidget->Slot);
		}
		if (pPanelSlot) {
			break;
		}
		else {
			if (pTargetWidget) {
				pTargetWidget = pTargetWidget->GetParent();
				//verifyf(pTargetWidget, TEXT("oops! something error"));
			}
			else {
				break;
			}
		}

	} while (pPanelSlot == nullptr && pTargetWidget != nullptr);


	return pPanelSlot;

}

#if WITH_EDITOR

void UHorizonWidgetFunctionLibrary::RebuildFlipbook(const UPaperFlipbook* PaperFlipbook, 
	TArray<FVector2D>& OutSourceUV, 
	TArray<FVector2D>& OutSourceSize)
{
	OutSourceUV.Empty();
	OutSourceSize.Empty();

	if (PaperFlipbook) {
		int32 numFrame = PaperFlipbook->GetNumFrames();
		int32 numKeyFrame = PaperFlipbook->GetNumKeyFrames();
		for (int32 i = 0; i < numKeyFrame; i++) {
			auto spriter = PaperFlipbook->GetSpriteAtFrame(i);
			if (spriter) {
				OutSourceUV.Emplace(spriter->GetSourceUV());
				OutSourceSize.Emplace(spriter->GetSourceSize());
	
			}

		}
	}
}
#endif //#if WITH_EDITOR


UWidgetAnimation* UHorizonWidgetFunctionLibrary::GetUserWidgetAnimation(UUserWidget* pUserWidget,
	const FName& animeName) 
{
	UWidgetBlueprintGeneratedClass* pBGClass = Cast<UWidgetBlueprintGeneratedClass>(pUserWidget->GetClass());
	return GetUserWidgetAnimation(pBGClass, animeName);
}

UWidgetAnimation* UHorizonWidgetFunctionLibrary::GetUserWidgetAnimation(
	UWidgetBlueprintGeneratedClass* pBGClass, 
	const FName& animeName) 
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonWidgetFunctionLibrary, GetUserWidgetAnimation)
	if (pBGClass) {
		for (UWidgetAnimation* Animation : pBGClass->Animations)
		{
			if (Animation->MovieScene)
			{
				if (animeName.IsEqual(Animation->MovieScene->GetFName())) {
					return Animation;
				}
			}
		}
	}
	return nullptr;

}

int32 UHorizonWidgetFunctionLibrary::FindCharIndexFromStr(int32 startIndex , TCHAR aChar, const FString& str)
{
	TArray<TCHAR> CharList;
	CharList.Emplace(aChar);
	int32 result = UHorizonWidgetFunctionLibrary::FindCharIndexFromStr(startIndex, CharList, str);


	return result;

}


int32 UHorizonWidgetFunctionLibrary::FindCharIndexFromStr(int32 startIndex, const TArray<TCHAR>& charList, const FString& str)
{
	int32 result = str.Len();
	int32 currentIndex = startIndex;
	while (currentIndex < str.Len()) {
		TCHAR currentChar = str[currentIndex];
		
		if(charList.Contains(currentChar))
		{
			result = currentIndex;
			break;
		}
	
		++currentIndex;
	};


	return result;

}


FString UHorizonWidgetFunctionLibrary::NormalizeBlueprintClassFilePath(const FString& filePath)
{
	FString result = filePath;
	//Blueprint'/Game/UMG/DialogueMsgTextTest/ButtonStyle/BP_DialogueBackgroundButtonStyle1.BP_DialogueBackgroundButtonStyle1'
	int32 lastFindCharIndex = -1;
	result.FindChar('\'', lastFindCharIndex);
	if (lastFindCharIndex != -1)
	{
		result = UKismetStringLibrary::GetSubstring(result, lastFindCharIndex + 1, filePath.Len() - lastFindCharIndex);
	}
	
	result = result.Replace(TEXT("'"), TEXT(""));


	result.FindLastChar('/', lastFindCharIndex);
	if (lastFindCharIndex != -1)
	{
		auto folderPath = UKismetStringLibrary::GetSubstring(result, 0, lastFindCharIndex + 1);
		auto fileName = UKismetStringLibrary::GetSubstring(result, lastFindCharIndex + 1, filePath.Len() - lastFindCharIndex);
		auto bIsClassSuffix = UKismetStringLibrary::GetSubstring(fileName, fileName.Len() - 2, 2) == TEXT("_C");
		if (bIsClassSuffix)
		{
			fileName = UKismetStringLibrary::GetSubstring(fileName, 0, fileName.Len() - 2);
		}

		fileName.FindLastChar('.', lastFindCharIndex);
		if (lastFindCharIndex == -1)
		{
			fileName = FString::Printf(TEXT("%s.%s"), *fileName, *fileName);
		}



		result = FString::Printf(TEXT("%s%s_C"), *folderPath, *fileName);
	}

	return result;

}





bool UHorizonWidgetFunctionLibrary::IsChildWidget(UUserWidget* InUserWidget, const TSharedRef<SWidget>& InWidget)
{
	bool bResult = false;
	if (InUserWidget && InUserWidget->GetCachedWidget())
	{
		TSharedPtr<SWidget> userWidgetPtr = InUserWidget->GetCachedWidget();
		auto widgetPtr = InWidget->GetParentWidget();
		while (widgetPtr.IsValid())
		{
			if (widgetPtr->GetType() == userWidgetPtr->GetType())
			{
				TSharedPtr<SObjectWidget> objectWidgetPtr = StaticCastSharedPtr<SObjectWidget>(widgetPtr);
				if (objectWidgetPtr.IsValid() && objectWidgetPtr->GetWidgetObject())
				{
					if (objectWidgetPtr->GetWidgetObject()->GetName() == InUserWidget->GetName())
					{
						UE_HORIZONUI_VERBOSE("%s : %s",
							*objectWidgetPtr->GetWidgetObject()->GetName(),
							*InUserWidget->GetName());
						bResult = true;
						break;
					}
				}
			}

			widgetPtr = widgetPtr->GetParentWidget();
		}
	}

	return bResult;
}

bool UHorizonWidgetFunctionLibrary::ContainWidgetType(const TSharedRef<SWidget>& InWidget, const TSharedRef<SWidget>& InTargetWidgt, bool bIsSearchFromEnd /*= true*/)
{
	FWidgetPath widgetPath;
	FSlateApplication::Get().GeneratePathToWidgetChecked(InWidget, widgetPath);

	return ContainWidgetType(widgetPath, InTargetWidgt->GetType(), bIsSearchFromEnd);
}

bool UHorizonWidgetFunctionLibrary::ContainWidgetType(
	const FWidgetPath& InNewWidgetPath, 
	const FName& InWidgetTypeName, 
	bool bIsSearchFromEnd)
{
	bool bResult = false;

	if (bIsSearchFromEnd)
	{
		for (int32 widgetIndex = InNewWidgetPath.Widgets.Num() - 1; widgetIndex >= 0 ; --widgetIndex)
		{
			if (InNewWidgetPath.Widgets[widgetIndex].Widget->GetType() == InWidgetTypeName)
			{
				bResult = true;
				break;
			}
		}
	}
	else
	{
		for (int32 widgetIndex = 0; widgetIndex < InNewWidgetPath.Widgets.Num(); ++widgetIndex)
		{
			if (InNewWidgetPath.Widgets[widgetIndex].Widget->GetType() == InWidgetTypeName)
			{
				bResult = true;
				break;
			}
		}
	}




	return bResult;
}


UWidget* UHorizonWidgetFunctionLibrary::GetWidgetFromNameRecursively(UUserWidget* pUserWidget, const FName& InWidgetName)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonWidgetFunctionLibrary, GetWidgetFromNameRecursively)
	UWidget* pResult = nullptr;
	if (pUserWidget && pUserWidget->WidgetTree)
	{
		pUserWidget->WidgetTree->ForEachWidget(
			[&](UWidget* InWidget)
		{
			if (InWidget->GetFName() == InWidgetName)
			{
				pResult = InWidget;
			}

			if (nullptr == pResult)
			{
				auto pChildUserWidget = Cast<UUserWidget>(InWidget);
				if (pChildUserWidget)
				{
					pResult = GetWidgetFromNameRecursively(pChildUserWidget, InWidgetName);
				}
			}
		});

	}
	return pResult;
}


UWidget* UHorizonWidgetFunctionLibrary::SetWidgetVisibility(
	UUserWidget* UserWidget,
	FName WidgetName, ESlateVisibility SlateVisiblity)
{
	auto pWidget = GetWidgetFromNameRecursively(UserWidget, WidgetName);
	if (pWidget)
	{
		pWidget->SetVisibility(SlateVisiblity);
	}
	else
	{
		if (UserWidget)
		{
			ensureMsgf(false, TEXT("%s can't find Widget: %s"), *UserWidget->GetName(), *WidgetName.ToString());
		}
	}

	return pWidget;
}


EHorizonUIInputMode UHorizonWidgetFunctionLibrary::GetInputMode(const APlayerController* InPC)
{

	if (IsValid(InPC))
	{
		UGameViewportClient* pGameViewportClient = InPC->GetWorld()->GetGameViewport();
		 
		bool bIgnore = pGameViewportClient->IgnoreInput();
		EMouseCaptureMode eCapt = pGameViewportClient->GetMouseCaptureMode();

		if (bIgnore == false && eCapt == EMouseCaptureMode::CaptureDuringMouseDown)
		{
			return EHorizonUIInputMode::GameAndUI;
		}
		else if (bIgnore == true && eCapt == EMouseCaptureMode::NoCapture)
		{
			return EHorizonUIInputMode::UIOnly;
		}
		else
		{
			return EHorizonUIInputMode::GameOnly;
		}
	}

	return EHorizonUIInputMode::Invalidated;

}

void UHorizonWidgetFunctionLibrary::SetInputMode(APlayerController* InPC, 
			EHorizonUIInputMode InInputMode, UWidget* InWidgetToFocus /*= nullptr*/,
			EMouseLockMode InMouseLockMode /*= EMouseLockMode::DoNotLock*/, bool bInHideCursorDuringCapture)
{
	if (InPC)
	{
		switch (InInputMode)
		{
		case EHorizonUIInputMode::Invalidated:
			break;
		case EHorizonUIInputMode::GameAndUI:
		{
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(InPC, InWidgetToFocus, 
												InMouseLockMode, bInHideCursorDuringCapture);
		}
			break;
		case EHorizonUIInputMode::UIOnly:
		{
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(InPC, InWidgetToFocus, InMouseLockMode);
		}
		break;
		case EHorizonUIInputMode::GameOnly:
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(InPC);
			break;
		}

	}
}


int32 UHorizonWidgetFunctionLibrary::GetUserIndex(UWidget* InWidget)
{
	int32 userIndex = -1;

	if (InWidget)
	{
		auto pOwningPlayer = InWidget->GetOwningPlayer();
		if (pOwningPlayer)
		{
			auto pLocalPlayer = pOwningPlayer->GetLocalPlayer();
			if (pLocalPlayer)
			{
				userIndex = FSlateApplication::Get().GetUserIndexForController(pLocalPlayer->GetControllerId());
			}
		}
	}
	return userIndex;
}
