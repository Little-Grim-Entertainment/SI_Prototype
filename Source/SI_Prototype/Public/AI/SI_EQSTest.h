// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "SI_EQSTest.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_EQSTest : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	USI_EQSTest();
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
