// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_WorldManager.generated.h"

class AAoS_SkySphere;
class UAoS_GameInstance;

UCLASS()
class AOS_PROTOTYPE_API UAoS_WorldManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UAoS_WorldManager();

	UFUNCTION()
	void SetSkySphere(AAoS_SkySphere* SkySphereToSet);
	
protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	bool Tick(float DeltaSeconds);

private:

	UPROPERTY()
	UAoS_GameInstance* GameInstance;
	UPROPERTY()
	AAoS_SkySphere* SkySphere;

	FTSTicker::FDelegateHandle TickerDelegateHandle;

	bool bTimePaused = false;
};
