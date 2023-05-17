// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SI_GameInstanceSubsystem.h"
#include "SI_GizboManager.generated.h"

class ASI_PlayerCameraManager;
class ASI_MoveToIndicator;
class ASI_Nick;
class ASI_Gizbo;
class ASI_GizboController;
/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_GizboManager : public USI_GameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Gizbo")
	void SpawnGizbo();
	UFUNCTION()
	void SetGizboStartTag(FString InStartTag);
	UFUNCTION(BlueprintPure, Category = "Gizbo")
	ASI_Gizbo* GetGizbo();
	UFUNCTION(BlueprintCallable, Category = "Gizbo")
	void ShowGizbo(bool bShouldHide);
	UFUNCTION(BlueprintPure, Category = "Gizbo")
	ASI_GizboController* GetGizboController();
	UPROPERTY()
	ASI_Nick* Nick;
	void StartMoveTo(ASI_PlayerCameraManager* InCameraManager ,AActor* InPawn, bool& InbMarkerIsValid);
	void StartUpdateIndicatorPositionTimer();
	void CancelUpdateIndicatorPositionTimer();
	void UpdateMoveToIndicatorPosition() const;
	ASI_MoveToIndicator* SpawnMoveToIndicator(FVector InHitLocation);
	UPROPERTY()
	ASI_PlayerCameraManager* CameraManager;
	UPROPERTY()
	TSubclassOf<ASI_MoveToIndicator> MoveToIndicatorClass;
	UPROPERTY()
	ASI_MoveToIndicator* MoveToIndicator;
	
protected:

	virtual void OnGameModeBeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float AdaptableActionMaximumRadius = 2000.0f;
	
private:

	FTimerHandle IndicatorPositionTimerHandle;
	float UpdateIndicatorDelay = 0.1f;
	UPROPERTY()
	ASI_GizboController* GizboController;
	UPROPERTY()
	ASI_Gizbo* GizboCharacter;

	FString GizboStartTag;
};
