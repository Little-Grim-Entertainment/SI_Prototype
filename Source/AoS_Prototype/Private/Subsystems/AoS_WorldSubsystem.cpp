// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/AoS_WorldSubsystem.h"
#include "AoS_GameInstance.h"
#include "AoS_GameplayTagManager.h"


void UAoS_WorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	InitializeDelegates();
	InitializeDelegateMaps();
}

void UAoS_WorldSubsystem::InitializeDelegates()
{
	if (!IsValid(GameInstance)){return;}

	GameInstance->OnGameModeBeginPlay.AddUObject(this, &ThisClass::OnGameModeBeginPlay);
	
	AoSTagManager = GameInstance->GetSubsystem<UAoS_GameplayTagManager>();
	if (!IsValid(AoSTagManager)) {return;}

	AoSTagManager->OnTagAdded().AddUObject(this, &ThisClass::OnGameplayTagAdded);
	AoSTagManager->OnTagRemoved().AddUObject(this, &ThisClass::OnGameplayTagRemoved);
}

void UAoS_WorldSubsystem::InitializeDelegateMaps()
{
	
}

void UAoS_WorldSubsystem::OnGameModeBeginPlay()
{
	
}

void UAoS_WorldSubsystem::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
}

void UAoS_WorldSubsystem::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
}
