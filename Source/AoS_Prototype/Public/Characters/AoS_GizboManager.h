// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_GameInstanceSubsystem.h"
#include "AoS_GizboManager.generated.h"

class AAoS_PlayerCameraManager;
class AAoS_MoveToIndicator;
class AAoS_Nick;
class AAoS_Gizbo;
class AAoS_GizboController;
/**
 * 
 */
UCLASS()
class AOS_PROTOTYPE_API UAoS_GizboManager : public UAoS_GameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Gizbo")
	void SpawnGizbo();
	UFUNCTION()
	void SetGizboStartTag(FString InStartTag);
	UFUNCTION(BlueprintPure, Category = "Gizbo")
	AAoS_Gizbo* GetGizbo();
	UFUNCTION(BlueprintCallable, Category = "Gizbo")
	void ShowGizbo(bool bShouldHide);
	UFUNCTION(BlueprintPure, Category = "Gizbo")
	AAoS_GizboController* GetGizboController();
	UPROPERTY()
	AAoS_Nick* Nick = nullptr;
	void StartMoveTo(AAoS_PlayerCameraManager* InCameraManager ,AActor* InPawn, bool& InbMarkerIsValid);
	void StartUpdateIndicatorPositionTimer();
	void UpdateMoveToIndicatorPosition() const;
	AAoS_MoveToIndicator* SpawnMoveToIndicator(FVector InHitLocation);

	TSubclassOf<AAoS_MoveToIndicator> MoveToIndicatorClass;
	UPROPERTY()
	AAoS_MoveToIndicator* MoveToIndicator;
	
protected:

	virtual void OnGameModeBeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float AdaptableActionMaximumRadius = 2000.0f;
	
private:

	FTimerHandle IndicatorPositionTimerHandle;
	float UpdateIndicatorDelay = 0.1f;
	UPROPERTY()
	AAoS_GizboController* GizboController;
	UPROPERTY()
	AAoS_Gizbo* GizboCharacter;

	FString GizboStartTag;
};
