// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AoS_GameInstance.generated.h"

class UAoS_CaseManager;


UENUM(BlueprintType)
enum EPlayerMode
{
	PM_ExplorationMode     UMETA(DisplayName = "ExplorationMode"),
	PM_DialogueMode      UMETA(DisplayName = "DialogueMode"),
	PM_ObservationMode   UMETA(DisplayName = "ObservationMode"),
	PM_GameMenuMode   UMETA(DisplayName = "GameMenuMode"),
	PM_VendorMode   UMETA(DisplayName = "VendorMode"),
  };

UCLASS()
class AOS_PROTOTYPE_API UAoS_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	UAoS_GameInstance();

	UFUNCTION(Exec, Category = Cases)
	void ResetCase(FString CaseToResetName);
	
private:

	UPROPERTY()
	UAoS_CaseManager* CaseManager;

	virtual void Init() override;
	
};
