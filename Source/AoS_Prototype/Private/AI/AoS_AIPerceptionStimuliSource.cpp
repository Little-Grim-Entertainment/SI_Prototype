// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AoS_AIPerceptionStimuliSource.h"

UAoS_AIPerceptionStimuliSource::UAoS_AIPerceptionStimuliSource(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bAutoRegisterAsSource = true;
}

void UAoS_AIPerceptionStimuliSource::RegisterSense(TSubclassOf<UAISense> SenseClass)
{
	RegisterAsSourceForSenses.AddUnique(SenseClass);
}