// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SI_GameInstanceSubsystem.h"
#include "SI_Types.h"
#include "SI_LevelManager.generated.h"

class USI_MediaDataAsset;
class USI_CinematicDataAsset;
class USI_VideoDataAsset;
class USI_UIManager;
class USI_MapData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBeginLevelLoad, USI_MapData*, LoadingLevel, bool, bShouldFade);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelLoaded, USI_MapData*, LoadedLevel, bool, bShouldFade);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUnloaded, USI_MapData*, UnloadedLevel);

UCLASS()
class SI_PROTOTYPE_API USI_LevelManager : public USI_GameInstanceSubsystem
{
	GENERATED_BODY()

	// This subsystem will handle the loading and unloading of levels inside the persistent level
	
public:

	USI_LevelManager();
	
	UFUNCTION(BlueprintCallable, Category = "Levels")
	void LoadLevelByTag(FGameplayTag InLevelToLoadTag, FString InPlayerStartTag = FString(TEXT("NickSpawn")), bool bAllowDelay = true, bool bShouldFade = true);

	UFUNCTION(BlueprintCallable, Category = "Levels")
	void LoadLevelOnMediaComplete(const FGameplayTag& InLevelToLoadTag, USI_MediaDataAsset* InMediaToPlay, const FString& InPlayerStartTag = FString(TEXT("NickSpawn")), bool bAllowDelay = true, bool bShouldFade = true);

	void LoadLevelOnCinematicComplete(const FGameplayTag& InLevelToLoadTag, const USI_CinematicDataAsset* InCinematicToPlay, const FString& InPlayerStartTag = FString(TEXT("NickSpawn")), bool bAllowDelay = true, bool bShouldFade = true);
	void LoadLevelOnVideoComplete(const FGameplayTag& InLevelToLoadTag, const USI_VideoDataAsset* InVideoToPlay, const FString& InPlayerStartTag = FString(TEXT("NickSpawn")), bool bAllowDelay = true, bool bShouldFade = true);
	
	void ExecuteLoadLevelOnVideoComplete();
	void ExecuteLoadLevelOnCinematicComplete();
	
	UFUNCTION(BlueprintCallable, Category = "Levels")
	USI_MapData* GetCurrentMap();
	UFUNCTION(BlueprintCallable, Category = "Levels")
	bool GetLevelHasLoaded() const;



	const TArray<FSI_MapState*>& GetAllMapStates() const;
	
	UFUNCTION(BlueprintCallable, Category = "Levels")
	TArray<FString>& GetMapNames();

	UFUNCTION(BlueprintCallable, Category = "Levels")
	USI_MapData* GetMapDataFromName(const FString& InMapName);
	

	FSI_MapState* GetMapStateByWorld();
	FSI_MapState* GetMapStateFromName(const FString& InMapName);
	FSI_MapState* GetMapStateByTag(const FGameplayTag InMapTag);
	FSI_MapState* GetCurrentLoadedMapState();

	
	FOnBeginLevelLoad& OnBeginLevelLoad();
	FOnLevelLoaded& OnLevelLoaded();
	FOnLevelUnloaded& OnLevelUnloaded();
	
	UFUNCTION()
	void LevelLoaded(UWorld* LoadedWorld);

protected:
	
	virtual void OnGameModeBeginPlay() override;
	virtual void OnPlayerStart() override;

	virtual void InitializeMapStates();

private:

	FOnBeginLevelLoad OnBeginLevelLoadDelegate;
	FOnLevelLoaded OnLevelLoadedDelegate;
	FOnLevelUnloaded OnLevelUnloadedDelegate;
	
	bool bLevelHasLoaded = false;
	bool bLoadShouldFade = false;
	bool bMapStatesInitialized;;

	FGameplayTag LevelToLoad;
	FGameplayTag LoadedLevel;

	UPROPERTY()
	USI_MapData* MainMenu;

	TArray<FSI_MapState*> MapStates;
	
	FTimerHandle LoadDelayHandle;
	FTimerDelegate LoadDelayDelegate;
	
	FTimerHandle UnloadDelayHandle;
	FTimerHandle PersistentLevelLoadTimerHandle;
};