// Created by horizon-studio, All Right Reserved


#include "Widget/Blueprint/HorizonMultiToggleButtonWidget.h"
#include "HorizonUIPrivate.h"



UHorizonMultiToggleButtonWidget::UHorizonMultiToggleButtonWidget()
{
	bIsFocusable = true;
	Visibility = ESlateVisibility::Visible;
}

void UHorizonMultiToggleButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Button_ToggleState_Prev)
	{
		Button_ToggleState_Prev->OnClicked.AddDynamic(this, &ThisClass::ToggleState_Prev);
	}

	if (Button_ToggleState_Next)
	{
		Button_ToggleState_Next->OnClicked.AddDynamic(this, &ThisClass::ToggleState_Next);
	}
}

void UHorizonMultiToggleButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Don't set to 0, if it is -1, it can mean "SystemDefault" if the state not toggled by user
	//if (StateList.Num() > 0)
	//{
	//	SetCurrentStateIndex(0);
	//}


}

void UHorizonMultiToggleButtonWidget::OnSynchronizeProperties_Implementation()
{
	if (CurrentStateIndex >= 0 && CurrentStateIndex < StateList.Num())
	{
		auto& currentState = StateList[CurrentStateIndex];
		if (TextBlock_CurrentState)
		{		
			TextBlock_CurrentState->SetText(currentState.Text);
			TextBlock_CurrentState->SetColorAndOpacity(currentState.TextColor);
		}

		if (Image_CurrentState)
		{
			Image_CurrentState->SetBrush(currentState.Brush);
		}
		OnStateSyncDelegate.Broadcast(CurrentStateIndex);
		OnStateSyncDelegateNative.Broadcast(CurrentStateIndex);
	}
}

void UHorizonMultiToggleButtonWidget::ToggleState_Prev()
{
	if (StateList.Num() > 0)
	{
		int32 currentStateIndex = CurrentStateIndex;
		int32 toStateIndex = GetToggleState_PrevIndex();

		if(currentStateIndex != toStateIndex)
		{ 
			CurrentStateIndex = toStateIndex;
			SynchronizeProperties();
			OnStateChangedDelegate.Broadcast(currentStateIndex, toStateIndex);
			OnStateChangedDelegateNative.Broadcast(currentStateIndex, toStateIndex);
		}

	}
}

void UHorizonMultiToggleButtonWidget::ToggleState_Next()
{
	if (StateList.Num() > 0)
	{
		int32 currentStateIndex = CurrentStateIndex;
		int32 toStateIndex = GetToggleState_NextIndex();
		if (currentStateIndex != toStateIndex)
		{
			CurrentStateIndex = toStateIndex;
			SynchronizeProperties();
			OnStateChangedDelegate.Broadcast(currentStateIndex, toStateIndex);
			OnStateChangedDelegateNative.Broadcast(currentStateIndex, toStateIndex);
		}
	}
}

void UHorizonMultiToggleButtonWidget::SetCurrentStateIndex(int32 InStateIndex)
{
	if (InStateIndex >= 0 && InStateIndex < StateList.Num())
	{
		if (CurrentStateIndex != InStateIndex)
		{
			int32 currentStateIndex = CurrentStateIndex;
			int32 toStateIndex = InStateIndex;
			CurrentStateIndex = toStateIndex;
			SynchronizeProperties();
			OnStateChangedDelegate.Broadcast(currentStateIndex, toStateIndex);
			OnStateChangedDelegateNative.Broadcast(currentStateIndex, toStateIndex);
		}
	}
	else 
	{
		ensureMsgf(false, TEXT("StateIndex(%d) not validated"), InStateIndex);
	}
}

int32 UHorizonMultiToggleButtonWidget::GetToggleState_PrevIndex()
{
	int32 result = -1;
	if (StateList.Num() > 0)
	{
		int32 currentStateIndex = CurrentStateIndex;
		int32 toStateIndex = currentStateIndex - 1;
		if (toStateIndex < 0)
		{
			if (bLoopToggleState)
			{
				toStateIndex = StateList.Num() - 1;
			}
			else
			{
				toStateIndex = 0;
			}
		}

		result = toStateIndex;

	}
	return result;
}

int32 UHorizonMultiToggleButtonWidget::GetToggleState_NextIndex()
{
	int32 result = -1;
	if (StateList.Num() > 0)
	{
		int32 currentStateIndex = CurrentStateIndex;
		int32 toStateIndex = currentStateIndex + 1;
		if (toStateIndex >= StateList.Num())
		{
			if (bLoopToggleState)
			{
				toStateIndex = 0;
			}
			else
			{
				toStateIndex = StateList.Num() - 1;
			}
		}
		result = toStateIndex;
	}
	return result;
}

FHorizonMultiToggleButtonState& UHorizonMultiToggleButtonWidget::GetState(int32 InStateIndex)
{
	if(InStateIndex >= 0 && InStateIndex < StateList.Num())
	{
		return StateList[InStateIndex];
	}
	else
	{
		static FHorizonMultiToggleButtonState emptyState;
		return emptyState;
	}

}
