// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AoS_GameInstance.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_LevelManager.generated.h"

class UAoS_UIManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginLevelLoad, ULevelStreaming*, LoadingLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelLoaded, ULevelStreaming*, LoadedLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUnloaded, ULevelStreaming*, UnloadedLevel);

UCLASS()
class AOS_PROTOTYPE_API UAoS_LevelManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UAoS_LevelManager();

	UPROPERTY(BlueprintAssignable, Category = "Levels")
	FOnBeginLevelLoad OnBeginLevelLoad;
	UPROPERTY(BlueprintAssignable, Category = "Levels")
	FOnLevelLoaded OnLevelLoaded;
	UPROPERTY(BlueprintAssignable, Category = "Levels")
	FOnLevelUnloaded OnLevelUnloaded;

	UFUNCTION(BlueprintCallable, Category = "Levels")
	void LoadLevel(const TSoftObjectPtr<UWorld> InLevelToLoad);

private:

	UPROPERTY()
	UWorld* World;
	UPROPERTY()
	UAoS_GameInstance* GameInstance;

	UPROPERTY()
	ULevelStreaming* LevelToLoad;
	UPROPERTY()
	ULevelStreaming* LevelToUnload;
	UPROPERTY()
	ULevelStreaming* CurrentStreamingLevel;
	

	UFUNCTION()
	void ExecuteLevelLoad(const ULevelStreaming* InLevelToLoad);
	UFUNCTION()
	void ExecuteLevelUnload(const ULevelStreaming* InLevelToUnload);
	
	UFUNCTION()
	void LevelUnloaded();
	UFUNCTION()
	void LevelLoaded();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
