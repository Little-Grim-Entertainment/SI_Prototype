// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/SI_GameInstanceSubsystem.h"
#include "SI_GameInstance.h"
#include "SI_GameplayTagManager.h"

void USI_GameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	InitializeDelegates();
	InitializeDelegateMaps();
}

void USI_GameInstanceSubsystem::InitializeDelegates()
{
	if (!IsValid(GameInstance)){return;}

	GameInstance->OnGameInstanceInit.AddUObject(this, &ThisClass::OnGameInstanceInit);
	GameInstance->OnPlayerStart.AddUObject(this, &ThisClass::OnGameInstanceInit);
	GameInstance->OnGameModeBeginPlay.AddUObject(this, &ThisClass::OnGameModeBeginPlay);
	GameInstance->OnInitGame.AddUObject(this, &ThisClass::OnInitGame);
}

void USI_GameInstanceSubsystem::InitializeDelegateMaps()
{
}

void USI_GameInstanceSubsystem::OnGameInstanceInit()
{
	if(Cast<USI_GameplayTagManager>(this) || !IsValid(GameInstance)) {return;}

	SITagManager = GameInstance->GetSubsystem<USI_GameplayTagManager>();
	if (!IsValid(SITagManager)) {return;}

	SITagManager->OnTagAdded().AddUObject(this, &ThisClass::OnGameplayTagAdded);
	SITagManager->OnTagRemoved().AddUObject(this, &ThisClass::OnGameplayTagRemoved);
}

void USI_GameInstanceSubsystem::OnInitGame()
{

}

void USI_GameInstanceSubsystem::OnPlayerStart()
{
}

void USI_GameInstanceSubsystem::OnGameModeBeginPlay()
{

}

void USI_GameInstanceSubsystem::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
}

void USI_GameInstanceSubsystem::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
}


