// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gadgets/SI_BaseGadget.h"

#include "LG_DebugMacros.h"

void ASI_BaseGadget::ActivatePrimaryAction_Implementation()
{
	LG_PRINT(5.f, Red, "SI_BaseGadget: Activate Primary");
		
}

void ASI_BaseGadget::ActivateSecondaryAction_Implementation()
{
}

void ASI_BaseGadget::CancelPrimaryAction_Implementation()
{
}

void ASI_BaseGadget::CancelSecondaryAction_Implementation()
{
}
