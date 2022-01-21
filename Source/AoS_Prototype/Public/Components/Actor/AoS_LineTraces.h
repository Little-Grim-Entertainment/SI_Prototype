// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AoS_LineTraces.generated.h"

UENUM(BlueprintType)
enum ETraceType
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
	TEnumAsByte<ETraceType> DrawDebugType;
	
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
class AOS_PROTOTYPE_API UAoS_LineTraces : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	class AAoS_PlayerController* PlayerController;

public:	
	// Sets default values for this component's properties
	UAoS_LineTraces();

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


