// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SI_GameInstance.generated.h"

class ASI_GameMode;

DECLARE_MULTICAST_DELEGATE(FOnGameInstanceInit);
DECLARE_MULTICAST_DELEGATE(FOnGameModeBeginPlay);
DECLARE_MULTICAST_DELEGATE(FOnPlayerStart);
DECLARE_MULTICAST_DELEGATE(FOnTagManagerInitialized);


UCLASS()
class SI_PROTOTYPE_API USI_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	USI_GameInstance();


	FOnGameInstanceInit& OnGameInstanceInit();
	FOnGameModeBeginPlay& OnGameModeBeginPlay();
	FOnPlayerStart& OnPlayerStart();
	FOnTagManagerInitialized& OnTagManagerInitialized();

	UFUNCTION()
	ASI_GameMode* GetGameMode();

protected:

	virtual void Init() override;
	
private:

	FOnGameInstanceInit OnGameInstanceInitDelegate;
	FOnGameModeBeginPlay OnOnGameModeBeginPlayDelegate;
	FOnPlayerStart OnOnPlayerStartDelegate;
	FOnTagManagerInitialized OnTagManagerInitializedDelegate;
	
	UPROPERTY()
	ASI_GameMode* GameMode;
};
