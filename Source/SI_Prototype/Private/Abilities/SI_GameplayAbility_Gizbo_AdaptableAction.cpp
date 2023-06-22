// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Gizbo_AdaptableAction.h"

#include "Actors/SI_MoveToIndicator.h"
#include "Cameras/SI_PlayerCameraManager.h"

void USI_GameplayAbility_Gizbo_AdaptableAction::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USI_GameplayAbility_Gizbo_AdaptableAction::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USI_GameplayAbility_Gizbo_AdaptableAction::StartAdaptableAction(ASI_PlayerCameraManager* InCameraManager, AActor* InPawn, bool& InbMarkerIsValid)
{
	float MaxMoveToDistance = 2000.0f;
	CameraManager = InCameraManager;
	
	FVector TraceStart = CameraManager->GetCameraLocation();
	FVector TraceEnd =  CameraManager->GetActorForwardVector() * MaxMoveToDistance + TraceStart;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(CameraManager);
	QueryParams.AddIgnoredActor(InPawn);
	
	FHitResult OutHit;
	
	bool bBlockingHit = GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, ECollisionChannel::ECC_WorldDynamic, QueryParams);
	//	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 30.0f, 0, 1.0f);

	if(bBlockingHit)
	{
		FVector HitLocation = OutHit.Location;
		MoveToIndicator = SpawnMoveToIndicator(HitLocation);
		InbMarkerIsValid = true;
		StartUpdateIndicatorPositionTimer();
	}	
}

void USI_GameplayAbility_Gizbo_AdaptableAction::StartUpdateIndicatorPositionTimer()
{
	GetWorld()->GetTimerManager().SetTimer(IndicatorPositionTimerHandle, this, &ThisClass::UpdateMoveToIndicatorPosition, UpdateIndicatorDelay, true);
}

void USI_GameplayAbility_Gizbo_AdaptableAction::CancelUpdateIndicatorPositionTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(IndicatorPositionTimerHandle);
}

void USI_GameplayAbility_Gizbo_AdaptableAction::UpdateMoveToIndicatorPosition() const
{
	if(!MoveToIndicator) return;
	
	FHitResult HitResult;
	FVector Start = CameraManager->GetCameraLocation();
	FVector End = CameraManager->GetCameraLocation() + CameraManager->GetActorForwardVector() * 2000;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel2);

	//TODO: Amend later once GAS is implemented, to check specifically for surfaces that can be traversed.
	if (HitResult.GetActor())
	{
		FVector HitLocation = HitResult.ImpactPoint;

		// Check whether the 'Move To' indicator is within a specific radius
		double Distance = (HitLocation - CameraManager->GetCameraLocation()).Length();
		
		if (Distance < AdaptableActionMaximumRadius)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Orange, FString::SanitizeFloat(Distance, 0));
			MoveToIndicator->SetActorLocation(HitLocation);
		}

		// Keep the 'Move To' actor confined to the bounds of a circle, with radius AdaptableActionMaximumRadius
		// See https://gamedev.stackexchange.com/questions/9607/moving-an-object-in-a-circular-path and
		// https://www.euclideanspace.com/maths/geometry/trig/inverse/index.htm and
		// https://forums.unrealengine.com/t/how-to-get-an-angle-between-2-vectors/280850

		//TODO: Requires further tuning, to make sure that the rotation is correct.
		//When the 'MoveTo' actor currently hits the boundary, it causes the indicator to jump away from where it was previously aligned.

		/*
		TODO: --Pace-- Not sure what Liam is trying to accomplish in this bit of code but removing to make it work simpler for now. 
			FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(CameraManager->GetCameraLocation(), HitLocation);
			double NickArcTan = atan2(CameraManager->GetCameraLocation().Y, CameraManager->GetCameraLocation().X);
			double MoveToArcTan = atan2(UKismetMathLibrary::GetForwardVector(Rotation).Y, UKismetMathLibrary::GetForwardVector(Rotation).X);
			double Angle = MoveToArcTan - NickArcTan;
				
			float Cosine = cos(Angle);
			float Sine = sin(Angle);
				
			HitLocation.X = CameraManager->GetCameraLocation().X + Cosine * AdaptableActionMaximumRadius;
			HitLocation.Y = CameraManager->GetCameraLocation().Y + Sine * AdaptableActionMaximumRadius;
			Distance = (HitLocation - CameraManager->GetCameraLocation()).Length();
		*/
		
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Orange, FString::SanitizeFloat(Distance, 0));
		MoveToIndicator->SetActorLocation(HitLocation);
	}
}

ASI_MoveToIndicator* USI_GameplayAbility_Gizbo_AdaptableAction::SpawnMoveToIndicator(FVector InHitLocation)
{
	MoveToIndicatorClass = GetMoveToIndicatorClass();
	if(MoveToIndicatorClass == nullptr)
	{
		MoveToIndicatorClass = GetMoveToIndicatorClass();
	}
	
	if(!IsValid(MoveToIndicator))
	{
		FRotator Rotation = FRotator();
		MoveToIndicator = GetWorld()->SpawnActor<ASI_MoveToIndicator>(MoveToIndicatorClass, InHitLocation, Rotation);
	}
	else
	{
		MoveToIndicator->SetActorHiddenInGame(false);
		MoveToIndicator->SetActorLocation(InHitLocation);
	}
	return MoveToIndicator;
}

void USI_GameplayAbility_Gizbo_AdaptableAction::HideMoveToIndicator()
{
	if(MoveToIndicator)
	{
		MoveToIndicator->SetActorHiddenInGame(true);
	}
}
