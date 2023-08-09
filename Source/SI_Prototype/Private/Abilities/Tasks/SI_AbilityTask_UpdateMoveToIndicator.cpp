// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/SI_AbilityTask_UpdateMoveToIndicator.h"

#include "Characters/SI_Nick.h"
#include "Controllers/SI_PlayerController.h"
#include "Actors/SI_MoveToIndicator.h"
#include "Cameras/SI_PlayerCameraManager.h"
#include "Interfaces/SI_MovableInterface.h"
#include "SI_GameplayTagManager.h"

void USI_AbilityTask_UpdateMoveToIndicator::Activate()
{
	Super::Activate();

	Nick = Cast<ASI_Nick>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(!IsValid(Nick)) {LG_LOG(LogSI_Ability, Error, "Nick is not valid"); return; }
	PC = Cast<ASI_PlayerController>(Nick->GetController());
	if(!IsValid(PC)) {LG_LOG_ERROR(LogSI_Ability,"PlayerController(PC) is not valid"); return; }
	SICameraManger = Cast<ASI_PlayerCameraManager>(PC->PlayerCameraManager);
	if(!IsValid(SICameraManger)) {LG_LOG_ERROR(LogSI_Ability,"SICameraManager is not valid"); return; }

}

void USI_AbilityTask_UpdateMoveToIndicator::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

ASI_MoveToIndicator* USI_AbilityTask_UpdateMoveToIndicator::SpawnMoveToIndicator(const FVector InHitLocation)
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
		MoveToIndicator->SetActiveMeshToDefault();
	}
	else
	{
		MoveToIndicator->SetActorHiddenInGame(false);
		MoveToIndicator->SetActorLocation(InHitLocation);
	}
	return MoveToIndicator;
}

void USI_AbilityTask_UpdateMoveToIndicator::DestroyMoveToIndicator()
{
	if(MoveToIndicator)
	{
		MoveToIndicator->Destroy();
	}
}

void USI_AbilityTask_UpdateMoveToIndicator::StartAdaptableAction(const AActor* InActor)
{

	FVector TraceStart = SICameraManger->GetCameraLocation();
	FVector TraceEnd =  TraceStart + SICameraManger->GetActorForwardVector() * AdaptableActionMaximumRadius;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(SICameraManger);
	QueryParams.AddIgnoredActor(InActor);
	
	FHitResult OutHit;
	
	bool bBlockingHit = GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, ECC_WorldDynamic, QueryParams);

	if(bBlockingHit)
	{
		if(!IsValid(MoveToIndicator))
		{
			MoveToIndicator = SpawnMoveToIndicator(OutHit.Location);
		}

		StartUpdateIndicatorPositionTimer();
	}	
}

void USI_AbilityTask_UpdateMoveToIndicator::StartUpdateIndicatorPositionTimer()
{
	GetWorld()->GetTimerManager().SetTimer(IndicatorPositionTimerHandle, this, &ThisClass::UpdateMoveToIndicatorPosition, UpdateIndicatorDelay, true);
}

void USI_AbilityTask_UpdateMoveToIndicator::CancelUpdateIndicatorPositionTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(IndicatorPositionTimerHandle);
}

void USI_AbilityTask_UpdateMoveToIndicator::UpdateMoveToIndicatorPosition()
{
	if(!MoveToIndicator) {LG_LOG_LOG(LogSI_Ability,"MoveToIndicator is not valid"); return; }
	
	FHitResult HitResult;
	FVector Start = SICameraManger->GetCameraLocation();
	FVector End = SICameraManger->GetCameraLocation() + SICameraManger->GetActorForwardVector() * AdaptableActionMaximumRadius;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel2);

	if (HitResult.GetActor())
	{
		FVector HitLocation = HitResult.ImpactPoint;
		
		if (HitResult.GetActor()->Implements<USI_MovableInterface>())
		{
			// Update HUD
			if(!bHitActorIsMovable)
			{
				PC->GetSITagManager()->AddNewGameplayTag(SITag_UI_HUD_QuickAction_Movable);
				bHitActorIsMovable = true;
			}
			//	FGameplayEventData Payload;
			//	Payload.Target = HitResult.GetActor();
			//	Payload.EventTag = SITag_Ability_PossessMovable;
			//	Nick->GetSIAbilitySystemComponent()->HandleGameplayEvent(Payload.EventTag, &Payload);
		}
		else
		{
			if(bHitActorIsMovable)
			{
				PC->GetSITagManager()->RemoveTag(SITag_UI_HUD_QuickAction_Movable);
			}
			bHitActorIsMovable = false;
		}
		
		MoveToIndicator->SetActorLocation(HitLocation);
	}
}