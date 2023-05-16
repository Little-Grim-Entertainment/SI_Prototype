// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "SI_InteractableComponent.generated.h"

class ISI_InteractInterface;
class ASI_PlayerController;
class USI_InteractionIcon;
class USI_InteractionPrompt;
class UWidgetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerBeginOverlap, class ASI_Nick*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerEndOverlap, class ASI_Nick*, Player);

UCLASS()
class SI_PROTOTYPE_API USI_InteractableComponent : public UBoxComponent
{
	GENERATED_BODY()

	UPROPERTY()
	bool bIsInteractable = true;
	
	UPROPERTY()
	ASI_Nick* PlayerCharacter;
	
	UPROPERTY()
	ASI_PlayerController* PlayerController;
	
	UPROPERTY()
	UWidgetComponent* InteractionIcon;
	
	UPROPERTY()
	UWidgetComponent* InteractionPrompt;

	ISI_InteractInterface* InteractableOwner;

	FTimerHandle RefreshDelayHandle;
	
public:	
	// Sets default values for this component's properties
	USI_InteractableComponent();

	UPROPERTY(BlueprintAssignable, Category = "Overlap")
	FOnPlayerBeginOverlap OnPlayerBeginOverlap;
	UPROPERTY(BlueprintAssignable, Category = "Overlap")
	FOnPlayerEndOverlap OnPlayerEndOverlap;

protected:
	
	UPROPERTY(EditAnywhere, Category = "Customization")
	FText InteractionText;

	// ================== FUNCTIONS ==================
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Getters
	UFUNCTION(BlueprintPure)
	FText GetInteractionText() {return InteractionText;}
	UFUNCTION(BlueprintPure)
	bool GetIsInteractable() {return bIsInteractable;}
	
	// Setters
	UFUNCTION(BlueprintCallable)
	void SetIsInteractable(bool bInteractable);
	UFUNCTION(BlueprintCallable)
	void SetInteractionText(FText TextToSet) { InteractionText = TextToSet;}

	UFUNCTION(BlueprintCallable)
	void ShowInteractionPromptWidget();
	UFUNCTION(BlueprintCallable)
	void RefreshInteractionPromptWidget(float InShowDelay);
	UFUNCTION(BlueprintCallable)
	void HideInteractionPromptWidget();
	UFUNCTION(BlueprintCallable)
	void ShowInteractionIconWidget();
	UFUNCTION(BlueprintCallable)
	void RefreshInteractionIconWidget(float InShowDelay);
	UFUNCTION(BlueprintCallable)
	void HideInteractionIconWidget();
	
	UFUNCTION(BlueprintPure)
	USI_InteractionPrompt* GetInteractionPromptWidget() const;
	UFUNCTION(BlueprintPure)
	USI_InteractionIcon* GetInteractionIconWidget() const;
};


