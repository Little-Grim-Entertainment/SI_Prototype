// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/AoS_AlbumWidget.h"
#include "Actors/AoS_InteractableActor.h"
#include "AoS_Gramaphone.generated.h"

class UAoS_GramaphoneMenu;
/**
 * 
 */
UCLASS()
class AOS_PROTOTYPE_API AAoS_Gramaphone : public AAoS_InteractableActor
{
	GENERATED_BODY()

public:

	AAoS_Gramaphone();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UAoS_GramaphoneMenu> GramaphoneMenu_Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* MusicComponent;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnAlbumSelected(UAoS_AlbumWidget* SelectedAlbumWidget);
	UFUNCTION(BlueprintNativeEvent)
	void OnAlbumPlayStopped();

	UFUNCTION(BlueprintPure, Category = "AlbumDetails")
	FAlbumDetails& GetCurrentAlbumDetails();	
	
protected:

	UPROPERTY(BlueprintReadOnly)
	UAoS_GramaphoneMenu* GramaphoneMenu;

	UFUNCTION()
	void OnGramaphoneMenuConstructed();
	
	virtual void OnInteract_Implementation(AActor* Caller) override;
		
	void CreateGramaphoneMenu();

private:
	
	FAlbumDetails CurrentAlbumDetails;
};
