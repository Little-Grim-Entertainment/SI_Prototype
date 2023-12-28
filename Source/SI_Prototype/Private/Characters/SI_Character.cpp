// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"

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

#if WITH_EDITOR
void ASI_Character::SetupPreviewCharacter()
{
	if(IsValid(GetCapsuleComponent())){GetCapsuleComponent()->DestroyComponent(true);}
	if(IsValid(GetArrowComponent())){GetArrowComponent()->DestroyComponent(true);}
}
#endif
