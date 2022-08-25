// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "AoS_CheatManager.generated.h"

class UAoS_GameInstance;


UCLASS()
class AOS_PROTOTYPE_API UAoS_CheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:
	
	UAoS_CheatManager();

	UFUNCTION(exec)
	void CheatSetTimeStamp(FString Day, int32 Hour, int32 Minutes, FString AMPM);
	UFUNCTION(exec)
	void CheatIncreaseSunRotationSpeed(float Percentage);

protected:

	virtual void InitCheatManager() override;
	
private:

	UPROPERTY()
	UAoS_GameInstance* GameInstance;
};
