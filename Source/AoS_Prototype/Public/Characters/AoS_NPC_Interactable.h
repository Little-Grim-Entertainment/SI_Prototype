// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AoS_NPC.h"
#include "AoS_NPC_Interactable.generated.h"

/**
 * 
 */
UCLASS()
class AOS_PROTOTYPE_API AAoS_NPC_Interactable : public AAoS_NPC
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* NPC_Cam;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* NickCam;
	
public:

	AAoS_NPC_Interactable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	FText CharacterName;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	class UAoS_InteractableComponent* InteractableComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	class UAoS_DialogueComponent* DialogueComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	class UBoxComponent* OverlapBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category = "Interaction")
	class UWidgetComponent* InteractionIcon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	class UWidgetComponent* InteractionPrompt;
	
};
