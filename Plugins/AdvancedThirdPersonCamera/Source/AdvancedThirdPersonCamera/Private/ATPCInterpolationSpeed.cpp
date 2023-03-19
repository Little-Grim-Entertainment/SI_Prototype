// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#include "ATPCInterpolationSpeed.h"

void FATPCInterploationSpeed::InterpolateSpeed(float DeltaTime)
{
	if (bUseInterpSpeedToInterpolation)
	{
		CurrentInterpSpeed = FMath::FInterpConstantTo(CurrentInterpSpeed, InterpSpeed, DeltaTime, InterpSpeedToInterpolation);
	}
}

float FATPCInterploationSpeed::GetCurrentInterpolationSpeed() const
{
	return bUseInterpSpeedToInterpolation ? CurrentInterpSpeed : InterpSpeed;
}

void FATPCInterploationSpeed::ResetCurrentSpeed()
{
	if (bUseInterpSpeedToInterpolation)
	{
		CurrentInterpSpeed = 0.f;
	}
}

FString FATPCInterploationSpeed::ToString() const
{
	return FString::Printf(TEXT("%.2f"), GetCurrentInterpolationSpeed());
}
