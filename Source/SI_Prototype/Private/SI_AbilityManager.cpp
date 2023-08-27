// Fill out your copyright notice in the Description page of Project Settings.


#include "SI_AbilityManager.h"

#include "LG_DebugMacros.h"
#include "SI_GameplayTagManager.h"
#include "SI_PlayerManager.h"
#include "Abilities/SI_GameplayAbility.h"
#include "Characters/SI_GizboManager.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"

DEFINE_LOG_CATEGORY(LogSI_AbilityManager)

void USI_AbilityManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
	if(!SITagManager->HasParentTag(InAddedTag,SITag_Ability)) return;
	
	Super::OnGameplayTagAdded(InAddedTag);
		
	if(InAddedTag == SITag_Ability_Cancel || InAddedTag == SITag_Ability_Confirm || InAddedTag == SITag_Ability_HoldConfirm)
	{
		AddRemoveLooseAbilityTags(InAddedTag);
		return;
	}

	TryActivateAbilityByTag(InAddedTag);
}

void USI_AbilityManager::TryActivateAbilityByTag(const FGameplayTag& InAddedTag)
{
	if(!IsValid(NickAbilitySystemComponent) || !IsValid(GizboAbilitySystemComponent))
	{
		GetAbilitySystemComponents();
	}
	
	if(!IsValid(NickAbilitySystemComponent))
		{LG_LOG(LogSI_AbilityManager, Error, "NickAbilitySystemComponent is null unable to activate ability!") return;}
	if(!IsValid(GizboAbilitySystemComponent))
		{LG_LOG(LogSI_AbilityManager, Error, "GizboAbilitySystemComponent is null unable to activate ability!") return;}
	
	if(SITagManager->HasParentTag(InAddedTag,SITag_Ability_Nick))
	{
		USI_GameplayAbility* CurrentAbility = NickAbilitySystemComponent->GetGameplayAbilityByTag(InAddedTag);
	
		if(!IsValid(CurrentAbility))
		{LG_LOG(LogSI_AbilityManager, Error, "%s is null unable to activate ability!", *CurrentAbility->GetName()); return;}

		LG_PRINT(10.f, Green, "Attempting to activate %s", *CurrentAbility->GetName());
		NickAbilitySystemComponent->TryActivateAbilitiesByTag(InAddedTag.GetSingleTagContainer(), false);
	}
	else if(SITagManager->HasParentTag(InAddedTag,SITag_Ability_Gizbo))
	{
		USI_GameplayAbility* CurrentAbility = GizboAbilitySystemComponent->GetGameplayAbilityByTag(InAddedTag);

		if(!IsValid(CurrentAbility))
		{LG_LOG(LogSI_AbilityManager, Error, "%s is null unable to activate ability!", *CurrentAbility->GetName()); return;}
	
		GizboAbilitySystemComponent->TryActivateAbilitiesByTag(InAddedTag.GetSingleTagContainer(), false);
	}
}

void USI_AbilityManager::TryCancelAbilityByTag(const FGameplayTag& InAddedTag)
{	
	USI_GameplayAbility* CurrentAbility = NickAbilitySystemComponent->GetGameplayAbilityByTag(InAddedTag);

	if(!IsValid(CurrentAbility))
		{LG_LOG( LogSI_AbilityManager, Error, "CurrentAbility is null unable to cancel ability!") return;}

	if(InAddedTag.RequestDirectParent() == SITag_Ability_Nick)
	{
		NickAbilitySystemComponent->CancelAbility(CurrentAbility);
	}
	else if(InAddedTag.RequestDirectParent() == SITag_Ability_Gizbo)
	{
		GizboAbilitySystemComponent->CancelAbility(CurrentAbility);
	}
}

void USI_AbilityManager::AddRemoveLooseAbilityTags(const FGameplayTag& InAddedTag)
{
	if(!IsValid(NickAbilitySystemComponent))
	{
		GetAbilitySystemComponents();
	}
		
	NickAbilitySystemComponent->AddLooseGameplayTag(InAddedTag);
	NickAbilitySystemComponent->RemoveLooseGameplayTag(InAddedTag);
	LG_LOG(LogSI_AbilityManager, Log, "%s was loose added and removed", *InAddedTag.ToString())
}

void USI_AbilityManager::GetAbilitySystemComponents()
{
	if(!IsValid(NickAbilitySystemComponent))
	{
		NickAbilitySystemComponent = PlayerManager->GetNickAbilitySystemComponent();
	}

	if(!IsValid(GizboAbilitySystemComponent))
	{
		USI_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GizboManager>();
		if(!IsValid(GizboManager)) {LG_LOG(LogSI_AbilityManager, Error, "GizboManager is invalid") return;}
		GizboAbilitySystemComponent = GizboManager->GetGizboASC();
	}
}

