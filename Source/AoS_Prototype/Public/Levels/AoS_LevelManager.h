// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_LevelManager.generated.h"

enum class EMapType : uint8;

class UAoS_GameInstance;
class UAoS_UIManager;
class UAoS_MapData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBeginLevelLoad, UAoS_MapData*, LoadingLevel, bool, bShouldFade);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelLoaded, UAoS_MapData*, LoadedLevel, bool, bShouldFade);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUnloaded, UAoS_MapData*, UnloadedLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMapTypeChanged, EMapType, NewMapType);

UCLASS()
class AOS_PROTOTYPE_API UAoS_LevelManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	// This subsystem will handle the loading and unloading of levels inside the persistent level
	
public:

	UAoS_LevelManager();

	UPROPERTY(BlueprintAssignable, Category = "Levels")
	FOnBeginLevelLoad OnBeginLevelLoad;
	UPROPERTY(BlueprintAssignable, Category = "Levels")
	FOnLevelLoaded OnLevelLoaded;
	UPROPERTY(BlueprintAssignable, Category = "Levels")
	FOnLevelUnloaded OnLevelUnloaded;
	UPROPERTY(BlueprintAssignable, Category = "MapData")
	FOnMapTypeChanged OnMapTypeChanged;
	
	UFUNCTION(BlueprintCallable, Category = "Levels")
	void LoadLevel(UAoS_MapData* InLevelToLoad, bool bAllowDelay = true, bool bShouldFade = true);
	UFUNCTION(BlueprintCallable, Category = "Levels")
	TArray<FString> GetMapNames();
	UFUNCTION(BlueprintCallable, Category = "Levels")
	UAoS_MapData* GetMapFromName(FString MapName);
	UFUNCTION(BlueprintCallable, Category = "Levels")
	EMapType GetCurrentMapType();
	
	UFUNCTION(BlueprintCallable)
    void UpdateMapType(EMapType InMapType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void LoadMainMenu();
	UFUNCTION()
	void LevelManagerOnGameInstanceInit();

	UAoS_MapData* GetCurrentStreamingLevel() const {return CurrentStreamingLevel;}

private:
		
	float LevelLoadDelay;
	bool bLoadShouldFade = true;
	
	UPROPERTY()
	UAoS_GameInstance* GameInstance;

	UPROPERTY()
	UAoS_MapData* LevelToLoad;
	UPROPERTY()
	UAoS_MapData* LevelToUnload;
	UPROPERTY()
	UAoS_MapData* CurrentStreamingLevel;
	UPROPERTY()
	UAoS_MapData* MainMenu;
	UPROPERTY()
	TEnumAsByte<EMapType> CurrentMapType;


	FTimerHandle LoadDelayHandle;
	FTimerHandle UnloadDelayHandle;
	FTimerHandle PersistentLevelLoadTimerHandle;

	UFUNCTION()
	void ExecuteLevelLoad(const UAoS_MapData* InLevelToLoad);
	UFUNCTION()
	void ExecuteLevelUnload(const UAoS_MapData* InLevelToUnload);

	UFUNCTION()
	void CheckForPersistentLevelLoaded();
	UFUNCTION()
	void OnPersistentLevelLoaded();
	
	UFUNCTION()
	void LevelUnloaded();
	UFUNCTION()
	void LevelLoaded();

	UAoS_MapData* GetMapDataFromStreamingLevel(ULevelStreaming* InStreamingLevel);
	void PostLoadDelay();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};