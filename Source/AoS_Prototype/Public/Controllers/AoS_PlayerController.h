// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/Actor/AoS_LineTraces.h"
#include "InputActionValue.h"
#include "AoS_PlayerController.generated.h"


class UAoS_EnhancedInputComponent;
class UMediaSoundComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableActorAdded, TArray<AActor*>, Actors);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractableActorRemoved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractPressed, AActor*, ActorToInteractWith, AActor*, Caller);

enum class EPlayerMode : uint8;

class AAoS_Nick;
class UAoS_HUD;

UCLASS()
class AOS_PROTOTYPE_API AAoS_PlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* InteractableActor;
	UPROPERTY()
	AActor* ObservableActor;
	UPROPERTY()
	UAoS_HUD* PlayerHUD;
	UPROPERTY()
	AAoS_Nick* Nick = nullptr;
	
	bool bPlayerCanMove = true;
	bool bPlayerCanTurn = true;

protected:

	bool bObservationMode = false;
	
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
	UPROPERTY(BlueprintAssignable)
	FOnInteractPressed OnInteractPressed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UAoS_EnhancedInputComponent* EnhancedInputSettings;
	
	
	FOnInteractableActorAdded OnInteractableActorAdded;
	FOnInteractableActorRemoved OnInteractableActorRemoved;

	// ================== FUNCTIONS ==================

	UFUNCTION(BlueprintImplementableEvent)	
	bool CreateLineTrace(ETraceType DrawDebugType, FVector Start, FVector End, FLinearColor TraceColor, FLinearColor TraceHitColor, FHitResult& HitResults);
	UFUNCTION(BlueprintCallable)
	void LockPlayerMovement(bool bLockMovement, bool bLockTurning);
	UFUNCTION(BlueprintCallable)
	void SetInteractableActor(AActor* InInteractableActor);
	UFUNCTION(BlueprintCallable)
	void SetObservableActor(AActor* InObservableActor);

	UFUNCTION(BlueprintPure)
	UMediaSoundComponent* GetMediaSoundComponent() const;
	
protected:

	// Player Input Functions
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostInitializeComponents() override;
	
	void RequestMoveForward(const FInputActionValue& ActionValue);
	void RequestMoveRight(const FInputActionValue& ActionValue);
	void RequestTurnRight(const FInputActionValue& ActionValue);
	void RequestLookUp(const FInputActionValue& ActionValue);
	void RequestInteract();
	void RequestEnterObservation();
	void RequestObserveObject();

	void PostCameraBlend(ACameraActor* InFollowCamera, ACameraActor* InObservationCamera);

	UFUNCTION()
	void OnPlayerModeChanged(EPlayerMode InPlayerMode, EPlayerMode InPreviousPlayerMode);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UMediaSoundComponent* MediaSoundComponent;
	
	FTimerHandle CameraBlendHandle;
	FTimerDelegate CameraBlendDelegate;
};
