// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ATPCInterpolationSpeed.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "ATPCFunctionLibrary.generated.h"

class AActor;

UCLASS()
class ADVANCEDTHIRDPERSONCAMERA_API UATPCFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
private:
	template<typename ValueType, typename SmoothInterpFunctionType, typename ConstInterpFunctionType, typename EqualValuePredType>
	static ValueType InterpImpl(const ValueType& Current, const ValueType& Target, float DeltaTime, FATPCInterploationSpeed& InterpSpeed, bool bResetSpeedIfResultEqualToTarget, SmoothInterpFunctionType SmoothInterpFunc, ConstInterpFunctionType ConstInterpFunc, EqualValuePredType EqualPred);

public:
	UFUNCTION(BlueprintCallable, Category = "ATPC|Utils", meta = (DisplayName = "Interpolate Speed"))
	static void InterpolationSpeed_InterpolateSpeed(FATPCInterploationSpeed& InterpSpeed, float DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "ATPC|Utils")
	static void InterpolationSpeed_ResetSpeed(FATPCInterploationSpeed& InterpSpeed);
	UFUNCTION(BlueprintCallable, Category = "ATPC|Utils", meta = (DisplayName = "Get Current Interpolation Speed"))
	static float InterpolationSpeed_GetCurrentInterpolationSpeed(const FATPCInterploationSpeed& InterpSpeed);

	UFUNCTION(BlueprintCallable, Category = "ATPC|Utils")
	static FVector InterpVector(const FVector& Current, const FVector& Target, float DeltaTime, FATPCInterploationSpeed& InterpSpeed, bool bResetSpeedIfResultEqualToTarget = true);
	UFUNCTION(BlueprintCallable, Category = "ATPC|Utils")
	static FRotator InterpRotator(const FRotator& Current, const FRotator& Target, float DeltaTime, FATPCInterploationSpeed& InterpSpeed, bool bResetSpeedIfResultEqualToTarget = true);
	UFUNCTION(BlueprintCallable, Category = "ATPC|Utils")
	static float InterpFloat(const float& Current, const float& Target, float DeltaTime, FATPCInterploationSpeed& InterpSpeed, bool bResetSpeedIfResultEqualToTarget = true);

	/** Reattach spring arm child components to atpc component */
	UFUNCTION(BlueprintCallable, Category = "ATPC|Gameplay")
	static bool ReplaceSpringArmToATPCComponent(AActor* Actor);
};

template<typename ValueType, typename SmoothInterpFunctionType, typename ConstInterpFunctionType, typename EqualValuePredType>
ValueType UATPCFunctionLibrary::InterpImpl(const ValueType& Current, const ValueType& Target, float DeltaTime, FATPCInterploationSpeed& InterpSpeed, bool bResetSpeedIfResultEqualToTarget, SmoothInterpFunctionType SmoothInterpFunc, ConstInterpFunctionType ConstInterpFunc, EqualValuePredType EqualResultTargetPred)
{
	InterpSpeed.InterpolateSpeed(DeltaTime);

	auto result = Current;

	switch (InterpSpeed.InterpType)
	{
	case EATPCInterpolationType::SmoothInterpolation:
		result = Invoke(SmoothInterpFunc, Current, Target, DeltaTime, InterpSpeed.GetCurrentInterpolationSpeed());
		break;
	case EATPCInterpolationType::ConstInterpolation:
		result = Invoke(ConstInterpFunc, Current, Target, DeltaTime, InterpSpeed.GetCurrentInterpolationSpeed());
		break;
	default:
		ensureMsgf(0, TEXT("Unsupported interpolation type: %d(%s)"), static_cast<int32>(InterpSpeed.InterpType), *UEnum::GetValueAsString(InterpSpeed.InterpType));
		break;
	}

	if (bResetSpeedIfResultEqualToTarget && Invoke(EqualResultTargetPred, result, Target))
	{
		InterpSpeed.ResetCurrentSpeed();
	}

	return result;
}
