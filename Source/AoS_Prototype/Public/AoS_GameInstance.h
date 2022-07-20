// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AoS_GameInstance.generated.h"

class UAoS_CaseManager;


USTRUCT(BlueprintType)
struct FCharacterData
{
	GENERATED_BODY()

	

};

UCLASS()
class AOS_PROTOTYPE_API UAoS_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	UAoS_GameInstance();

	UFUNCTION(Exec, Category = Cases)
	void ResetCases();
	
private:

	UPROPERTY()
	UAoS_CaseManager* CaseManager;

	virtual void Init() override;
	
};
