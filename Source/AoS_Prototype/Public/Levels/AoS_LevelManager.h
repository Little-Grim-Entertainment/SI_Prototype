// This subsystem will handle the loading and unloading of levels inside the persistent level

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_LevelManager.generated.h"

class UAoS_GameInstance;
class UAoS_UIManager;
class UAoS_MapData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginLevelLoad, UAoS_MapData*, LoadingLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelLoaded, UAoS_MapData*, LoadedLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUnloaded, UAoS_MapData*, UnloadedLevel);

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
	void LoadLevel(UAoS_MapData* InLevelToLoad, bool bAllowDelay = true);
	UFUNCTION(BlueprintCallable, Category = "Levels")
	TArray<FString> GetMapNames();
	UFUNCTION(BlueprintCallable, Category = "Levels")
	UAoS_MapData* GetMapFromName(FString MapName);

	UAoS_MapData* GetCurrentStreamingLevel() const {return CurrentStreamingLevel;}

private:

	UPROPERTY()
	UWorld* World;
	UPROPERTY()
	UAoS_GameInstance* GameInstance;

	UPROPERTY()
	UAoS_MapData* LevelToLoad;
	UPROPERTY()
	UAoS_MapData* LevelToUnload;
	UPROPERTY()
	UAoS_MapData* CurrentStreamingLevel;


	FTimerHandle LoadDelayHandle;
	FTimerHandle UnloadDelayHandle;

	UFUNCTION()
	void ExecuteLevelLoad(const UAoS_MapData* InLevelToLoad);
	UFUNCTION()
	void ExecuteLevelUnload(const UAoS_MapData* InLevelToUnload);
	
	UFUNCTION()
	void LevelUnloaded();
	UFUNCTION()
	void LevelLoaded();

	UAoS_MapData* GetMapDataFromStreamingLevel(ULevelStreaming* InStreamingLevel);
	void PostLoadDelay();
	void PostUnloadDelay();

	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
