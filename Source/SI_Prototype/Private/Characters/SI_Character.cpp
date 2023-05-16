// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_Character.h"

// Sets default values
ASI_Character::ASI_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASI_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASI_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

