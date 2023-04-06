// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/AoS_GameInstanceSubsystem.h"
#include "AoS_GameInstance.h"
#include "AoS_GameplayTagManager.h"

void UAoS_GameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	if (!IsValid(GameInstance)){return;}

	GameInstance->OnGameInstanceInit.AddDynamic(this, &ThisClass::OnGameInstanceInit);
	GameInstance->OnPlayerStart.AddDynamic(this, &ThisClass::OnGameInstanceInit);
	GameInstance->OnGameModeBeginPlay.AddDynamic(this, &ThisClass::OnGameModeBeginPlay);
	GameInstance->OnInitGame.AddDynamic(this, &ThisClass::OnInitGame);	
}

void UAoS_GameInstanceSubsystem::OnGameInstanceInit()
{
	GameInstance->OnPlayerModeChanged.AddDynamic(this, &ThisClass::OnPlayerModeChanged);

	if(Cast<UAoS_GameplayTagManager>(this)) {return;}

	AoS_GameplayTagManager = GameInstance->GetSubsystem<UAoS_GameplayTagManager>();
	if (!IsValid(AoS_GameplayTagManager)) {return;}

	AoS_GameplayTagManager->OnTagAdded().AddUObject(this, &ThisClass::OnGameplayTagAdded);
	AoS_GameplayTagManager->OnTagRemoved().AddUObject(this, &ThisClass::OnGameplayTagRemoved);
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

void UAoS_GameInstanceSubsystem::OnPlayerModeChanged(EPlayerMode NewPlayerMode, EPlayerMode InPreviousPlayerMode)
{
	
}

void UAoS_GameInstanceSubsystem::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
}

void UAoS_GameInstanceSubsystem::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
}


