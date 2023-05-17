// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_GizboManager.h"

#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SI_GameInstance.h"
#include "Characters/SI_Character.h"
#include "Characters/SI_Nick.h"
#include "Characters/SI_Gizbo.h"
#include "Controllers/SI_GizboController.h"
#include "Data/Characters/SI_CharacterData.h"
#include "Actors/SI_MoveToIndicator.h"
#include "Cameras/SI_PlayerCameraManager.h"
#include "GameFramework/PlayerStart.h"
#include "GameModes/SI_GameMode.h"


void USI_GizboManager::SpawnGizbo()
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
			GizboCharacter = GetWorld()->SpawnActor<ASI_Gizbo>(GameInstance->GetGameMode()->GizboCDA->CharacterClass, GizboLocation, GizboStart->GetActorRotation(), PlayerSpawnParameters);
		}
		else
		{
			GizboCharacter->SetActorLocation(GizboLocation);
			GizboCharacter->SetActorRotation(GizboStart->GetActorRotation());
		}
	}
	
	if (!GizboController && GizboCharacter)
	{
		GizboController = Cast<ASI_GizboController>(GizboCharacter->GetController());
	}

	if (GizboController)
	{
		GizboController->Possess(GizboCharacter);
		GizboController->Nick = Nick;
		MoveToIndicatorClass = GizboController->GetMoveToIndicatorClass();
	}
}

void USI_GizboManager::SetGizboStartTag(FString InStartTag)
{
	GizboStartTag = InStartTag;
}

ASI_Gizbo* USI_GizboManager::GetGizbo()
{
	return GizboCharacter;
}

ASI_GizboController* USI_GizboManager::GetGizboController()
{
	return GizboController;
}

void USI_GizboManager::StartMoveTo(ASI_PlayerCameraManager* InCameraManager, AActor* InPawn, bool& InbMarkerIsValid)
{
	float MaxMoveToDistance = 2000.0f;
	CameraManager = InCameraManager;
	
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
		StartUpdateIndicatorPositionTimer();
	}	
}

void USI_GizboManager::StartUpdateIndicatorPositionTimer()
{
	GetWorld()->GetTimerManager().SetTimer(IndicatorPositionTimerHandle, this, &USI_GizboManager::UpdateMoveToIndicatorPosition, UpdateIndicatorDelay, true);
}

void USI_GizboManager::CancelUpdateIndicatorPositionTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(IndicatorPositionTimerHandle);
}

void USI_GizboManager::UpdateMoveToIndicatorPosition() const
{
	if(!MoveToIndicator) return;
	
	FHitResult HitResult;
	FVector Start = CameraManager->GetCameraLocation();
	FVector End = CameraManager->GetCameraLocation() + CameraManager->GetActorForwardVector() * 2000;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel2);

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
		//TODO: Pace... Not sure what Liam is trying to accomplish in this bit of code but removing for now. 
		/*	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(CameraManager->GetCameraLocation(), HitLocation);
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

ASI_MoveToIndicator* USI_GizboManager::SpawnMoveToIndicator(FVector InHitLocation)
{
	if(MoveToIndicatorClass == nullptr)
	{
		MoveToIndicatorClass = GizboController->GetMoveToIndicatorClass();
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
void USI_GizboManager::ShowGizbo(bool bShouldHide)
{
	if (!IsValid(GizboCharacter)) {return;}
	GizboCharacter->SetActorHiddenInGame(bShouldHide);
}

void USI_GizboManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();

	SpawnGizbo();
}
