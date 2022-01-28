// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Scene/AoS_InteractableComponent.h"
#include "Characters/AoS_Nick.h"
#include "Controllers/AoS_PlayerController.h"

UAoS_InteractableComponent::UAoS_InteractableComponent()
{
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UAoS_InteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UAoS_InteractableComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UAoS_InteractableComponent::OnEndOverlap);
}

void UAoS_InteractableComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAoS_Nick* PlayerCharacter = Cast<AAoS_Nick>(OtherActor);
	AAoS_PlayerController* PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerCharacter && PlayerController)
	{
		OnPlayerBeginOverlap.Broadcast(PlayerCharacter);
		PlayerController->AddToInteractableActors(GetOwner());
	}
}

void UAoS_InteractableComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AAoS_Nick* PlayerCharacter = Cast<AAoS_Nick>(OtherActor);
	AAoS_PlayerController* PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());	AActor* AttachedActor = GetOwner();
	if (PlayerCharacter)
	{
		OnPlayerEndOverlap.Broadcast(PlayerCharacter);
		PlayerController->RemoveFromInteractableActors(GetOwner());
	}
}


// Called every frame
void UAoS_InteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}