// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/AoS_WorldSubsystem.h"
#include "AoS_GameInstance.h"
#include "AoS_GameplayTagManager.h"


void UAoS_WorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	if (!IsValid(GameInstance)){return;}

	GameInstance->OnPlayerModeChanged.AddDynamic(this, &ThisClass::OnPlayerModeChanged);
	GameInstance->OnGameModeBeginPlay.AddDynamic(this, &ThisClass::OnGameModeBeginPlay);
	
	AoS_GameplayTagManager = GameInstance->GetSubsystem<UAoS_GameplayTagManager>();
	if (!IsValid(AoS_GameplayTagManager)) {return;}

	AoS_GameplayTagManager->OnTagAdded().AddUObject(this, &ThisClass::OnGameplayTagAdded);
	AoS_GameplayTagManager->OnTagRemoved().AddUObject(this, &ThisClass::OnGameplayTagRemoved);
}

void UAoS_WorldSubsystem::OnGameModeBeginPlay()
{
	
}

void UAoS_WorldSubsystem::OnPlayerModeChanged(EPlayerMode NewPlayerMode, EPlayerMode InPreviousPlayerMode)
{

}

void UAoS_WorldSubsystem::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
}

void UAoS_WorldSubsystem::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
}
