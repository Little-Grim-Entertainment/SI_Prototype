// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_UIManager.generated.h"

class AAoS_PlayerController;
class UAoS_HUD;
class UDlgContext;
class UAoS_UserWidget;
class UAoS_GameInstance;
class UAoS_MapData;

enum class EPlayerMode : uint8;

UCLASS()
class AOS_PROTOTYPE_API UAoS_UIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	// This subsystem will handle the creation and display of the various UI in Ace of Spades
	
public:

	UAoS_UIManager();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreatePlayerHUD();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowPlayerHUD(bool bShouldShow);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RemovePlayerHUD();
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void DisplayLoadingScreen(bool bShouldDisplay, bool bShouldFade);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void DisplayDialogueBox(UDlgContext* DlgContext);

	// Game Instance Delegates
	UFUNCTION()
	void OnPlayerModeChanged(EPlayerMode NewPlayerMode);
	
	// Level Manager Delegates
	UFUNCTION()
	void OnLevelBeginLoad(UAoS_MapData* LoadingLevel, bool bShouldFade);
	UFUNCTION()
	void OnLevelFinishLoad(UAoS_MapData* LoadingLevel, bool bShouldFade);

	UFUNCTION()
	void OnGameInstanceInit();

protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:

	UPROPERTY()
	UWorld* World;
	UPROPERTY()
	UAoS_GameInstance* GameInstance;
	UPROPERTY()
	AAoS_PlayerController* PlayerController;
	UPROPERTY()
	UAoS_UserWidget* LoadingScreen;
	UPROPERTY()
	UAoS_HUD* PlayerHUD;
	
};
