// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AoS_InteractableActor.h"
#include "Components/Scene/AoS_InteractableComponent.h"
#include "Characters/AoS_Nick.h"
#include "Components/WidgetComponent.h"
#include "UI/AoS_InteractionIcon.h"
#include "UI/AoS_InteractionPrompt.h"

// Sets default values
AAoS_InteractableActor::AAoS_InteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	
	InteractableComponent = CreateDefaultSubobject<UAoS_InteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(RootComponent);
	
	InteractionIcon = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionIcon"));
	InteractionIcon->SetupAttachment(RootComponent);
	
	InteractionPrompt = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionPrompt"));
	InteractionPrompt->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAoS_InteractableActor::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(InteractionPrompt))
	{
		UAoS_InteractionPrompt* InteractionPromptWidget = Cast<UAoS_InteractionPrompt>(InteractionPrompt->GetWidget());
		if (IsValid(InteractionPromptWidget))
		{
			InteractionPromptWidget->SetInteractText(InteractableComponent->GetInteractionText());
		}
	}

	InteractableComponent->OnPlayerBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	InteractableComponent->OnPlayerEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
}


// Called every frame
void AAoS_InteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAoS_InteractableActor::OnBeginOverlap(AAoS_Nick* InNickActor)
{
	if (IsValid(InteractionPrompt))
	{
		UAoS_InteractionPrompt* InteractionPromptWidget = GetInteractionPromptWidget();
		if (IsValid(InteractionPromptWidget))
		{
			InteractionPromptWidget->SetInteractText(InteractableComponent->GetInteractionText());
			InteractionPromptWidget->ShowWidget();
		}
	}
}

void AAoS_InteractableActor::OnEndOverlap(AAoS_Nick* InNickActor)
{
	if (IsValid(InteractionPrompt))
	{
		UAoS_InteractionPrompt* InteractionPromptWidget = GetInteractionPromptWidget();
		if (IsValid(InteractionPromptWidget))
		{
			InteractionPromptWidget->HideWidget();
		}
	}
}


void AAoS_InteractableActor::ShowInteractionPromptWidget()
{
	GetInteractionPromptWidget()->ShowWidget();
}

void AAoS_InteractableActor::RefreshInteractionPromptWidget()
{
	GetInteractionPromptWidget()->RefreshWidget();
}

void AAoS_InteractableActor::HideInteractionPromptWidget()
{
	GetInteractionPromptWidget()->HideWidget();
}

void AAoS_InteractableActor::ShowInteractionIconWidget()
{
	GetInteractionIconWidget()->ShowWidget();
}

void AAoS_InteractableActor::RefreshInteractionIconWidget()
{
	GetInteractionIconWidget()->RefreshWidget();
}

void AAoS_InteractableActor::HideInteractionIconWidget()
{
	GetInteractionIconWidget()->HideWidget();
}

UAoS_InteractionPrompt* AAoS_InteractableActor::GetInteractionPromptWidget() const
{
	return Cast<UAoS_InteractionPrompt>(InteractionPrompt->GetWidget());
}

UAoS_InteractionIcon* AAoS_InteractableActor::GetInteractionIconWidget() const
{
	return Cast<UAoS_InteractionIcon>(InteractionIcon->GetWidget());
}
