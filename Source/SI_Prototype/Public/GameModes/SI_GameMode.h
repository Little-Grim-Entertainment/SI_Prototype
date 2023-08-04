// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "GameFramework/GameMode.h"
#include "SI_GameMode.generated.h"

class USI_CharacterData;
class USI_GameInstance;
class USI_GameplayAbility;
class USI_HUD;
class USI_LevelManager;
class USI_MoviePlayerWidget;
class USI_SkipWidget;
class USI_UserWidget;

class APlayerStart;

UCLASS()
class SI_PROTOTYPE_API ASI_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	ASI_GameMode();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Classes)
	TSubclassOf<USI_UserWidget> MainMenuClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Classes)
	TSubclassOf<USI_UserWidget> SystemMenuClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Classes)
	TSubclassOf<USI_HUD> PlayerHUD_Class;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Classes)
	TSubclassOf<USI_MoviePlayerWidget> MoviePlayerWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Classes)
	TSubclassOf<USI_SkipWidget> SkipWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Classes)
	TArray<TSubclassOf<USI_UserWidget>> LoadingScreens;

	UPROPERTY(EditAnywhere, Category = Data)
	USI_CharacterData* NickSpadeCDA;
	UPROPERTY(EditAnywhere, Category = Data)
	USI_CharacterData* GizboCDA;
	
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

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

private:

	UPROPERTY()
	USI_LevelManager* LevelManager;
	UPROPERTY()
	USI_GameInstance* GameInstance;
};