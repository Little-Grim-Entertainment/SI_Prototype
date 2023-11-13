// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SI_Character.h"
#include "AIController.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "Controllers/SI_NPCController_Interactable.h"
#include "SI_NPC.generated.h"

using namespace SI_NativeGameplayTagLibrary;

struct FGameplayTagContainer;
class USI_StateTreeComponentBase;

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
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, NoClear, Category = "AI")
	FGameplayTag CurrentBehaviorTag = SITag_Behavior;


};
