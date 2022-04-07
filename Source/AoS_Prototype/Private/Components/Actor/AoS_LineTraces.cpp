// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actor/AoS_LineTraces.h"
#include "Controllers/AoS_PlayerController.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UAoS_LineTraces::UAoS_LineTraces()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bEnableInteractableSearch = false;
	bInteractableFound = false;
	// ...
}


// Called when the game starts
void UAoS_LineTraces::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AAoS_PlayerController>(GetOwner());
	if (PlayerController)
	{
		PlayerController->OnInteractableActorAdded.AddDynamic(this, &UAoS_LineTraces::UAoS_LineTraces::EnableInteractableSearch);
		PlayerController->OnInteractableActorRemoved.AddDynamic(this, &UAoS_LineTraces::UAoS_LineTraces::DisableInteractableSearch);
	}
}


// Called every frame
void UAoS_LineTraces::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bEnableInteractableSearch)
	{
		AActor* InteractableActor = SearchForInteractableActor();
		if (InteractableActor && !bInteractableFound)
		{
			PlayerController->SetFocusedActor(InteractableActor);
			bInteractableFound = true;
		}
		if (!InteractableActor && bInteractableFound)
		{
			PlayerController->SetFocusedActor(nullptr);
			bInteractableFound = false;
		}
	}
	else if (bInteractableFound)
	{
		PlayerController->SetFocusedActor(nullptr);
		bInteractableFound = false;
	}
}

// Interactable Actor Search

AActor* UAoS_LineTraces::SearchForInteractableActor()
{
	FVector SearchStart;
	FVector SearchEnd;
	FHitResult HitResults;
	TArray<AActor*> ActorsToIgnore;
	
	SetTraceVectors(SearchStart, SearchEnd, InteractableSearch.StartZOffset, InteractableSearch.EndZOffset, InteractableSearch.SearchDistance);
	if (PlayerController->CreateLineTrace(InteractableSearch.DrawDebugType, SearchStart, SearchEnd, InteractableSearch.TraceColor, InteractableSearch.TraceHitColor, HitResults))
	{
		for (int i = 0; i < InteractableActors.Num(); i++)
		{
			if (HitResults.GetActor() == InteractableActors[i])
			{
				return InteractableActors[i];
			}
		}	
	}
	return nullptr;
}

void UAoS_LineTraces::EnableInteractableSearch(TArray<AActor*> ActorsToSearchFor)
{
	if (ActorsToSearchFor.Num() == 0) {return;}
	InteractableActors.Empty();
	InteractableActors = ActorsToSearchFor;
	bEnableInteractableSearch = true;
}

void UAoS_LineTraces::DisableInteractableSearch()
{
	InteractableActors.Empty();
	bEnableInteractableSearch = false;
}

// Helper Functions

void UAoS_LineTraces::SetTraceVectors(FVector& StartVector, FVector& EndVector, const float StartZOffset, const float EndZOffset, const float SearchDistance)
{
	if (!PlayerController) {return;}
	FVector Loc;
	FRotator Rot;
	PlayerController->GetPlayerViewPoint(Loc, Rot);
	const FVector PlayerLocation = PlayerController->GetCharacter()->GetActorLocation();
		
	StartVector = FVector(PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z + StartZOffset);
	const FVector NoOffsetEndVector = StartVector + (Rot.Vector() * SearchDistance);
	EndVector = FVector(NoOffsetEndVector.X, NoOffsetEndVector.Y, NoOffsetEndVector.Z + EndZOffset);
}

