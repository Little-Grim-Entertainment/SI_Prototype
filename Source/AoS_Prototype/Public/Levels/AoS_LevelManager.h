// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_LevelManager.generated.h"

class UAoS_UIManager;

UCLASS()
class AOS_PROTOTYPE_API UAoS_LevelManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UAoS_LevelManager();

	UFUNCTION(BlueprintCallable, Category = "Levels")
	void LoadLevel(TSoftObjectPtr<UWorld> LevelToLoad);

private:

	UPROPERTY()
	UWorld* World;
	UPROPERTY()
	UGameInstance* GameInstance;
	UPROPERTY()
	UAoS_UIManager* UIManager;
	
	UPROPERTY()
	TSoftObjectPtr<UWorld> CurrentStreamingLevel;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void SetCurrentStreamingLevel(TSoftObjectPtr<UWorld> LevelToSet);
	
};
