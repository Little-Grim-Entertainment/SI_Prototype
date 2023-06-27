// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_InteractableActor.h"
#include "Interfaces/SI_MovableInterface.h"
#include "SI_MovableActor.generated.h"

UCLASS()
class SI_PROTOTYPE_API ASI_MovableActor : public ASI_InteractableActor, public ISI_MovableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASI_MovableActor();

	UStaticMeshComponent* GetMesh() const { return Mesh; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnPossessMovable_Implementation(AActor* Caller) override;
	virtual void OnEndPossessMovable_Implementation(AActor* Caller) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
