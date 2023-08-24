// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/SI_InteractableActor.h"
#include "GameFramework/Actor.h"
#include "SI_SpawnGadgetButton.generated.h"

class ASI_BaseGadget;
class UTextRenderComponent;

UCLASS()
class SI_PROTOTYPE_API ASI_SpawnGadgetButton : public ASI_InteractableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASI_SpawnGadgetButton();

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Button;
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* Text;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASI_BaseGadget> GadgetClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnInteract_Implementation(AActor* Caller) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
