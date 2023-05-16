// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SI_AIPerceptionStimuliSource.h"

USI_AIPerceptionStimuliSource::USI_AIPerceptionStimuliSource(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bAutoRegisterAsSource = true;
}

void USI_AIPerceptionStimuliSource::RegisterSense(TSubclassOf<UAISense> SenseClass)
{
	RegisterAsSourceForSenses.AddUnique(SenseClass);
}