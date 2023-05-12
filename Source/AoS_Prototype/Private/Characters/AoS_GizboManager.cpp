// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AoS_GizboManager.h"

#include "AoS_GameInstance.h"
#include "Characters/AoS_Nick.h"
#include "Camera/CameraComponent.h"
#include "Actors/AoS_MoveToIndicator.h"
#include "Cameras/AoS_PlayerCameraManager.h"
#include "Characters/AoS_Character.h"
#include "Characters/AoS_Gizbo.h"
#include "Controllers/AoS_GizboController.h"
#include "Data/Characters/AoS_CharacterData.h"
#include "GameFramework/PlayerStart.h"
#include "GameModes/AoS_GameMode.h"
#include "Kismet/KismetMathLibrary.h"


void UAoS_GizboManager::SpawnGizbo()
{
	if (!GameInstance->GetGameMode()->GizboCDA) {return;}
	if (!GameInstance->GetGameMode()->GizboCDA->CharacterClass){return;}

	if (GizboStartTag == "")
	{
		GizboStartTag = "Gizbo_DefaultSpawn";
	}
	
	if (const APlayerStart* GizboStart = GameInstance->GetGameMode()->GetPlayerStart(GizboStartTag))
	{
		FVector GizboLocation = FVector(GizboStart->GetActorLocation().X, GizboStart->GetActorLocation().Y, GizboStart->GetActorLocation().Z - 50);
		
		if (!GizboCharacter)
		{
			const FActorSpawnParameters PlayerSpawnParameters;
			GizboCharacter = GetWorld()->SpawnActor<AAoS_Gizbo>(GameInstance->GetGameMode()->GizboCDA->CharacterClass, GizboLocation, GizboStart->GetActorRotation(), PlayerSpawnParameters);
		}
		else
		{
			GizboCharacter->SetActorLocation(GizboLocation);
			GizboCharacter->SetActorRotation(GizboStart->GetActorRotation());
		}
	}
	
	if (!GizboController && GizboCharacter)
	{
		GizboController = Cast<AAoS_GizboController>(GizboCharacter->GetController());
	}

	if (GizboController)
	{
		GizboController->Possess(GizboCharacter);
		GizboController->Nick = Nick;
	}
}

void UAoS_GizboManager::SetGizboStartTag(FString InStartTag)
{
	GizboStartTag = InStartTag;
}

AAoS_Gizbo* UAoS_GizboManager::GetGizbo()
{
	return GizboCharacter;
}

AAoS_GizboController* UAoS_GizboManager::GetGizboController()
{
	return GizboController;
}

void UAoS_GizboManager::StartMoveTo(AAoS_PlayerCameraManager* InCameraManager, AActor* InPawn, bool& InbMarkerIsValid)
{
	float MaxMoveToDistance = 2000.0f;
	
	FVector TraceStart = InCameraManager->GetCameraLocation();
	FVector TraceEnd =  InCameraManager->GetActorForwardVector() * MaxMoveToDistance + TraceStart;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(InCameraManager);
	QueryParams.AddIgnoredActor(InPawn);
	
	FHitResult OutHit;
	
	bool bBlockingHit = GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, ECollisionChannel::ECC_WorldDynamic, QueryParams);
//	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 30.0f, 0, 1.0f);

	if(bBlockingHit)
	{
		FVector HitLocation = OutHit.Location;
		MoveToIndicator = SpawnMoveToIndicator(HitLocation);
		InbMarkerIsValid = true;
	}
	StartUpdateIndicatorPositionTimer();
}

void UAoS_GizboManager::StartUpdateIndicatorPositionTimer()
{
	GetWorld()->GetTimerManager().SetTimer(IndicatorPositionTimerHandle, this, &UAoS_GizboManager::UpdateMoveToIndicatorPosition, UpdateIndicatorDelay, true);
}

void UAoS_GizboManager::UpdateMoveToIndicatorPosition() const
{
	if(!IsValid(Nick)) return; 
	
	FHitResult HitResult;
	FVector Start = Nick->GetFollowCamera()->GetComponentLocation();
	FVector End = Nick->GetFollowCamera()->GetComponentLocation() + Nick->GetFollowCamera()->GetForwardVector() * 2000;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel2);

	//TODO: Amend later once GAS is implemented, to check specifically for surfaces that can be traversed.
	if (HitResult.GetActor())
	{
		FVector HitLocation = HitResult.ImpactPoint;

		// Check whether the 'Move To' indicator is within a specific radius
		double Distance = (HitLocation - Nick->GetActorLocation()).Length();
		
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
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Nick->GetFollowCamera()->GetComponentLocation(), HitLocation);
		double NickArcTan = atan2(Nick->GetFollowCamera()->GetComponentLocation().Y, Nick->GetFollowCamera()->GetComponentLocation().X);
		double MoveToArcTan = atan2(UKismetMathLibrary::GetForwardVector(Rotation).Y, UKismetMathLibrary::GetForwardVector(Rotation).X);
		double Angle = MoveToArcTan - NickArcTan;
			
		float Cosine = cos(Angle);
		float Sine = sin(Angle);
			
		HitLocation.X = Nick->GetActorLocation().X + Cosine * AdaptableActionMaximumRadius;
		HitLocation.Y = Nick->GetActorLocation().Y + Sine * AdaptableActionMaximumRadius;
		Distance = (HitLocation - Nick->GetActorLocation()).Length();
			
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Orange, FString::SanitizeFloat(Distance, 0));
		MoveToIndicator->SetActorLocation(HitLocation);
	}
}

AAoS_MoveToIndicator* UAoS_GizboManager::SpawnMoveToIndicator(FVector InHitLocation)
{
	if(!IsValid(MoveToIndicator))
	{
		FRotator Rotation = FRotator();
		MoveToIndicator = GetWorld()->SpawnActor<AAoS_MoveToIndicator>(MoveToIndicatorClass, InHitLocation, Rotation);
	}
	else
	{
		MoveToIndicator->SetActorHiddenInGame(false);
		MoveToIndicator->SetActorLocation(InHitLocation);
	}
	return MoveToIndicator;
}

void UAoS_GizboManager::ShowGizbo(bool bShouldHide)
{
	if (!IsValid(GizboCharacter)) {return;}
	GizboCharacter->SetActorHiddenInGame(bShouldHide);
}

void UAoS_GizboManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();

	SpawnGizbo();
}
