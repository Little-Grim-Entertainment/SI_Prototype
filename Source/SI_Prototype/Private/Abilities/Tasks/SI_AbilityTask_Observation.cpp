// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/SI_AbilityTask_Observation.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "Characters/SI_Nick.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"


using namespace SI_NativeGameplayTagLibrary;

USI_AbilityTask_Observation::USI_AbilityTask_Observation(const FObjectInitializer& ObjectInitializer)
{
	bTickingTask = true;
}

USI_AbilityTask_Observation* USI_AbilityTask_Observation::ObservationTask(UGameplayAbility* InOwningAbility)
{
	USI_AbilityTask_Observation* ObservationTask = NewAbilityTask<USI_AbilityTask_Observation>(InOwningAbility);

	ObservationTask->OwningAbility = InOwningAbility;
		
	return ObservationTask;
}

void USI_AbilityTask_Observation::Activate()
{
	Super::Activate();

	PlayerController = OwningAbility->GetOwningActorFromActorInfo()->GetInstigatorController<APlayerController>();
	if(!IsValid(PlayerController)) {LG_LOG(LogLG_Ability, Error, "PlayerController is not valid"); return; }
	Nick = Cast<ASI_Nick>(PlayerController->GetPawn());
	if(!IsValid(Nick)) {LG_LOG(LogLG_Ability, Error, "Nick is not valid"); return; }
}

void USI_AbilityTask_Observation::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	StartLineTrace();
}

void USI_AbilityTask_Observation::StartLineTrace()
{
	//line trace that ignores nick and only targets objects with the tag "SI_ObservationTarget"
	FHitResult HitResult;
	const FVector StartLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
	const FVector EndLocation = StartLocation + (PlayerController->PlayerCameraManager->GetCameraRotation().Vector() * 1000);
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);

	//if the line trace hits an object with the tag "SI_ObservationTarget" then set the observation target to that object
	if(HitResult.GetActor())
	{
		ASI_InteractableActor* IActor = Cast<ASI_InteractableActor>(HitResult.GetActor());
		if(IsValid(IActor) && IActor->AbilitySystemComponent->HasMatchingGameplayTag(SITag_Actor_Observable))
		{
			IActor->HighlightBeginTimer();

			if(Nick->GetCurrentInteractableActor() != IActor)
			{
				Nick->SetCurrentInteractableActor(IActor);
			}
		}
		else
		{
			Nick->SetCurrentInteractableActor(nullptr);
		}
	}
}

