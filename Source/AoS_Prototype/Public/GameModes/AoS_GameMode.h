// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AoS_GameMode.generated.h"

class UAoS_MoviePlayerWidget;
class UAoS_GameInstance;
class UAoS_UserWidget;
class APlayerStart;
class UAoS_CharacterData;
class UAoS_LevelManager;
class UAoS_HUD;
class UAoS_SkipWidget;
class UAoS_InputConfig;
class UAoS_MapList;

UCLASS()
class AOS_PROTOTYPE_API AAoS_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AAoS_GameMode();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Classes)
	TSubclassOf<UAoS_UserWidget> MainMenuClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Classes)
	TSubclassOf<UAoS_UserWidget> SystemMenuClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Classes)
	TSubclassOf<UAoS_HUD> PlayerHUD_Class;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Classes)
	TSubclassOf<UAoS_MoviePlayerWidget> MoviePlayerWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Classes)
	TSubclassOf<UAoS_SkipWidget> SkipWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Classes)
	TArray<TSubclassOf<UAoS_UserWidget>> LoadingScreens;

	UPROPERTY(EditAnywhere, Category = Data)
	UAoS_InputConfig* InputConfig;
	UPROPERTY(EditAnywhere, Category = Data)
	UAoS_CharacterData* NickSpadeCDA;
	UPROPERTY(EditAnywhere, Category = Data)
	UAoS_CharacterData* GizboCDA;
	UPROPERTY(EditAnywhere, Category = Data)
	UAoS_MapList* MapList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WorldSettings")
	float TimeModifier = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Levels")
	float LevelLoadDelay = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MusicSettings")
	float GlobalFadeInDuration = .5f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MusicSettings")
	float GlobalFadeOutDuration = .5f;
	
	UFUNCTION(BlueprintCallable, Category = "PlayerStart")
	APlayerStart* GetPlayerStart(FString InPlayerStartTag = FString(TEXT(""))) const;
	UFUNCTION(BlueprintCallable, Category = "PlayerStart")
	TArray<APlayerStart*> GetAllPlayerStarts() const;
	
	UFUNCTION(BlueprintCallable, Category = "PlayerStart")
	void RestartNickSpawn();

protected:

	virtual void BeginPlay() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

private:

	UPROPERTY()
	UAoS_LevelManager* LevelManager;
	UPROPERTY()
	UAoS_GameInstance* GameInstance;
};
