// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SI_GameInstance.generated.h"

class ASI_GameMode;

DECLARE_MULTICAST_DELEGATE(FOnSubsystemBindingsComplete);
DECLARE_MULTICAST_DELEGATE(FOnGameInstanceInit);
DECLARE_MULTICAST_DELEGATE(FOnGameModeBeginPlay);
DECLARE_MULTICAST_DELEGATE(FOnInitGame);
DECLARE_MULTICAST_DELEGATE(FOnPlayerStart);
DECLARE_MULTICAST_DELEGATE(FGameModeSet);
DECLARE_MULTICAST_DELEGATE(FOnTagManagerInitialized);


UCLASS()
class SI_PROTOTYPE_API USI_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	USI_GameInstance();

	FOnSubsystemBindingsComplete OnSubsystemBindingsComplete;
	FOnPlayerStart OnPlayerStart;
	FOnGameInstanceInit OnGameInstanceInit;
	FOnGameModeBeginPlay OnGameModeBeginPlay;
	FOnInitGame OnInitGame;

	FOnTagManagerInitialized& OnTagManagerInitialized();

	UFUNCTION()
	ASI_GameMode* GetGameMode();

protected:

	virtual void Init() override;
	
private:

	FGameModeSet GameModeSet;

	FOnTagManagerInitialized OnTagManagerInitializedDelegate;
	
	UPROPERTY()
	ASI_GameMode* GameMode;
};
