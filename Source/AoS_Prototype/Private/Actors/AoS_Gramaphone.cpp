// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AoS_Gramaphone.h"

#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Components/Button.h"
#include "UI/AoS_GramaphoneMenu.h"
#include "Controllers/AoS_PlayerController.h"


AAoS_Gramaphone::AAoS_Gramaphone()
{
	MusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicComponent"));
	MusicComponent->SetupAttachment(RootComponent);
}

void AAoS_Gramaphone::OnGramaphoneMenuConstructed()
{
	for (UAoS_AlbumWidget* CurrentAlbumWidget : GramaphoneMenu->GetAlbumWidgets())
	{
		CurrentAlbumWidget->OnAlbumSelected.AddDynamic(this, &ThisClass::OnAlbumSelected);
		if (!GramaphoneMenu->BTN_Stop->OnClicked.IsBound())
		{
			GramaphoneMenu->BTN_Stop->OnClicked.AddDynamic(this, &ThisClass::AAoS_Gramaphone::OnAlbumPlayStopped);
		}
	}
}

void AAoS_Gramaphone::OnInteract_Implementation(AActor* Caller)
{
	Super::OnInteract_Implementation(Caller);

	CreateGramaphoneMenu();
}

void AAoS_Gramaphone::CreateGramaphoneMenu()
{
	AAoS_PlayerController* PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(PlayerController) || !IsValid(GramaphoneMenu_Class)){return;}
	
	GramaphoneMenu = CreateWidget<UAoS_GramaphoneMenu>(PlayerController, GramaphoneMenu_Class);
	if (IsValid(GramaphoneMenu))
	{
		GramaphoneMenu->OnNativeConstructionComplete.AddDynamic(this, &ThisClass::AAoS_Gramaphone::OnGramaphoneMenuConstructed);
		GramaphoneMenu->SetCurrentAlbumDetails(CurrentAlbumDetails);
		GramaphoneMenu->SetIsAlbumPlaying(MusicComponent->IsPlaying());
		GramaphoneMenu->AddToViewport();
	}
}

void AAoS_Gramaphone::OnAlbumSelected_Implementation(UAoS_AlbumWidget* SelectedAlbumWidget)
{
	CurrentAlbumDetails = SelectedAlbumWidget->GetAlbumDetails();
}

void AAoS_Gramaphone::OnAlbumPlayStopped_Implementation()
{
	
}

FAlbumDetails& AAoS_Gramaphone::GetCurrentAlbumDetails()
{
	return CurrentAlbumDetails;
}
