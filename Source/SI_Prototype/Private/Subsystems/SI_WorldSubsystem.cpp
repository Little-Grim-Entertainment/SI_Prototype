// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/SI_WorldSubsystem.h"
#include "SI_GameInstance.h"
#include "SI_GameplayTagManager.h"


void USI_WorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	if(!IsValid(GameInstance)) {return;}

	InitializeDelegates();
}

void USI_WorldSubsystem::InitializeDelegates()
{
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

void USI_WorldSubsystem::OnGameplayTagAdded(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload)
{

}

void USI_WorldSubsystem::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag, FSITagPayload* InTagPayload)
{
}
