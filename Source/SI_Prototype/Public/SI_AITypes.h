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

	FSI_NPCMemory() {};
	FSI_NPCMemory(FVector& InLocation, FRotator& InRotation);

	FVector& GetMoveToLocation() { return MoveToLocation; }
	void SetMoveToLocation(FVector& InLocation);
	FRotator& GetMoveToRotation() { return MoveToRotation; }
	void SetMoveToRotation(FRotator& InRotation);
	TObjectPtr<ASI_Nick> GetNick() { return Nick; }
	void SetNick(TObjectPtr<ASI_Nick> InNick);

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<ASI_Nick> Nick = nullptr;
	UPROPERTY(EditAnywhere, Category = "AI")
	FVector MoveToLocation = FVector();
	UPROPERTY(EditAnywhere, Category = "AI")
	FRotator MoveToRotation = FRotator();

	FOnMoveToLocationUpdated OnMoveToLocationUpdated;
	FOnMoveToRotationUpdated OnMoveToRotationUpdated;
	
	bool operator == (const FSI_NPCMemory& Other) const;
	bool operator != (const FSI_NPCMemory& Other) const;
};