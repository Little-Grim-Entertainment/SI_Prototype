// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_Character.h"


#include "Characters/SI_CharacterManager.h"


// Sets default values
ASI_Character::ASI_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

USI_CharacterData* ASI_Character::GetCharacterData() const
{
	return CharacterData;
}
