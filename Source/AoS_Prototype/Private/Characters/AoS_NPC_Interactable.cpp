// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AoS_NPC_Interactable.h"
#include "Components/Scene/AoS_InteractableComponent.h"
#include "Controllers/AoS_NPCController_Interactable.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"



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
}


void AAoS_NPC_Interactable::BeginPlay()
{
	Super::BeginPlay();

	SetAIDialogueTree();
}

void AAoS_NPC_Interactable::SetAIDialogueTree()
{
	AIController = Cast<AAoS_NPCController_Interactable>(GetController());
	if (AIController)
	{
		if (DialogueTree)
		{
			AIController->SetDialogueTree(DialogueTree);
		}
	}
}

void AAoS_NPC_Interactable::StartDialogue()
{
	if (AIController)
	{
		AIController->StartDialogue();
	}
}

void AAoS_NPC_Interactable::EndtDialogue()
{
	if (AIController)
	{
		AIController->EndDialogue();
	}
}
