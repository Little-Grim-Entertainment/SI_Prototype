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

UCLASS()
class AOS_PROTOTYPE_API AAoS_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AAoS_GameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes)
	TSubclassOf<UAoS_UserWidget> MainMenuClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes)
	TSubclassOf<UAoS_HUD> PlayerHUD_Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes)
	TSubclassOf<UAoS_MoviePlayerWidget> MoviePlayerWidget;
	
	UPROPERTY(EditAnywhere, Category = "CharacterData")
	UAoS_CharacterData* NickSpadeCDA;
	UPROPERTY(EditAnywhere, Category = "CharacterData")
	UAoS_CharacterData* GizboCDA;
	
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
