// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SI_GameInstanceSubsystem.h"
#include "SI_WorldManager.generated.h"

class ASI_SunLight;
class ASI_SkySphere;
class USI_MapData;

UENUM(BlueprintType)
enum class EWeekDay : uint8
{
	WD_Sunday = 0	UMETA(DisplayName = "Sunday"),
	WD_Monday		UMETA(DisplayName = "Monday"),
	WD_Tuesday		UMETA(DisplayName = "Tuesday"),
	WD_Wednesday	UMETA(DisplayName = "Wednesday"),
	WD_Thursday		UMETA(DisplayName = "Thursday"),
	WD_Friday		UMETA(DisplayName = "Friday"),
	WD_Saturday		UMETA(DisplayName = "Saturday"),
	Count			UMETA(Hidden)
};

ENUM_RANGE_BY_COUNT(EWeekDay, EWeekDay::Count);

UENUM(BlueprintType)
enum class EMeridiemIndicator : uint8
{
	WD_AM = 0	UMETA(DisplayName = "AM"),
	WD_PM		UMETA(DisplayName = "PM"),
	Count			UMETA(Hidden)
};

ENUM_RANGE_BY_COUNT(EMeridiemIndicator, EMeridiemIndicator::Count);

USTRUCT(BlueprintType)
struct FTimeStamp
{
	GENERATED_BODY()

	EWeekDay WeekDay = EWeekDay::WD_Sunday;
	int32 Hour = 0;
	int32 Minute = 0;
	int32 Second = 0;
	int32 Millisecond = 0;
	EMeridiemIndicator MeridiemIndicator = EMeridiemIndicator::WD_AM;
	float CurrentTimeFloat = 0.00000;
};

USTRUCT()
struct FSIWorldTimer
{
	GENERATED_BODY()
	
	FString TimerName = "NULL";
	FTimerHandle TimerHandle;
	FTimerDelegate::TMethodPtr< class USI_WorldManager > TimerMethod;
	float Rate = 0.0f;
	bool bShouldLoop = true;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewDayStarted, EWeekDay, NewDay);

// This system is responsible for handling world events such as the time of day and world clock

UCLASS()
class SI_PROTOTYPE_API USI_WorldManager : public USI_GameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USI_WorldManager();

	UPROPERTY(BlueprintAssignable, Category = "Time")
	FOnNewDayStarted OnNewDayStarted;

	UFUNCTION()
	void SetSkySphere(ASI_SkySphere* SkySphereToSet);
	UFUNCTION()
	void OnLevelFinishLoad(USI_MapData* LoadedLevel, bool bShouldFade);

	// Timers
	UFUNCTION(BlueprintCallable)
	void StartTimerByHandle(FTimerHandle& InTimerHandle);
	UFUNCTION(BlueprintCallable)
	void PauseTimerByHandle(FTimerHandle& InTimerHandle, bool bShouldPause);
	UFUNCTION(BlueprintCallable)
	void PauseTimerByName(FString InTimerName, bool bShouldPause);
	UFUNCTION()
	void ResetTimerByHandle(FTimerHandle& InTimerHandle);
	UFUNCTION()
	FSIWorldTimer& GetTimerByHandle(FTimerHandle& InTimerHandle);
	UFUNCTION()
	FSIWorldTimer& GetTimerByName(FString InTimerName);

	
	UFUNCTION()
	void SetSunRotationModifier(float InRate);
	
	UFUNCTION(BlueprintCallable)
	void SetTimeStamp(EWeekDay InWeekDay, int32 InHour, int32 InMin, EMeridiemIndicator InMeridiemIndicator);
	
	UFUNCTION(BlueprintCallable)
	FTimeStamp GetTimeStamp();


	
protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void OnGameInstanceInit() override;
	
	bool Tick(float DeltaSeconds);

private:

	UPROPERTY()
	ASI_SkySphere* SkySphere;

	float SunRotationModifier = 1.0f;
	float SunRotationSpeed = 0.005f;
	
	FTimeStamp CurrentTimeStamp;
		
	FTSTicker::FDelegateHandle TickerDelegateHandle;
	FTimerHandle TimeOfDayHandle;

	TArray<FSIWorldTimer> WorldTimers;
	FSIWorldTimer DefaultTimer;
	
	bool bRotateSun = false;

	ASI_SunLight* GetLevelSunLight();

	UFUNCTION()
	void UpdateWorld();
	UFUNCTION()
	void UpdateTimer();
	UFUNCTION()
	void UpdateSky();
	UFUNCTION()
	void UpdateFloatTime();
	UFUNCTION()
	void InitializeWorldTimers();

	void CreateNewWorldTimer(FTimerHandle& InTimerHandle, FString InTimerName, FTimerDelegate::TMethodPtr<USI_WorldManager> InTimerMethod, float InRate, bool bInShouldLoop);
};

