// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_Gizbo.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"
#include "Actors/SI_InteractableActor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

using namespace SI_NativeGameplayTagLibrary;

ASI_Gizbo::ASI_Gizbo()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	AbilitySystemComponent = CreateDefaultSubobject<USI_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	
	//Picked up object Dampening;
	AdjustedDampening = 1000.0f;

	//Furthest distance gizbo can be from object and Interact
	InteractDistance = 75.0f;
	
	// Distance item is held in front of character
	CarryOffset = 75.0f;	
}

// Called every frame
void ASI_Gizbo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Does character have something picked up?
	if(bIsHoldingItem)
	{
		// Move object to Grab location and change its linear dampening
		// HeldItemPosition();
	}	
}

UAbilitySystemComponent* ASI_Gizbo::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASI_Gizbo::ConstructGadget(FGameplayTag InGadgetTag, APawn* InPawnRequestingGadget)
{
	
}

USI_AbilitySystemComponent* ASI_Gizbo::GetSIAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASI_Gizbo::BeginPlay()
{
	Super::BeginPlay();

	GiveAbilities();
}

void ASI_Gizbo::GiveAbilities()
{
	if (!IsValid(AbilitySystemComponent)) {return;}

	for (TSubclassOf<USI_GameplayAbility>& Ability : DefaultAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
	}
}

void ASI_Gizbo::HeldItemPosition()
{
	//If Rigid body goes to sleep it wont move with Gizbo so if it goes to sleep wake it up again.
	if(!ObjectBeingCarried->RigidBodyIsAwake())
	{
		ObjectBeingCarried->WakeRigidBody();
	}
	PhysicsHandle->SetTargetLocationAndRotation(GetActorLocation() + (GetViewRotation().Vector() * CarryOffset) , CarriedObjectRotation);
}

void ASI_Gizbo::PickupItem(AActor* InHitActor)
{
		HeldActor = InHitActor;
		USkeletalMeshComponent* GizboMesh = GetMesh();
		FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
		HeldActor->AttachToComponent(GizboMesh, AttachRules, PickupSocket);
		bIsHoldingItem = true;
}

void ASI_Gizbo::DropItem()
{
	HeldActor->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	bIsHoldingItem = false;
}

void ASI_Gizbo::LocatePickupItem()
{
	//Are our hands empty	
	if(!bIsHoldingItem)
	{
		// Collects all Actors hit with Sweep
		TArray<FHitResult> Hits; 
		//Trace starting point
		FVector StartLocation = GetActorLocation();
		//Trace ending point
		FVector EndLocation = (GetActorForwardVector() * InteractDistance) + StartLocation;
		//Trace Collision channels
		ECollisionChannel CollisionChannel = ECC_GameTraceChannel4;
		// Check for collisions based on CollisionChannel
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);
		// Sets shape and size for the end of the trace is used to make easier interaction and not needing pinpoint accuracy for smaller objects
		FCollisionShape Shape;
		Shape.SetSphere(InteractDistance * 2);
		
		//LineTrace to detect object
		bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, StartLocation, EndLocation, FQuat::Identity, ObjectQueryParams, Shape );

		//Debug Draw
	//	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	//	DrawDebugLine(GetWorld(), StartLocation, EndLocation, LineColor, false, 2.0f, 0, 0.0f);
	//	DrawDebugSphere(GetWorld(), EndLocation, InteractDistance, 32, LineColor, false, 2.0f);
		
		for (FHitResult Hit : Hits)
		{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Gizbo: Located %s"), *Hit.GetActor()->GetName()));
			
			if(Hit.GetActor()->Implements<USI_InteractInterface>() && Hit.GetActor() != this)
			{
				PickupItem(Hit.GetActor());
					return;
			}
		}
	}
}