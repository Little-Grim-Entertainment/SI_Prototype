// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/SI_LocalPlayerSubsystem.h"
#include "SI_GameInstance.h"
#include "SI_GameplayTagManager.h"
#include "SI_PlayerManager.h"
#include "SI_AbilityManager.h"

void USI_LocalPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	InitializeDelegates();
	InitializeDelegateMaps();
}

void USI_LocalPlayerSubsystem::InitializeDelegates()
{
	if (!IsValid(GameInstance)){return;}

	GameInstance->OnPlayerStart().AddUObject(this, &ThisClass::OnPlayerStart);
	GameInstance->OnGameModeBeginPlay().AddUObject(this, &ThisClass::OnGameModeBeginPlay);
	
	SITagManager = GameInstance->GetSubsystem<USI_GameplayTagManager>();
	if (!IsValid(SITagManager)) {return;}

	SITagManager->OnTagAdded().AddUObject(this, &ThisClass::OnGameplayTagAdded);
	SITagManager->OnTagRemoved().AddUObject(this, &ThisClass::OnGameplayTagRemoved);	
}

void USI_LocalPlayerSubsystem::InitializeDelegateMaps()
{
	
}

void USI_LocalPlayerSubsystem::OnPlayerStart()
{
	 PlayerManager = GetLocalPlayer()->GetSubsystem<USI_PlayerManager>();
	AbilityManager = GetLocalPlayer()->GetSubsystem<USI_AbilityManager>();
}

void USI_LocalPlayerSubsystem::OnGameModeBeginPlay()
{
	
}

void USI_LocalPlayerSubsystem::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
	
}

void USI_LocalPlayerSubsystem::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
	
}
