// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_InteractionPrompt.h"
#include "Components/TextBlock.h"


void USI_InteractionPrompt::SetInteractText_Implementation(const FText& InInteractionText)
{
	InteractionText = InInteractionText;
}

void USI_InteractionPrompt::ShowWidget_Implementation()
{
	Super::ShowWidget_Implementation();
}
