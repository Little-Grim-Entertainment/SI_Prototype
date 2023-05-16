// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actor/SI_EnhancedInputComponent.h"
#include "GameModes/SI_GameMode.h"


USI_InputConfig* USI_EnhancedInputComponent::GetInputConfig() const
{
	const ASI_GameMode* GameMode = Cast<ASI_GameMode>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GameMode)) {return nullptr;}

	return GameMode->InputConfig;
}
