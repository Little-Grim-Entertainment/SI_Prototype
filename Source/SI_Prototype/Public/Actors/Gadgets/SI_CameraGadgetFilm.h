// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SI_CameraGadgetFilm.generated.h"

UCLASS()
class SI_PROTOTYPE_API ASI_CameraGadgetFilm : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASI_CameraGadgetFilm();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* BlankFilm;

private:


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
