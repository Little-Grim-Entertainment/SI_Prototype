// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_PossessMovable.h"

#include "Actors/SI_PossessedMovable.h"
#include "Cameras/SI_PlayerCameraManager.h"
#include "Characters/SI_Nick.h"
#include "Controllers/SI_PlayerController.h"
#include "GameplayTags/SI_GameplayTagManager.h"

void USI_GameplayAbility_PossessMovable::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	LG_LOG_LOG(LogLG_Ability," Ability Activated");
	
	Nick = Cast<ASI_Nick>(ActorInfo->OwnerActor);
	if(!IsValid(Nick)) return;
	PC = Cast<ASI_PlayerController>(Nick->GetController());
	if(!IsValid(PC)) return;
	SICameraManger = Cast<ASI_PlayerCameraManager>(PC->PlayerCameraManager);
	if(!IsValid(SICameraManger)) return;
	SITagManager = PC->GetSITagManager();
	if(!IsValid(SITagManager))	{return;}

	if(PossessTarget(ActorInfo, TriggerEventData))
	{
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_PossessMovable, SITag_Player_State);
		UpdateMoveToLocation();
	}

	// Get Object Selected
	// Spawn Camera w/ boom or Use Existing Camera & boom attached to Nick
	// Move Existing Camera Boom to selected object nia update location
	// or
	// Spawn new Camera w/ Boom 
	
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Orange,"Ability: PossessMovable");
}

void USI_GameplayAbility_PossessMovable::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Exploration, SITag_Player_State);
}

bool USI_GameplayAbility_PossessMovable::PossessTarget(const FGameplayAbilityActorInfo* InActorInfo, const FGameplayEventData* InTriggerEventData)
{
	PossessedMovable = SpawnPossessedMovable(InTriggerEventData->Target->GetActorLocation());
	if(!IsValid(PossessedMovable)) return false;
	
	PC->Possess(PossessedMovable);

	return true;
}

ASI_PossessedMovable* USI_GameplayAbility_PossessMovable::SpawnPossessedMovable(const FVector InHitLocation)
{
	PossessedMovableClass = GetPossessedMovableClass();
	if(PossessedMovableClass == nullptr)
	{
		PossessedMovableClass = GetPossessedMovableClass();
	}
	
	if(!IsValid(PossessedMovable))
	{
		FRotator Rotation = FRotator();
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		PossessedMovable = GetWorld()->SpawnActor<ASI_PossessedMovable>(PossessedMovableClass, InHitLocation, Rotation, SpawnParams);
		PossessedMovable->SetActiveMeshToDefault();
	}
	else
	{
		PossessedMovable->SetActorHiddenInGame(false);
		PossessedMovable->MeshComponent->SetWorldLocation(InHitLocation);
	}
	
	return PossessedMovable;
}

void USI_GameplayAbility_PossessMovable::UpdateMoveToLocation()
{	
	FVector TraceStart = SICameraManger->GetCameraLocation();
	FVector TraceEnd =  TraceStart + SICameraManger->GetActorForwardVector() * AdaptableActionMaximumRadius;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(SICameraManger);
	
	FHitResult OutHit;
	
	bool bBlockingHit = GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, ECC_WorldDynamic, QueryParams);
	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 30.0f, 0, 1.0f);

	if(bBlockingHit)
	{
		PossessedMovable = SpawnPossessedMovable(OutHit.Location);
		
		StartUpdateIndicatorPositionTimer();
	}	
}

void USI_GameplayAbility_PossessMovable::StartUpdateIndicatorPositionTimer()
{
	GetWorld()->GetTimerManager().SetTimer(GhostActorPositionTimerHandle, this, &ThisClass::UpdateMoveToLocation, UpdateIndicatorDelay, true);
}

void USI_GameplayAbility_PossessMovable::CancelUpdateIndicatorPositionTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(GhostActorPositionTimerHandle);
}