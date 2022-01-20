// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Scene/AoS_Interactable.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Characters/AoS_Nick.h"

// Sets default values for this component's properties
UAoS_Interactable::UAoS_Interactable()
{
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(GetAttachmentRoot());
	InteractionTypeIcon = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionTypeIcon"));
	InteractionTypeIcon->SetupAttachment(GetAttachmentRoot());
	
	// off to improve performance if you don't need them.
	InteractionTypeIcon->SetVisibility(false);
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAoS_Interactable::BeginPlay()
{
	Super::BeginPlay();
	
	if (OverlapBox)
	{
		OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &UAoS_Interactable::OnComponentBeginOverlap);
		OverlapBox->OnComponentEndOverlap.AddDynamic(this, &UAoS_Interactable::OnComponentEndOverlap);
	}

}

void UAoS_Interactable::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAoS_Nick* PlayerCharacter = Cast<AAoS_Nick>(OtherActor);
	AActor* AttachedActor = GetOwner();
	if (PlayerCharacter)
	{
		OnPlayerBeginOverlap.Broadcast(PlayerCharacter);
		PlayerCharacter->AddToInteractableActors(AttachedActor);
	}
}

void UAoS_Interactable::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AAoS_Nick* PlayerCharacter = Cast<AAoS_Nick>(OtherActor);
	AActor* AttachedActor = GetOwner();
	if (PlayerCharacter)
	{
		OnPlayerEndOverlap.Broadcast(PlayerCharacter);
		PlayerCharacter->RemoveFromInteractableActors(AttachedActor);
	}
}


// Called every frame
void UAoS_Interactable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}




