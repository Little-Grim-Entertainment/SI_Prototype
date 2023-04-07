// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actor/AoS_EnhancedInputComponent.h"
#include "GameModes/AoS_GameMode.h"


UAoS_InputConfig* UAoS_EnhancedInputComponent::GetInputConfig() const
{
	const AAoS_GameMode* GameMode = Cast<AAoS_GameMode>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GameMode)) {return nullptr;}

	return GameMode->InputConfig;
}
