// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/Actor/AoS_LineTraces.h"
#include "AoS_PlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableActorAdded, TArray<AActor*>, Actors);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractableActorRemoved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractPressed, AActor*, ActorToInteractWith, AActor*, Caller);

enum class EPlayerMode : uint8;

class UAoS_HUD; class AAoS_Nick;

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

	bool bObservationMode = false;

	AAoS_Nick* Nick = nullptr;

	float ObservationDistance = 1000.;
	FVector ObservationStart = FVector(0);
	FVector ObservationEnd = FVector(0);
	
	
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
	UPROPERTY(BlueprintAssignable)
	FOnInteractPressed OnInteractPressed;

	
	FOnInteractableActorAdded OnInteractableActorAdded;
	FOnInteractableActorRemoved OnInteractableActorRemoved;

	UPROPERTY()
	TArray<AActor*> InteractableActors;

	// ================== FUNCTIONS ==================

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractableActorFound(AActor* ActorFound);
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractableActorLost(AActor* ActorLost);
	UFUNCTION(BlueprintImplementableEvent)	
	bool CreateLineTrace(ETraceType DrawDebugType, FVector Start, FVector End, FLinearColor TraceColor, FLinearColor TraceHitColor, FHitResult& HitResults);
	UFUNCTION(BlueprintCallable)
	void LockPlayerMovement(bool bLockMovement, bool bLockTurning);
	
	void SetFocusedActor(AActor* ActorToSet);
	void AddToInteractableActors(AActor* ActorToAdd);
	void RemoveFromInteractableActors(AActor* ActorToRemove);
	
protected:

	// Player Input Functions
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void RequestMoveForward(float Value);
	void RequestMoveRight(float Value);
	void RequestTurnRight(float AxisValue);
	void RequestLookUp(float AxisValue);
	void RequestInteract();
	void RequestObservation();
};
