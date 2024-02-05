// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Interact.h"
#include "Controllers/SI_PlayerController.h"
#include "Interfaces/SI_InteractInterface.h"
#include "Actors/SI_InteractableActor.h"
#include "Characters/SI_Character.h"
#include "Characters/SI_Nick.h"


void USI_GameplayAbility_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                   const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	LG_LOG_LOG(LogLG_Ability," Ability Activated");
	
	TObjectPtr<ASI_Character> Character = Cast<ASI_Character>(ActorInfo->OwnerActor);

	LocateInteractable(Character);
	
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void USI_GameplayAbility_Interact::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USI_GameplayAbility_Interact::LocateInteractable(TObjectPtr<ASI_Character> InCharacter)
{
	if(!IsValid(InCharacter)) {LG_LOG_LOG(LogLG_Ability,"InActor is not valid"); return; }
	//Are our hands empty	
	if(InCharacter->bIsHoldingItem) {LG_LOG_LOG(LogLG_Ability,"InActor is holding an Item. Cannot Interact."); return;}

	// Collects all Actors hit with Sweep
	TArray<FHitResult> Hits; 
	//Trace starting point
	FVector StartLocation = InCharacter->GetActorLocation();
	//Trace ending point
	FVector EndLocation = (InCharacter->GetActorForwardVector() * InCharacter->InteractDistance) + StartLocation;
	//Trace Collision channels
	ECollisionChannel CollisionChannel = ECC_GameTraceChannel4;
	// Check for collisions based on CollisionChannel
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);
	// Sets shape and size for the end of the trace is used to make easier interaction and not needing pinpoint accuracy for smaller objects
	FCollisionShape Shape;
	Shape.SetSphere(InCharacter->InteractDistance * 2);
		
	//LineTrace to detect object
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, StartLocation, EndLocation, FQuat::Identity, ObjectQueryParams, Shape );

	//Debug Draw
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, LineColor, false, 2.0f, 0, 0.0f);
	DrawDebugSphere(GetWorld(), EndLocation, InCharacter->InteractDistance, 32, LineColor, false, 1.0f);
		
	for (FHitResult Hit : Hits)
	{
		
		if(Hit.GetActor()->Implements<USI_InteractInterface>())
		{
			ASI_InteractableActor* HitInteractable = Cast<ASI_InteractableActor>(Hit.GetActor());
			if(!IsValid(HitInteractable)) return;

			if(HitInteractable->InteractionTags.HasTagExact(SITag_Interaction_Pickup))
			{
				//PickupObject(HitInteractable);
				return;
			}
			if(HitInteractable->InteractionTags.HasTagExact(SITag_Interaction_Push) )
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Gizbo: Pushable Located %s"), *Hit.GetActor()->GetName()));
			}
		}
	}
}