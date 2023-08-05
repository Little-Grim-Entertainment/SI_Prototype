// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SI_Character.h"
#include "AIController.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "SI_NPC.generated.h"

using namespace SI_NativeGameplayTagLibrary;

struct FGameplayTagContainer;
/**
 * Base NPC class for SI Prototype
 */
UCLASS()
class SI_PROTOTYPE_API ASI_NPC : public ASI_Character
{
	GENERATED_BODY()

public:
	ASI_NPC();
	
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
	FGameplayTag& GetCurrentBehaviorTag();

	UFUNCTION(BlueprintSetter, Category = "AI")
	void SetCurrentBehavior(const FGameplayTag NewBehaviorTag);

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
	TObjectPtr<UBehaviorTree> DefaultTree = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, NoClear, Category = "AI")
	FGameplayTag CurrentBehaviorTag = SITag_Behavior;


};
