//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "HorizonRadioButton.h"
//
//
//void UHorizonRadioButton::OnWidgetRebuilt()
//{
//	Super::OnWidgetRebuilt();
//	if (!IsDesignTime())
//	{
//		OnCheckStateChanged.RemoveDynamic(this, &ThisClass::NativeOnCheckStateChanged);
//		OnCheckStateChanged.AddDynamic(this, &ThisClass::NativeOnCheckStateChanged);
//		TryChecked();
//	}
//
//}
//
//#if WITH_EDITOR
//
//const FText UHorizonRadioButton::GetPaletteCategory()
//{
//	return NSLOCTEXT("HorizonPlugin", "HorizonPlugin", "HorizonPlugin");
//}
//
//
//
//
//
//void UHorizonRadioButton::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
//	Super::PostEditChangeProperty(PropertyChangedEvent);
//
//}
//
//
//
//
//
//#endif //#if WITH_EDITOR
//
//void UHorizonRadioButton::SetChecked()
//{
//	bool _bIsChecked = IsChecked();
//	NativeOnCheckStateChanged(true);
//	if (!_bIsChecked)
//	{
//		OnCheckedDelegate.Broadcast();
//		OnCheckedDelegateNative.Broadcast();
//	}
//}
//
//void UHorizonRadioButton::NativeOnCheckStateChanged(bool bIsChecked)
//{
//
//	auto pParentPanel = GetParent();
//	if (pParentPanel)
//	{
//		TArray<UWidget*> allChridren = pParentPanel->GetAllChildren();
//		for (auto& it : allChridren)
//		{
//			UHorizonRadioButton* pRadioButton = Cast<UHorizonRadioButton>(it);
//			if (nullptr == pRadioButton) { continue; }
//			if (pRadioButton != this)
//			{
//				// uncheck others if the widget is checked
//				if (pRadioButton->GetCheckedState() == ECheckBoxState::Checked)
//				{
//					pRadioButton->SetIsChecked(false);
//					pRadioButton->OnUnCheckedDelegate.Broadcast();
//					pRadioButton->OnUnCheckedDelegateNative.Broadcast();
//
//				}
//			}
//			else
//			{
//				if (GetCheckedState() != ECheckBoxState::Checked)
//				{
//					// click same widget, force checked
//					SetIsChecked(true);
//				}
//				else
//				{
//					OnCheckedDelegate.Broadcast();
//					OnCheckedDelegateNative.Broadcast();
//				}
//			}
//		}
//	}
//
//}
//
//void UHorizonRadioButton::TryChecked()
//{
//	bool bHasChecked = false;
//	auto pParentPanel = GetParent();
//	if (pParentPanel)
//	{
//		TArray<UWidget*> allChridren = pParentPanel->GetAllChildren();
//		for (auto& it : allChridren)
//		{
//			UHorizonRadioButton* pRadioButton = Cast<UHorizonRadioButton>(it);
//			if (pRadioButton)
//			{
//				if (pRadioButton->IsChecked())
//				{
//					bHasChecked = true;
//					break;
//				}
//			}
//		}
//	}
//	if (false == bHasChecked)
//	{
//		SetChecked();
//	}
//}
