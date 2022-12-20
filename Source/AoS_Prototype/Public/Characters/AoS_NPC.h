// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AoS_Character.h"
#include "AIController.h"
#include "AoS_NPC.generated.h"

UENUM(BlueprintType)
enum class ECurrentBehavior : uint8
{
	CB_Nothing					UMETA(DisplayName = "Nothing"),
	CB_Wandering				UMETA(DisplayName = "Wandering"),
	CB_Patrolling				UMETA(DisplayName = "Patrolling"),
	CB_MovingToTarget			UMETA(DisplayName = "Moving to Target"),
	CB_PerformingMainAction		UMETA(DisplayName = "Performing Main Action")
};

/**
 * Base NPC class for AoS Prototype
 */
UCLASS()
class AOS_PROTOTYPE_API AAoS_NPC : public AAoS_Character
{
	GENERATED_BODY()

public:
	AAoS_NPC();
	
	UFUNCTION(BlueprintGetter, Category = "AI")
	virtual UBehaviorTree* GetNothingTree() const;
	
	UFUNCTION(BlueprintGetter, Category = "AI")
	virtual UBehaviorTree* GetWanderingTree() const;
	
	UFUNCTION(BlueprintGetter, Category = "AI")
	virtual UBehaviorTree* GetPatrollingTree() const;

	UFUNCTION(BlueprintGetter, Category = "AI")
	virtual UBehaviorTree* GetMovingToTargetTree() const;

	UFUNCTION(BlueprintGetter, Category = "AI")
	virtual UBehaviorTree* GetMainTree() const;

	UFUNCTION(BlueprintGetter, Category = "AI")
	ECurrentBehavior GetCurrentBehavior() const;

	UFUNCTION(BlueprintSetter, Category = "AI")
	void SetCurrentBehavior(const ECurrentBehavior NewBehavior);

	UFUNCTION(BlueprintGetter, Category = "AI")
	bool IsDoingNothing() const;

	UFUNCTION(BlueprintGetter, Category = "AI")
	bool IsWandering() const;

	UFUNCTION(BlueprintGetter, Category = "AI")
	bool IsPatrolling() const;

	UFUNCTION(BlueprintGetter, Category = "AI")
	bool IsMovingToTarget() const;

	UFUNCTION(BlueprintGetter, Category = "AI")
	bool IsPerformingMainAction() const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, NoClear, Category = "AI")
	TObjectPtr<UBehaviorTree> NothingTree = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, NoClear, Category = "AI")
	TObjectPtr<UBehaviorTree> WanderingTree = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, NoClear, Category = "AI")
	TObjectPtr<UBehaviorTree> PatrollingTree = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, NoClear, Category = "AI")
	TObjectPtr<UBehaviorTree> MovingToTargetTree = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, NoClear, Category = "AI")
	TObjectPtr<UBehaviorTree> MainTree = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, NoClear, Category = "AI")
	ECurrentBehavior CurrentBehavior = ECurrentBehavior::CB_Nothing;
};
