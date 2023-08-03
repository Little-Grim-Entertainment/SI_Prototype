// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Debug/SI_GameplayTagViewer.h"

#include "SI_GameplayTagManager.h"
#include "SI_GameplayTagTypes.h"
#include "Components/PanelWidget.h"
#include "UI/GameplayTags/LGGameplayTagCategoryWidget.h"
#include "UI/GameplayTags/LGGameplayTagEntryWidget.h"
#include "SI_NativeGameplayTagLibrary.h"

void USI_GameplayTagViewer::InitializeTagCategories()
{
	Super::InitializeTagCategories();

	SITagManager = GetGameInstance()->GetSubsystem<USI_GameplayTagManager>();
	if(!IsValid(SITagManager)) {return;}

	CameraTags = CreateTagCategory("Camera Tags");
	DebugTags = CreateTagCategory("Debug Tags");
	GadgetTags = CreateTagCategory("Gadget Tags");
	GameStateTags = CreateTagCategory("GameState Tags");
	LevelTags = CreateTagCategory("Level Tags");
	MediaTags = CreateTagCategory("Media Tags");
	MusicTags = CreateTagCategory("Music Tags");
	PlayerStateTags = CreateTagCategory("PlayerState Tags");
	UITags = CreateTagCategory("UI Tags");
	
	UpdateTagEntries();
}

void USI_GameplayTagViewer::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateTagEntries();
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
