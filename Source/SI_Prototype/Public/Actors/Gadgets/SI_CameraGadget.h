// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_BaseGadget.h"
#include "Abilities/SI_GameplayAbility_Gadget_UsePrimary.h"
#include "SI_CameraGadget.generated.h"

UCLASS()
class SI_PROTOTYPE_API ASI_CameraGadget : public ASI_BaseGadget
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASI_CameraGadget();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Film)
	USceneComponent* Film;

private:
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* CameraBase;
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* CameraLens;
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* CameraFlash;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
