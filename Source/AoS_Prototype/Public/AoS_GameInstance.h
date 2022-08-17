// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/AoS_PlayerController.h"
#include "Engine/GameInstance.h"
#include "AoS_GameInstance.generated.h"

class UAoS_UserWidget;
class UAoS_WorldManager;
class AAoS_Character;
class UAoS_CharacterData;
class AAoS_Nick;
class APlayerStart;

class UAoS_CaseManager;
class UAoS_LevelManager;
class UAoS_UIManager;

class UAoS_MapList;

UENUM(BlueprintType)
enum EPlayerMode
{
	PM_ExplorationMode     UMETA(DisplayName = "ExplorationMode"),
	PM_DialogueMode      UMETA(DisplayName = "DialogueMode"),
	PM_ObservationMode   UMETA(DisplayName = "ObservationMode"),
	PM_InspectionMode   UMETA(DisplayName = "InspectionMode"),
	PM_InterrogationMode   UMETA(DisplayName = "nterrogationMode"),
	PM_GameMenuMode   UMETA(DisplayName = "GameMenuMode"),
	PM_VendorMode   UMETA(DisplayName = "VendorMode"),
  };

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerModeChanged, EPlayerMode, NewPlayerMode);

UCLASS()
class AOS_PROTOTYPE_API UAoS_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	UAoS_GameInstance();

	UPROPERTY(BlueprintAssignable, Category = "PlayerData")
	FOnPlayerModeChanged OnPlayerModeChanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WorldSettings")
	float TimeModifier = 10.0f;
	UPROPERTY(EditAnywhere, Category = "PlayerData")
	UAoS_CharacterData* CDA_NickSpade;
	UPROPERTY(EditAnywhere, Category = "Loading")
	TSubclassOf<UAoS_UserWidget> LoadingScreen;
	UPROPERTY(EditAnywhere, Category = "Levels")
	UAoS_MapList* MapList;
	
	UFUNCTION(Exec, Category = Cases)
	void ResetCase(FString CaseToResetName);
	
	UFUNCTION(BlueprintCallable)
	void SpawnPlayer();
	
	UFUNCTION(BlueprintPure, Category = "PlayerData")
	EPlayerMode GetPlayerMode() const;
	UFUNCTION(BlueprintPure, Category = "PlayerData")
	AAoS_PlayerController* GetAOSPlayerController();
	
	UFUNCTION(BlueprintCallable, Category = "PlayerData")
	void SetPlayerMode(EPlayerMode InPlayerMode);

	void SetupLevelBindings();
	void SetupUIBindings();
	void SetupCaseBindings();
	
	// Level Delegates
	UFUNCTION()
	void OnLevelBeginLoad(ULevelStreaming* LoadingLevel);
	UFUNCTION()
	void OnLevelFinishLoad(ULevelStreaming* LoadedLevel);
	UFUNCTION()
	void OnLevelFinishUnload(ULevelStreaming* UnloadedLevel);

	UAoS_WorldManager* GetWorldManager() const {return WorldManager;};
		
private:

	// Subsystems
	UPROPERTY()
	UAoS_CaseManager* CaseManager;
	UPROPERTY()
	UAoS_LevelManager* LevelManager;
	UPROPERTY()
	UAoS_UIManager* UIManager;
	UPROPERTY()
	UAoS_WorldManager* WorldManager;
	
	UPROPERTY()
	AAoS_Nick* NickSpadeCharacter;
	UPROPERTY()
	AAoS_PlayerController* AoS_PlayerController;

	EPlayerMode PlayerMode;
	bool bIsInMenu;

	virtual void Init() override;

	APlayerStart* GetPlayerStart() const;
	
};
