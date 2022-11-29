// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_InteractionPrompt.h"
#include "Components/TextBlock.h"


void UAoS_InteractionPrompt::SetInteractText_Implementation(const FText& InInteractionText)
{
	InteractionText = InInteractionText;
}

void UAoS_InteractionPrompt::ShowWidget_Implementation()
{
	Super::ShowWidget_Implementation();
}
