// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_WorldManager.generated.h"

class AAoS_SunLight;
enum class EMapType : uint8;

class AAoS_SkySphere;
class UAoS_GameInstance;
class UAoS_MapData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNewDayStarted);

UCLASS()
class AOS_PROTOTYPE_API UAoS_WorldManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UAoS_WorldManager();

	UPROPERTY(BlueprintAssignable, Category = "Time")
	FOnNewDayStarted OnNewDayStarted;

	UFUNCTION()
	void SetSkySphere(AAoS_SkySphere* SkySphereToSet);

	void WorldOnMapTypeChange(EMapType InMapType);
	
	UFUNCTION()
	void WorldManagerOnGameInstanceInit();
	UFUNCTION()
	void WorldOnLevelFinishLoad(UAoS_MapData* LoadedLevel);

	UFUNCTION(BlueprintCallable)
	void StartTimer();
	UFUNCTION()
	void UpdateTimer();
	
protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	bool Tick(float DeltaSeconds);

private:

	UPROPERTY()
	UAoS_GameInstance* GameInstance;
	UPROPERTY()
	AAoS_SkySphere* SkySphere;

	int32 CurrentTimeHour = 0;
	int32 CurrentTimeMin = 0;
	int32 CurrentTimeSec = 0;
	int32 CurrentTimeMilSec = 0;
	
	FTSTicker::FDelegateHandle TickerDelegateHandle;
	FTimerHandle TimeOfDayHandle;
	FTimerHandle NormalTimeOfDayHandle;

	

	bool bTimePaused = false;

	AAoS_SunLight* GetLevelSunLight();
};
