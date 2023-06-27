// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "Components/Actor/SI_LineTraces.h"
#include "InputActionValue.h"
#include "SI_PlayerController.generated.h"

class USI_GameplayTagManager;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableActorAdded, TArray<AActor*>, Actors);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractableActorRemoved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractPressed, AActor*, ActorToInteractWith, AActor*, Caller);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCameraSetup);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPostCameraSetup, AActor*, InNewViewTarget);

class ASI_InteractableActor;
class ASI_MoveToIndicator;
class USI_EnhancedInputComponent;
class UMediaSoundComponent;
class USI_UserWidget;
class USI_GizboManager;
class ASI_Gizbo;
class ASI_Nick;
class USI_HUD;

UCLASS()
class SI_PROTOTYPE_API ASI_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
	UPROPERTY()
	ASI_InteractableActor* InteractableActor;
	UPROPERTY()
	AActor* ObservableActor;
	UPROPERTY()
	USI_HUD* PlayerHUD;
	UPROPERTY()
	ASI_Nick* Nick;
	
	UPROPERTY()
	USI_GizboManager* GizboManager;
	UPROPERTY()
	AActor* MoveToActor;
	
	bool bPlayerCanMove = true;
	bool bPlayerCanTurn = true;

protected:

	bool bObservationMode = false;
	bool bAdaptableActionMode = false; 
	bool bMoveToMarker = false;
	
	float ObservationDistance = 1000.;

	FVector ObservationStart = FVector(0);
	FVector ObservationEnd = FVector(0);
	
public:
	
	ASI_PlayerController();
		
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

	UPROPERTY()
	ASI_Gizbo* Gizbo;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	USI_EnhancedInputComponent* EnhancedInputSettings;
	
	FOnInteractableActorAdded OnInteractableActorAdded;
	FOnInteractableActorRemoved OnInteractableActorRemoved;
	
	UPROPERTY(BlueprintAssignable, Category = "PlayerCamera")
	FOnCameraSetup OnCameraSetup;
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "PlayerCamera")
	FOnPostCameraSetup OnPostCameraSetup;

	// ================== FUNCTIONS ==================
	UFUNCTION(BlueprintImplementableEvent)	
	bool CreateLineTrace(ETraceType DrawDebugType, FVector Start, FVector End, FLinearColor TraceColor, FLinearColor TraceHitColor, FHitResult& HitResults);
	UFUNCTION(BlueprintCallable)
	void SetInteractableActor(AActor* InInteractableActor);
	UFUNCTION(BlueprintCallable)
	void SetObservableActor(AActor* InObservableActor);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void AddInputMappingByTag(const FGameplayTag InMappingTag, const FGameplayTag InSecondaryTag = FGameplayTag());
	void AddSecondaryInputMappingByTag(FGameplayTag InMappingTag, FGameplayTag InSecondaryTag);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void RemoveInputMappingByTag(const FGameplayTag InMappingTag, const FGameplayTag InSecondaryTag = FGameplayTag());
	
	void SetFocusedWidget(USI_UserWidget* InWidgetToFocus);
	
	UFUNCTION()
	void SetMenuMode(bool bSetMenuMode = false);
	
	UFUNCTION(BlueprintPure)
	UMediaSoundComponent* GetMediaSoundComponent() const;

	bool IsInMenuMode() const;

protected:
	// Player Input Functions
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostInitializeComponents() override;
	virtual void SetupInputComponent() override;
	
	void RequestMoveForward(const FInputActionValue& ActionValue);
	void RequestMoveRight(const FInputActionValue& ActionValue);
	void RequestTurnRight(const FInputActionValue& ActionValue);
	void RequestLookUp(const FInputActionValue& ActionValue);
	void RequestInteract();
	void RequestToggleObservation();
	void RequestObserveObject();
	void RequestSkipCinematic();
	void RequestNextDialogue();
	void RequestPreviousDialogue();
	void RequestExitDialogue();
	void RequestToggleSystemMenu();
	void RequestUseGadget();
	void RequestUseGadgetSecondary();
	
	// Gizbo
	void RequestToggleGizboFollow(); //TODO: Amend later once the radial menu for Gizbo commands has been implemented
	void RequestToggleGizboAdaptableAction();//TODO: Amend later once the radial menu for Gizbo commands has been implemented
	void RequestGizboAdaptableActionConfirm(); //TODO: Amend later once the radial menu for Gizbo commands has been implemented
	void RequestGizboUseGadget();
	void RequestGizboUseGadgetSecondary();

	//ConstructGadget
	void RequestGadget(AActor* InActor, FGameplayTag InGadgetTag);
	void RequestGadgetNickOne();
	void RequestGadgetNickTwo();
	void RequestGadgetNickThree();
	void RequestGadgetNickFour();
	void RequestGadgetGizboOne();
	void RequestGadgetGizboTwo();
	void RequestGadgetGizboThree();
	void RequestGadgetGizboFour();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UMediaSoundComponent* MediaSoundComponent;
	
	UPROPERTY()
	USI_UserWidget* FocusedWidget;
	UPROPERTY()
	USI_GameplayTagManager* SITagManager;

	bool bInMenuMode;
	bool bUsingAdaptableAction;

	FTimerHandle CameraBlendHandle;
};
