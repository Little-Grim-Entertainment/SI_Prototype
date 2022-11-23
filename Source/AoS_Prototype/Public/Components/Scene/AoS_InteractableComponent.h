// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "AoS_InteractableComponent.generated.h"

class UWidgetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerBeginOverlap, class AAoS_Nick*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerEndOverlap, class AAoS_Nick*, Player);

UCLASS()
class AOS_PROTOTYPE_API UAoS_InteractableComponent : public UBoxComponent
{
	GENERATED_BODY()

	UPROPERTY()
	bool bIsInteractable = true;
	UPROPERTY()
	AAoS_Nick* PlayerCharacter;
	UPROPERTY()
	class AAoS_PlayerController* PlayerController;
	
public:	
	// Sets default values for this component's properties
	UAoS_InteractableComponent();

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
};


