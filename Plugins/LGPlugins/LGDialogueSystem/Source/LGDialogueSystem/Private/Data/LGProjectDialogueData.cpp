// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/LGProjectDialogueData.h"
#include "Data/LGDialogueDataAsset.h"

void ULGProjectDialogueData::UpdateAllDialogue()
{
	for (const FLGCharacterDialogue& CurrentCharacterDialogue : CharacterDialogue)
	{
		ULGDialogueDataAsset* CurrentDialogueData = CurrentCharacterDialogue.CharacterDialogueData;
		
		if(!IsValid(CurrentDialogueData)){continue;}
		CurrentDialogueData->UpdateDialogue_Internal();
	}
}

#if WITH_EDITOR
void ULGProjectDialogueData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName MemberPropertyName = (PropertyChangedEvent.MemberProperty != nullptr) ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None;

	if (MemberPropertyName == GET_MEMBER_NAME_CHECKED(ULGProjectDialogueData, CharacterDialogue))
	{
		FArrayProperty* ArrayProperty = static_cast<FArrayProperty*>(PropertyChangedEvent.MemberProperty);
		if(!ArrayProperty) {return;}
		FObjectProperty* ObjectProperty = static_cast<FObjectProperty*>(PropertyChangedEvent.Property);
		if(!ObjectProperty) {return;}
		
		void* ArrayPtr = ArrayProperty->ContainerPtrToValuePtr<void>(this);
		TArray<FLGCharacterDialogue>* CharacterDialogueArray = static_cast<TArray<FLGCharacterDialogue>*>(ArrayPtr);
		if(!CharacterDialogueArray) {return;}
		
		for(FLGCharacterDialogue& CurrentCharacterDialogue : *CharacterDialogueArray)
		{
			UObject* ObjectPtr = ObjectProperty->GetObjectPropertyValue_InContainer(&CurrentCharacterDialogue);
			if(!IsValid(ObjectPtr)) {return;}

			ULGDialogueDataAsset* CurrentDialogueDataAsset = Cast<ULGDialogueDataAsset>(ObjectPtr);
			if(!IsValid(CurrentDialogueDataAsset)) {continue;}
			
			CurrentCharacterDialogue.CharacterTag = CurrentDialogueDataAsset->GetCharacterTag();
			return;
		}
	}
}
#endif
