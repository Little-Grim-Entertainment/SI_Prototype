// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net


#include "Widget/HorizonDialogueStyleInfo.h"
#include "HorizonUIPrivate.h"
#include "Widget/HorizonWidgetFunctionLibrary.h"


#if WITH_EDITOR

void UHorizonDialogueStyleInfo::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) 
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//auto nameCPP = PropertyChangedEvent.Property->GetNameCPP();
	//// FIX crash
	//if (nameCPP != GET_MEMBER_NAME_CHECKED(UHorizonDialogueMsgTextBlock, SegmentStyleList).ToString() &&
	//	nameCPP != TEXT("SpecifiedColor"))
	//{
	//	Super::PostEditChangeProperty(PropertyChangedEvent);
	//}

	////


}

void UHorizonDialogueStyleInfo::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
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
	//	if (nameCPP == GET_MEMBER_NAME_CHECKED(UHorizonDialogueStyleInfo, SegmentStyleList).ToString())
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

#endif