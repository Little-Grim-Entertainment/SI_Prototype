// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SI_InteractableActor.h"
#include "Components/Scene/SI_InteractableComponent.h"
#include "Characters/SI_Nick.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/SI_InteractionIcon.h"
#include "UI/SI_InteractionPrompt.h"

// Sets default values
ASI_InteractableActor::ASI_InteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	
	HighlightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HighlightMesh"));
	HighlightMesh->SetupAttachment(RootComponent);
	HighlightMesh->SetVisibility(false);
	
	InteractableComponent = CreateDefaultSubobject<USI_InteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(RootComponent);
	
	InteractionIcon = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionIcon"));
	InteractionIcon->SetupAttachment(RootComponent);
	
	InteractionPrompt = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionPrompt"));
	InteractionPrompt->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASI_InteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(InteractionPrompt))
	{
		USI_InteractionPrompt* InteractionPromptWidget = Cast<USI_InteractionPrompt>(InteractionPrompt->GetWidget());
		if (IsValid(InteractionPromptWidget))
		{
			InteractionPromptWidget->SetInteractText(InteractableComponent->GetInteractionText());
		}
	}
	if (IsValid(InteractableComponent))
	{
		InteractableComponent->OnPlayerBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
		InteractableComponent->OnPlayerEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);	
	}
}

// Called every frame
void ASI_InteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASI_InteractableActor::OnBeginOverlap(ASI_Nick* InNickActor)
{
	if (!IsValid(InteractableComponent)) {return;}
	InteractableComponent->ShowInteractionPromptWidget();
}

void ASI_InteractableActor::OnEndOverlap(ASI_Nick* InNickActor)
{
	if (!IsValid(InteractableComponent)) {return;}
	InteractableComponent->HideInteractionPromptWidget();
}

UWidgetComponent* ASI_InteractableActor::GetInteractionIconComponent_Implementation()
{
	return InteractionIcon;
}

UWidgetComponent* ASI_InteractableActor::GetInteractionPromptComponent_Implementation()
{
	return InteractionPrompt;
}
