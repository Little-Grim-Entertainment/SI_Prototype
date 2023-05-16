// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SI_Gramaphone.h"

#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Components/Button.h"
#include "UI/SI_GramaphoneMenu.h"
#include "Controllers/SI_PlayerController.h"


ASI_Gramaphone::ASI_Gramaphone()
{
	MusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicComponent"));
	MusicComponent->SetupAttachment(RootComponent);
}

void ASI_Gramaphone::OnGramaphoneMenuConstructed()
{
	for (USI_AlbumWidget* CurrentAlbumWidget : GramaphoneMenu->GetAlbumWidgets())
	{
		if (!CurrentAlbumWidget->OnAlbumSelected.IsBound())
		{
			CurrentAlbumWidget->OnAlbumSelected.AddDynamic(this, &ThisClass::OnAlbumSelected);
		}
		if (!GramaphoneMenu->BTN_Stop->OnClicked.IsBound())
		{
			GramaphoneMenu->BTN_Stop->OnClicked.AddDynamic(this, &ThisClass::ASI_Gramaphone::OnAlbumPlayStopped);
		}
	}
}

void ASI_Gramaphone::OnInteract_Implementation(AActor* Caller)
{
	Super::OnInteract_Implementation(Caller);

	CreateGramaphoneMenu();
}

void ASI_Gramaphone::CreateGramaphoneMenu()
{
	ASI_PlayerController* PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(PlayerController) || !IsValid(GramaphoneMenu_Class)){return;}

	if (!IsValid(GramaphoneMenu))
	{
		GramaphoneMenu = CreateWidget<USI_GramaphoneMenu>(PlayerController, GramaphoneMenu_Class);
		if (IsValid(GramaphoneMenu))
		{
			GramaphoneMenu->OnNativeConstructionComplete.AddDynamic(this, &ThisClass::ASI_Gramaphone::OnGramaphoneMenuConstructed);
			GramaphoneMenu->SetCurrentAlbumDetails(CurrentAlbumDetails);
			GramaphoneMenu->SetIsAlbumPlaying(MusicComponent->IsPlaying());
			GramaphoneMenu->AddToViewport();
		}
	}
	else
	{
			GramaphoneMenu->SetCurrentAlbumDetails(CurrentAlbumDetails);
			GramaphoneMenu->SetIsAlbumPlaying(MusicComponent->IsPlaying());
			GramaphoneMenu->AddToViewport();
	}

}

void ASI_Gramaphone::OnAlbumSelected_Implementation(USI_AlbumWidget* SelectedAlbumWidget)
{
	CurrentAlbumDetails = SelectedAlbumWidget->GetAlbumDetails();
}

void ASI_Gramaphone::OnAlbumPlayStopped_Implementation()
{
	
}

FAlbumDetails& ASI_Gramaphone::GetCurrentAlbumDetails()
{
	return CurrentAlbumDetails;
}
