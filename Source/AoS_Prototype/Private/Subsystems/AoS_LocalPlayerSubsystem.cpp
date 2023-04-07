// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/AoS_LocalPlayerSubsystem.h"
#include "AoS_GameInstance.h"
#include "AoS_GameplayTagManager.h"


void UAoS_LocalPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	InitializeDelegates();
	InitializeDelegateMaps();
}

void UAoS_LocalPlayerSubsystem::InitializeDelegates()
{
	if (!IsValid(GameInstance)){return;}

	GameInstance->OnGameModeBeginPlay.AddUObject(this, &ThisClass::OnGameModeBeginPlay);

	AoSTagManager = GameInstance->GetSubsystem<UAoS_GameplayTagManager>();
	if (!IsValid(AoSTagManager)) {return;}

	AoSTagManager->OnTagAdded().AddUObject(this, &ThisClass::OnGameplayTagAdded);
	AoSTagManager->OnTagRemoved().AddUObject(this, &ThisClass::OnGameplayTagRemoved);	
}

void UAoS_LocalPlayerSubsystem::InitializeDelegateMaps()
{
	
}

void UAoS_LocalPlayerSubsystem::OnGameModeBeginPlay()
{
	
}

void UAoS_LocalPlayerSubsystem::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
	
}

void UAoS_LocalPlayerSubsystem::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
	
}
