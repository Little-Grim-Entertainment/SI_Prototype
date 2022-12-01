// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AoS_NPC_Interactable.h"
#include "Components/Scene/AoS_InteractableComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "UI/AoS_InteractionPrompt.h"

AAoS_NPC_Interactable::AAoS_NPC_Interactable()
{
	InteractableComponent = CreateDefaultSubobject<UAoS_InteractableComponent>(TEXT("InteractableComponent"));
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


void AAoS_NPC_Interactable::BeginPlay()
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
	if (IsValid(InteractableComponent))
	{
		InteractableComponent->OnPlayerBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
		InteractableComponent->OnPlayerEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);	
	}
}

void AAoS_NPC_Interactable::OnBeginOverlap(AAoS_Nick* InNickActor)
{
	if (!IsValid(InteractableComponent)) {return;}
	InteractableComponent->ShowInteractionPromptWidget();
}

void AAoS_NPC_Interactable::OnEndOverlap(AAoS_Nick* InNickActor)
{
	if (!IsValid(InteractableComponent)) {return;}
	InteractableComponent->HideInteractionPromptWidget();
}

UWidgetComponent* AAoS_NPC_Interactable::GetInteractionIconComponent_Implementation()
{
	return InteractionIcon;
}

UWidgetComponent* AAoS_NPC_Interactable::GetInteractionPromptComponent_Implementation()
{
	return InteractionPrompt;
}

