// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AoS_GameInstance.generated.h"

class AAoS_GameMode;
class UAoS_HUD;
class AAoS_GizboController;
class AAoS_PlayerController;
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
enum class EPlayerMode : uint8
{
	PM_NONE					UMETA(DisplayName = "NONE"),
	PM_MainMenuMode			UMETA(DisplayName = "MainMenuMode"),
	PM_ExplorationMode		UMETA(DisplayName = "ExplorationMode"),
	PM_LevelLoadingMode		UMETA(DisplayName = "LevelLoadingMode"),
	PM_CinematicMode		UMETA(DisplayName = "CinematicMode"),
	PM_DialogueMode			UMETA(DisplayName = "DialogueMode"),
	PM_ObservationMode		UMETA(DisplayName = "ObservationMode"),
	PM_InspectionMode		UMETA(DisplayName = "InspectionMode"),
	PM_InterrogationMode	UMETA(DisplayName = "InterrogationMode"),
	PM_GameMenuMode			UMETA(DisplayName = "GameMenuMode"),
	PM_VendorMode			UMETA(DisplayName = "VendorMode"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerModeChanged, EPlayerMode, NewPlayerMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSubsystemBindingsComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameInstanceInit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameModeBeginPlay);

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
	UPROPERTY(BlueprintAssignable, Category = "MapData")
	FOnGameModeBeginPlay OnGameModeBeginPlay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WorldSettings")
	float TimeModifier = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Loading")
	TArray<TSubclassOf<UAoS_UserWidget>> LoadingScreens;
	UPROPERTY(EditAnywhere, Category = "Levels")
	UAoS_MapList* MapList;
	UPROPERTY(EditAnywhere, Category = "Levels")
	float LevelLoadDelay = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MusicSettings")
	float AudioFadeInDuration = .5f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MusicSettings")
	float AudioFadeOutDuration = .5f;
	
	UFUNCTION(BlueprintPure, Category = "PlayerData")
	EPlayerMode GetPlayerMode() const;
	UFUNCTION(BlueprintPure, Category = "GameMode")
	AAoS_GameMode* GetCurrentGameMode();

	UFUNCTION()
	void SetCurrentGameMode(AAoS_GameMode* InGameMode);
	
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
	AAoS_GameMode* CurrentGameMode;
	
	EPlayerMode PlayerMode;

	virtual void Init() override;
	
};
