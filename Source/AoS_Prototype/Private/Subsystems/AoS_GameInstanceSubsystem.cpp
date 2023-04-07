// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/AoS_GameInstanceSubsystem.h"
#include "AoS_GameInstance.h"
#include "AoS_GameplayTagManager.h"

void UAoS_GameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	InitializeDelegates();
	InitializeDelegateMaps();
}

void UAoS_GameInstanceSubsystem::InitializeDelegates()
{
	if (!IsValid(GameInstance)){return;}

	GameInstance->OnGameInstanceInit.AddUObject(this, &ThisClass::OnGameInstanceInit);
	GameInstance->OnPlayerStart.AddUObject(this, &ThisClass::OnGameInstanceInit);
	GameInstance->OnGameModeBeginPlay.AddUObject(this, &ThisClass::OnGameModeBeginPlay);
	GameInstance->OnInitGame.AddUObject(this, &ThisClass::OnInitGame);
}

void UAoS_GameInstanceSubsystem::InitializeDelegateMaps()
{
}

void UAoS_GameInstanceSubsystem::OnGameInstanceInit()
{
	if(Cast<UAoS_GameplayTagManager>(this) || !IsValid(GameInstance)) {return;}

	AoSTagManager = GameInstance->GetSubsystem<UAoS_GameplayTagManager>();
	if (!IsValid(AoSTagManager)) {return;}

	AoSTagManager->OnTagAdded().AddUObject(this, &ThisClass::OnGameplayTagAdded);
	AoSTagManager->OnTagRemoved().AddUObject(this, &ThisClass::OnGameplayTagRemoved);
}

void UAoS_GameInstanceSubsystem::OnInitGame()
{

}

void UAoS_GameInstanceSubsystem::OnPlayerStart()
{
}

void UAoS_GameInstanceSubsystem::OnGameModeBeginPlay()
{

}

void UAoS_GameInstanceSubsystem::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
}

void UAoS_GameInstanceSubsystem::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
}


