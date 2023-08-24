// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gadgets/SI_CameraGadget.h"


// Sets default values
ASI_CameraGadget::ASI_CameraGadget()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraBase"));
	CameraLens = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraLens"));
	CameraFlash = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraFlash"));
	CameraBase->SetupAttachment(RootComponent);
	CameraLens->SetupAttachment(CameraBase);
	CameraFlash->SetupAttachment(CameraBase);
}

// Called when the game starts or when spawned
void ASI_CameraGadget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASI_CameraGadget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

