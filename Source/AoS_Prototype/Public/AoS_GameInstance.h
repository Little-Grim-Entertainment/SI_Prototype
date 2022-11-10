// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AoS_Gizbo.h"
#include "Controllers/AoS_GizboController.h"
#include "Controllers/AoS_PlayerController.h"
#include "Engine/GameInstance.h"
#include "Levels/AoS_LevelManager.h"
#include "AoS_GameInstance.generated.h"

class UAoS_UserWidget;
class UAoS_WorldManager;
class AAoS_Character;
class UAoS_CharacterData;
class AAoS_Nick;
class AAoS_Gizbo;
class APlayerStart;

class UAoS_CaseManager;
class UAoS_LevelManager;
class UAoS_UIManager;

class UAoS_MapList;
class UAoS_MapData;

UENUM(BlueprintType)
enum EPlayerMode
{
	PM_ExplorationMode     UMETA(DisplayName = "ExplorationMode"),
	PM_DialogueMode      UMETA(DisplayName = "DialogueMode"),
	PM_ObservationMode   UMETA(DisplayName = "ObservationMode"),
	PM_InspectionMode   UMETA(DisplayName = "InspectionMode"),
	PM_InterrogationMode   UMETA(DisplayName = "InterrogationMode"),
	PM_GameMenuMode   UMETA(DisplayName = "GameMenuMode"),
	PM_VendorMode   UMETA(DisplayName = "VendorMode"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerModeChanged, EPlayerMode, NewPlayerMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSubsystemBindingsComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameInstanceInit);



UCLASS()
class AOS_PROTOTYPE_API UAoS_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	UAoS_GameInstance();

	UPROPERTY(BlueprintAssignable, Category = "PlayerData")
	FOnSubsystemBindingsComplete OnSubsystemBindingsComplete;
	UPROPERTY(BlueprintAssignable, Category = "PlayerData")
	FOnPlayerModeChanged OnPlayerModeChanged;

	UPROPERTY(BlueprintAssignable, Category = "MapData")
	FOnGameInstanceInit OnGameInstanceInit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WorldSettings")
	float TimeModifier = 10.0f;
	UPROPERTY(EditAnywhere, Category = "PlayerData")
	UAoS_CharacterData* CDA_NickSpade;
	UPROPERTY(EditAnywhere, Category = "GizboData")
	UAoS_CharacterData* CDA_Gizbo;
	UPROPERTY(EditAnywhere, Category = "Loading")
	TArray<TSubclassOf<UAoS_UserWidget>> LoadingScreens;
	UPROPERTY(EditAnywhere, Category = "Levels")
	UAoS_MapList* MapList;
	UPROPERTY(EditAnywhere, Category = "Levels")
	float LevelLoadDelay = 0.0f;
	
	UFUNCTION(Exec, Category = Cases)
	void CheatResetCase(FString CaseToResetName);
	
	UFUNCTION(BlueprintCallable)
	void SpawnPlayer();

	UFUNCTION(BlueprintCallable)
	void SpawnGizbo();
	
	UFUNCTION(BlueprintPure, Category = "PlayerData")
	EPlayerMode GetPlayerMode() const;
	UFUNCTION(BlueprintPure, Category = "PlayerData")
	AAoS_PlayerController* GetAOSPlayerController();
	UFUNCTION(BlueprintPure, Category = "GizboData")
	AAoS_GizboController* GetAOSGizboController();
	
	UFUNCTION()
	UAoS_UIManager* GetUIManager() const {return UIManager;}
	UFUNCTION()
	UAoS_WorldManager* GetWorldManager() const {return WorldManager;}
	UFUNCTION()
	UAoS_LevelManager* GetLevelManager() const {return LevelManager;}
	UFUNCTION()
	UAoS_CaseManager* GetCaseManager() const {return CaseManager;}
		
	UFUNCTION(BlueprintCallable, Category = "PlayerData")
	void SetPlayerMode(EPlayerMode InPlayerMode);
	UFUNCTION()
	void SetupBindings();

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
	UPROPERTY()
	AAoS_Gizbo* GizboCharacter;
	UPROPERTY()
	AAoS_GizboController* AoS_GizboController;
	
	FTimerHandle LoadingScreenDelayHandle;
	EPlayerMode PlayerMode;
	bool bIsInMenu;

	virtual void Init() override;
	
	APlayerStart* GetPlayerStart() const;

	// Level Delegates
	UFUNCTION()
	void OnLevelBeginLoad(UAoS_MapData* LoadingLevel, bool bShouldFade = true);
	UFUNCTION()
	void OnLevelFinishLoad(UAoS_MapData* LoadedLevel, bool bShouldFade = true);
	UFUNCTION()
	void OnLevelFinishUnload(UAoS_MapData* UnloadedLevel);
	UFUNCTION()
	void OnMapTypeChanged(EMapType InMapType);
	
};
