// Fill out your copyright notice in the Description page of Project Settings.


#include "Cameras/SI_PlayerCameraManager.h"

#include "ATPCCameraComponent.h"
#include "SI_GameInstance.h"
#include "Characters/SI_Nick.h"
#include "GameplayTags/SI_GameplayTagManager.h"

void ASI_PlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	
	if(Cast<USI_GameplayTagManager>(this) || !IsValid(GameInstance)) {return;}

	SITagManager = GameInstance->GetSubsystem<USI_GameplayTagManager>();
	if (!IsValid(SITagManager)) {return;}

	SITagManager->OnTagAdded().AddUObject(this, &ThisClass::OnGameplayTagAdded);
	SITagManager->OnTagRemoved().AddUObject(this, &ThisClass::OnGameplayTagRemoved);
}

void ASI_PlayerCameraManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload)
{
	if(!SITagManager->HasParentTag(InAddedTag, SITag_Camera)){return;}

	ASI_Nick* Nick = Cast<ASI_Nick>(GetOwningPlayerController()->GetPawn());
	 if(!IsValid(Nick)) {return;}
	
	Nick->GetATPCCamera()->SetCameraMode(InAddedTag, false, false);	
}

void ASI_PlayerCameraManager::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag, FSITagPayload* InTagPayload)
{
	
}

