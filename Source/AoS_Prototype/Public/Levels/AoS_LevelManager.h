// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_GameInstanceSubsystem.h"
#include "AoS_Types.h"
#include "AoS_LevelManager.generated.h"

class UAoS_MediaDataAsset;
class UAoS_CinematicDataAsset;
class UAoS_VideoDataAsset;
class UAoS_UIManager;
class UAoS_MapData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBeginLevelLoad, UAoS_MapData*, LoadingLevel, bool, bShouldFade);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelLoaded, UAoS_MapData*, LoadedLevel, bool, bShouldFade);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUnloaded, UAoS_MapData*, UnloadedLevel);

UCLASS()
class AOS_PROTOTYPE_API UAoS_LevelManager : public UAoS_GameInstanceSubsystem
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
	
	UFUNCTION(BlueprintCallable, Category = "Levels")
	void LoadLevelByTag(FGameplayTag InLevelToLoadTag, FString InPlayerStartTag = FString(TEXT("NickSpawn")), bool bAllowDelay = true, bool bShouldFade = true);

	UFUNCTION(BlueprintCallable, Category = "Levels")
	void LoadLevelOnMediaComplete(const FGameplayTag& InLevelToLoadTag, UAoS_MediaDataAsset* InMediaToPlay, const FString& InPlayerStartTag = FString(TEXT("NickSpawn")), bool bAllowDelay = true, bool bShouldFade = true);

	void LoadLevelOnCinematicComplete(const FGameplayTag& InLevelToLoadTag, const UAoS_CinematicDataAsset* InCinematicToPlay, const FString& InPlayerStartTag = FString(TEXT("NickSpawn")), bool bAllowDelay = true, bool bShouldFade = true);
	void LoadLevelOnVideoComplete(const FGameplayTag& InLevelToLoadTag, const UAoS_VideoDataAsset* InVideoToPlay, const FString& InPlayerStartTag = FString(TEXT("NickSpawn")), bool bAllowDelay = true, bool bShouldFade = true);
	
	void ExecuteLoadLevelOnVideoComplete();
	void ExecuteLoadLevelOnCinematicComplete();
	
	UFUNCTION(BlueprintCallable, Category = "Levels")
	UAoS_MapData* GetCurrentMap() const;
	UFUNCTION(BlueprintCallable, Category = "Levels")
	bool GetLevelHasLoaded() const;

	UFUNCTION(BlueprintCallable, Category = "Levels")
	FAoS_MapState& GetMapStateByTag(const FGameplayTag InMapTag);
	UFUNCTION(BlueprintCallable, Category = "Levels")
	FAoS_MapState& GetMapStateByWorld();

	UFUNCTION(BlueprintCallable, Category = "Levels")
	const TArray<FAoS_MapState>& GetAllMapStates() const;
	
	UFUNCTION(BlueprintCallable, Category = "Levels")
	TArray<FString>& GetMapNames();
	UFUNCTION(BlueprintCallable, Category = "Levels")
	FAoS_MapState& GetMapStateFromName(FString InMapName);
	
	UFUNCTION()
	void LevelLoaded(UWorld* LoadedWorld);

	UFUNCTION(BlueprintCallable, Category = "Levels")
	FAoS_MapState& GetCurrentLoadedMapState() const;

protected:
	
	virtual void OnInitGame() override;
	virtual void OnGameModeBeginPlay() override;
	virtual void OnPlayerStart() override;

	virtual void InitializeMapStates();

private:

	bool bLevelHasLoaded = false;
	bool bLoadShouldFade = false;

	FAoS_MapState* LevelStateToLoad;
	FAoS_MapState* LoadedMapState;

	UPROPERTY()
	UAoS_MapData* MainMenu;

	TArray<FAoS_MapState> MapStates;
	
	FTimerHandle LoadDelayHandle;
	FTimerDelegate LoadDelayDelegate;
	
	FTimerHandle UnloadDelayHandle;
	FTimerHandle PersistentLevelLoadTimerHandle;
};