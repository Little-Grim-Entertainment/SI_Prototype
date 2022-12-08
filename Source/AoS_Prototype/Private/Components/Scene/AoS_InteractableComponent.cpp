// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Scene/AoS_InteractableComponent.h"

#include "Characters/AoS_Nick.h"
#include "Components/WidgetComponent.h"
#include "Interfaces/AoS_InteractInterface.h"
#include "Controllers/AoS_PlayerController.h"
#include "UI/AoS_InteractionIcon.h"
#include "UI/AoS_InteractionPrompt.h"
#include "UI/AoS_UIManager.h"

UAoS_InteractableComponent::UAoS_InteractableComponent()
{
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UAoS_InteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InteractableOwner = Cast<IAoS_InteractInterface>(GetOwner());
	if (InteractableOwner)
	{
		InteractionIcon = InteractableOwner->Execute_GetInteractionIconComponent(Cast<UObject>(GetOwner()));
		InteractionPrompt = InteractableOwner->Execute_GetInteractionPromptComponent(Cast<UObject>(GetOwner()));
	}
	
	OnComponentBeginOverlap.AddDynamic(this, &UAoS_InteractableComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UAoS_InteractableComponent::OnEndOverlap);
}

void UAoS_InteractableComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner()) {return;}
	PlayerCharacter = Cast<AAoS_Nick>(OtherActor);
	PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerCharacter && PlayerController && bIsInteractable)
	{
		PlayerController->SetInteractableActor(GetOwner());
		OnPlayerBeginOverlap.Broadcast(PlayerCharacter);
	}
}

void UAoS_InteractableComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PlayerCharacter)
	{
		UAoS_UIManager* UIManager = Cast<UAoS_UIManager>(GetWorld()->GetGameInstance()->GetSubsystem<UAoS_UIManager>());
		if (IsValid(UIManager))
		{
			UAoS_InteractionWidget* InteractableWidget = Cast<UAoS_InteractionWidget>(InteractionPrompt->GetWidget());
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
void UAoS_InteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAoS_InteractableComponent::SetIsInteractable(bool bInteractable)
{
	bIsInteractable = bInteractable;
}

void UAoS_InteractableComponent::ShowInteractionPromptWidget()
{
	if (!IsValid(InteractionPrompt)) {return;}
	
	UAoS_InteractionPrompt* InteractionPromptWidget = GetInteractionPromptWidget();
	if (IsValid(InteractionPromptWidget))
	{
		InteractionPromptWidget->SetInteractText(GetInteractionText());
		InteractionPromptWidget->ShowWidget();
	}
}

void UAoS_InteractableComponent::RefreshInteractionPromptWidget(float InShowDelay)
{
	if (!IsValid(InteractionPrompt)) {return;}
	
	const UAoS_InteractionPrompt* InteractionPromptWidget = GetInteractionPromptWidget();
	if (IsValid(InteractionPromptWidget))
	{
		HideInteractionPromptWidget();
		GetWorld()->GetTimerManager().SetTimer(RefreshDelayHandle, this, &ThisClass::ShowInteractionPromptWidget, InShowDelay, false);
	}
}

void UAoS_InteractableComponent::HideInteractionPromptWidget()
{
	if (!IsValid(InteractionPrompt)) {return;}
	
	UAoS_InteractionPrompt* InteractionPromptWidget = GetInteractionPromptWidget();
	if (IsValid(InteractionPromptWidget))
	{
		InteractionPromptWidget->HideWidget();
	}
}

void UAoS_InteractableComponent::ShowInteractionIconWidget()
{
	if (!IsValid(InteractionIcon)) {return;}
	
	UAoS_InteractionIcon* InteractionIconWidget = GetInteractionIconWidget();
	if (IsValid(InteractionIconWidget))
	{
		InteractionIconWidget->ShowWidget();
	}
}

void UAoS_InteractableComponent::RefreshInteractionIconWidget(float InShowDelay)
{
	if (!IsValid(InteractionIcon)) {return;}
	
	const UAoS_InteractionIcon* InteractionIconWidget = GetInteractionIconWidget();
	if (IsValid(InteractionIconWidget))
	{
		HideInteractionIconWidget();
		GetWorld()->GetTimerManager().SetTimer(RefreshDelayHandle, this, &ThisClass::ShowInteractionIconWidget, InShowDelay, false);
	}
}

void UAoS_InteractableComponent::HideInteractionIconWidget()
{
	if (!IsValid(InteractionIcon)) {return;}
	
	UAoS_InteractionIcon* InteractionIconWidget = GetInteractionIconWidget();
	if (IsValid(InteractionIconWidget))
	{
		InteractionIconWidget->HideWidget();
	}
}

UAoS_InteractionPrompt* UAoS_InteractableComponent::GetInteractionPromptWidget() const
{
	return Cast<UAoS_InteractionPrompt>(InteractionPrompt->GetWidget());
}

UAoS_InteractionIcon* UAoS_InteractableComponent::GetInteractionIconWidget() const
{
	return Cast<UAoS_InteractionIcon>(InteractionIcon->GetWidget());
}
