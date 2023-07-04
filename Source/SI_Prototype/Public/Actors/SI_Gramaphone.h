// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SI_AlbumWidget.h"
#include "Actors/SI_InteractableActor.h"
#include "SI_Gramaphone.generated.h"

class USI_GramaphoneMenu;
/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API ASI_Gramaphone : public ASI_InteractableActor
{
	GENERATED_BODY()

public:

	ASI_Gramaphone();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<USI_GramaphoneMenu> GramaphoneMenu_Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* MusicComponent;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnAlbumSelected(USI_AlbumWidget* SelectedAlbumWidget);
	UFUNCTION(BlueprintNativeEvent)
	void OnAlbumPlayStopped();

	UFUNCTION(BlueprintPure, Category = "AlbumDetails")
	FAlbumDetails& GetCurrentAlbumDetails();	
	
protected:

	UPROPERTY(BlueprintReadOnly)
	USI_GramaphoneMenu* GramaphoneMenu;

	UFUNCTION()
	void OnGramaphoneMenuConstructed();
	
	virtual void OnInteract_Implementation(AActor* Caller) override;
		
	void CreateGramaphoneMenu();

private:
	
	FAlbumDetails CurrentAlbumDetails;
};
