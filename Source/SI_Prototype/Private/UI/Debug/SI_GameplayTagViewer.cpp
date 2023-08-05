// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Debug/SI_GameplayTagViewer.h"

#include "SI_GameplayTagManager.h"
#include "SI_GameplayTagTypes.h"
#include "Components/PanelWidget.h"
#include "UI/GameplayTags/LGGameplayTagCategoryWidget.h"
#include "UI/GameplayTags/LGGameplayTagEntryWidget.h"
#include "SI_NativeGameplayTagLibrary.h"

USI_GameplayTagViewer::USI_GameplayTagViewer()
{
	bCategoriesInitialized = false;
}

void USI_GameplayTagViewer::InitializeTagCategories()
{
	Super::InitializeTagCategories();

	SITagManager = GetGameInstance()->GetSubsystem<USI_GameplayTagManager>();
	if(!IsValid(SITagManager)) {return;}

	CameraTags = CreateTagCategory("Camera Tags");
	if(!IsValid(CameraTags)) {return;}
	
	DebugTags = CreateTagCategory("Debug Tags");
	if(!IsValid(CameraTags)) {return;}
	
	GadgetTags = CreateTagCategory("Gadget Tags");
	if(!IsValid(CameraTags)) {return;}
	
	GameStateTags = CreateTagCategory("GameState Tags");
	if(!IsValid(CameraTags)) {return;}
	
	LevelTags = CreateTagCategory("Level Tags");
	if(!IsValid(CameraTags)) {return;}
	
	MediaTags = CreateTagCategory("Media Tags");
	if(!IsValid(CameraTags)) {return;}
	
	MusicTags = CreateTagCategory("Music Tags");
	if(!IsValid(CameraTags)) {return;}
	
	PlayerStateTags = CreateTagCategory("PlayerState Tags");
	if(!IsValid(CameraTags)) {return;}
	
	UITags = CreateTagCategory("UI Tags");
	if(!IsValid(CameraTags)) {return;}
	
	bCategoriesInitialized = true;
	
	UpdateTagEntries();
}

void USI_GameplayTagViewer::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(bCategoriesInitialized)
	{
		UpdateTagEntries();
	}
}

void USI_GameplayTagViewer::UpdateTagEntries()
{
	if(!IsValid(SITagManager)) {return;}
	
	GenerateEntriesFromTagContainer(CameraTags, SITagManager->GetContainerTypeByTag(SITag_Camera));
	GenerateEntriesFromTagContainer(DebugTags, SITagManager->GetContainerTypeByTag(SITag_Debug));
	GenerateEntriesFromTagContainer(GadgetTags, SITagManager->GetContainerTypeByTag(SITag_Gadget));
	GenerateEntriesFromTagContainer(GameStateTags, SITagManager->GetContainerTypeByTag(SITag_Game_State));
	GenerateEntriesFromTagContainer(LevelTags, SITagManager->GetContainerTypeByTag(SITag_Map));
	GenerateEntriesFromTagContainer(MediaTags, SITagManager->GetContainerTypeByTag(SITag_Media));
	GenerateEntriesFromTagContainer(MusicTags, SITagManager->GetContainerTypeByTag(SITag_Audio_Music));
	GenerateEntriesFromTagContainer(PlayerStateTags, SITagManager->GetContainerTypeByTag(SITag_Player_State));
	GenerateEntriesFromTagContainer(UITags, SITagManager->GetContainerTypeByTag(SITag_UI));

	UpdateCategoriesVisibility();
}
