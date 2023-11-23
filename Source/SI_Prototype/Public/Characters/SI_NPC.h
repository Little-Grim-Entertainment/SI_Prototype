// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SI_Character.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "SI_NPC.generated.h"

using namespace SI_NativeGameplayTagLibrary;

DECLARE_MULTICAST_DELEGATE_OneParam(FBehaviorTagUpdated, FGameplayTag& InBehaviorTag)

struct FGameplayTagContainer;
class UStateTreeComponent;

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
	FGameplayTag& GetCurrentBehaviorTag();
	UFUNCTION(BlueprintSetter, Category = "AI")
	void SetCurrentBehavior(const FGameplayTag NewBehaviorTag);
	UFUNCTION(BlueprintGetter, Category = "AI")
	bool IsPerformingMainAction() const;

	FBehaviorTagUpdated OnBehaviorTagUpdated;
	
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, NoClear, Category = "AI")
	FGameplayTag CurrentBehaviorTag = SITag_Behavior;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category = "AI")
	TObjectPtr<UStateTreeComponent> StateTreeComponent;
};
