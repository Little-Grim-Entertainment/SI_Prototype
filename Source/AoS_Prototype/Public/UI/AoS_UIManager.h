// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_UIManager.generated.h"

class UAoS_UserWidget;
class UAoS_GameInstance;

UCLASS()
class AOS_PROTOTYPE_API UAoS_UIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	void DisplayLoadingScreen(bool bShouldDisplay);

private:

	UPROPERTY()
	UWorld* World;
	UPROPERTY()
	UAoS_GameInstance* GameInstance;
	UPROPERTY()
	UAoS_UserWidget* LoadingScreen;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
};
