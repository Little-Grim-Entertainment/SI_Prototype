// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/SI_WorldSubsystem.h"
#include "SI_GameInstance.h"
#include "SI_GameplayTagManager.h"


void USI_WorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	InitializeDelegates();
}

void USI_WorldSubsystem::InitializeDelegates()
{
	if (!IsValid(GameInstance)){return;}
	GameInstance->OnGameModeBeginPlay.AddUObject(this, &ThisClass::OnGameModeBeginPlay);
	
	SITagManager = GameInstance->GetSubsystem<USI_GameplayTagManager>();
	if (!IsValid(SITagManager))
	{
		GameInstance->OnTagManagerInitialized().AddUObject(this, &USI_WorldSubsystem::InitializeDelegates);
		return;
	}

	SITagManager->OnTagAdded().AddUObject(this, &ThisClass::OnGameplayTagAdded);
	SITagManager->OnTagRemoved().AddUObject(this, &ThisClass::OnGameplayTagRemoved);
	InitializeDelegateMaps();
}

void USI_WorldSubsystem::InitializeDelegateMaps()
{
	
}

void USI_WorldSubsystem::OnGameModeBeginPlay()
{

}

void USI_WorldSubsystem::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
}

void USI_WorldSubsystem::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
}
