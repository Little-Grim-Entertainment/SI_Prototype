// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SI_LineTraces.generated.h"

UENUM(BlueprintType)
enum class ETraceType : uint8
{
	None		UMETA(DisplayName = "None"),
	ForOneFrame UMETA(DisplayName = "ForOneFrame"), 
	ForDuration UMETA(DisplayName = "ForDuration"),
	Persistent  UMETA(DisplayName = "Persistent"),
};

USTRUCT(BlueprintType)
struct FTraceConditions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SearchDistance = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETraceType DrawDebugType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Offsets")
	float StartZOffset = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Offsets")
	float EndZOffset = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Colors")
	FLinearColor TraceColor = FLinearColor::Red;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Colors")
	FLinearColor TraceHitColor = FLinearColor::Green;	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SI_PROTOTYPE_API USI_LineTraces : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	class ASI_PlayerController* PlayerController;

public:	
	// Sets default values for this component's properties
	USI_LineTraces();

	UPROPERTY()
	TArray<AActor*> InteractableActors;
	UPROPERTY()
	bool bEnableInteractableSearch;
	UPROPERTY()
	bool bInteractableFound;
	
	UPROPERTY(EditAnywhere, Category = "LineTraces")
	FTraceConditions InteractableSearch;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "LineTracing")
	AActor* SearchForInteractableActor();
	
	UFUNCTION(BlueprintCallable, Category = "LineTracing")
	void EnableInteractableSearch(const TArray<AActor*> ActorsToSearchFor);
	UFUNCTION(BlueprintCallable, Category = "LineTracing")
	void DisableInteractableSearch();

private:

	void SetTraceVectors(FVector& StartVector, FVector& EndVector, const float StartZOffset, const float EndZOffset, const float SearchDistance);
		
};


