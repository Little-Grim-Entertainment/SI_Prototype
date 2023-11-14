// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/SI_AbilityTask_UpdateMoveToIndicator.h"

#include "Characters/SI_Nick.h"
#include "Controllers/SI_PlayerController.h"
#include "Actors/SI_MoveToIndicator.h"
#include "Cameras/SI_PlayerCameraManager.h"
#include "Interfaces/SI_MovableInterface.h"
#include "SI_GameplayTagManager.h"

USI_AbilityTask_UpdateMoveToIndicator::USI_AbilityTask_UpdateMoveToIndicator(
	const FObjectInitializer& ObjectInitializer)
{
	bTickingTask = true;
}

USI_AbilityTask_UpdateMoveToIndicator* USI_AbilityTask_UpdateMoveToIndicator::UpdateMoveToIndicatorTask(UGameplayAbility* InOwningAbility)
{
	USI_AbilityTask_UpdateMoveToIndicator* UpdateMoveToIndicatorTask= NewAbilityTask<USI_AbilityTask_UpdateMoveToIndicator>(InOwningAbility);

	UpdateMoveToIndicatorTask->OwningAbility = InOwningAbility;
		
	return UpdateMoveToIndicatorTask;
}

void USI_AbilityTask_UpdateMoveToIndicator::Activate()
{
	Super::Activate();
	
	PC = OwningAbility->GetOwningActorFromActorInfo()->GetInstigatorController<ASI_PlayerController>();
	if(!IsValid(PC)) {LG_LOG_ERROR(LogLG_Ability,"PlayerController(PC) is not valid"); return; }
	Nick = Cast<ASI_Nick>(PC->GetPawn());
	if(!IsValid(Nick)) {LG_LOG(LogLG_Ability, Error, "Nick is not valid"); return; }
	SICameraManger = Cast<ASI_PlayerCameraManager>(PC->PlayerCameraManager);
	if(!IsValid(SICameraManger)) {LG_LOG_ERROR(LogLG_Ability,"SICameraManager is not valid"); return; }
}

void USI_AbilityTask_UpdateMoveToIndicator::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	
	UpdateMoveToIndicatorPosition();
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

void USI_AbilityTask_UpdateMoveToIndicator::UpdateMoveToIndicatorPosition()
{
	if(!MoveToIndicator) {LG_LOG_LOG(LogLG_Ability,"MoveToIndicator is not valid"); return; }
	
	FHitResult HitResult;
	FVector TraceStart = SICameraManger->GetCameraLocation();
	FVector TraceEnd =  TraceStart + SICameraManger->GetActorForwardVector() * AdaptableActionMaximumRadius;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(SICameraManger);
	QueryParams.AddIgnoredActor(Nick);
	
	bool bBlockingHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_WorldDynamic, QueryParams);

	if(bBlockingHit)
	{
		if(!IsValid(MoveToIndicator))
		{
			MoveToIndicator = SpawnMoveToIndicator(HitResult.Location);
		}
	}
	
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