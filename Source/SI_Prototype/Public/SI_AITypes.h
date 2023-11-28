// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_AITypes.generated.h"

class ASI_NPCController;
class ASI_Nick;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMoveToLocationUpdated, FVector&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMoveToRotationUpdated, FRotator&)

USTRUCT(BlueprintType)
struct FSI_NPCMemory
{
	GENERATED_BODY()

	FSI_NPCMemory() = default;
	FSI_NPCMemory(FVector& InLocation, FRotator& InRotation);

	FVector& GetMoveToLocation() { return MoveToLocation; }
	void SetMoveToLocation(FVector& InLocation);
	FRotator& GetMoveToRotation() { return MoveToRotation; }
	void SetMoveToRotation(FRotator& InRotation);
	TObjectPtr<ASI_Nick> GetNick() { return Nick; }
	void SetNick(TObjectPtr<ASI_Nick> InNick);

	UPROPERTY(EditAnywhere, Category = "AI | Memory")
	TObjectPtr<ASI_Nick> Nick = nullptr;
	UPROPERTY(EditAnywhere, Category = "AI | Memory")
	FVector MoveToLocation = FVector();
	UPROPERTY(EditAnywhere, Category = "AI | Memory")
	FRotator MoveToRotation = FRotator();

	FOnMoveToLocationUpdated OnMoveToLocationUpdated;
	FOnMoveToRotationUpdated OnMoveToRotationUpdated;
	
	bool operator == (const FSI_NPCMemory& Other) const;
	bool operator != (const FSI_NPCMemory& Other) const;
};

USTRUCT(BlueprintType)
struct FSI_NPCMovementHelper
{
	GENERATED_BODY()

	FSI_NPCMovementHelper() = default;

	float CalculateMovementSpeed(float InCurrentDistance, float InCurrentTargetSpeed);
	
	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MinDistance = 1.0f;
	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MaxDistance = 250.0f;
	
	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MinSpeed = 1.0f;
	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MaxSpeed = 300.0f;
	
	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MinTargetSpeed = 1.0f;
	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MaxTargetSpeed = 300.0f;
};