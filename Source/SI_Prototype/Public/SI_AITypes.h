// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_AITypes.generated.h"

class ASI_NPCController;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMoveToLocationUpdated, FVector&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMoveToRotationUpdated, FRotator&)

USTRUCT(BlueprintType)
struct FSI_NPCMemory
{
	GENERATED_BODY()

	FSI_NPCMemory() {};
	FSI_NPCMemory(AActor* InTargetActor);
	FSI_NPCMemory(FVector& InLocation, FRotator& InRotation);

	FVector& GetMoveToLocation() { return MoveToLocation; }
	void SetMoveToLocation(FVector& InLocation);
	FRotator& GetMoveToRotation() { return MoveToRotation; }
	void SetMoveToRotation(FRotator& InRotation);

	UPROPERTY(EditAnywhere, Category = "Input", meta=(Optional))
	TObjectPtr<AActor> TargetActor = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input", meta=(Optional))
	float AcceptanceRadius = 50.0f;
	UPROPERTY(EditAnywhere, Category = "Input", meta=(Optional))
	FVector MoveToLocation = FVector();
	UPROPERTY(EditAnywhere, Category = "Input", meta=(Optional))
	FRotator MoveToRotation = FRotator();

	FOnMoveToLocationUpdated OnMoveToLocationUpdated;
	FOnMoveToRotationUpdated OnMoveToRotationUpdated;
	
	bool operator == (const FSI_NPCMemory& Other) const;
	bool operator != (const FSI_NPCMemory& Other) const;
};