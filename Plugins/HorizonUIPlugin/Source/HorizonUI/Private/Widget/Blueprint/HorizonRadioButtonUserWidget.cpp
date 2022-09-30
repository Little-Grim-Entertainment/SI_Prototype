// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#include "Widget/Blueprint/HorizonRadioButtonUserWidget.h"
#include "HorizonUIPrivate.h"
#include "Widget/Components/HorizonRadioButton.h"

UHorizonRadioButtonUserWidget::UHorizonRadioButtonUserWidget()
{
	Text_Main = FText::FromString(TEXT("Text Block"));
	bIsFocusable = true;
	Visibility = ESlateVisibility::Visible;
}

void UHorizonRadioButtonUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (CheckBox_Main)
	{
		CheckBox_Main->OnCheckStateChanged.AddDynamic(this, &ThisClass::NativeOnCheckStateChanged);
	}
}

void UHorizonRadioButtonUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CheckBox_Main)
	{
		TryChecked();

	}

}


void UHorizonRadioButtonUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UHorizonRadioButtonUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UHorizonRadioButtonUserWidget::OnSynchronizeProperties_Implementation()
{
	Super::OnSynchronizeProperties_Implementation();
	GatherAllRadioButton();
	if (TextBlock_Main)
	{
		TextBlock_Main->SetText(FText::AsCultureInvariant(Text_Main));
	}

	if (bCheckedByDefault)
	{
		SetChecked();	
	}

}



void UHorizonRadioButtonUserWidget::SetChecked()
{

	NativeOnCheckStateChanged(true);

	
}

bool UHorizonRadioButtonUserWidget::IsChecked()
{
	if (CheckBox_Main)
	{
		return CheckBox_Main->IsChecked();
	}
	return false;
}



void UHorizonRadioButtonUserWidget::NativeOnCheckStateChanged(bool bIsChecked)
{
	if (AllRadioButtons.Num() > 0)
	{
		// uncheck others if the widget is checked
		for (auto& it : AllRadioButtons)
		{
			UHorizonRadioButtonUserWidget* pRadioButtonWidget = Cast<UHorizonRadioButtonUserWidget>(it);
			if (nullptr == pRadioButtonWidget || nullptr == pRadioButtonWidget->CheckBox_Main) { continue; }
			if (pRadioButtonWidget != this)
			{
			
				if (pRadioButtonWidget->IsChecked())
				{
					pRadioButtonWidget->HandleOnCheckStateChanged(false);

				}
			}
		}

		// check this widget
		for (auto& it : AllRadioButtons)
		{
			UHorizonRadioButtonUserWidget* pRadioButtonWidget = Cast<UHorizonRadioButtonUserWidget>(it);
			if (nullptr == pRadioButtonWidget || nullptr == pRadioButtonWidget->CheckBox_Main) { continue; }
			if (pRadioButtonWidget == this)
			{
				bool _bIsChecked = IsChecked();

				if (!_bIsChecked && !bIsChecked)
				{
					HandleOnCheckStateChanged(true);
				}
				else
				{
					HandleOnCheckStateChanged(bIsChecked);
				}
				break;
			}
		}
	}
	else
	{
		HandleOnCheckStateChanged(bIsChecked);
	}


}




void UHorizonRadioButtonUserWidget::HandleOnCheckStateChanged(bool bIsChecked)
{
	if (CheckBox_Main)
	{
		CheckBox_Main->SetIsChecked(bIsChecked);
		BP_OnCheckStateChanged(bIsChecked);
		if (bIsChecked)
		{
			OnCheckedDelegate.Broadcast();
			OnCheckedDelegateNative.Broadcast();
		}
		else
		{
			OnUnCheckedDelegate.Broadcast();
			OnUnCheckedDelegateNative.Broadcast();			
		}

	}
}

void UHorizonRadioButtonUserWidget::GatherAllRadioButton()
{
	AllRadioButtons.Reset();
	UPanelWidget* pParentPanel = GetParent();
	if (pParentPanel)
	{
		TArray<UWidget*> allChridren = pParentPanel->GetAllChildren();
		for (auto& it : allChridren)
		{
			UHorizonRadioButtonUserWidget* pRadioButtonWidget = Cast<UHorizonRadioButtonUserWidget>(it);
			if (pRadioButtonWidget)
			{
				AllRadioButtons.AddUnique(pRadioButtonWidget);
			}
		}
	}
}

void UHorizonRadioButtonUserWidget::TryChecked()
{
	bool bHasChecked = false;

	for (auto& it : AllRadioButtons)
	{
		UHorizonRadioButtonUserWidget* pRadioButtonWidget = Cast<UHorizonRadioButtonUserWidget>(it);
		if (pRadioButtonWidget)
		{
			if (pRadioButtonWidget->IsChecked())
			{
				bHasChecked = true;
				break;
			}
		}
	}
	
	if (false == bHasChecked)
	{
		NativeOnCheckStateChanged(true);
	}
}


