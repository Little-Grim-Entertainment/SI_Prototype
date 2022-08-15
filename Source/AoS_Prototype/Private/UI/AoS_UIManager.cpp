// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_UIManager.h"
#include "AoS_GameInstance.h"
#include "UI/AoS_UserWidget.h"


void UAoS_UIManager::DisplayLoadingScreen(bool bShouldDisplay)
{
	if(GameInstance)
	{
		//LoadingScreen = CreateWidget(GetWorld()->GetFirstPlayerController(), GameInstance->LoadingScreen);
	}
}

void UAoS_UIManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	World = GetWorld();
	if (World)
	{
		GameInstance = Cast<UAoS_GameInstance>(World->GetGameInstance());
		if (GameInstance)
		{
			
		}
	}
}
