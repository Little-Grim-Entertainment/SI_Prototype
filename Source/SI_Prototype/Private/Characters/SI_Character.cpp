// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_Character.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


#include "Characters/SI_CharacterManager.h"


// Sets default values
ASI_Character::ASI_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}
	

USI_CharacterData* ASI_Character::GetCharacterData() const
{
	return CharacterData;
}
// Called when the game starts or when spawned
void ASI_Character::BeginPlay()
{
	Super::BeginPlay();

	//Does character have something picked up?
	if(bIsHoldingItem)
	{
		// Move object to Grab location and change its linear dampening
		HeldItemPosition();
	}		
}

void ASI_Character::HeldItemPosition()
{
	//If Rigid body goes to sleep it wont move with Gizbo so if it goes to sleep wake it up again.
	if(!ObjectBeingCarried->RigidBodyIsAwake())
	{
		ObjectBeingCarried->WakeRigidBody();
	}
	PhysicsHandle->SetTargetLocationAndRotation(GetActorLocation() + (GetViewRotation().Vector() * CarryOffset) , CarriedObjectRotation);
}
