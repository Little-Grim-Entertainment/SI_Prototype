// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SI_PowerDoor.generated.h"

class ASI_PowerActor;
//TODO: RENAME ALL OF THIS STUFF TO ASI_SOMETHING
UCLASS()
class SI_PROTOTYPE_API APowerDoor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APowerDoor();

	UPROPERTY(EditAnywhere, Category = Power)
	TArray<ASI_PowerActor*> AttachedPowerActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timer)
	FTimerHandle FDoorMovementTimer;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckPowerRequirements(bool bIsFullyPowered);	
	UFUNCTION(BlueprintImplementableEvent)
	void OpenDoorBPEvent();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
