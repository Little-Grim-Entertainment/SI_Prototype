// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actor/SI_EnhancedInputComponent.h"

#include "SI_GameInstance.h"
#include "GameModes/SI_GameMode.h"


USI_InputConfig* USI_EnhancedInputComponent::GetInputConfig() const
{
	const USI_GameInstance* GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	if (!IsValid(GameInstance)) {return nullptr;}

	return GameInstance->InputConfig;
}
