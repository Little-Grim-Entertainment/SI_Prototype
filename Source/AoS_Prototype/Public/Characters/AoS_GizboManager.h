// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_GameInstanceSubsystem.h"
#include "AoS_GizboManager.generated.h"

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
	
	
protected:

	virtual void OnGameModeBeginPlay() override;
	
private:

	UPROPERTY()
	AAoS_GizboController* AoS_GizboController;
	UPROPERTY()
	AAoS_Gizbo* GizboCharacter;

	FString GizboStartTag;
};
