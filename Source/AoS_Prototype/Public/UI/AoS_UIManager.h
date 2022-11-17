// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_GameInstanceSubsystem.h"
#include "AoS_UIManager.generated.h"

class UAoS_DialogueManager;
class UAoS_Objective;
class UAoS_Part;
class UAoS_Case;
class AAoS_PlayerController;
class UAoS_HUD;
class UAoS_UserWidget;
class UAoS_MapData;

enum class EPlayerMode : uint8;

UCLASS()
class AOS_PROTOTYPE_API UAoS_UIManager : public UAoS_GameInstanceSubsystem
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

	// Level Manager Delegates
	UFUNCTION()
	void OnLevelBeginLoad(UAoS_MapData* LoadingLevel, bool bShouldFade);
	UFUNCTION()
	void OnLevelFinishLoad(UAoS_MapData* LoadingLevel, bool bShouldFade);

	// Case Manager Delegates
	UFUNCTION()
	void OnCaseAccepted(UAoS_Case* AcceptedCase);
	UFUNCTION()
	void OnCaseActivated(UAoS_Case* ActivatedCase);
	UFUNCTION()
	void OnCaseCompleted(UAoS_Case* CompletedCase);

	UFUNCTION()
	void OnPartActivated(UAoS_Part* ActivatedPart);
	UFUNCTION()
	void OnPartCompleted(UAoS_Part* CompletedPart);
	
	UFUNCTION()
	void OnObjectiveActivated(UAoS_Objective* ActivatedObjective);
	UFUNCTION()
	void OnObjectiveCompleted(UAoS_Objective* CompletedObjective);

	//Dialogue Manager Delegates
	void BindDialogueManagerDelegates(UAoS_DialogueManager* InDialogueManager);

protected:

	virtual void OnGameInstanceInit() override;
	virtual void OnPlayerModeChanged(EPlayerMode NewPlayerMode) override;

	void DisplayDialogueBox();


private:

	void BindLevelManagerDelegates();
	void BindCaseManagerDelegates();
	
	UPROPERTY()
	AAoS_PlayerController* PlayerController;
	UPROPERTY()
	UAoS_UserWidget* LoadingScreen;
	UPROPERTY()
	UAoS_HUD* PlayerHUD;
	
};
