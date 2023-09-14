// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gadgets/SI_CameraGadgetFilm.h"


// Sets default values
ASI_CameraGadgetFilm::ASI_CameraGadgetFilm()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlankFilm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlankFilm"));
	BlankFilm->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASI_CameraGadgetFilm::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASI_CameraGadgetFilm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

