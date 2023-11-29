// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "SI_CheatManager.generated.h"

class USI_GameInstance;
class USI_GameplayTagManager;
class USI_GameplayTagViewer;


UCLASS()
class SI_PROTOTYPE_API USI_CheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:
	
	USI_CheatManager();

	// Global Cheats
	UFUNCTION(exec)
	void CheatEnableColor(bool bShouldEnable);
	
	// World Manager Cheats
	UFUNCTION(exec)
	void CheatSetTimeStamp(FString Day, int32 Hour, int32 Minutes, FString AMPM);
	UFUNCTION(exec)
	void CheatIncreaseSunRotationSpeed(float Percentage);
	UFUNCTION(exec)
	void CheatPauseWorldTimer(bool bShouldPause);


	// Case Manager Cheats
	void CheatResetCase(const FString& CaseToResetName);
	UFUNCTION(exec)
	void CheatResetPlayedVideos();
	UFUNCTION(exec)

	// Cinematic Manager Cheats
	void CheatResetPlayedCinematics();
	UFUNCTION(exec)
	void CheatSkipVideo();
	UFUNCTION(exec)
	void CheatSkipCinematic();
	UFUNCTION(exec)
	void CheatHideHud(const bool bShouldHide);
	UFUNCTION(exec)
	void CheatHideMapMenu(const bool bShouldHide);

	// Debug Commands
	UFUNCTION(exec)
	void DebugToggleGameplayTagViewer();

	//UI Manager Cheats
	UFUNCTION(exec)
	void CheatDisableUI();
	
protected:

	virtual void InitCheatManager() override;
	
private:

	UPROPERTY()
	USI_GameInstance* GameInstance;
	UPROPERTY()
	USI_GameplayTagManager* SITagManager;
};
