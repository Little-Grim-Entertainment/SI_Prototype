// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#include "Widget/Components/HorizonDialogueMsgTextBlock.h"
#include "HorizonUIPrivate.h"
#include "FileSystem/HorizonFileSystem.h"
#include "Widget/HorizonWidgetFunctionLibrary.h"
#include "Widget/Components/HorizonTextBlock.h"
#include "Widget/Components/HorizonButton.h"
#include "Widget/Components/HorizonFlipbookWidget.h"
#include "Decorator/HorizonDialogueMsgDecorator.h"

//// UnrealEd
//#if WITH_EDITOR
//#include "FileHelpers.h"
//#endif




//
//#if WITH_EDITOR
//#include "Editor/Transactor.h"
//#endif
#define LOCTEXT_NAMESPACE "UMG"

/////////////////////////////////////////////////////


namespace horizonui
{
	static bool ApplySegmentStyle(FHorizonDialogueSegmentInfo& segParam,
		const FString& segName,
		const TArray<FHorizonDialogueSegmentInfoStyle>& segmentStyleList)
	{
		bool bStyleFound = false;
		for (int32 i = 0; i < segmentStyleList.Num(); ++i) {
			const auto& it = segmentStyleList[i];
			if (segName == it.StyleName.ToString()) {
				segParam.SegmentStyleReferenceIndex = i;
				bStyleFound = true;
				if (it.ColorAndOpacity.Num() > 0) {
					segParam.ColorAndOpacity = it.ColorAndOpacity.Last();
				}

				if (it.DialogueMsgSpeed.Num() > 0) {
					segParam.DialogueMsgSpeed = it.DialogueMsgSpeed.Last();
				}
				if (it.DialogueMsgWait.Num() > 0) {
					segParam.DialogueMsgWait = it.DialogueMsgWait.Last();
				}
				if (it.ShadowOffset.Num() > 0) {
					segParam.ShadowOffset = it.ShadowOffset.Last();
				}

				if (it.ShadowColorAndOpacity.Num() > 0) {
					segParam.ShadowColorAndOpacity = it.ShadowColorAndOpacity.Last();
				}
				if (it.Font.Num() > 0) {
					segParam.Font = it.Font.Last();
				}

				if (it.FontSize.Num() > 0) {
					segParam.Font.Size = it.FontSize.Last();
				}
				if (it.TypefaceFontName.Num() > 0) {
					segParam.Font.TypefaceFontName = it.TypefaceFontName.Last();
				}

				if (it.PaddingMargin.Num() > 0) {
					segParam.PaddingMargin = it.PaddingMargin.Last();
				}

				if (it.ImageSize.Num() > 0) {
					segParam.ImageSize = it.ImageSize.Last();
				}

				if (it.HypertextReference.Num() > 0) {
					segParam.HypertextReference = it.HypertextReference.Last();
				}

				if (it.HypertextHoveredColor.Num() > 0) {
					segParam.HypertextHoveredColor = it.HypertextHoveredColor.Last();
				}

				if (it.HypertextVisitedColor.Num() > 0) {
					segParam.HypertextVisitedColor = it.HypertextVisitedColor.Last();
				}

				if (it.BackgroundButtonClass.Num() > 0) {
					segParam.BackgroundButtonClass = it.BackgroundButtonClass.Last();
				}

				if (it.DialogueSoundVolumeMultiplier.Num() > 0) {
					segParam.DialogueSoundVolumeMultiplier = it.DialogueSoundVolumeMultiplier.Last();
				}
				if (it.DialogueSoundPitchMultiplier.Num() > 0) {
					segParam.DialogueSoundPitchMultiplier = it.DialogueSoundPitchMultiplier.Last();
				}
				if (it.DialogueSoundStartTime.Num() > 0) {
					segParam.DialogueSoundStartTime = it.DialogueSoundStartTime.Last();
				}

				if (it.RubyTextStyleInfo.Text.Num() > 0)
				{
					segParam.RubyTextInfo.Text = it.RubyTextStyleInfo.Text.Last();
				}
				if(it.RubyTextStyleInfo.ColorAndOpacity.Num() > 0)
				{
					segParam.RubyTextInfo.ColorAndOpacity = it.RubyTextStyleInfo.ColorAndOpacity.Last();
				}
				if (it.RubyTextStyleInfo.Font.Num() > 0)
				{
					segParam.RubyTextInfo.Font = it.RubyTextStyleInfo.Font.Last();
				}
				if (it.RubyTextStyleInfo.ShadowOffset.Num() > 0)
				{
					segParam.RubyTextInfo.ShadowOffset = it.RubyTextStyleInfo.ShadowOffset.Last();
				}
				if (it.RubyTextStyleInfo.ShadowColorAndOpacity.Num() > 0)
				{
					segParam.RubyTextInfo.ShadowColorAndOpacity = it.RubyTextStyleInfo.ShadowColorAndOpacity.Last();
				}
				if (it.RubyTextStyleInfo.PaddingMargin.Num() > 0)
				{
					segParam.RubyTextInfo.PaddingMargin = it.RubyTextStyleInfo.PaddingMargin.Last();
				}
				break;
			}
		}
		return bStyleFound;
	}



	//template<class T>
	//struct FClassFinderOptional : public FGCObject
	//{
	//	TSubclassOf<T> Class;
	//	FClassFinderOptional(const TCHAR* ClassToFind)
	//	{
	//		//ConstructorHelpers::CheckIfIsInConstructor(ClassToFind);
	//		FString PathName(ClassToFind);
	//		ConstructorHelpers::StripObjectClass(PathName, true);
	//		// If there is no dot, add ".<object_name>_C"
	//		int32 PackageDelimPos = INDEX_NONE;
	//		PathName.FindChar(TCHAR('.'), PackageDelimPos);
	//		if (PackageDelimPos == INDEX_NONE)
	//		{
	//			int32 ObjectNameStart = INDEX_NONE;
	//			PathName.FindLastChar(TCHAR('/'), ObjectNameStart);
	//			if (ObjectNameStart != INDEX_NONE)
	//			{
	//				const FString ObjectName = PathName.Mid(ObjectNameStart + 1);
	//				PathName += TCHAR('.');
	//				PathName += ObjectName;
	//				PathName += TCHAR('_');
	//				PathName += TCHAR('C');
	//			}
	//		}
	//		Class = LoadClass<T>(NULL, *PathName);
	//		if (Class)
	//		{
	//			Class->AddToRoot();
	//		}
	//		//Class = ConstructorHelpersInternal::FindOrLoadClass(PathName, T::StaticClass());
	//		//ValidateObject(*Class, PathName, *PathName);
	//	}
	//	bool Succeeded()
	//	{
	//		return !!*Class;
	//	}

	//	virtual void AddReferencedObjects(FReferenceCollector& Collector) override
	//	{
	//		UClass* ReferencedClass = Class.Get();
	//		Collector.AddReferencedObject(ReferencedClass);
	//		Class = ReferencedClass;
	//	}

	//	virtual FString GetReferencerName() const override
	//	{
	//		return TEXT("FClassFinder");
	//	}
	//};

};


UHorizonDialogueMsgTextBlock::UHorizonDialogueMsgTextBlock()
{
	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(TEXT("/Engine/EngineFonts/Roboto"));
		Font = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Bold"));

		//if (nullptr == DefaultButtonStyleWidgetClass)
		//{
		//	static horizonui::FClassFinderOptional<UHorizonButton> DefaultButtonStyleWidgetFinder(TEXT("/HorizonUIPlugin/Widget/Component/DefaultButtonStyleWidget"));
		//	DefaultButtonStyleWidgetClass = DefaultButtonStyleWidgetFinder.Class;
		//}
		//if (nullptr == DefaultButtonStyleWidgetClass)
		//{
		//	static horizonui::FClassFinderOptional<UHorizonButton> DefaultButtonStyleWidgetFinder(TEXT("/HorizonDialoguePlugin/Widget/Component/DefaultButtonStyleWidget"));
		//	DefaultButtonStyleWidgetClass = DefaultButtonStyleWidgetFinder.Class;
		//}



	}

}




void UHorizonDialogueMsgTextBlock::PostLoad()
{
	Super::PostLoad();
	if (EHorizonDialogueTextOverflowWarpMethod_DEPRECATED::Invalidated != TextOverFlowWarpMethod_DEPRECATED)
	{
		TextOverFlowWrapMethod = (EHorizonDialogueTextOverflowWrapMethod)TextOverFlowWarpMethod_DEPRECATED;
		TextOverFlowWarpMethod_DEPRECATED = EHorizonDialogueTextOverflowWarpMethod_DEPRECATED::Invalidated;
#if WITH_EDITOR

		UPackage* pPackage = GetPackage();
		if (pPackage)
		{
			pPackage->SetDirtyFlag(true);
			FString msg = FString::Printf(TEXT("Please Resave %s for TextOverFlowWarpMethod_DEPRECATED, or It will not work in future release"), *pPackage->GetPathName());
			UE_HORIZONUI_WARNING("%s", *msg);
			ensureMsgf(false, TEXT("%s"), *msg);
			FMessageLog("HorizonUI").Warning(FText::FromString(msg));
			//FMessageLog("HorizonUI").Notify(FText::FromString(msg));
		}

#endif
	}
}

#if 1  //============================Begin Widget override=============================

void UHorizonDialogueMsgTextBlock::SynchronizeProperties()
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, SynchronizeProperties);
	Super::SynchronizeProperties();
	SetText(Text);
	SetColorAndOpacity(ColorAndOpacity);
	SetShadowColorAndOpacity(ShadowColorAndOpacity);
	SetShadowOffset(ShadowOffset);
	SetFont(Font);
	SetIsDialogueMsgText(bIsDialogueMsgText);
	SetIsStartTickDialogueMsg(bIsStartTickDialogueMsg);
	SetIsRepeatDialogueMsg(bIsRepeatDialogueMsg);
	SetDialogueMsgSpeed(DialogueMsgSpeed);
	SetIsRichText(bIsRichText);
	SetJustification(Justification);
	if (bIsRichText) {
		//OnWidgetRebuilt();
	}
}
void UHorizonDialogueMsgTextBlock::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	//MyTextBlock.Reset();
}



TSharedRef<SWidget> UHorizonDialogueMsgTextBlock::RebuildWidget() 
{

	return Super::RebuildWidget();
}
void UHorizonDialogueMsgTextBlock::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	
	if (!bCreationFromPalette) {

		bNeedRebuildDialogueMsgText = true;
	}
	else {
		bCreationFromPalette = false;
	}


	//GetWorld()->ForceGarbageCollection(true);
}
void UHorizonDialogueMsgTextBlock::OnBindingChanged(const FName& Property)
{
	Super::OnBindingChanged(Property);
}
#endif //============================End Widget override=============================




#if WITH_EDITOR

FString UHorizonDialogueMsgTextBlock::GetLabelMetadata() const
{
	const int32 MaxSampleLength = 15;

	FString TextStr = Text.ToString();
	TextStr = TextStr.Len() <= MaxSampleLength ? TextStr : TextStr.Left(MaxSampleLength - 2) + TEXT("..");
	return TEXT(" \"") + TextStr + TEXT("\"");
}

void UHorizonDialogueMsgTextBlock::HandleTextCommitted(const FText& InText, ETextCommit::Type CommitteType)
{
	//TODO UMG How will this migrate to the template?  Seems to me we need the previews to have access to their templates!
	//TODO UMG How will the user click the editable area?  There is an overlay blocking input so that other widgets don't get them.
	//     Need a way to recognize one particular widget and forward things to them!
}


//#if (ENGINE_MAJOR_VERSION <= 4) && (ENGINE_MINOR_VERSION <= 12)
/*const FSlateBrush* UHorizonDialogueMsgTextBlock::GetEditorIcon()
{
	return FUMGStyle::Get().GetBrush("Widget.TextBlock");
}*/
//#endif //#if (ENGINE_MAJOR_VERSION <= 4) && (ENGINE_MINOR_VERSION <= 12)

const FText UHorizonDialogueMsgTextBlock::GetPaletteCategory()
{
	return NSLOCTEXT("HorizonPlugin", "HorizonPlugin", "HorizonPlugin");
}

void UHorizonDialogueMsgTextBlock::OnCreationFromPalette()
{
	Text = FText::FromString("Dialogue Text Block");
	//UE_HRIZONLOG_LOG("");
	bCreationFromPalette = true;
}


void UHorizonDialogueMsgTextBlock::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {

	if (PropertyChangedEvent.Property)
	{
		auto nameCPP = PropertyChangedEvent.Property->GetNameCPP();
		// FIX crash
		if (nameCPP != GET_MEMBER_NAME_CHECKED(UHorizonDialogueMsgTextBlock, SegmentStyleList).ToString() &&
			nameCPP != TEXT("SpecifiedColor"))
		{
			Super::PostEditChangeProperty(PropertyChangedEvent);
		}
	}

	//


}

void UHorizonDialogueMsgTextBlock::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	//auto pHeadNode = PropertyChangedEvent.PropertyChain.GetHead();
	//if (pHeadNode)
	//{
	//	auto pHead = pHeadNode->GetValue();
	//	//auto propertyCppType = pHead->GetCPPType();
	//	//auto prevNode = PropertyChangedEvent.PropertyChain.GetTail()->GetPrevNode();
	//	auto nameCPP = pHead->GetNameCPP();
	//	//auto fieldCppType = TEXT("F") + FHorizonDialogueSegmentInfoStyle::StaticStruct()->GetName();
	//	if (nameCPP == GET_MEMBER_NAME_CHECKED(UHorizonDialogueMsgTextBlock, SegmentStyleList).ToString())
	//	{
	//		auto pStructList = pHead->ContainerPtrToValuePtr<TArray<FHorizonDialogueSegmentInfoStyle>>(this);
	//		FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	//		if (PropertyName == GET_MEMBER_NAME_CHECKED(FHorizonDialogueSegmentInfoStyle, PaperFlipbook))
	//		{
	//			// rebuild sourceUV and sourceSize for HorizonFlipbookWidget
	//			for (int32 i = 0; i < pStructList->Num(); i++) {
	//				auto& pStruct = (*pStructList)[i];
	//				UHorizonWidgetFunctionLibrary::RebuildFlipbook(pStruct.PaperFlipbook.LoadSynchronous(), pStruct.PaperFlipbookSourceUV, pStruct.PaperFlipbookSourceSize);
	//			}

	//		}
	//	}
	//}
}


#endif //#if WITH_EDITOR


#if 1  //============================Begin Tick=============================
bool UHorizonDialogueMsgTextBlock::IsTickable() const
{
	return (bIsStartTickDialogueMsg || bNeedRebuildDialogueMsgText) && MyCanvas.IsValid();
}



void UHorizonDialogueMsgTextBlock::Tick(float DeltaTime) {

	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, Tick)
	if (false == bIgnoreTimeDilation)
	{
		auto pWorld = GetWorld();
		if (pWorld)
		{
			auto pWorldSettings = pWorld->GetWorldSettings();

			if (pWorldSettings)
			{
				DeltaTime = DeltaTime * CustomTimeDilation * pWorldSettings->GetEffectiveTimeDilation();
			}
		}
	}

	if (bNeedRebuildDialogueMsgText)
	{
		auto geometry = GetCachedGeometry();
		if (geometry.Size.X > 0 || bForceRebuildDialogueMsgText)
		{
			bNeedRebuildDialogueMsgText = false;
			RebuildDialogueMsgTextBlock();
			OnRebuildDialogueDelegate.Broadcast();
			OnRebuildDialogueDelegateNative.Broadcast();
		}
		return;
	}




	if (CurrentPageIndex < DialoguePageInfoList.Num() && DialoguePageInfoList.Num() > 0)
	{

		auto currentPageInfo = DialoguePageInfoList[CurrentPageIndex];
		if (CurrentDialogueLineIndex < currentPageInfo.EndLineIndex)
		{
			FHorizonDialogueLineInfo& lineInfo = DialogueLineInfoList[CurrentDialogueLineIndex];
			if (lineInfo.CurrentDialogueBlockIndex < lineInfo.DialogueBlockInfoList.Num()) {
				FHorizonDialogueBlockInfo& blockInfo = lineInfo.DialogueBlockInfoList[lineInfo.CurrentDialogueBlockIndex];
				FHorizonDialogueSegmentInfo& segInfo = DialogueSegmentInfoList[blockInfo.SegmentReferenceIndex];
				
				if (segInfo.CurrentMsgWaitTime >= segInfo.DialogueMsgWait)
				{	
					MsgDeltaTime += DeltaTime;
					switch (segInfo.TypeEnum) {
					case EHorizonDialogueSegmentType::Text:
					{
						TriggerPlaySound(segInfo);
						TriggerCustomEventCallback(segInfo);

						if (blockInfo.CurrentCharIndex < blockInfo.MsgText.Len()) {

							if(segInfo.DialogueMsgSpeed >= 0)
							{ 
								if (MsgDeltaTime >= segInfo.DialogueMsgSpeed) {
									int32 numWord = FMath::FloorToInt(MsgDeltaTime / segInfo.DialogueMsgSpeed);
									blockInfo.CurrentCharIndex += numWord;
									auto subStr = blockInfo.MsgText.Mid(0, blockInfo.CurrentCharIndex);

									if (blockInfo.WidgetWeakPtr.IsValid() && blockInfo.WidgetWeakPtr->IsA<UHorizonTextBlock>())
									{
										auto pTextBlock = Cast<UHorizonTextBlock>(blockInfo.WidgetWeakPtr.Get());
										pTextBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
										pTextBlock->SetText(FText::FromString(subStr));
										OnCharAdvancedDelegate.Broadcast(blockInfo);
										OnCharAdvancedDelegateNative.Broadcast(blockInfo);
									}
									MsgDeltaTime = 0.0f;
								}
							}
							else
							{
								SkipCurrentDialoguePage();
								MsgDeltaTime = 0.0f;
							}
						}
						//advanced blockIndex
						if (blockInfo.CurrentCharIndex >= blockInfo.MsgText.Len()) 
						{
							if(blockInfo.RubyTextWeakPtr.IsValid())
							{
								blockInfo.RubyTextWeakPtr->SetText(FText::FromString(blockInfo.RubyText));
								blockInfo.RubyTextWeakPtr->SetVisibility(ESlateVisibility::HitTestInvisible);
							}
							++lineInfo.CurrentDialogueBlockIndex;
						}

					}
					break;
					case EHorizonDialogueSegmentType::Image:
					case EHorizonDialogueSegmentType::PaperFlipbook:
					case EHorizonDialogueSegmentType::Material:
					{
						if (blockInfo.WidgetWeakPtr.IsValid()) {
							blockInfo.WidgetWeakPtr->SetVisibility(ESlateVisibility::HitTestInvisible);
						}

						TriggerPlaySound(segInfo);
						TriggerCustomEventCallback(segInfo);
						OnCharAdvancedDelegate.Broadcast(blockInfo);
						OnCharAdvancedDelegateNative.Broadcast(blockInfo);
						MsgDeltaTime = 0.0f;
						++lineInfo.CurrentDialogueBlockIndex;
					}
					break;
					case EHorizonDialogueSegmentType::HyperText:
					{
						MsgDeltaTime = 0.0f;
						OnCharAdvancedDelegate.Broadcast(blockInfo);
						OnCharAdvancedDelegateNative.Broadcast(blockInfo);
						++lineInfo.CurrentDialogueBlockIndex;

					}
					break;
					}


					UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(blockInfo.WidgetWeakPtr->Slot);
					auto currentPosition = canvasPanelSlot->GetPosition();
					if (CurrentPageIndex > 0)
					{
						float paddingMarginTop = DialogueSegmentInfoList[blockInfo.SegmentReferenceIndex].PaddingMargin.Top;
						currentPosition.Y = lineInfo.Position.Y - CurrentPageHeightOffset + paddingMarginTop;
					}
#if !UE_BUILD_SHIPPING
					//Debug auto page position
					if (currentPageInfo.StartLineIndex == CurrentDialogueLineIndex)
					{
						UE_HORIZONUI_VERBOSE("page %d, line: %d, %f", CurrentPageIndex, CurrentDialogueLineIndex, currentPosition.Y);
					}
#endif
					canvasPanelSlot->SetPosition(currentPosition);
					if (blockInfo.WidgetBackgroundWeakPtr.IsValid())
					{
						blockInfo.WidgetBackgroundWeakPtr->SetVisibility(ESlateVisibility::Visible);
						UCanvasPanelSlot* buttonCanvasPanelSlot = Cast<UCanvasPanelSlot>(blockInfo.WidgetBackgroundWeakPtr->Slot);
						if (buttonCanvasPanelSlot)
						{
							buttonCanvasPanelSlot->SetPosition(currentPosition);
						}
					}

					if (blockInfo.RubyTextWeakPtr.IsValid())
					{
						SetupRubyTextPosition(currentPosition, blockInfo, segInfo);
		
					}
				}
				else
				{
					segInfo.CurrentMsgWaitTime += DeltaTime;
				}
			}




			//add line index if all Dialogue block shown
			if (lineInfo.CurrentDialogueBlockIndex >= lineInfo.DialogueBlockInfoList.Num())
			{
				CurrentDialogueLineIndex++;
			}
		}
		else
		{
			bool bIsDialogueMsgComplete = false;
			if (FMath::IsNearlyZero(AutoNextDialogueMsgPageDeltaTime))
			{
				FHorizonDialogueDialoguePageResult result;
				result.PageIndex = CurrentPageIndex;
				OnDialoguePageEndFunction.Broadcast(result);
				OnDialoguePageEndFunctionNative.Broadcast(result);
				
				// if this is last page and not repeating, 
				// then stop tick and trigger OnDialogueMsgCompleteFunction
				if (!bIsRepeatDialogueMsg)
				{
					int32 newPage = CurrentPageIndex + 1;
					if (newPage >= DialoguePageInfoList.Num())
					{
						bIsDialogueMsgComplete = true;
						SetIsStartTickDialogueMsg(false, false);
						OnDialogueMsgCompleteFunction.Broadcast();
						OnDialogueMsgCompleteFunctionNative.Broadcast();
					}
				}
			}
			if (!bIsDialogueMsgComplete)
			{
				if (bIsAutoNextDialogueMsgPage && CurrentDialogueLineIndex < DialogueLineInfoList.Num())
				{
					AutoNextDialogueMsgPageDeltaTime += DeltaTime;
					if (AutoNextDialogueMsgPageDeltaTime >= AutoNextDialogueMsgPageInterval)
					{
						AutoNextDialogueMsgPageDeltaTime = 0.0f;

						NextDialogueMsgPage();
					}
					
				}
				else
				{
					// Set to a small number, 
					// So OnDialoguePageFinishedFunction will not trigger multiple time
					AutoNextDialogueMsgPageDeltaTime = 0.01f;
					TickRepeatDialogue(DeltaTime);
				}
			}



		}
	}
	else
	{
		ensureMsgf(false, TEXT("oops! something error"));
		TickRepeatDialogue(DeltaTime);
	}
}



void UHorizonDialogueMsgTextBlock::TickRepeatDialogue(float DeltaTime)
{
	if (CurrentDialogueLineIndex >= DialogueLineInfoList.Num())
	{
		if (bIsRepeatDialogueMsg) 
		{
			RepeatDialogueMsgDeltaTime += DeltaTime;
			if (RepeatDialogueMsgDeltaTime >= RepeatDialogueMsgInterval) 
			{
				SetIsStartTickDialogueMsg(true, true);
				OnDialogueMsgLoopFunction.Broadcast();
				OnDialogueMsgLoopFunctionNative.Broadcast();
				RepeatDialogueMsgDeltaTime = 0.0f;
			}
		}
		else 
		{
			SetIsStartTickDialogueMsg(false, false);
			OnDialogueMsgCompleteFunction.Broadcast();
			OnDialogueMsgCompleteFunctionNative.Broadcast();

		}
	}
}
#endif //============================End Tick=============================


#if 1 //============================Begin DialogueText Method=============================
void UHorizonDialogueMsgTextBlock::SetColorAndOpacity(FSlateColor InColorAndOpacity)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, SetColorAndOpacity)
	ColorAndOpacity = InColorAndOpacity;
	if (bIsRichText) {
		//RebuildWidget();
	}
	else {
		for (auto& lineInfoIt : DialogueLineInfoList) {
			for (auto& blockInfo : lineInfoIt.DialogueBlockInfoList) {

				if (blockInfo.WidgetWeakPtr.IsValid() && blockInfo.WidgetWeakPtr->IsA<UHorizonTextBlock>()) {
					auto pTextBlock = Cast<UHorizonTextBlock>(blockInfo.WidgetWeakPtr.Get());
					pTextBlock->SetColorAndOpacity(ColorAndOpacity);
				}
			}
		}
	}

}

void UHorizonDialogueMsgTextBlock::SetOpacity(float InOpacity)
{
	FLinearColor CurrentColor = ColorAndOpacity.GetSpecifiedColor();
	CurrentColor.A = InOpacity;

	SetColorAndOpacity(FSlateColor(CurrentColor));
}

void UHorizonDialogueMsgTextBlock::SetShadowColorAndOpacity(FLinearColor InShadowColorAndOpacity, bool bForce /*= false*/ )
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, SetShadowColorAndOpacity)
	ShadowColorAndOpacity = InShadowColorAndOpacity;
	if (!bIsRichText || bForce) 
	{
		for (auto& lineInfoIt : DialogueLineInfoList) {
			for (auto& blockInfo : lineInfoIt.DialogueBlockInfoList) {
				if (blockInfo.WidgetWeakPtr.IsValid() && blockInfo.WidgetWeakPtr->IsA<UHorizonTextBlock>()) {
					auto pTextBlock = Cast<UHorizonTextBlock>(blockInfo.WidgetWeakPtr.Get());
					pTextBlock->SetShadowColorAndOpacity(ShadowColorAndOpacity);
				}
			}
		}
	}
}

void UHorizonDialogueMsgTextBlock::SetShadowOffset(FVector2D InShadowOffset, bool bForce /*= false*/)
{
	ShadowOffset = InShadowOffset;
	if (!bIsRichText || bForce)
	{
		for (auto& lineInfo : DialogueLineInfoList) {
			for (auto& blockInfo : lineInfo.DialogueBlockInfoList) {
				if (blockInfo.WidgetWeakPtr.IsValid() && blockInfo.WidgetWeakPtr->IsA<UHorizonTextBlock>()) {
					auto pTextBlock = Cast<UHorizonTextBlock>(blockInfo.WidgetWeakPtr.Get());
					pTextBlock->SetShadowOffset(ShadowOffset);
				}
			}
		}
	}
}

void UHorizonDialogueMsgTextBlock::SetFont(FSlateFontInfo InFontInfo, bool bForce /*= false*/)
{
	Font = InFontInfo;
	if (!bIsRichText || bForce)
	{
		for (auto& lineInfo : DialogueLineInfoList) {
			for (auto& blockInfo : lineInfo.DialogueBlockInfoList) {
				if (blockInfo.WidgetWeakPtr.IsValid() && blockInfo.WidgetWeakPtr->IsA<UHorizonTextBlock>()) {
					auto pTextBlock = Cast<UHorizonTextBlock>(blockInfo.WidgetWeakPtr.Get());
					pTextBlock->SetFont(Font);
				}

			}
		}
	}
}

void  UHorizonDialogueMsgTextBlock::SetFontSize(int32 fontSize) {
	Font.Size = fontSize;
}

void UHorizonDialogueMsgTextBlock::SetJustification(ETextJustify::Type InJustification, bool bForce /*= false*/)
{
	Justification = InJustification;
	if (!bIsRichText || bForce)
	{
		for (auto& lineInfo : DialogueLineInfoList) {
			for (auto& blockInfo : lineInfo.DialogueBlockInfoList) {
				if (blockInfo.WidgetWeakPtr.IsValid() && blockInfo.WidgetWeakPtr->IsA<UHorizonTextBlock>()) {
					auto pTextBlock = Cast<UHorizonTextBlock>(blockInfo.WidgetWeakPtr.Get());
					pTextBlock->SetJustification(Justification);
				}

			}
		}
	}
}

FText UHorizonDialogueMsgTextBlock::GetText() const
{
	return Text;
}

void UHorizonDialogueMsgTextBlock::SetText(FText InText)
{
	Text = InText;
	//RebuildWidget();
}

void UHorizonDialogueMsgTextBlock::SetTextAndRebuildDialogue(const FText& InText)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, SetTextAndRebuildDialogue)
	if (!Text.EqualTo(InText))
	{
		Text = InText;
		ClearChildren();
		RequestRebuildDialogue();
	}


}


void UHorizonDialogueMsgTextBlock::SetTextAndRebuildDialogue(FText&& InText)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, SetTextAndRebuildDialogue_MoveTemp)
	if (!Text.EqualTo(InText))
	{
		Text = MoveTemp(InText);
		ClearChildren();
		RequestRebuildDialogue();
	}
}

#endif //============================End DialogueText Method=============================

#if 1 //============================Begin DialogueMsg: Setter/Getter=============================

void UHorizonDialogueMsgTextBlock::SetIsRichText(bool b) 
{
	bIsRichText = b;
}

void UHorizonDialogueMsgTextBlock::SetIsDialogueMsgText(bool b) {
	bIsDialogueMsgText = b;
	if (!bIsDialogueMsgText) {
		for (auto& lineInfo : DialogueLineInfoList) {
			for (auto& blockInfo : lineInfo.DialogueBlockInfoList) {
				if (blockInfo.WidgetWeakPtr.IsValid() && blockInfo.WidgetWeakPtr->IsA<UHorizonTextBlock>()) {
					auto pTextBlock = Cast<UHorizonTextBlock>(blockInfo.WidgetWeakPtr.Get());
					pTextBlock->SetText(FText::FromString(blockInfo.MsgText));
				}

			}
		}
	}
}
void UHorizonDialogueMsgTextBlock::SetDialogueMsgSpeed(float speed, bool bForce /*= false*/) {
	if (FMath::IsNearlyZero(speed))
	{
		speed = 0.000001f;
	}
	DialogueMsgSpeed = speed;
	if (!bIsRichText || bForce)
	{
		for (auto& segInfoIt : DialogueSegmentInfoList) {
			segInfoIt.DialogueMsgSpeed = speed;

		}
	}
}

void UHorizonDialogueMsgTextBlock::SetIsStartTickDialogueMsg(bool bShouldStartTick, bool bShouldResetDialogue) 
{
	bIsStartTickDialogueMsg = bShouldStartTick;
	if (bShouldResetDialogue)
	{
		ResetDialogueMsgText();
	}
}


void UHorizonDialogueMsgTextBlock::SetIsRepeatDialogueMsg(bool b) 
{
	bIsRepeatDialogueMsg = b;
}

void UHorizonDialogueMsgTextBlock::SetRepeatDialogueMsgInterval(float interval)
{
	RepeatDialogueMsgInterval = interval;
}



int32 UHorizonDialogueMsgTextBlock::GetTextLength()
{
	return TexLength;
}

void UHorizonDialogueMsgTextBlock::RequestRebuildDialogue()
{
	bNeedRebuildDialogueMsgText = true;
}


bool UHorizonDialogueMsgTextBlock::IsNeedRebuildDialogueMsgText() 
{ 
	return bNeedRebuildDialogueMsgText; 
}
#endif //============================End DialogueMsg: Setter/Getter=============================

#if 1 //============================Begin DialogueMsg=============================
void UHorizonDialogueMsgTextBlock::StartDialogue()
{
	SetIsStartTickDialogueMsg(true, true);
};


void UHorizonDialogueMsgTextBlock::StopDialogue()
{
	//reset dialogue
	ResetDialogueMsgText();
	//stop tick
	SetIsStartTickDialogueMsg(false, false);
}


void UHorizonDialogueMsgTextBlock::SkipDialogue()
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, SkipDialogue)
	if (GetCurrentPageIndex() != DialoguePageInfoList.Num() - 1)
	{
		SetDialogueMsgPage(DialoguePageInfoList.Num() - 1);
	}
	SkipCurrentDialoguePage();
}







void UHorizonDialogueMsgTextBlock::PauseDialogue()
{
	SetIsStartTickDialogueMsg(false, false);

}

void UHorizonDialogueMsgTextBlock::ResumeDialogue()
{
	SetIsStartTickDialogueMsg(true, false);

}

void UHorizonDialogueMsgTextBlock::ResetDialogueMsgText()
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, ResetDialogueMsgText)
	if (bIsDialogueMsgText)
	{
		for (auto& lineInfoIt : DialogueLineInfoList) {
			lineInfoIt.CurrentDialogueBlockIndex = 0;
			for (auto& blockInfoIt : lineInfoIt.DialogueBlockInfoList) {
				blockInfoIt.CurrentCharIndex = 0;
				if (blockInfoIt.WidgetWeakPtr.IsValid())
				{
					blockInfoIt.WidgetWeakPtr->SetVisibility(ESlateVisibility::Hidden);
				}
				if (blockInfoIt.WidgetBackgroundWeakPtr.IsValid())
				{
					blockInfoIt.WidgetBackgroundWeakPtr->SetVisibility(ESlateVisibility::Hidden);
				}
				if (blockInfoIt.RubyTextWeakPtr.IsValid())
				{
					blockInfoIt.RubyTextWeakPtr->SetVisibility(ESlateVisibility::Hidden);
				}
				
			}
		}


		for (auto& segInfoIt : DialogueSegmentInfoList) 
		{
			segInfoIt.bDialogueSoundPlayed = false;
			segInfoIt.bEventCallbackCalled = false;
			segInfoIt.CurrentMsgWaitTime = 0.0f;
		}
		//SetIsStartTickDialogue(true);
		CurrentDialogueLineIndex = 0;
		CurrentPageIndex = 0;
		CurrentPageHeightOffset = 0.0f;
		MsgDeltaTime = 0.0f;
		AutoNextDialogueMsgPageDeltaTime = 0.0f;
		RepeatDialogueMsgDeltaTime = 0.0f;
	}
}

void UHorizonDialogueMsgTextBlock::RebuildDialogueMsgTextBlock()
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, RebuildDialogueMsgTextBlock)
	TexLength = 0;
	RebuildSegmentInfoList();
	RebuildLineInfoList();
	RebuildPageInfoList();


	RebuildBlockInfoJustification();
	//RebuildBlockInfoDecoration();





	MsgDeltaTime = 0.0f;
	if (bIsDialogueMsgText)
	{
		SetIsStartTickDialogueMsg(true, true);
	}
	else 
	{
		SetIsStartTickDialogueMsg(false, false);
	}

	CalculateAutoNextDialogueMsgPageInterval();

}

void UHorizonDialogueMsgTextBlock::TriggerCustomEventCallback(FHorizonDialogueSegmentInfo& InSegInfo)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, TriggerCustomEventCallback)
	if (!InSegInfo.bEventCallbackCalled)
	{
		if (InSegInfo.EventName.IsSet())
		{
			InSegInfo.bEventCallbackCalled = true;
			OnCustomEventDelegate.Broadcast(InSegInfo.EventName.GetValue(), InSegInfo);
			OnCustomEventDelegateNative.Broadcast(InSegInfo.EventName.GetValue(), InSegInfo);
		}
	}
}

void UHorizonDialogueMsgTextBlock::TriggerPlaySound(FHorizonDialogueSegmentInfo& InSegInfo)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, TriggerPlaySound)
	if (InSegInfo.DialogueSound && !InSegInfo.bDialogueSoundPlayed)
	{
		InSegInfo.bDialogueSoundPlayed = true;

		UGameplayStatics::PlaySound2D(this, InSegInfo.DialogueSound,
			InSegInfo.DialogueSoundVolumeMultiplier,
			InSegInfo.DialogueSoundPitchMultiplier, InSegInfo.DialogueSoundStartTime);
	}
}

#endif //============================End DialogueMsg=============================

#if 1 //============================Begin DialogueMsg Page=============================
void UHorizonDialogueMsgTextBlock::NextDialogueMsgPage(bool bShouldStartTick)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, NextDialogueMsgPage)
	int32 newPage = CurrentPageIndex + 1;

	if(newPage >= DialoguePageInfoList.Num())
	{ 
		if (bIsRepeatDialogueMsg)
		{
			newPage = 0;
			SetDialogueMsgPage(newPage, bShouldStartTick);
		}
		else
		{
			newPage = DialoguePageInfoList.Num() - 1;
		}
		
	}
	if (newPage != CurrentPageIndex)
	{
		SetDialogueMsgPage(newPage, bShouldStartTick);
	}

}



void UHorizonDialogueMsgTextBlock::PrevDialogueMsgPage(bool bShouldStartTick)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, PrevDialogueMsgPage)
	int32 newPage = CurrentPageIndex - 1;

	if (newPage < 0)
	{
		newPage = 0;
	}
	if (newPage != CurrentPageIndex)
	{
		SetDialogueMsgPage(newPage, bShouldStartTick);
	}

}


TOptional<float> UHorizonDialogueMsgTextBlock::GetMinimalPaddingMarginTopOffset(const FHorizonDialogueLineInfo& InLineInfo)
{
	TOptional<float> minPadingMarginTopOffset;
	for (auto& blockInfoIt : InLineInfo.DialogueBlockInfoList)
	{
		// skip zero
		if (!FMath::IsNearlyZero(DialogueSegmentInfoList[blockInfoIt.SegmentReferenceIndex].PaddingMargin.Top))
		{
			if (!minPadingMarginTopOffset.IsSet())
			{
				minPadingMarginTopOffset = DialogueSegmentInfoList[blockInfoIt.SegmentReferenceIndex].PaddingMargin.Top;
			}
			else
			{
				minPadingMarginTopOffset = FMath::Min(minPadingMarginTopOffset.GetValue(), DialogueSegmentInfoList[blockInfoIt.SegmentReferenceIndex].PaddingMargin.Top);
			}
		}
	}

	return minPadingMarginTopOffset;
}

void UHorizonDialogueMsgTextBlock::SetDialogueMsgPage(int32 InPageIndex, bool bShouldStartTick)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, SetDialogueMsgPage)
	if (InPageIndex < DialoguePageInfoList.Num())
	{
		AutoNextDialogueMsgPageDeltaTime = 0.0f;
		for (auto& it : DialoguePageInfoList)
		{
			SetPageVisiblity(false, it);
		}
		CurrentPageHeightOffset = 0.0f;
		for (int32 i = 0; i < InPageIndex; ++i)
		{
			CurrentPageHeightOffset += DialoguePageInfoList[i].PageHeight;
			CurrentPageHeightOffset = CurrentPageHeightOffset + (LineMargin.Bottom - LineMargin.Top);
		}
		//MaxLineHeight
		CurrentPageIndex = InPageIndex;
		auto& currentPageInfo = DialoguePageInfoList[InPageIndex];
		CurrentDialogueLineIndex = DialoguePageInfoList[InPageIndex].StartLineIndex;

#if 1 // Add padingMarginTopOffset for each page
		for (int32 nPageIndex = 0; nPageIndex < InPageIndex; ++nPageIndex)
		{
			auto& prevCurrentPageInfo = DialoguePageInfoList[nPageIndex];

	
			for (int32 i = prevCurrentPageInfo.StartLineIndex; i < prevCurrentPageInfo.EndLineIndex; ++i)
			{
				// find minimal off set in the line
				FHorizonDialogueLineInfo& lineInfo = DialogueLineInfoList[i];
				TOptional<float> minPadingMarginTopOffset = GetMinimalPaddingMarginTopOffset(lineInfo);
			

				if (minPadingMarginTopOffset.IsSet())
				{
					CurrentPageHeightOffset += minPadingMarginTopOffset.GetValue();
				}
			}
		}




#endif
		

		TOptional<float> currentPagePadingMarginTopOffset;

		for (int32 i = currentPageInfo.StartLineIndex; i < currentPageInfo.EndLineIndex; ++i)
		{
			FHorizonDialogueLineInfo& lineInfo = DialogueLineInfoList[i];
			lineInfo.CurrentDialogueBlockIndex = 0;
			for (auto& blockInfoIt : lineInfo.DialogueBlockInfoList)
			{
				blockInfoIt.CurrentCharIndex = 0;
			}
			if (!currentPagePadingMarginTopOffset.IsSet())
			{
				currentPagePadingMarginTopOffset = GetMinimalPaddingMarginTopOffset(lineInfo);

				// Skip calculate offset for last page
				if (DialoguePageInfoList.Num()-1 == InPageIndex)
				{
					currentPagePadingMarginTopOffset.Reset();
				}
			}
		}

		if (currentPagePadingMarginTopOffset.IsSet())
		{
			float lineOffOffset = currentPagePadingMarginTopOffset.GetValue();
			CurrentPageHeightOffset += lineOffOffset;
		}

		SetIsStartTickDialogueMsg(bShouldStartTick, false);
		FHorizonDialogueDialoguePageResult result;
		result.PageIndex = InPageIndex;
		OnSetDialoguePageFunction.Broadcast(result);
		OnSetDialoguePageFunctionNative.Broadcast(result);
	}
}

void UHorizonDialogueMsgTextBlock::SetIsAutoNextDialogueMsgPage(bool b)
{
	bIsAutoNextDialogueMsgPage = b;

}


void UHorizonDialogueMsgTextBlock::SetAutoNextDialogueMsgPageIntervalRate(float InAutoNextDialogueMsgPageIntervalRate)
{
	AutoNextDialogueMsgPageIntervalRate = InAutoNextDialogueMsgPageIntervalRate;
	CalculateAutoNextDialogueMsgPageInterval();
}




int32 UHorizonDialogueMsgTextBlock::GetCurrentPageTextLength()
{
	int32 result = 0;
	if (CurrentPageIndex < DialoguePageInfoList.Num())
	{
		auto& currentPageInfo = DialoguePageInfoList[CurrentPageIndex];

		for (int32 i = currentPageInfo.StartLineIndex; i < currentPageInfo.EndLineIndex; ++i)
		{
			FHorizonDialogueLineInfo& lineInfo = DialogueLineInfoList[i];
			
			result += Algo::Accumulate(lineInfo.DialogueBlockInfoList, 0, [](int32 InAcc, const auto& InBlockInfo)
			{
				return InAcc + InBlockInfo.MsgText.Len();
			});
		}
	}
	return result;
}



FText UHorizonDialogueMsgTextBlock::GetPageTextByIndex(int32 PageIndex)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, GetPageTextByIndex)
	FString result;
	if (PageIndex >= 0 && PageIndex < DialoguePageInfoList.Num())
	{
		auto& currentPageInfo = DialoguePageInfoList[PageIndex];

		for (int32 i = currentPageInfo.StartLineIndex; i < currentPageInfo.EndLineIndex; ++i)
		{
			FHorizonDialogueLineInfo& lineInfo = DialogueLineInfoList[i];

			result += Algo::Accumulate(lineInfo.DialogueBlockInfoList, FString(), [](FString&& InString, const auto& InBlockInfo)
			{
				return InString + InBlockInfo.MsgText;
			});
		}
	}

	return FText::FromString(result);

}



int32 UHorizonDialogueMsgTextBlock::GetNumPage()
{
	return DialoguePageInfoList.Num();
}

void UHorizonDialogueMsgTextBlock::SkipCurrentDialogueMsgPageTick()
{
	SkipCurrentDialoguePage();
}


void UHorizonDialogueMsgTextBlock::SkipCurrentDialoguePage()
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, SkipCurrentDialoguePage)
	if (CurrentPageIndex < DialoguePageInfoList.Num())
	{
		auto currentPageInfo = DialoguePageInfoList[CurrentPageIndex];
		for (int32 i = CurrentDialogueLineIndex; i < currentPageInfo.EndLineIndex; ++i)
		{
			FHorizonDialogueLineInfo& lineInfo = DialogueLineInfoList[i];


			for (auto& blockInfo : lineInfo.DialogueBlockInfoList)
			{

				if (blockInfo.WidgetWeakPtr.IsValid())
				{
					UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(blockInfo.WidgetWeakPtr->Slot);
					if(canvasPanelSlot)
					{ 
						auto currentPosition = canvasPanelSlot->GetPosition();
						if (CurrentPageIndex > 0)
						{
							currentPosition.Y = lineInfo.Position.Y - CurrentPageHeightOffset + DialogueSegmentInfoList[blockInfo.SegmentReferenceIndex].PaddingMargin.Top;
						}
						canvasPanelSlot->SetPosition(currentPosition);

						blockInfo.WidgetWeakPtr->SetVisibility(ESlateVisibility::HitTestInvisible);
						if (blockInfo.WidgetBackgroundWeakPtr.IsValid())
						{
							blockInfo.WidgetBackgroundWeakPtr->SetVisibility(ESlateVisibility::Visible);
							UCanvasPanelSlot* buttonCanvasPanelSlot = Cast<UCanvasPanelSlot>(blockInfo.WidgetBackgroundWeakPtr->Slot);
							if (buttonCanvasPanelSlot)
							{
								buttonCanvasPanelSlot->SetPosition(currentPosition);
							}
						}
						if (blockInfo.RubyTextWeakPtr.IsValid())
						{
							blockInfo.RubyTextWeakPtr->SetVisibility(ESlateVisibility::HitTestInvisible);
							blockInfo.RubyTextWeakPtr->SetText(FText::FromString(blockInfo.RubyText));
							SetupRubyTextPosition(currentPosition, blockInfo, DialogueSegmentInfoList[blockInfo.SegmentReferenceIndex]);
						}
					}

					if (blockInfo.WidgetWeakPtr->IsA<UHorizonTextBlock>()) {
						auto pTextBlock = Cast<UHorizonTextBlock>(blockInfo.WidgetWeakPtr.Get());
						pTextBlock->SetText(FText::FromString(blockInfo.MsgText));
					}
				}
			}
		}
		//Debug auto page position
		//if (currentPageInfo.StartLineIndex == CurrentDialogueLineIndex)
		//{
		//	UE_LOG(LogTemp, Log, TEXT("page %d, line: %d, %f"), CurrentPageIndex, CurrentDialogueLineIndex, currentPosition.Y);
		//}

		CurrentDialogueLineIndex = currentPageInfo.EndLineIndex;
	}
}

bool UHorizonDialogueMsgTextBlock::IsDialogueMsgPageEnd()
{
	if (IsDialogueMsgText())
	{
		if (CurrentPageIndex < DialoguePageInfoList.Num())
		{
			auto currentPageInfo = DialoguePageInfoList[CurrentPageIndex];
			return CurrentDialogueLineIndex == currentPageInfo.EndLineIndex;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}

}




bool UHorizonDialogueMsgTextBlock::IsDialogueMsgCompleted()
{
	if (IsDialogueMsgText())
	{
		return CurrentDialogueLineIndex >= DialogueLineInfoList.Num();
	}
	else
	{
		return true;
	}
}


void UHorizonDialogueMsgTextBlock::CalculateAutoNextDialogueMsgPageInterval()
{
	int32 numPage = FMath::Max(1, DialoguePageInfoList.Num());
	AutoNextDialogueMsgPageInterval = AutoNextDialogueMsgPageIntervalRate * (GetTextLength() / numPage);
	AutoNextDialogueMsgPageInterval = FMath::Clamp(AutoNextDialogueMsgPageInterval, AutoNextDialogueMsgPageIntervalMin, AutoNextDialogueMsgPageIntervalMax);

}


void UHorizonDialogueMsgTextBlock::SetPageVisiblity(bool bVisibility, const FHorizonDialoguePageInfo& InPageInfo)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, SetPageVisiblity)
	for (int32 i = InPageInfo.StartLineIndex; i < InPageInfo.EndLineIndex; ++i)
	{
		FHorizonDialogueLineInfo& lineInfo = DialogueLineInfoList[i];
		for (auto& blockInfo : lineInfo.DialogueBlockInfoList)
		{
			if (blockInfo.WidgetWeakPtr.IsValid()) 
			{
				if (bVisibility)
				{
					blockInfo.WidgetWeakPtr->SetVisibility(ESlateVisibility::HitTestInvisible);
				}
				else
				{
					blockInfo.WidgetWeakPtr->SetVisibility(ESlateVisibility::Hidden);

				}
			}
			if (blockInfo.WidgetBackgroundWeakPtr.IsValid())
			{
				if (bVisibility)
				{
					blockInfo.WidgetBackgroundWeakPtr->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					blockInfo.WidgetBackgroundWeakPtr->SetVisibility(ESlateVisibility::Hidden);
				}
			}

			if (blockInfo.RubyTextWeakPtr.IsValid()) 
			{
				if (bVisibility)
				{
					blockInfo.RubyTextWeakPtr->SetVisibility(ESlateVisibility::HitTestInvisible);
				}
				else
				{
					blockInfo.RubyTextWeakPtr->SetVisibility(ESlateVisibility::Hidden);

				}
			}
		}

	}

}




#endif //============================End Dialogue Page=============================


#if 1 //============================Begin Dialogue: Rebuild=============================
void UHorizonDialogueMsgTextBlock::RebuildSegmentInfoList()
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, RebuildSegmentInfoList)
	//rebuild style info
	StyleInfoList.Empty();
	for (auto& styleInfoClassIt : StyleInfoClassList)
	{
		if (styleInfoClassIt)
		{
			auto styleInfo = NewObject<UHorizonDialogueStyleInfo>(this, styleInfoClassIt,
				NAME_None, EObjectFlags::RF_NoFlags,
				nullptr, true);
			if (styleInfo)
			{
				StyleInfoList.Emplace(styleInfo);
			}
		}
	}




	DialogueSegmentInfoList.Empty();//DialogueSegmentInfoList.RemoveAll([](const FHorizonDialogueSegmentInfo& element) {return true; });

	if (bIsRichText) 
	{
		FString segmentStr = FString::Printf(TEXT("%s%s%s"), TEXT("<text>"), *Text.ToString(), TEXT("</text>"));
		FXmlFile xmlFile(segmentStr, EConstructMethod::ConstructFromBuffer);


		//const char* AAA = R"(C:\AAAA\BBB)";
		if (xmlFile.IsValid()) 
		{
			const FXmlNode* pRootNode = xmlFile.GetRootNode();
			FHorizonDialogueSegmentInfo rootSegParam = CreateSegmentInfo(CreateDefaultSegmentInfo(EHorizonDialogueSegmentType::Invalidated), pRootNode);
			if (pRootNode) 
			{
				RebuildSegmentInfoListImplement(rootSegParam, pRootNode);
			}
			else 
			{
				AddTextSegmentInfo(Text.ToString());
				verifyf(false, TEXT("oops! something error, should never go here"));
			}
		}
		else 
		{
			AddTextSegmentInfo(Text.ToString());
		}
	}
	else 
	{
		AddTextSegmentInfo(Text.ToString());
	}



	//BuildSegmentInfoList(segmentStr);

}


void UHorizonDialogueMsgTextBlock::RebuildLineInfoList()
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, RebuildLineInfoList)
	//clear up
	ClearChildren();
	DialogueLineInfoList.Empty();

	auto& geometry = GetCachedGeometry();

	float widgetWidth = 0.0f;
	// setup line init info 
	UCanvasPanelSlot* pTextBlockCanvasPanelSlot = UHorizonWidgetFunctionLibrary::GetParentCanvasPanelSlot(this);

	if (pTextBlockCanvasPanelSlot && !pTextBlockCanvasPanelSlot->bAutoSize )
	{
		widgetWidth = geometry.Size.X;
	}
	else
	{
		if (nullptr == pTextBlockCanvasPanelSlot)
		{
			widgetWidth = geometry.Size.X;
		}
		else
		{
			widgetWidth = FMath::Max(pTextBlockCanvasPanelSlot->GetSize().X, geometry.Size.X);
		}

	}


	const TSharedRef< FSlateFontMeasure >& FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();

	MaxLineWidth = FMath::Max(Font.Size, (int32)(widgetWidth - (LineMargin.Left + LineMargin.Right)));
	float currentLineWidth = 0;

	DialogueLineInfoList.Emplace(FHorizonDialogueLineInfo());

	FVector2D blockPos(LineMargin.Left, 0);
	//int32 blockPosX = LineMargin.Left;
	//int32 blockPosY = 0;
	//parse segment into line and block
	//for (const auto& it : DialogueSegmentInfoList) {
	for (int32 currentSegInfoIndex = 0; currentSegInfoIndex < DialogueSegmentInfoList.Num(); ++currentSegInfoIndex) {
		auto& segInfo = DialogueSegmentInfoList[currentSegInfoIndex];
		BuildSegmeentDecoration(currentSegInfoIndex);
		switch (segInfo.TypeEnum) 
		{
		case EHorizonDialogueSegmentType::Text:
		{

			switch (GetTextOverflowWrapMethod())
			{
			case EHorizonDialogueTextOverflowWrapMethod::Normal:
			{
				TextOverflowWarpNormal_Implement(currentLineWidth, blockPos, currentSegInfoIndex, MaxLineWidth, segInfo);
			}
			break;
			case EHorizonDialogueTextOverflowWrapMethod::BreakAll:
			{
				TextOverflowWarpBreakAll_Implement(currentLineWidth, blockPos, currentSegInfoIndex, MaxLineWidth, segInfo);
			}
			break;
			}

		}
		break;
		case EHorizonDialogueSegmentType::NewPage:
		case EHorizonDialogueSegmentType::NewLine:
		{

			blockPos.X = LineMargin.Left;
			DialogueLineInfoList.Last().LineWidth = currentLineWidth;
			//new line
			auto lineInfo = FHorizonDialogueLineInfo();
			if (EHorizonDialogueSegmentType::NewPage == segInfo.TypeEnum)
			{
				lineInfo.bNewPage = true;

			}
			lineInfo.MaxLineHeight = Font.Size;
			lineInfo.Position.Y = DialogueLineInfoList.Last().Position.Y + DialogueLineInfoList.Last().MaxLineHeight + LineMargin.Bottom;
			DialogueLineInfoList.Emplace(lineInfo);
			currentLineWidth = 0;
			break;
		}
		break;
		case EHorizonDialogueSegmentType::Image:
		case EHorizonDialogueSegmentType::PaperFlipbook:
		case EHorizonDialogueSegmentType::Material:
		{
			//first line only calculate from top
			if (DialogueLineInfoList.Num() == 1) 
			{
				blockPos.Y = LineMargin.Top;
			}
			else 
			{
				blockPos.Y = DialogueLineInfoList.Last(1).Position.Y + DialogueLineInfoList.Last(1).MaxLineHeight + LineMargin.Bottom;
			}

			//auto& blockInfo = segInfo.TypeEnum == EHorizonDialogueSegmentType::Image ? CreateDialogueImageBlockInfo(i, blockPos) : CreateDialoguePaperFlipbookBlockInfo(i, blockPos);
			FHorizonDialogueBlockInfo blockInfo;
			if (segInfo.TypeEnum == EHorizonDialogueSegmentType::Image ||
				segInfo.TypeEnum == EHorizonDialogueSegmentType::Material) 
			{
				blockInfo = CreateDialogueImageBlockInfo(currentSegInfoIndex, blockPos);
			}
			else if (segInfo.TypeEnum == EHorizonDialogueSegmentType::PaperFlipbook) 
			{
				blockInfo = CreateDialogueFlipbookBlockInfo(currentSegInfoIndex, blockPos);
			}
			else 
			{
				verifyf(false, TEXT("oops! something error"));
			}

			if (blockInfo.WidgetWeakPtr.IsValid())
			{
				UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(blockInfo.WidgetWeakPtr->Slot);
				if (canvasPanelSlot) 
				{
					FVector2D size = canvasPanelSlot->GetSize();
					currentLineWidth += size.X;


					//if image size larger than maxLineWidth, then move the image to new line
					if (currentLineWidth > MaxLineWidth) {
						//setup prev line width
						DialogueLineInfoList.Last().LineWidth = currentLineWidth - size.X;

						//add new line
						DialogueLineInfoList.Emplace(FHorizonDialogueLineInfo());
						DialogueLineInfoList.Last().LineWidth = size.X;
						currentLineWidth = size.X;

						//blockPos calculate from new line
						{
							blockPos.X = LineMargin.Left;
							//first line only calculate from top
							if (DialogueLineInfoList.Num() == 1) {
								blockPos.Y = LineMargin.Top;
							}
							else 
							{
								blockPos.Y = DialogueLineInfoList.Last(1).Position.Y + DialogueLineInfoList.Last(1).MaxLineHeight + LineMargin.Bottom;
							}
						}

						FVector2D paddingPos = blockPos + FVector2D(0, (int32)segInfo.PaddingMargin.Top);
						canvasPanelSlot->SetPosition(paddingPos);
						AddBackgroundButton(currentSegInfoIndex, blockInfo, canvasPanelSlot, paddingPos);
					}
					CalculateMaxLineHeight(DialogueLineInfoList.Last(), segInfo, size);
					AddDialogueBlock(DialogueLineInfoList.Last(), MoveTemp(blockInfo));

				}
			}


			blockPos.X = LineMargin.Left + currentLineWidth;

		}
		break;

		case EHorizonDialogueSegmentType::HyperText:
			break;

		};



	}
}


void UHorizonDialogueMsgTextBlock::RebuildPageInfoList()
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, RebuildPageInfoList)
	DialoguePageInfoList.Empty();

	// setup line init info 
	auto& geometry = GetCachedGeometry();
	float canvasHeight = geometry.Size.Y;






	int32 startLineIndex = 0;
	int32 currentLineIndex = 0;
	float currentPageHeight = 0;
	while (currentLineIndex < DialogueLineInfoList.Num())
	{
		const auto& lineInfo = DialogueLineInfoList[currentLineIndex];
		float maxPageHeight = FMath::Max((float)Font.Size, canvasHeight - lineInfo.MaxLineHeight);
		if ((currentPageHeight >= maxPageHeight) || 
			(lineInfo.bNewPage && !FMath::IsNearlyZero(currentPageHeight)) // Handle NewPage tag
		   )
		{
			//handle extreme case, just paging everyline if startLineIndex == (currentLineIndex - 1)
			//if (startLineIndex < (currentLineIndex - 1) && !lineInfo.bNewPage)
			//{
			//	--currentLineIndex;
			//	currentPageHeight = currentPageHeight - (LineMargin.Bottom);
			//	auto& prevLineInfo = DialogueLineInfoList[currentLineIndex];
			//	currentPageHeight = currentPageHeight - prevLineInfo.MaxLineHeight;
			//}
			if (startLineIndex == currentLineIndex)
			{
				++currentLineIndex;
				ensureMsgf(false, TEXT("oops! something error"));
			}

			DialoguePageInfoList.Emplace(FHorizonDialoguePageInfo(startLineIndex, currentLineIndex, currentPageHeight));
			startLineIndex = currentLineIndex;
			currentPageHeight = 0;
		}
		else
		{
			if (FMath::IsNearlyZero(currentPageHeight))
			{
				currentPageHeight += LineMargin.Top;
			}
			else
			{
				currentPageHeight += LineMargin.Bottom;
			}

			currentPageHeight = currentPageHeight + lineInfo.MaxLineHeight;
			++currentLineIndex;

		}

	}
	//last page
	DialoguePageInfoList.Emplace(FHorizonDialoguePageInfo(startLineIndex, currentLineIndex, currentPageHeight));

}

void UHorizonDialogueMsgTextBlock::RebuildBlockInfoJustification()
{
	for (auto& lineInfo : DialogueLineInfoList) 
	{
		for (auto& blockInfo : lineInfo.DialogueBlockInfoList) 
		{
			UCanvasPanelSlot* widgetCanvasPanelSlot = nullptr;
			if (blockInfo.WidgetWeakPtr.IsValid())
			{
				widgetCanvasPanelSlot = Cast<UCanvasPanelSlot>(blockInfo.WidgetWeakPtr->Slot);
			}
			UCanvasPanelSlot* widgetBackgroundCanvasPanelSlot = nullptr;
			if (blockInfo.WidgetBackgroundWeakPtr.IsValid())
			{
				widgetBackgroundCanvasPanelSlot = Cast<UCanvasPanelSlot>(blockInfo.WidgetBackgroundWeakPtr->Slot);
			}

			UCanvasPanelSlot* widgetRubyTextCanvasPanelSlot = nullptr;
			if (blockInfo.RubyTextWeakPtr.IsValid())
			{
				widgetRubyTextCanvasPanelSlot = Cast<UCanvasPanelSlot>(blockInfo.RubyTextWeakPtr->Slot);
			}
			float widthOffset = 0.0f;
			switch (Justification)
			{
			case ETextJustify::Left:
			{
				widthOffset = 0.0f;
			}
			break;
			case ETextJustify::Right:
			{
				widthOffset = MaxLineWidth - lineInfo.LineWidth;
			}
			break;
			case ETextJustify::Center:
			{
				widthOffset = (MaxLineWidth - lineInfo.LineWidth) * 0.5f;
			}
			break;
			}

			if (widgetCanvasPanelSlot)
			{
				auto currentPos = widgetCanvasPanelSlot->GetPosition();
				currentPos.X += widthOffset;
				widgetCanvasPanelSlot->SetPosition(currentPos);
			}
			if (widgetBackgroundCanvasPanelSlot)
			{
				auto currentPos = widgetBackgroundCanvasPanelSlot->GetPosition();
				currentPos.X += widthOffset;
				widgetBackgroundCanvasPanelSlot->SetPosition(currentPos);
			}
			if (widgetRubyTextCanvasPanelSlot)
			{
				auto currentPos = widgetRubyTextCanvasPanelSlot->GetPosition();
				currentPos.X += widthOffset;
				widgetRubyTextCanvasPanelSlot->SetPosition(currentPos);
			}

		}
	}

}

void UHorizonDialogueMsgTextBlock::CalculateBlockSize(FHorizonDialogueBlockInfo& InBlockInfo)
{
	if (InBlockInfo.WidgetWeakPtr.IsValid())
	{
		// Reinit current widget BlockSize in case Decorator change widget content
		UTextBlock* pTextBlock = Cast<UTextBlock>(InBlockInfo.WidgetWeakPtr.Get());
		if (pTextBlock)
		{
			FHorizonDialogueSegmentInfo& segInfo = DialogueSegmentInfoList[InBlockInfo.SegmentReferenceIndex];
			const TSharedRef< FSlateFontMeasure >& fontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
			InBlockInfo.BlockSize = fontMeasure->Measure(InBlockInfo.MsgText, segInfo.Font);

			if (segInfo.RubyTextInfo.Text.IsSet() && InBlockInfo.RubyTextWeakPtr.IsValid())
			{
				InBlockInfo.RubyTextBlockSize = fontMeasure->Measure(InBlockInfo.RubyText, segInfo.RubyTextInfo.Font);
				InBlockInfo.BlockSize.Y = InBlockInfo.BlockSize.Y + InBlockInfo.RubyTextBlockSize.Y + segInfo.RubyTextInfo.PaddingMargin.Bottom;
			}

		}
		else
		{
			UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(InBlockInfo.WidgetWeakPtr->Slot);
			if (canvasPanelSlot)
			{
				InBlockInfo.BlockSize = canvasPanelSlot->GetSize();
			}
		}
	}
}

void UHorizonDialogueMsgTextBlock::CalculateMaxLineHeight(FHorizonDialogueLineInfo& InLineInfo, 
	const FHorizonDialogueSegmentInfo& InSegInfo, 
	const FVector2D& InOneCharSize)
{

	InLineInfo.MaxLineHeight = FMath::Max(InLineInfo.MaxLineHeight, (int32)(InOneCharSize.Y + FMath::Abs(InSegInfo.PaddingMargin.Top)));

	if (InSegInfo.RubyTextInfo.Text.IsSet())
	{
		const TSharedRef<FSlateFontMeasure>& fontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
		FVector2D rubyTextOneCharSize = fontMeasure->Measure(InSegInfo.RubyTextInfo.Text.GetValue(), 0, 1, InSegInfo.RubyTextInfo.Font);
		if(!FMath::IsNearlyZero(InSegInfo.RubyTextInfo.PaddingMargin.Top))
		{ 
			InLineInfo.MaxLineHeight = FMath::Max(InLineInfo.MaxLineHeight, (int32)( rubyTextOneCharSize.Y + FMath::Abs(InSegInfo.RubyTextInfo.PaddingMargin.Top)));
		}
	}
}

void UHorizonDialogueMsgTextBlock::SetupRubyTextPosition(const FVector2D& InCurrentPosition, 
FHorizonDialogueBlockInfo& InBlockInfo, const FHorizonDialogueSegmentInfo& InSegInfo)
{
	if(InBlockInfo.RubyTextWeakPtr.IsValid())
	{ 
		UCanvasPanelSlot* pRubyTextCanvasPanelSlot = Cast<UCanvasPanelSlot>(InBlockInfo.RubyTextWeakPtr->Slot);
		if (pRubyTextCanvasPanelSlot)
		{
			auto rubyTextCurrentPosition = InCurrentPosition;
			rubyTextCurrentPosition = rubyTextCurrentPosition + FVector2D(0, InSegInfo.PaddingMargin.Top + InSegInfo.RubyTextInfo.PaddingMargin.Top);
			// padding to block center
			rubyTextCurrentPosition.X = rubyTextCurrentPosition.X + (InBlockInfo.BlockSize.X * 0.5f) - (InBlockInfo.RubyTextBlockSize.X * 0.5f);
			pRubyTextCanvasPanelSlot->SetPosition(rubyTextCurrentPosition);
		}
	}
}

void UHorizonDialogueMsgTextBlock::BuildSegmeentDecoration(int32 InCurrentSegInfoIndex)
{

	if(InCurrentSegInfoIndex < DialogueSegmentInfoList.Num())
	{
		auto& segInfo = DialogueSegmentInfoList[InCurrentSegInfoIndex];
		if (DecoratorClasses.Num() > 0)
		{
			for (TSubclassOf<UHorizonDialogueMsgDecorator>& decoratorClass : DecoratorClasses)
			{
				auto pDecorator = decoratorClass.GetDefaultObject();
				if (pDecorator)
				{
					pDecorator->BuildSegment(this, InCurrentSegInfoIndex, segInfo, DialogueSegmentInfoList);
				}
			}
		}
	}

}

void UHorizonDialogueMsgTextBlock::PreBuildBlockDecoration(FHorizonDialogueBlockInfo& InBlockInfo)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, PreBuildBlockDecoration)
	if (DecoratorClasses.Num() > 0)
	{
		for (TSubclassOf<UHorizonDialogueMsgDecorator>& decoratorClass : DecoratorClasses)
		{
			auto pDecorator = decoratorClass.GetDefaultObject();
			if (pDecorator)
			{
				check(InBlockInfo.SegmentReferenceIndex < DialogueSegmentInfoList.Num());
				pDecorator->PreRun(this, InBlockInfo, DialogueSegmentInfoList[InBlockInfo.SegmentReferenceIndex]);
			}
		}
	}
}

void UHorizonDialogueMsgTextBlock::BuildBlockDecoration(FHorizonDialogueBlockInfo& InBlockInfo)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, BuildBlockDecoration)
	if (DecoratorClasses.Num() > 0)
	{
		for (TSubclassOf<UHorizonDialogueMsgDecorator>& decoratorClass : DecoratorClasses)
		{
			auto pDecorator = decoratorClass.GetDefaultObject();
			if (pDecorator)
			{
				check(InBlockInfo.SegmentReferenceIndex < DialogueSegmentInfoList.Num());
				pDecorator->Run(this, InBlockInfo, DialogueSegmentInfoList[InBlockInfo.SegmentReferenceIndex]);
			}
		}
		// Recalculate BlockSize in case decorator change block content
		CalculateBlockSize(InBlockInfo);
	}
}
//
//void UHorizonDialogueMsgTextBlock::RebuildBlockInfoDecoration()
//{
//	if (DecoratorClasses.Num() > 0)
//	{
//		for (TSubclassOf<UHorizonDialogueMsgDecorator>& decoratorClass : DecoratorClasses)
//		{
//			auto pDecorator = decoratorClass.GetDefaultObject();
//			if(pDecorator)
//			{ 
//				for (auto& lineInfo : DialogueLineInfoList)
//				{
//					for (auto& blockInfo : lineInfo.DialogueBlockInfoList)
//					{
//						check(blockInfo.SegmentReferenceIndex < DialogueSegmentInfoList.Num());
//						pDecorator->Run(this, blockInfo, DialogueSegmentInfoList[blockInfo.SegmentReferenceIndex]);
//					}
//				}
//			}
//		}
//	}
//}

void UHorizonDialogueMsgTextBlock::RebuildSegmentInfoListImplement(const FHorizonDialogueSegmentInfo& parentSegParam, const FXmlNode* pCurrentNode) 
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, RebuildSegmentInfoListImplement)
	//depth first
	if (pCurrentNode && pCurrentNode->GetFirstChildNode())
	{
		FHorizonDialogueSegmentInfo currentSegParam = CreateSegmentInfo(parentSegParam, pCurrentNode);
		RebuildSegmentInfoListImplement(currentSegParam, pCurrentNode->GetFirstChildNode());
	}

	if (pCurrentNode) 
	{
		FHorizonDialogueSegmentInfo currentSegParam = CreateSegmentInfo(parentSegParam, pCurrentNode);

		//if (pCurrentNode->GetChildrenNodes().Num() == 0) {
		if (currentSegParam.TypeEnum == EHorizonDialogueSegmentType::Text)
		{
			//currentSegParam.
			currentSegParam.Text = pCurrentNode->GetContent();
			//Value.ReplaceInline(TEXT("&quot;"), TEXT("\""), ESearchCase::CaseSensitive);
			//Value.ReplaceInline(TEXT("&amp;"), TEXT("&"), ESearchCase::CaseSensitive);
			//Value.ReplaceInline(TEXT("&apos;"), TEXT("'"), ESearchCase::CaseSensitive);
			//Value.ReplaceInline(TEXT("&lt;"), TEXT("<"), ESearchCase::CaseSensitive);
			//Value.ReplaceInline(TEXT("&gt;"), TEXT(">"), ESearchCase::CaseSensitive);

			//handle special character
			currentSegParam.Text.ReplaceInline(TEXT("&nbsp;"), TEXT(" "));
			currentSegParam.Text.ReplaceInline(TEXT("&quot;"), TEXT("\""));
			currentSegParam.Text.ReplaceInline(TEXT("&amp;"), TEXT("&"));
			currentSegParam.Text.ReplaceInline(TEXT("&apos;"), TEXT("'"));
			currentSegParam.Text.ReplaceInline(TEXT("&lt;"), TEXT("<"));
			currentSegParam.Text.ReplaceInline(TEXT("&gt;"), TEXT(">"));
			//padding spcae
			if (currentSegParam.PaddingMargin.Left > 0) 
			{
				currentSegParam.Text = currentSegParam.Text.LeftPad(currentSegParam.Text.Len() + (int32)currentSegParam.PaddingMargin.Left);
			}
			if ((int32)currentSegParam.PaddingMargin.Right > 0) 
			{
				currentSegParam.Text = currentSegParam.Text.RightPad(currentSegParam.Text.Len() + (int32)currentSegParam.PaddingMargin.Right);
			}
		}
		DialogueSegmentInfoList.Emplace(MoveTemp(currentSegParam));
		//}
		RebuildSegmentInfoListImplement(parentSegParam, pCurrentNode->GetNextNode());
	}


}

void UHorizonDialogueMsgTextBlock::AddTextSegmentInfo(const FString& text) 
{
	DialogueSegmentInfoList.Emplace(CreateDefaultSegmentInfo(EHorizonDialogueSegmentType::Text));
	FHorizonDialogueSegmentInfo& info = DialogueSegmentInfoList.Last();
	info.Text = text;
}

FHorizonDialogueSegmentInfo UHorizonDialogueMsgTextBlock::CreateDefaultSegmentInfo(EHorizonDialogueSegmentType segmentType)
{
	FHorizonDialogueSegmentInfo info;
	info.TypeEnum = segmentType;
	info.ColorAndOpacity = ColorAndOpacity;
	info.DialogueMsgSpeed = DialogueMsgSpeed;
	info.DialogueMsgWait = 0.0f;
	info.Font = Font;
	info.ShadowColorAndOpacity = ShadowColorAndOpacity;
	info.ShadowOffset = ShadowOffset;

	info.RubyTextInfo.Font = Font;
	info.RubyTextInfo.ColorAndOpacity = ColorAndOpacity;
	info.RubyTextInfo.ShadowColorAndOpacity = ShadowColorAndOpacity;
	info.RubyTextInfo.ShadowOffset = ShadowOffset;
	info.RubyTextInfo.PaddingMargin.Top = -(info.RubyTextInfo.Font.Size + 5);
	return info;
}

FHorizonDialogueSegmentInfo UHorizonDialogueMsgTextBlock::CreateSegmentInfo(const FHorizonDialogueSegmentInfo& parentSegParam, const FXmlNode* pXmlNode) 
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, CreateSegmentInfo)

	FHorizonDialogueSegmentInfo segParam = parentSegParam;
	if (pXmlNode->GetTag().Equals(TEXT("text"), ESearchCase::IgnoreCase)) {
		segParam.TypeEnum = EHorizonDialogueSegmentType::Text;
	}
	if (pXmlNode->GetTag().Equals(TEXT("img"), ESearchCase::IgnoreCase)) {
		segParam.TypeEnum = EHorizonDialogueSegmentType::Image;
	}

	if (pXmlNode->GetTag().Equals(TEXT("br"), ESearchCase::IgnoreCase)) {
		segParam.TypeEnum = EHorizonDialogueSegmentType::NewLine;
	}


	if (pXmlNode->GetTag().Equals(TEXT("p"), ESearchCase::IgnoreCase)) {
		segParam.TypeEnum = EHorizonDialogueSegmentType::NewPage;
	}

	if (pXmlNode->GetTag().Equals(TEXT("PaperFlipBook"), ESearchCase::IgnoreCase) ||
		pXmlNode->GetTag().Equals(TEXT("PFB"), ESearchCase::IgnoreCase)) {
		segParam.TypeEnum = EHorizonDialogueSegmentType::PaperFlipbook;
	}

	if (pXmlNode->GetTag().Equals(TEXT("mat"), ESearchCase::IgnoreCase)) {
		segParam.TypeEnum = EHorizonDialogueSegmentType::Material;
	}


	if (pXmlNode->GetTag().Equals(TEXT("a"), ESearchCase::IgnoreCase)) {
		segParam.TypeEnum = EHorizonDialogueSegmentType::HyperText;
	}

	const auto& attributeList = pXmlNode->GetAttributes();
	for (const auto& attrIt : attributeList) {
		const FString tag = attrIt.GetTag();
		FString value = attrIt.GetValue();

		//apply style first, and then replace with
		if (tag.Equals(TEXT("style"), ESearchCase::IgnoreCase)) {
			bool bStyleFound = horizonui::ApplySegmentStyle(segParam, value, SegmentStyleList);


			if (!bStyleFound)
			{
				for (int32 i = 0; i < StyleInfoList.Num(); ++i)
				{
					//if (styleInfo)
					{
						auto& styleInfo = StyleInfoList[i];
						bStyleFound = horizonui::ApplySegmentStyle(segParam, value, styleInfo->SegmentStyleList);
						if (bStyleFound)
						{
							segParam.StyleInfoReferenceIndex = i; // current styleInfo index
							break;
						}
					}

				}
			}


			if (!bStyleFound)
			{
				//FMessageLog HorizonUIPluginLog(GName_HorizonUIPlugin);
				auto pOuter = GetOuter();
				auto pUserWidget = pOuter->GetOuter();
				auto message = FString::Printf(TEXT("%s.%s can't find style name: %s"), *pUserWidget->GetName(), *GetName(), *value);
				//HorizonUIPluginLog.Warning(FText::FromString(message));
				//HorizonUIPluginLog.Notify(FText::FromString(message));
				ensureMsgf(bStyleFound, TEXT("%s"), *message);
			}
			continue;
		}


		if (tag.Equals(TEXT("color"), ESearchCase::IgnoreCase)) 
		{
			TOptional<FLinearColor> color = ParseLinearColor(value);
			if (color.IsSet())
			{
				segParam.ColorAndOpacity = color.GetValue();
			}

			continue;
		}

		if (tag.Equals(TEXT("speed"), ESearchCase::IgnoreCase)) {
			if (value.IsNumeric()) {
				segParam.DialogueMsgSpeed = FCString::Atof(*value);
			}
			continue;
		}

		if (tag.Equals(TEXT("sound"), ESearchCase::IgnoreCase))
		{
			segParam.DialogueSoundPath = value;
			continue;
		}

		if (tag.Equals(TEXT("soundVolume"), ESearchCase::IgnoreCase))
		{
			if (value.IsNumeric())
			{
				segParam.DialogueSoundVolumeMultiplier = FCString::Atof(*value);
			}
			continue;
		}


		if (tag.Equals(TEXT("soundPitch"), ESearchCase::IgnoreCase))
		{
			if (value.IsNumeric())
			{
				segParam.DialogueSoundPitchMultiplier = FCString::Atof(*value);
			}
			continue;
		}


		if (tag.Equals(TEXT("soundStartTime"), ESearchCase::IgnoreCase))
		{
			if (value.IsNumeric())
			{
				segParam.DialogueSoundStartTime = FCString::Atof(*value);
			}
			continue;
		}



		if (tag.Equals(TEXT("wait"), ESearchCase::IgnoreCase)) {
			if (value.IsNumeric()) {
				segParam.DialogueMsgWait = FCString::Atof(*value);
			}
			continue;
		}



		if (tag.Equals(TEXT("shadowColor"), ESearchCase::IgnoreCase) ||
			tag.Equals(TEXT("shadow_color"), ESearchCase::IgnoreCase)) {
			TOptional<FLinearColor> color = ParseLinearColor(value);
			if (color.IsSet())
			{
				segParam.ShadowColorAndOpacity = color.GetValue();
			}

			continue;
		}

		//	FVector2D ShadowOffset;
		if (tag.Equals(TEXT("shadowOffset"), ESearchCase::IgnoreCase) ||
			tag.Equals(TEXT("shadow_offset"), ESearchCase::IgnoreCase)) 
		{
			TOptional<FVector2D> result = ParseVector2D(value);
			if(result.IsSet())
			{
				segParam.ShadowOffset = result.GetValue();
			}
		
			continue;
		}


		if (tag.Equals(TEXT("fontPath"), ESearchCase::IgnoreCase) ||
			tag.Equals(TEXT("font_path"), ESearchCase::IgnoreCase)) {

			//ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(*value);
			UFont* font = UHorizonFileSystem::GetInstance()->LoadFont(*value);
			segParam.Font = FSlateFontInfo(font, Font.Size, Font.TypefaceFontName);
			//segParam.Font.TypefaceFontName 
			continue;
		}

		if (tag.Equals(TEXT("fontType"), ESearchCase::IgnoreCase) ||
			tag.Equals(TEXT("font_type"), ESearchCase::IgnoreCase)) {
			segParam.Font.TypefaceFontName = *value;
			continue;
		}

		if (tag.Equals(TEXT("fontSize"), ESearchCase::IgnoreCase) ||
			tag.Equals(TEXT("font_size"), ESearchCase::IgnoreCase)) {
			if (value.IsNumeric()) {
				segParam.Font.Size = FCString::Atoi(*value);
			}
			continue;
		}

		if (tag.Equals(TEXT("padding-left"), ESearchCase::IgnoreCase)) {
			if (value.IsNumeric()) {
				segParam.PaddingMargin.Left = FCString::Atof(*value);
			}
			continue;
		}

		if (tag.Equals(TEXT("padding-right"), ESearchCase::IgnoreCase)) {
			if (value.IsNumeric()) {
				segParam.PaddingMargin.Right = FCString::Atof(*value);
			}
			continue;
		}

		if (tag.Equals(TEXT("padding-top"), ESearchCase::IgnoreCase)) {
			if (value.IsNumeric()) {
				segParam.PaddingMargin.Top = FCString::Atof(*value);
			}
			continue;
		}


		if (tag.Equals(TEXT("filePath"), ESearchCase::IgnoreCase) ||
			tag.Equals(TEXT("file_path"), ESearchCase::IgnoreCase)) {

			segParam.FilePath = value;
			continue;
		}

		if (tag.Equals(TEXT("size"), ESearchCase::IgnoreCase))
		{
			TOptional<FVector2D> result = ParseVector2D(value);
			if (result.IsSet())
			{
				segParam.ImageSize = result.GetValue();
			}
			continue;
		}


		if (tag.Equals(TEXT("href"), ESearchCase::IgnoreCase))
		{
			segParam.HypertextReference = value;
			continue;
		}

		if (tag.Equals(TEXT("hoveredColor"), ESearchCase::IgnoreCase))
		{
			TOptional<FLinearColor> color = ParseLinearColor(value);
			if (color.IsSet())
			{
				segParam.HypertextHoveredColor = color.GetValue();
			}
			continue;
		}

		if (tag.Equals(TEXT("visitedColor"), ESearchCase::IgnoreCase))
		{
			TOptional<FLinearColor> color = ParseLinearColor(value);
			if (color.IsSet())
			{
				segParam.HypertextVisitedColor = color.GetValue();
			}

			continue;
		}

		if (tag.Equals(TEXT("eventName"), ESearchCase::IgnoreCase))
		{
			segParam.EventName = value;
			continue;
		}

		if (tag.Equals(TEXT("eventPayload"), ESearchCase::IgnoreCase))
		{
			segParam.EventPayload = value;
			continue;
		}

		if (tag.Equals(TEXT("Tag"), ESearchCase::IgnoreCase))
		{
			segParam.Tags = UKismetStringLibrary::ParseIntoArray(value, TEXT(","));
			for(auto& it : segParam.Tags)
			{
				it.TrimStartAndEndInline();
			}
			continue;
		}



		if(ParseRubyTextSegmentInfo(tag, value, segParam))
		{
			continue;
		}
	}

	return segParam;
}


bool UHorizonDialogueMsgTextBlock::ParseRubyTextSegmentInfo(const FString& InTag, FString InValue, FHorizonDialogueSegmentInfo& InSegParam)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, ParseRubyTextSegmentInfo)
	bool bResult = false;

	do 
	{
		if (InTag.Equals(TEXT("ruby.text"), ESearchCase::IgnoreCase))
		{
			InSegParam.RubyTextInfo.Text = InValue;
			bResult = true;
			break;
		}
		if (InTag.Equals(TEXT("ruby.color"), ESearchCase::IgnoreCase))
		{

			TOptional<FLinearColor> color = ParseLinearColor(InValue);
			if (color.IsSet())
			{
				InSegParam.RubyTextInfo.ColorAndOpacity = color.GetValue();
			}
			break;
		}
		if (InTag.Equals(TEXT("ruby.shadowColor"), ESearchCase::IgnoreCase)) 
		{

			TOptional<FLinearColor> color = ParseLinearColor(InValue);
			if(color.IsSet())
			{ 
				InSegParam.RubyTextInfo.ShadowColorAndOpacity = color.GetValue();
			}
			break;
		}

		//	FVector2D ShadowOffset;
		if (InTag.Equals(TEXT("ruby.shadowOffset"), ESearchCase::IgnoreCase)) 
		{
			TOptional<FVector2D> result = ParseVector2D(InValue);
			if (result.IsSet())
			{
				InSegParam.RubyTextInfo.ShadowOffset = result.GetValue();
			}
			break;
		}


		if (InTag.Equals(TEXT("ruby.fontPath"), ESearchCase::IgnoreCase))
		{
			UFont* font = UHorizonFileSystem::GetInstance()->LoadFont(*InValue);
			InSegParam.RubyTextInfo.Font = FSlateFontInfo(font, Font.Size, Font.TypefaceFontName);
			break;
		}

		if (InTag.Equals(TEXT("ruby.fontType"), ESearchCase::IgnoreCase))
		{
			InSegParam.RubyTextInfo.Font.TypefaceFontName = *InValue;
			break;
		}

		if (InTag.Equals(TEXT("ruby.fontSize"), ESearchCase::IgnoreCase))
		{
			if (InValue.IsNumeric()) {
				InSegParam.RubyTextInfo.Font.Size = FCString::Atoi(*InValue);
			}
			break;
		}

		if (InTag.Equals(TEXT("ruby.padding-left"), ESearchCase::IgnoreCase))
		{
			if (InValue.IsNumeric()) {
				InSegParam.RubyTextInfo.PaddingMargin.Left = FCString::Atof(*InValue);
			}
			break;
		}

		if (InTag.Equals(TEXT("ruby.padding-right"), ESearchCase::IgnoreCase))
		{
			if (InValue.IsNumeric()) {
				InSegParam.RubyTextInfo.PaddingMargin.Right = FCString::Atof(*InValue);
			}
			break;
		}

		if (InTag.Equals(TEXT("ruby.padding-top"), ESearchCase::IgnoreCase))
		{
			if (InValue.IsNumeric()) 
			{
				InSegParam.RubyTextInfo.PaddingMargin.Top = FCString::Atof(*InValue);
			}
			break;
		}

	} while (0);


	return bResult;
}

TOptional<FVector2D> UHorizonDialogueMsgTextBlock::ParseVector2D(FString& InValue)
{
	TOptional<FVector2D> result;
	InValue.ReplaceInline(TEXT("("), TEXT(" "));
	InValue.ReplaceInline(TEXT("{"), TEXT(" "));
	InValue.ReplaceInline(TEXT("["), TEXT(" "));
	InValue.ReplaceInline(TEXT(")"), TEXT(" "));
	InValue.ReplaceInline(TEXT("}"), TEXT(" "));
	InValue.ReplaceInline(TEXT("]"), TEXT(" "));
	InValue.TrimStartAndEndInline();
	//value.Trim();
	//value.TrimTrailing();
	TArray<FString> parse;

	InValue.ParseIntoArray(parse, TEXT(","), true);
	if (parse.Num() >= 2) 
	{
		result = FVector2D(FCString::Atof(*parse[0]), FCString::Atof(*parse[1]));
	}
	return result;
}

TOptional<FLinearColor> UHorizonDialogueMsgTextBlock::ParseLinearColor(FString& InValue)
{
	TOptional<FLinearColor> result;
	InValue.ReplaceInline(TEXT("0x"), TEXT("#"), ESearchCase::IgnoreCase);
	FColor color = FColor::FromHex(InValue);
	float colorBase = (float)255.0f;
	result = FLinearColor(color.R / colorBase, color.G / colorBase, color.B / colorBase, color.A / colorBase);
	return result;
}

FHorizonDialogueBlockInfo UHorizonDialogueMsgTextBlock::CreateDialogueTextBlockInfo(int32 segmentIndex, int32 startIndex, int32 endIndex, const FVector2D& pos) 
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, CreateDialogueTextBlockInfo)
	FHorizonDialogueSegmentInfo& segInfo = DialogueSegmentInfoList[segmentIndex];
	FName name = *FString::Printf(TEXT("%s.%d.%d.%d"), *FString(GetName()), segmentIndex, startIndex, endIndex);

	FVector2D paddingPos = pos + FVector2D(0, segInfo.PaddingMargin.Top);
	const TSharedRef<FSlateFontMeasure>& fontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
	int32 count = (endIndex - startIndex);
	FHorizonDialogueBlockInfo blockInfo;
	blockInfo.Name = name;
	blockInfo.SegmentReferenceIndex = segmentIndex;
	blockInfo.MsgText = segInfo.Text.Mid(startIndex, count);
	if (segInfo.RubyTextInfo.Text.IsSet())
	{
		blockInfo.RubyText = segInfo.RubyTextInfo.Text.GetValue();
	}
	PreBuildBlockDecoration(blockInfo);
	// MsgText
	{
		blockInfo.WidgetWeakPtr = CreateDialogueTextBlock(segInfo);//NewObject<UHorizonTextBlock>(GetOuter());

		if (blockInfo.WidgetWeakPtr.IsValid()) 
		{
			UHorizonTextBlock* pTextBlock = Cast<UHorizonTextBlock>(blockInfo.WidgetWeakPtr.Get());
			RemoveChild(pTextBlock);
			AddChild(pTextBlock);

		

			pTextBlock->SetColorAndOpacity(segInfo.ColorAndOpacity);
			pTextBlock->SetShadowColorAndOpacity(segInfo.ShadowColorAndOpacity.GetSpecifiedColor());
			pTextBlock->SetShadowOffset(segInfo.ShadowOffset);
			pTextBlock->SetFont(segInfo.Font);
			pTextBlock->SetJustification(Justification);
			if (!bIsDialogueMsgText)
			{
				pTextBlock->SetText(FText::FromString(blockInfo.MsgText));
			}
			else 
			{
				//info.TextBlock->SetText(FText::FromString(info.MsgText));
			}

			UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(pTextBlock->Slot);
			canvasPanelSlot->SetAutoSize(true);

		
			canvasPanelSlot->SetPosition(paddingPos);
			//UCanvasPanelSlot* pDialogueTextBlockCanvasPanelSlot = UHorizonWidgetFunctionLibrary::GetParentCanvasPanelSlot(this);
			//verifyf(pDialogueTextBlockCanvasPanelSlot, TEXT("oops! You need put HorizonDialogueMsgTextBlock under the hierarchy of CanvasPanel"));
			//canvasPanelSlot->SetSize(pDialogueTextBlockCanvasPanelSlot->GetSize());

			pTextBlock->SetVisibility(ESlateVisibility::HitTestInvisible); //should not have hit test in UMG editor

			AddBackgroundButton(segmentIndex, blockInfo, canvasPanelSlot, paddingPos);
		}

	}

	// Has RubyText
	if(segInfo.RubyTextInfo.Text.IsSet())
	{
		blockInfo.RubyTextWeakPtr = CreateDialogueRubyTextBlock(segInfo);
		if (blockInfo.RubyTextWeakPtr.IsValid())
		{
			UHorizonTextBlock* pTextBlock = Cast<UHorizonTextBlock>(blockInfo.RubyTextWeakPtr.Get());
			RemoveChild(pTextBlock);
			AddChild(pTextBlock);
			pTextBlock->SetColorAndOpacity(segInfo.RubyTextInfo.ColorAndOpacity);
			pTextBlock->SetShadowColorAndOpacity(segInfo.RubyTextInfo.ShadowColorAndOpacity.GetSpecifiedColor());
			pTextBlock->SetShadowOffset(segInfo.RubyTextInfo.ShadowOffset);
			pTextBlock->SetFont(segInfo.RubyTextInfo.Font);
			pTextBlock->SetJustification(Justification);
			if (!bIsDialogueMsgText)
			{
				pTextBlock->SetText(FText::FromString(blockInfo.RubyText));
			}

			UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(pTextBlock->Slot);
			canvasPanelSlot->SetAutoSize(true);
			CalculateBlockSize(blockInfo);
			SetupRubyTextPosition(paddingPos, blockInfo, segInfo);
			pTextBlock->SetVisibility(ESlateVisibility::HitTestInvisible); //should not have hit test in UMG editor

		}

	}



	CalculateBlockSize(blockInfo);
	BuildBlockDecoration(blockInfo);


	return blockInfo;
}

FHorizonDialogueBlockInfo UHorizonDialogueMsgTextBlock::CreateDialogueImageBlockInfo(int32 segmentIndex, const FVector2D& pos)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, CreateDialogueImageBlockInfo)
	FName name = *FString::Printf(TEXT("%s.image%d"), *FString(GetName()), segmentIndex);

	FHorizonDialogueBlockInfo blockInfo;
	blockInfo.Name = name;
	blockInfo.SegmentReferenceIndex = segmentIndex;
	PreBuildBlockDecoration(blockInfo);
	auto& segInfo = DialogueSegmentInfoList[segmentIndex];
	blockInfo.WidgetWeakPtr = CreateDialogueImage(segInfo);//NewObject<UHorizonImage>(GetOuter());
	if (blockInfo.WidgetWeakPtr.IsValid()) {

		UHorizonImage* pImage = Cast<UHorizonImage>(blockInfo.WidgetWeakPtr.Get());
		pImage->UVRegion.bIsValid = false;
		AddChild(pImage);
		int32 width = 32;
		int32 height = 32;
		UTexture2D* pTexture = nullptr;
		UMaterial* pMaterial = nullptr;
		UPaperSprite* pSprite = nullptr;
		
		if (segInfo.FilePath.IsSet()) 
		{
			FSoftObjectPath assetRef = segInfo.FilePath.GetValue();
			auto loadedObject = assetRef.TryLoad();
			pSprite = Cast<UPaperSprite>(loadedObject);
			pMaterial = Cast<UMaterial>(loadedObject);
			if (nullptr == pSprite && nullptr == pMaterial)
			{
				pTexture = UHorizonFileSystem::GetInstance()->LoadTexture2D(assetRef.ToString(), width, height);
			}


		}
		else 
		{
			if (segInfo.StyleInfoReferenceIndex >= 0)
			{
				
				if (segInfo.SegmentStyleReferenceIndex >= 0)
				{
					auto& segStyleList = StyleInfoList[segInfo.StyleInfoReferenceIndex]->SegmentStyleList;
					auto& segInfoStyle = segStyleList[segInfo.SegmentStyleReferenceIndex];
					pTexture = segInfoStyle.Texture2D.LoadSynchronous();
					pMaterial = segInfoStyle.Material.LoadSynchronous();
					pSprite = segInfoStyle.PaperSprite.LoadSynchronous();
				}
			}
			else
			{		
				if (segInfo.SegmentStyleReferenceIndex >= 0)
				{
					auto& segStyleList = SegmentStyleList;
					auto& segInfoStyle = segStyleList[segInfo.SegmentStyleReferenceIndex];
					pTexture = segInfoStyle.Texture2D.LoadSynchronous();
					pMaterial = segInfoStyle.Material.LoadSynchronous();
					pSprite = segInfoStyle.PaperSprite.LoadSynchronous();
				}
			}


		}



		if (pTexture) 
		{
			pImage->SetBrushFromTexture(pTexture, true);
		}


		if (pMaterial) 
		{
			pImage->SetBrushFromMaterial(pMaterial);
		}

		if (pSprite)
		{
			pImage->Brush.SetResourceObject(pSprite);

		}

		pImage->SynchronizeProperties();
		UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(pImage->Slot);
		if (segInfo.ImageSize.IsSet()) 
		{
			canvasPanelSlot->SetSize(segInfo.ImageSize.GetValue());
		}
		FVector2D paddingPos = pos + FVector2D(0, (int32)segInfo.PaddingMargin.Top);
		canvasPanelSlot->SetPosition(paddingPos);
		pImage->SetColorAndOpacity(segInfo.ColorAndOpacity.GetSpecifiedColor());
		if (bIsDialogueMsgText) 
		{
			pImage->SetVisibility(ESlateVisibility::Hidden);
		}
		else 
		{
			pImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
		AddBackgroundButton(segmentIndex, blockInfo, canvasPanelSlot, paddingPos);

	}





	CalculateBlockSize(blockInfo);
	BuildBlockDecoration(blockInfo);
	return blockInfo;
}

FHorizonDialogueBlockInfo UHorizonDialogueMsgTextBlock::CreateDialogueFlipbookBlockInfo(int32 segmentIndex, const FVector2D& pos) 
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, CreateDialogueFlipbookBlockInfo)
	FName name = *FString::Printf(TEXT("%s.PaperFlipbookWidget%d"), *FString(GetName()), segmentIndex);
	auto& segInfo = DialogueSegmentInfoList[segmentIndex];
	FHorizonDialogueBlockInfo blockInfo;
	blockInfo.Name = name;
	blockInfo.SegmentReferenceIndex = segmentIndex;
	PreBuildBlockDecoration(blockInfo);
	blockInfo.WidgetWeakPtr = CreateDialogueFlipbook(segInfo);//NewObject<UHorizonFlipbookWidget>(GetOuter());
	if (blockInfo.WidgetWeakPtr.IsValid()) {
		UHorizonFlipbookWidget* pWidget = Cast<UHorizonFlipbookWidget>(blockInfo.WidgetWeakPtr.Get());
		//FStringAssetReference assetRef = segInfo.ImageFilePath.GetValue();
		//UHorizonFileSystem::LoadPaperFlipbook
		UPaperFlipbook* flipbook = nullptr;
		if (segInfo.FilePath.IsSet())
		{
			FSoftObjectPath assetRef = segInfo.FilePath.GetValue();
			flipbook = UHorizonFileSystem::GetInstance()->LoadPaperFlipbook(assetRef.ToString());

		}
		else if (segInfo.StyleInfoReferenceIndex >= 0)
		{
			if (segInfo.SegmentStyleReferenceIndex >= 0)
			{
				auto& segStyleList = StyleInfoList[segInfo.StyleInfoReferenceIndex]->SegmentStyleList;
				auto& segInfoStyle = segStyleList[segInfo.SegmentStyleReferenceIndex];
				flipbook = segInfoStyle.PaperFlipbook.LoadSynchronous();
			}
		}
		else
		{
			if (segInfo.SegmentStyleReferenceIndex >= 0)
			{
				auto& segStyleList = SegmentStyleList;
				auto& segInfoStyle = segStyleList[segInfo.SegmentStyleReferenceIndex];
				flipbook = segInfoStyle.PaperFlipbook.LoadSynchronous();
			}
		}




		if (flipbook)
		{

			pWidget->SetFlipbook(flipbook);
			pWidget->SetColorAndOpacity(segInfo.ColorAndOpacity.GetSpecifiedColor());
			AddChild(pWidget);
			UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(pWidget->Slot);
			if (segInfo.ImageSize.IsSet()) {
				canvasPanelSlot->SetSize(segInfo.ImageSize.GetValue());
			}
			FVector2D paddingPos = pos + FVector2D(0, (int32)segInfo.PaddingMargin.Top);
			canvasPanelSlot->SetPosition(paddingPos);
			pWidget->SetColorAndOpacity(segInfo.ColorAndOpacity.GetSpecifiedColor());
			if (bIsDialogueMsgText) {
				pWidget->SetVisibility(ESlateVisibility::Hidden);
			}
			else {
				pWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
			}
			pWidget->SynchronizeProperties();
			AddBackgroundButton(segmentIndex, blockInfo, canvasPanelSlot, paddingPos);

		}
		
	}


	CalculateBlockSize(blockInfo);
	BuildBlockDecoration(blockInfo);
	return blockInfo;
}

void UHorizonDialogueMsgTextBlock::AddBackgroundButton(
	int32 segmentIndex,
	FHorizonDialogueBlockInfo& blockInfo,
	UCanvasPanelSlot* pCanvasPanelSlot,
	const FVector2D& paddingPos)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, AddBackgroundButton)
	if (pCanvasPanelSlot)
	{
		auto& segInfo = DialogueSegmentInfoList[segmentIndex];
		if (!blockInfo.WidgetBackgroundWeakPtr.IsValid())
		{
			if (!segInfo.FilePath.IsSet() && segInfo.HypertextReference.IsSet())
			{
				// Use DefaultButtonStyleWidget for HypertextReference
				segInfo.BackgroundButtonClass = DefaultButtonStyleWidgetClass;
			}

			if (segInfo.FilePath.IsSet() && segInfo.HypertextReference.IsSet())
			{
				// Try Load ButtonStyleWidget BlueprintClass
				auto filePath = UHorizonWidgetFunctionLibrary::NormalizeBlueprintClassFilePath(segInfo.FilePath.GetValue());
				FSoftClassPath clsRef = filePath;
				UClass* blueprintClass = clsRef.TryLoadClass<UHorizonButton>();
				if (blueprintClass)
				{
					segInfo.BackgroundButtonClass = blueprintClass;
				}
			}




			if (segInfo.BackgroundButtonClass)
			{
				blockInfo.WidgetBackgroundWeakPtr = NewObject<UHorizonButton>(GetOuter(),
					segInfo.BackgroundButtonClass, NAME_None, EObjectFlags::RF_NoFlags,
					nullptr, true);
				AddChild(blockInfo.WidgetBackgroundWeakPtr.Get());
			}
		}
		auto pButton = Cast<UHorizonButton>(blockInfo.WidgetBackgroundWeakPtr.Get());
		if (pButton)
		{
			FHorizonDialogueHypertextResult hyperTextResult;
			hyperTextResult.DialogueMsgTextBlock = this;
			hyperTextResult.SegmentIndex = segmentIndex;
			hyperTextResult.LineIndex = DialogueLineInfoList.Num() - 1;
			hyperTextResult.BlockIndex = DialogueLineInfoList.Last().DialogueBlockInfoList.Num();
			hyperTextResult.HypertextReference = segInfo.HypertextReference.Get(FString());

			FString Pair, PairKey, PairValue;
			auto tempStr = hyperTextResult.HypertextReference;
			while (UGameplayStatics::GrabOption(tempStr, Pair))
			{
				UGameplayStatics::GetKeyValue(Pair, PairKey, PairValue);
				hyperTextResult.UrlEncodeMap.Emplace(PairKey, PairValue);
			}
			//UGameplayStatics::GetKeyValue();
			//FString NewPlayerName = UGameplayStatics::ParseOption(Options, TEXT("Name")).Left(20);
			//
			if (!pButton->OnClickedDelegateNative.IsBoundToObject(this))
			{
				pButton->OnClickedDelegateNative.AddWeakLambda(this,
					[this, hyperTextResult](UHorizonButton* InButton) {
						OnHypertextClickedDelegate.Broadcast(hyperTextResult);
						OnHypertextClickedDelegateNative.Broadcast(hyperTextResult);
					}
				);
			}
			if (!pButton->OnPressedDelegateNative.IsBoundToObject(this))
			{
				pButton->OnPressedDelegateNative.AddWeakLambda(this,
					[this, hyperTextResult](UHorizonButton* InButton) {

						OnHypertextPressedDelegate.Broadcast(hyperTextResult);
						OnHypertextPressedDelegateNative.Broadcast(hyperTextResult);
					}
				);
			}
			if (!pButton->OnReleasedDelegateNative.IsBoundToObject(this))
			{
				pButton->OnReleasedDelegateNative.AddWeakLambda(this,
					[this, hyperTextResult](UHorizonButton* InButton) {

						OnHypertextReleasedDelegate.Broadcast(hyperTextResult);
						OnHypertextReleasedDelegateNative.Broadcast(hyperTextResult);

						if (hyperTextResult.SegmentIndex < DialogueSegmentInfoList.Num())
						{
							auto& tmpSegInfo = DialogueSegmentInfoList[hyperTextResult.SegmentIndex];
							tmpSegInfo.bHypertextVisited = true;
							SetSegmentColor(hyperTextResult.SegmentIndex, hyperTextResult.LineIndex, tmpSegInfo.HypertextVisitedColor);
						}
					}
				);
			}
			if (!pButton->OnHoveredDelegateNative.IsBoundToObject(this))
			{
				pButton->OnHoveredDelegateNative.AddWeakLambda(this,
					[this, hyperTextResult](UHorizonButton* InButton) {
						OnHypertextHoveredDelegate.Broadcast(hyperTextResult);
						OnHypertextHoveredDelegateNative.Broadcast(hyperTextResult);
						if (hyperTextResult.SegmentIndex < DialogueSegmentInfoList.Num())
						{
							auto& tmpSegInfo = DialogueSegmentInfoList[hyperTextResult.SegmentIndex];
							SetSegmentColor(hyperTextResult.SegmentIndex, hyperTextResult.LineIndex, tmpSegInfo.HypertextHoveredColor);

						}

					}
				);
			}

			if (!pButton->OnUnhoveredDelegateNative.IsBoundToObject(this))
			{
				pButton->OnUnhoveredDelegateNative.AddWeakLambda(this,
					[this, hyperTextResult, pButton](UHorizonButton* InButton) {
						OnHypertextUnhoveredDelegate.Broadcast(hyperTextResult);
						OnHypertextUnhoveredDelegateNative.Broadcast(hyperTextResult);
						if (hyperTextResult.SegmentIndex < DialogueSegmentInfoList.Num())
						{
							auto& tmpSegInfo = DialogueSegmentInfoList[hyperTextResult.SegmentIndex];
							FSlateColor color = tmpSegInfo.ColorAndOpacity;
							if (tmpSegInfo.bHypertextVisited)
							{
								color = tmpSegInfo.HypertextVisitedColor;
							}

							SetSegmentColor(hyperTextResult.SegmentIndex, hyperTextResult.LineIndex, color);
						}
					}
				);
			}

			UCanvasPanelSlot* pButtonCanvasPanelSlot = Cast<UCanvasPanelSlot>(pButton->Slot);
			CalculateBlockSize(blockInfo);
			pButtonCanvasPanelSlot->SetSize(blockInfo.BlockSize);
			pButtonCanvasPanelSlot->SetPosition(paddingPos);


			pButtonCanvasPanelSlot->SetZOrder(pCanvasPanelSlot->ZOrder - 1);
			//pButton->SetVisibility(ESlateVisibility::Visible);
		}



	}
}

void UHorizonDialogueMsgTextBlock::AddDialogueBlock(FHorizonDialogueLineInfo& lineInfo, FHorizonDialogueBlockInfo&& blockInfo)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, AddDialogueBlock)
	auto& segInfo = DialogueSegmentInfoList[blockInfo.SegmentReferenceIndex];
	LoadSound(segInfo, blockInfo);

	UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(blockInfo.WidgetWeakPtr->Slot);
	verifyf(canvasPanelSlot, TEXT("oops! something error in UHorizonDialogueMsgTextBlock::AddDialogueBlock"));
	lineInfo.Position = FVector2D(LineMargin.Left, canvasPanelSlot->GetPosition().Y);
	TexLength += blockInfo.MsgText.Len();
	lineInfo.DialogueBlockInfoList.Emplace(Forward<FHorizonDialogueBlockInfo>(blockInfo));
}



void UHorizonDialogueMsgTextBlock::LoadSound(FHorizonDialogueSegmentInfo& segInfo,
	FHorizonDialogueBlockInfo& blockInfo)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, LoadSound)
	USoundBase* pDialogueSound = nullptr;
	if (segInfo.DialogueSoundPath.IsSet())
	{
		pDialogueSound = UHorizonFileSystem::GetInstance()->LoadSound(segInfo.DialogueSoundPath.GetValue());
	}
	else
	{

		if (segInfo.StyleInfoReferenceIndex >= 0)
		{
			if (segInfo.SegmentStyleReferenceIndex >= 0)
			{
				auto& segStyleList = StyleInfoList[segInfo.StyleInfoReferenceIndex]->SegmentStyleList;
				auto& segInfoStyle = segStyleList[segInfo.SegmentStyleReferenceIndex];
				pDialogueSound = segInfoStyle.DialogueSound.LoadSynchronous();
			}
		}
		else
		{
			if (segInfo.SegmentStyleReferenceIndex >= 0)
			{
				auto& segStyleList = SegmentStyleList;
				auto& segInfoStyle = segStyleList[segInfo.SegmentStyleReferenceIndex];
				pDialogueSound = segInfoStyle.DialogueSound.LoadSynchronous();
			}
		}
	}
	segInfo.DialogueSound = pDialogueSound;

}




void UHorizonDialogueMsgTextBlock::SetSegmentColor(int32 segmentIndex, int32 lineIndex, const FSlateColor& InColor)
{
	for (auto& lineInfoIt : DialogueLineInfoList)
	{
		for (auto& blockInfoIt : lineInfoIt.DialogueBlockInfoList)
		{
			if (blockInfoIt.SegmentReferenceIndex == segmentIndex)
			{
				UHorizonTextBlock* pTextBlock = Cast<UHorizonTextBlock>(blockInfoIt.WidgetWeakPtr.Get());
				if (pTextBlock)
				{
					pTextBlock->SetColorAndOpacity(InColor);
				}
				UHorizonImage* pImage = Cast<UHorizonImage>(blockInfoIt.WidgetWeakPtr.Get());
				if (pImage)
				{
					pImage->SetColorAndOpacity(InColor.GetSpecifiedColor());
				}
				UHorizonFlipbookWidget* pFlipbook = Cast<UHorizonFlipbookWidget>(blockInfoIt.WidgetWeakPtr.Get());
				if (pFlipbook)
				{
					pFlipbook->SetColorAndOpacity(InColor.GetSpecifiedColor());

				}
			}

		}
	}
}







#endif //============================End Dialogue: Rebuild=============================




#if 1 //============================Begin Dialogue Method: Text Overflow=============================
EHorizonDialogueTextOverflowWrapMethod UHorizonDialogueMsgTextBlock::GetTextOverflowWrapMethod() const
{
	return TextOverFlowWrapMethod;
}

void UHorizonDialogueMsgTextBlock::SetTextOverflowWrapMethod(EHorizonDialogueTextOverflowWrapMethod InOverflowWrapMethod)
{
	TextOverFlowWrapMethod = InOverflowWrapMethod;
}

bool UHorizonDialogueMsgTextBlock::TryAddNewLine(
	TCHAR currentChar, float& currentLineWidth,
	FVector2D& blockPos,
	const int& currentSegInfoIndex, int& segStartCharIndex, int& segCharIndex)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, TryAddNewLine)
	bool bResult = (currentChar == '\n') || (currentChar == '\r');
	if (bResult) {
		//float linePosY = (DialogueLineInfoList.Last().MaxLineHeight * (DialogueLineInfoList.Num()-1)) + lineOffsetY;
		AddDialogueBlock(DialogueLineInfoList.Last(),
			CreateDialogueTextBlockInfo(currentSegInfoIndex, segStartCharIndex, segCharIndex, blockPos));

		//skip this char and advance for next line
		++segCharIndex;
		segStartCharIndex = segCharIndex;

		blockPos.X = LineMargin.Left;
		//new line
		DialogueLineInfoList.Last().LineWidth = currentLineWidth;
		DialogueLineInfoList.Emplace(FHorizonDialogueLineInfo());
		currentLineWidth = 0;
	}

	return bResult;

}

bool UHorizonDialogueMsgTextBlock::TryAddDialogueBlock(
	const float& maxLineWidth,
	const FVector2D& oneWordSize, float& currentLineWidth,
	FVector2D& blockPos,
	const int& currentSegInfoIndex, int& segStartCharIndex, int& segCharIndex,
	bool bWordBreakMode)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, TryAddDialogueBlock)
	bool bResult = false;

	if (currentLineWidth > (maxLineWidth - oneWordSize.X))
	{
		if (bWordBreakMode && (segStartCharIndex == segCharIndex))//currentLineWidth == 0)
		{
			//each line should has one char at least
			++segCharIndex;
		}

		if (segStartCharIndex != segCharIndex)
		{
			AddDialogueBlock(DialogueLineInfoList.Last(),
				CreateDialogueTextBlockInfo(currentSegInfoIndex, segStartCharIndex, segCharIndex, blockPos));
			//ensureMsgf(segStartCharIndex != segCharIndex, TEXT("oops! something error"));
			segStartCharIndex = segCharIndex;
		}

		blockPos.X = LineMargin.Left;
		//new line
		auto& lastLineInfo = DialogueLineInfoList.Last();
		lastLineInfo.LineWidth = currentLineWidth;
		if (0 == lastLineInfo.LineWidth)
		{
			// Remove empty line with only space for some edge case
			DialogueLineInfoList.RemoveAt(DialogueLineInfoList.Num()-1);
		}
		DialogueLineInfoList.Emplace(FHorizonDialogueLineInfo());
		//don't skip this char and advance for next line
		currentLineWidth = 0;
		bResult = true;

	}
	return bResult;

}



void UHorizonDialogueMsgTextBlock::TextOverflowWarpNormal_WordBreakImplement(int32& segCharIndex, int32& segWordCharEndIndex,
	float& currentLineWidth, FVector2D& blockPos, const int32& currentSegInfoIndex,
	const float& maxLineWidth, const FHorizonDialogueSegmentInfo& segInfo)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, TextOverflowWarpNormal_WordBreakImplement)
	int32 segStartCharIndex = segCharIndex;

	const TSharedRef< FSlateFontMeasure >& FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
	while (segCharIndex < segWordCharEndIndex) {

		//first line only calculate from top
		if (DialogueLineInfoList.Num() == 1) {
			blockPos.Y = LineMargin.Top;
		}
		else {
			blockPos.Y = DialogueLineInfoList.Last(1).Position.Y + DialogueLineInfoList.Last(1).MaxLineHeight + LineMargin.Bottom;
		}




		FVector2D oneCharSize = FontMeasure->Measure(segInfo.Text, segCharIndex, segCharIndex + 1, segInfo.Font);


		CalculateMaxLineHeight(DialogueLineInfoList.Last(), segInfo, oneCharSize);


		bool bEndOfLine = TryAddDialogueBlock(maxLineWidth, oneCharSize,
			currentLineWidth, blockPos,
			currentSegInfoIndex,
			segStartCharIndex, segCharIndex, true);
		if (bEndOfLine)
		{
			continue;
		}

		//advance for next char
		currentLineWidth += oneCharSize.X;
		++segCharIndex;


	};
	// Put rest text into next line block for Current long word
	segWordCharEndIndex = segStartCharIndex;


}

void  UHorizonDialogueMsgTextBlock::TextOverflowWarpNormal_Implement(float& currentLineWidth, FVector2D& blockPos, const int& currentSegInfoIndex,
	const float& maxLineWidth, const FHorizonDialogueSegmentInfo& segInfo)
{
	DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(UHorizonDialogueMsgTextBlock, TextOverflowWarpNormal_Implement)


	TArray<TCHAR> charList;
	charList.Emplace(' ');
	charList.Emplace('\t');
	charList.Emplace('\n');
	charList.Emplace('\r');
	//TODO: implement
	const TSharedRef< FSlateFontMeasure >& FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
	int32 segStartCharIndex = 0;
	int32 segCharIndex = 0;
	while (segCharIndex < segInfo.Text.Len()) {
		//first line only calculate from top
		if (DialogueLineInfoList.Num() == 1) {
			blockPos.Y = LineMargin.Top;
		}
		else {
			blockPos.Y = DialogueLineInfoList.Last(1).Position.Y + DialogueLineInfoList.Last(1).MaxLineHeight + LineMargin.Bottom;
		}
		//segInfo.Text.fi
		//index to space


		TCHAR currentChar = segInfo.Text[segCharIndex];

		if (TryAddNewLine(currentChar,
			currentLineWidth, blockPos,
			currentSegInfoIndex,
			segStartCharIndex, segCharIndex))
		{
			continue;
		}


		int32 segWordCharEndIndex = segCharIndex;
		auto charCodePoint = segInfo.Text[segWordCharEndIndex];
		if ((charCodePoint >= 0 && charCodePoint <= 255) || // English
			(charCodePoint >= 256 && charCodePoint <= 546) ||
			(charCodePoint >= 1024 && charCodePoint <= 1314) // Russian 
			)
		{
			segWordCharEndIndex = UHorizonWidgetFunctionLibrary::FindCharIndexFromStr(segCharIndex, charList, segInfo.Text);
			//plus 1 if current char is
			if (segWordCharEndIndex == segCharIndex)
			{
				++segWordCharEndIndex;
			}

		}
		else
		{
			segWordCharEndIndex = segCharIndex + 1;
		}
		//segInfo.Text.
#if defined(UE_BUILD_DEBUG)
		auto oneWordDebug = UKismetStringLibrary::GetSubstring(segInfo.Text, segCharIndex, segWordCharEndIndex - segCharIndex);
#endif


		FVector2D oneWordSize = FontMeasure->Measure(segInfo.Text, segCharIndex, segWordCharEndIndex, segInfo.Font);
		if (currentChar == '\t')
		{
			oneWordSize.X += Font.Size;
		}



		CalculateMaxLineHeight(DialogueLineInfoList.Last(), segInfo, oneWordSize);


		//if (currentLineWidth != 0) 
		{
			if (segStartCharIndex == segCharIndex)
			{
				if (maxLineWidth - oneWordSize.X > 0)
				{
					if (FMath::IsNearlyZero(currentLineWidth))
					{
						// try add one char if this is beginning of current  line
						++segCharIndex;
					}
				}
				else
				{
					//handle overflow word in current line if at start char
					TextOverflowWarpNormal_WordBreakImplement(segCharIndex, segWordCharEndIndex, currentLineWidth, blockPos,
						currentSegInfoIndex, maxLineWidth, segInfo);
					segStartCharIndex = segWordCharEndIndex;
					continue;
				}

			}

			bool bEndOfLine = TryAddDialogueBlock(maxLineWidth, oneWordSize,
				currentLineWidth, blockPos,
				currentSegInfoIndex,
				segStartCharIndex, segCharIndex);
			if (bEndOfLine)
			{
				if (' ' == currentChar && 0 == currentLineWidth)
				{
					++segCharIndex; //skip space char at beginning of line
					++segStartCharIndex;
				}

				if (0 == currentLineWidth && oneWordSize.X > maxLineWidth)
				{
					//handle overflow word in next line
					TextOverflowWarpNormal_WordBreakImplement(segCharIndex, segWordCharEndIndex, currentLineWidth, blockPos,
						currentSegInfoIndex, maxLineWidth, segInfo);
					segStartCharIndex = segWordCharEndIndex;
				}
				continue;
			}
		}

		currentLineWidth += oneWordSize.X;
		//process to next word

		segCharIndex += (segWordCharEndIndex - segCharIndex);
	};
	{
		//float linePosY = (DialogueLineInfoList.Last().MaxLineHeight * (DialogueLineInfoList.Num() - 1)) + lineOffsetY;
		DialogueLineInfoList.Last().LineWidth = currentLineWidth;
		AddDialogueBlock(DialogueLineInfoList.Last(),
			CreateDialogueTextBlockInfo(currentSegInfoIndex, segStartCharIndex, segCharIndex, blockPos));
		blockPos.X = LineMargin.Left + currentLineWidth;
	}
}

void UHorizonDialogueMsgTextBlock::TextOverflowWarpBreakAll_Implement(
	float& currentLineWidth, FVector2D& blockPos, const int& currentSegInfoIndex,
	const float& maxLineWidth, const FHorizonDialogueSegmentInfo& segInfo)
{

	const TSharedRef< FSlateFontMeasure >& FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
	int32 segStartCharIndex = 0;
	int32 segCharIndex = 0;
	while (segCharIndex < segInfo.Text.Len()) {

		//first line only calculate from top
		if (DialogueLineInfoList.Num() == 1) {
			blockPos.Y = LineMargin.Top;
		}
		else {
			blockPos.Y = DialogueLineInfoList.Last(1).Position.Y + DialogueLineInfoList.Last(1).MaxLineHeight + LineMargin.Bottom;
		}


		TCHAR currentChar = segInfo.Text[segCharIndex];

		if (TryAddNewLine(currentChar,
			currentLineWidth, blockPos,
			currentSegInfoIndex,
			segStartCharIndex, segCharIndex))
		{
			continue;
		}


		FVector2D oneWordSize = FontMeasure->Measure(segInfo.Text, segCharIndex, segCharIndex + 1, segInfo.Font);

		if (currentChar == '\t') {
			oneWordSize.X = Font.Size * 2;
		}

		CalculateMaxLineHeight(DialogueLineInfoList.Last(), segInfo, oneWordSize);
		


		if (TryAddDialogueBlock(maxLineWidth, oneWordSize,
			currentLineWidth, blockPos,
			currentSegInfoIndex,
			segStartCharIndex, segCharIndex, true))
		{
			continue;
		}

		//advance for next char
		currentLineWidth += oneWordSize.X;
		++segCharIndex;


	};
	{
		//float linePosY = (DialogueLineInfoList.Last().MaxLineHeight * (DialogueLineInfoList.Num() - 1)) + lineOffsetY;
		DialogueLineInfoList.Last().LineWidth = currentLineWidth;
		AddDialogueBlock(DialogueLineInfoList.Last(),
			CreateDialogueTextBlockInfo(currentSegInfoIndex, segStartCharIndex, segCharIndex, blockPos));
		blockPos.X = LineMargin.Left + currentLineWidth;
	}
}





#endif //============================End Dialogue Method: Text Overflow=============================

#if 1 //============================Begin CreateWidget=============================



UHorizonImage* UHorizonDialogueMsgTextBlock::CreateDialogueImage(FHorizonDialogueSegmentInfo& InSegInfo)
{
	return NewObject<UHorizonImage>(GetOuter());
}

UHorizonFlipbookWidget* UHorizonDialogueMsgTextBlock::CreateDialogueFlipbook(FHorizonDialogueSegmentInfo& InSegInfo)
{
	return NewObject<UHorizonFlipbookWidget>(GetOuter());
}

UHorizonTextBlock* UHorizonDialogueMsgTextBlock::CreateDialogueTextBlock(FHorizonDialogueSegmentInfo& InSegInfo)
{
	return NewObject<UHorizonTextBlock>(GetOuter());
}

UHorizonTextBlock* UHorizonDialogueMsgTextBlock::CreateDialogueRubyTextBlock(FHorizonDialogueSegmentInfo& InSegInfo)
{
	return NewObject<UHorizonTextBlock>(GetOuter());
}

#endif //============================End CreateWidget=============================


#undef LOCTEXT_NAMESPACE
