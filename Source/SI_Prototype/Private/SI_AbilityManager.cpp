// Fill out your copyright notice in the Description page of Project Settings.


#include "SI_AbilityManager.h"
#include "LG_DebugMacros.h"
#include "GameplayTag/SI_GameplayTagManager.h"
#include "SI_PlayerManager.h"
#include "Abilities/SI_GameplayAbility.h"
#include "Characters/SI_GizboManager.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"

void USI_AbilityManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload)
{
	if(!SITagManager->HasParentTag(InAddedTag,SITag_Ability)) return;
	
	Super::OnGameplayTagAdded(InAddedTag);
		
	if(InAddedTag == SITag_Ability_Cancel || InAddedTag == SITag_Ability_Confirm || InAddedTag == SITag_Ability_HoldConfirm)
	{
		AddRemoveLooseAbilityTags(InAddedTag);
		return;
	}

	TryActivateAbilityByTag(InAddedTag, InTagPayload);
}

void USI_AbilityManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();
	
	if(!IsValid(PlayerManager)) {LG_LOG(LogLG_AbilityManager, Error, "PlayerManager is null unable to GetNickAbilitySystemComponent!") return;}

	NickAbilitySystemComponent = PlayerManager->GetNickAbilitySystemComponent();
}

void USI_AbilityManager::TryActivateAbilityByTag(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload)
{
	if(InTagPayload == nullptr)	{LG_LOG(LogLG_AbilityManager, Error, "InTagPayload is null unable to activate ability!") return;}
	
	USI_AbilitySystemComponent* CharacterAbilitySystemComponent = InTagPayload->Target->GetComponentByClass<USI_AbilitySystemComponent>();
	if(!IsValid(CharacterAbilitySystemComponent)) {LG_LOG(LogLG_AbilityManager, Error, "CharacterAbilitySystemComponent is null unable to activate ability!") return;}
	
	USI_GameplayAbility* CurrentAbility = CharacterAbilitySystemComponent->GetGameplayAbilityByTag(InAddedTag);
	if(!IsValid(CurrentAbility)) {LG_LOG(LogLG_AbilityManager, Error, "CurrentAbility is null unable to activate ability!"); return;}

	FGameplayEventData Payload;
	Payload.Target = *InTagPayload->Target;
	Payload.Instigator = *InTagPayload->Instigator;
	Payload.EventTag = InAddedTag;

	//HandleGameplayEvent returns 0 if the ability isn't set to be triggered via event
	//We want to use HandleGameplayEvent if we need to pass in a Payload
	if (CharacterAbilitySystemComponent->HandleGameplayEvent(InAddedTag, &Payload) == 0)
	{
		CharacterAbilitySystemComponent->TryActivateAbilitiesByTag(InAddedTag.GetSingleTagContainer(), false);
	}
}

void USI_AbilityManager::TryCancelAbilityByTag(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload)
{	
	USI_AbilitySystemComponent* CharacterAbilitySystemComponent = InTagPayload->Target->GetComponentByClass<USI_AbilitySystemComponent>();
	if(!IsValid(CharacterAbilitySystemComponent)) {LG_LOG(LogLG_AbilityManager, Error, "CharacterAbilitySystemComponent is null unable to cancel ability!") return;}
		
	USI_GameplayAbility* CurrentAbility = CharacterAbilitySystemComponent->GetGameplayAbilityByTag(InAddedTag);
	if(!IsValid(CurrentAbility)) {LG_LOG(LogLG_AbilityManager, Error, "CurrentAbility is null unable to activate ability!"); return;}

	CharacterAbilitySystemComponent->CancelAbility(CurrentAbility);
}

void USI_AbilityManager::AddRemoveLooseAbilityTags(const FGameplayTag& InAddedTag)
{
	if(!IsValid(NickAbilitySystemComponent))
	{
		NickAbilitySystemComponent = PlayerManager->GetNickAbilitySystemComponent();
		
		if(!IsValid(NickAbilitySystemComponent)) {LG_LOG(LogLG_AbilityManager, Error, "NickAbilitySystemComponent is null unable to activate ability!") return;}
	}
	
	NickAbilitySystemComponent->AddLooseGameplayTag(InAddedTag);
	NickAbilitySystemComponent->RemoveLooseGameplayTag(InAddedTag);
	LG_LOG(LogLG_AbilityManager, VeryVerbose, "%s was loose added and removed", *InAddedTag.ToString())
}

