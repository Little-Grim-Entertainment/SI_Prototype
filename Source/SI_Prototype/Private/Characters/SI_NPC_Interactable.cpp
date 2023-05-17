// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_NPC_Interactable.h"
#include "Components/Scene/SI_InteractableComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "UI/SI_InteractionPrompt.h"

ASI_NPC_Interactable::ASI_NPC_Interactable()
{
	InteractableComponent = CreateDefaultSubobject<USI_InteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractionIcon = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionIcon"));
	InteractionIcon->SetupAttachment(RootComponent);
	InteractionPrompt = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionPrompt"));
	InteractionPrompt->SetupAttachment(RootComponent);
	NPC_Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("NPC Cam"));
	NPC_Cam->SetupAttachment(RootComponent);
	NickCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Nick Cam"));
	NickCam->SetupAttachment(RootComponent);
	NickPosition = CreateDefaultSubobject<USceneComponent>(TEXT("NickPosition"));
	NickPosition->SetupAttachment(RootComponent);
	
}


void ASI_NPC_Interactable::BeginPlay()
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

void ASI_NPC_Interactable::OnBeginOverlap(ASI_Nick* InNickActor)
{
	if (!IsValid(InteractableComponent)) {return;}
	InteractableComponent->ShowInteractionPromptWidget();
}

void ASI_NPC_Interactable::OnEndOverlap(ASI_Nick* InNickActor)
{
	if (!IsValid(InteractableComponent)) {return;}
	InteractableComponent->HideInteractionPromptWidget();
}

void ASI_NPC_Interactable::OnInteract_Implementation(AActor* Caller)
{
	ISI_InteractInterface::OnInteract_Implementation(Caller);

	if (IsValid(InteractionPrompt))
	{
		USI_InteractionPrompt* InteractionPromptWidget = Cast<USI_InteractionPrompt>(InteractionPrompt->GetWidget());
		if (IsValid(InteractionPromptWidget))
		{
			InteractionPromptWidget->HideWidget();
		}
	}
}

void ASI_NPC_Interactable::OnInteractEnd_Implementation(AActor* Caller)
{
	ISI_InteractInterface::OnInteractEnd_Implementation(Caller);
	
	if (IsValid(InteractionPrompt))
	{
		USI_InteractionPrompt* InteractionPromptWidget = Cast<USI_InteractionPrompt>(InteractionPrompt->GetWidget());
		if (IsValid(InteractionPromptWidget))
		{
			InteractionPromptWidget->ShowWidget();
		}
	}
}

UWidgetComponent* ASI_NPC_Interactable::GetInteractionIconComponent_Implementation()
{
	return InteractionIcon;
}

UWidgetComponent* ASI_NPC_Interactable::GetInteractionPromptComponent_Implementation()
{
	return InteractionPrompt;
}

