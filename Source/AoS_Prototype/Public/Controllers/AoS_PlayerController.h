// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/Actor/AoS_LineTraces.h"
#include "AoS_PlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableActorAdded, TArray<AActor*>, Actors);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractableActorRemoved);

class UAoS_HUD;

UCLASS()
class AOS_PROTOTYPE_API AAoS_PlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* FocusedActor;
	UPROPERTY()
	UAoS_HUD* PlayerHUD;

	bool bPlayerCanMove = true;
	bool bPlayerCanTurn = true;

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<UAoS_HUD> PlayerHUD_Class;
	
public:
	
	AAoS_PlayerController();
		
	// ================== VARIABLES ==================

	// Player Input Variables
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	UPROPERTY(EditDefaultsOnly, Category = LineTracing)
	UAoS_LineTraces* LineTraceComponent;

	FOnInteractableActorAdded OnInteractableActorAdded;
	FOnInteractableActorRemoved OnInteractableActorRemoved;

	UPROPERTY()
	TArray<AActor*> InteractableActors;

	// ================== FUNCTIONS ==================

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractPressed(AActor* ActorToInteractWith, AActor* Caller);
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractableActorFound(AActor* ActorFound);
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractableActorLost(AActor* ActorLost);
	UFUNCTION(BlueprintImplementableEvent)	
	bool CreateLineTrace(ETraceType DrawDebugType, FVector Start, FVector End, FLinearColor TraceColor, FLinearColor TraceHitColor, FHitResult& HitResults);
	UFUNCTION(BlueprintCallable)
	void ShowHUD();
	UFUNCTION(BlueprintCallable)
	void HideHUD();
	UFUNCTION(BlueprintCallable)
	void RefreshHUD();
	UFUNCTION(BlueprintCallable)
	void LockPlayerMovement(bool bLockMovement, bool bLockTurning);
	
	void SetFocusedActor(AActor* ActorToSet);
	void AddToInteractableActors(AActor* ActorToAdd);
	void RemoveFromInteractableActors(AActor* ActorToRemove);
	
	// Getters
	UFUNCTION(BlueprintPure)
	UAoS_HUD* GetPlayerHUD();
	
	
protected:

	// Player Input Functions
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	void RequestMoveForward(float Value);
	void RequestMoveRight(float Value);
	void RequestTurnRight(float AxisValue);
	void RequestLookUp(float AxisValue);
	void RequestInteract();
	
};
