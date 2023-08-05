// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_GizboManager.h"

#include "SI_GameInstance.h"
#include "Characters/SI_Character.h"
#include "Characters/SI_Gizbo.h"
#include "Controllers/SI_GizboController.h"
#include "Data/Characters/SI_CharacterData.h"
#include "GameFramework/PlayerStart.h"
#include "GameModes/SI_GameMode.h"
#include "SI_GameplayTagManager.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"

DEFINE_LOG_CATEGORY(LogSI_GizboManager);

void USI_GizboManager::SpawnGizbo()
{
	if (!GameInstance->GetGameMode()->GizboCDA)
		{UE_LOG(LogSI_GizboManager, Error, TEXT("GizboCDA is null unable to spawn gizbo!"));	return;}
	
	if (!GameInstance->GetGameMode()->GizboCDA->CharacterClass)
		{UE_LOG(LogSI_GizboManager, Error, TEXT("GizboCDA->CharacterClass is null unable to spawn gizbo!"));return;}

	if (GizboStartTag == "")
	{
		GizboStartTag = "Gizbo_DefaultSpawn";
	}
	
	if (const APlayerStart* GizboStart = GameInstance->GetGameMode()->GetPlayerStart(GizboStartTag))
	{
		FVector GizboLocation = FVector(GizboStart->GetActorLocation().X, GizboStart->GetActorLocation().Y, GizboStart->GetActorLocation().Z - 50);
		
		if (!GizboCharacter)
		{
			const FActorSpawnParameters PlayerSpawnParameters;
			GizboCharacter = GetWorld()->SpawnActor<ASI_Gizbo>(GameInstance->GetGameMode()->GizboCDA->CharacterClass, GizboLocation, GizboStart->GetActorRotation(), PlayerSpawnParameters);
		}
		else
		{
			GizboCharacter->SetActorLocation(GizboLocation);
			GizboCharacter->SetActorRotation(GizboStart->GetActorRotation());
		}
	}
	if(GizboCharacter)
	{
		GizboAbilitySystemComponent = GizboCharacter->GetSIAbilitySystemComponent();
	}
	
	if (GizboController)
	{
		GizboController->Possess(GizboCharacter);
		GizboController->Nick = Nick;
	}
		
	if (!GizboController && GizboCharacter)
	{
		GizboController = Cast<ASI_GizboController>(GizboCharacter->GetController());
	}
	
}

void USI_GizboManager::SetGizboStartTag(FString InStartTag)
{
	GizboStartTag = InStartTag;
}

ASI_Gizbo* USI_GizboManager::GetGizbo()
{
	return GizboCharacter;
}

ASI_GizboController* USI_GizboManager::GetGizboController()
{
	return GizboController;
}

void USI_GizboManager::ShowGizbo(bool bShouldHide)
{
	if (!IsValid(GizboCharacter))
		{UE_LOG(LogSI_GizboManager, Error, TEXT("GizboCharacter is null unable to show gizbo!")); return;}
	
	GizboCharacter->SetActorHiddenInGame(bShouldHide);
}

void USI_GizboManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();

	SpawnGizbo();
}

void USI_GizboManager::InitializeDelegates()
{
	Super::InitializeDelegates();
	
	SITagManager = GameInstance->GetSubsystem<USI_GameplayTagManager>();
	if (!IsValid(SITagManager)) {UE_LOG(LogSI_GizboManager, Error, TEXT("SITagManager is null unable to initialize delegates!")); return;}
	
	ActivateAbilityDelegate.BindUObject(this, &ThisClass::TryActivateAbilityByTag);
}

void USI_GizboManager::InitializeDelegateMaps()
{
	Super::InitializeDelegateMaps();

	GizboDelegateContainer.Add(SITag_Ability_Gizbo, ActivateAbilityDelegate);	
}

//Called from listener of GameplayTagManager OnTagAddedDelegate.Broadcast() in AddNewGameplayTag()
void USI_GizboManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
	if(!IsValid(GetWorld()))
		{UE_LOG(LogSI_GizboManager, Error, TEXT("World is null unable to add tag!")); return;}
	if(!SITagManager->HasParentTag(InAddedTag, SITag_Ability_Gizbo))
		{UE_LOG(LogSI_GizboManager, VeryVerbose, TEXT("Tag %s is not a child of SITag_Ability_Gizbo!"), *InAddedTag.ToString()); return;}
	
	Super::OnGameplayTagAdded(InAddedTag);	
	
	if (SITagManager->HasParentTag(InAddedTag, SITag_Ability_Gizbo))
	{
		CurrentAbilityTag = InAddedTag;
		GizboDelegateContainer.Find(SITag_Ability_Gizbo)->Execute();
		return;
	}
	
	GizboDelegateContainer.Find(InAddedTag)->Execute();
}

//Called from listener of GameplayTagManager OnTagRemovedDelegate.Broadcast() in RemoveTag()
void USI_GizboManager::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
	if(!IsValid(GetWorld()))
		{UE_LOG(LogSI_GizboManager, Error, TEXT("World is null unable to remove tag!")); return;}
	if(!SITagManager->HasParentTag(InRemovedTag, SITag_Ability_Gizbo))
		{UE_LOG(LogSI_GizboManager, VeryVerbose, TEXT("Tag %s is not a child of SITag_Ability_Gizbo!"), *InRemovedTag.ToString()); return;}
	
	Super::OnGameplayTagRemoved(InRemovedTag);

	if(SITagManager->HasParentTag(InRemovedTag, SITag_Ability_Gizbo))
	{
		CurrentAbilityTag = InRemovedTag;
		TryCancelAbilityByTag();
	}
}

void USI_GizboManager::TryActivateAbilityByTag()
{
	if(!IsValid(GizboAbilitySystemComponent))
	{
		GizboAbilitySystemComponent = GizboCharacter->GetSIAbilitySystemComponent();
	}

	USI_GameplayAbility* CurrentAbility = GizboAbilitySystemComponent->GetGameplayAbilityByTag(CurrentAbilityTag);

	if(!IsValid(CurrentAbility))
		{UE_LOG(LogSI_GizboManager, Error, TEXT("%s is null unable to activate ability!"), *CurrentAbility->GetName()); return;}
	
	if(GizboAbilitySystemComponent->TryActivateAbilitiesByTag(CurrentAbilityTag.GetSingleTagContainer(), false))
	{
		ActiveAbilitiesContainer.Add(CurrentAbilityTag, CurrentAbility);
	}
}

void USI_GizboManager::TryCancelAbilityByTag()
{	
	USI_GameplayAbility* CurrentAbility = GizboAbilitySystemComponent->GetGameplayAbilityByTag(CurrentAbilityTag);

	if(!IsValid(CurrentAbility))
		{UE_LOG(LogSI_GizboManager, Error, TEXT("%s is null unable to cancel ability!"), *CurrentAbility->GetName()); return;}
	
	if(!ActiveAbilitiesContainer.IsEmpty() && *ActiveAbilitiesContainer.Find(CurrentAbilityTag) == CurrentAbility)
	{
		GizboAbilitySystemComponent->CancelAbility(CurrentAbility);
	}
}