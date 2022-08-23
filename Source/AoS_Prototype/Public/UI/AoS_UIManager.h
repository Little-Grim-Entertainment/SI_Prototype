// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_UIManager.generated.h"

class UAoS_UserWidget;
class UAoS_GameInstance;
class UAoS_MapData;

UCLASS()
class AOS_PROTOTYPE_API UAoS_UIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	// This subsystem will handle the creation and display of the various UI in Ace of Spades
	
public:

	UAoS_UIManager();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void DisplayLoadingScreen(bool bShouldDisplay);

	void UIOnLevelBeginLoad(UAoS_MapData* LoadingLevel);
	void UIOnLevelFinishLoad(UAoS_MapData* LoadingLevel);

	UFUNCTION()
	void UIManagerOnGameInstanceInit();

private:

	UPROPERTY()
	UWorld* World;
	UPROPERTY()
	UAoS_GameInstance* GameInstance;
	UPROPERTY()
	UAoS_UserWidget* LoadingScreen;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	
};
