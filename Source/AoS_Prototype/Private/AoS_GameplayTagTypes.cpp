// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_GameplayTagTypes.h"

void FAoS_GameplayTagContainer::SetParentTag(const FGameplayTag& InParentTag)
{
	ParentTag = InParentTag;
}

const FGameplayTag& FAoS_GameplayTagContainer::GetParentTag() const
{
	return ParentTag;
}
