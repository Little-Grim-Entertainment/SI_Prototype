// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Scene/SI_InteractableComponent.h"

#include "Characters/SI_Nick.h"
#include "Components/WidgetComponent.h"
#include "Interfaces/SI_InteractInterface.h"
#include "Controllers/SI_PlayerController.h"
#include "UI/SI_InteractionIcon.h"
#include "UI/SI_InteractionPrompt.h"
#include "UI/SI_UIManager.h"

USI_InteractableComponent::USI_InteractableComponent()
{
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void USI_InteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InteractableOwner = Cast<ISI_InteractInterface>(GetOwner());
	if (InteractableOwner)
	{
		InteractionIcon = InteractableOwner->Execute_GetInteractionIconComponent(Cast<UObject>(GetOwner()));
		InteractionPrompt = InteractableOwner->Execute_GetInteractionPromptComponent(Cast<UObject>(GetOwner()));
	}
	
	OnComponentBeginOverlap.AddDynamic(this, &USI_InteractableComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &USI_InteractableComponent::OnEndOverlap);
}

void USI_InteractableComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner()) {return;}
	PlayerCharacter = Cast<ASI_Nick>(OtherActor);
	PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerCharacter && PlayerController && bIsInteractable)
	{
		PlayerController->SetInteractableActor(GetOwner());
		OnPlayerBeginOverlap.Broadcast(PlayerCharacter);
	}
}

void USI_InteractableComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PlayerCharacter)
	{
		USI_UIManager* UIManager = Cast<USI_UIManager>(GetWorld()->GetGameInstance()->GetSubsystem<USI_UIManager>());
		if (IsValid(UIManager))
		{
			USI_InteractionWidget* InteractableWidget = Cast<USI_InteractionWidget>(InteractionPrompt->GetWidget());
			if (IsValid(InteractableWidget))
			{
				UIManager->RemoveActiveInteractionWidget(InteractableWidget);
			}
		}
		PlayerController->SetInteractableActor(nullptr);
		OnPlayerEndOverlap.Broadcast(PlayerCharacter);
		PlayerCharacter = nullptr;
		PlayerController = nullptr;
	}
}


// Called every frame
void USI_InteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USI_InteractableComponent::SetIsInteractable(bool bInteractable)
{
	bIsInteractable = bInteractable;
}

void USI_InteractableComponent::ShowInteractionPromptWidget()
{
	if (!IsValid(InteractionPrompt)) {return;}
	
	USI_InteractionPrompt* InteractionPromptWidget = GetInteractionPromptWidget();
	if (IsValid(InteractionPromptWidget))
	{
		InteractionPromptWidget->SetInteractText(GetInteractionText());
		InteractionPromptWidget->ShowWidget();
	}
}

void USI_InteractableComponent::RefreshInteractionPromptWidget(float InShowDelay)
{
	if (!IsValid(InteractionPrompt)) {return;}
	
	const USI_InteractionPrompt* InteractionPromptWidget = GetInteractionPromptWidget();
	if (IsValid(InteractionPromptWidget))
	{
		HideInteractionPromptWidget();
		GetWorld()->GetTimerManager().SetTimer(RefreshDelayHandle, this, &ThisClass::ShowInteractionPromptWidget, InShowDelay, false);
	}
}

void USI_InteractableComponent::HideInteractionPromptWidget()
{
	if (!IsValid(InteractionPrompt)) {return;}
	
	USI_InteractionPrompt* InteractionPromptWidget = GetInteractionPromptWidget();
	if (IsValid(InteractionPromptWidget))
	{
		InteractionPromptWidget->HideWidget();
	}
}

void USI_InteractableComponent::ShowInteractionIconWidget()
{
	if (!IsValid(InteractionIcon)) {return;}
	
	USI_InteractionIcon* InteractionIconWidget = GetInteractionIconWidget();
	if (IsValid(InteractionIconWidget))
	{
		InteractionIconWidget->ShowWidget();
	}
}

void USI_InteractableComponent::RefreshInteractionIconWidget(float InShowDelay)
{
	if (!IsValid(InteractionIcon)) {return;}
	
	const USI_InteractionIcon* InteractionIconWidget = GetInteractionIconWidget();
	if (IsValid(InteractionIconWidget))
	{
		HideInteractionIconWidget();
		GetWorld()->GetTimerManager().SetTimer(RefreshDelayHandle, this, &ThisClass::ShowInteractionIconWidget, InShowDelay, false);
	}
}

void USI_InteractableComponent::HideInteractionIconWidget()
{
	if (!IsValid(InteractionIcon)) {return;}
	
	USI_InteractionIcon* InteractionIconWidget = GetInteractionIconWidget();
	if (IsValid(InteractionIconWidget))
	{
		InteractionIconWidget->HideWidget();
	}
}

USI_InteractionPrompt* USI_InteractableComponent::GetInteractionPromptWidget() const
{
	return Cast<USI_InteractionPrompt>(InteractionPrompt->GetWidget());
}

USI_InteractionIcon* USI_InteractableComponent::GetInteractionIconWidget() const
{
	return Cast<USI_InteractionIcon>(InteractionIcon->GetWidget());
}
