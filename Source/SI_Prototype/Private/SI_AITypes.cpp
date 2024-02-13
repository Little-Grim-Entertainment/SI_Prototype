// Fill out your copyright notice in the Description page of Project Settings.


#include "SI_AITypes.h"

#include "GameplayTagContainer.h"

FSI_NPCMemory::FSI_NPCMemory(FVector& InLocation, FRotator& InRotation, FGameplayTag& InNextActionTag)
	:	MoveToLocation (InLocation),
		MoveToRotation (InRotation),
		NextActionTag (InNextActionTag)
{
}

void FSI_NPCMemory::SetMoveToLocation(const FVector& InLocation)
{
	MoveToLocation = InLocation;

	OnMoveToLocationUpdated.Broadcast(MoveToLocation);
}

void FSI_NPCMemory::SetMoveToRotation(const FRotator& InRotation)
{
	MoveToRotation = InRotation;
	
	OnMoveToRotationUpdated.Broadcast(MoveToRotation);
}

void FSI_NPCMemory::SetNextActionTag(const FGameplayTag& InNextActionTag)
{
	NextActionTag = InNextActionTag;
}

void FSI_NPCMemory::SetNick(TObjectPtr<ASI_Nick> InNick)
{
	Nick = InNick;
}

void FSI_NPCMemory::SetTargetObject(TObjectPtr<AActor> InTargetObject)
{
	TargetObject = InTargetObject;
}

void FSI_NPCMemory::SetAbilityCaller(TObjectPtr<AActor> InAbilityCaller)
{
	AbilityCaller = InAbilityCaller;
}

void FSI_NPCMemory::SetAbilityInstigator(TObjectPtr<AActor> InAbilityInstigator)
{
	AbilityInstigator = InAbilityInstigator;
}

bool FSI_NPCMemory::operator==(const FSI_NPCMemory& Other) const
{
	return MoveToLocation == Other.MoveToLocation && MoveToRotation == Other.MoveToRotation;
}

bool FSI_NPCMemory::operator!=(const FSI_NPCMemory& Other) const
{
	return MoveToLocation != Other.MoveToLocation || MoveToRotation != Other.MoveToRotation;
}

float FSI_NPCMovementHelper::CalculateMovementSpeed(float InCurrentDistance, float InCurrentTargetSpeed)
{
	const float DistanceDelta = MaxDistance - MinDistance;
	const float SpeedDelta = MaxSpeed - MinSpeed;
	const float TargetSpeedDelta = MaxTargetSpeed - MinTargetSpeed;
	
	const float DistanceToUse = InCurrentDistance - MinDistance;
	const float DistanceRatio = FMath::Clamp(DistanceToUse / DistanceDelta, 0.0f, 1.0f);

	const float TargetSpeedToUse = InCurrentTargetSpeed - MinTargetSpeed;
	const float TargetSpeedRatio = FMath::Clamp(TargetSpeedToUse / TargetSpeedDelta, 0.0f, 1.0f);

	const float TotalRatio = FMath::Min(DistanceRatio + TargetSpeedRatio, 1.0f);

	const float DesiredSpeed = MinSpeed + (TotalRatio * SpeedDelta);

	return DesiredSpeed;
}
