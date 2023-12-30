// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SI_NPC.h"
#include "Interfaces/SI_InteractInterface.h"
#include "SI_NPC_Interactable.generated.h"


class ASI_Nick;
class USI_InteractableComponent;

UCLASS()
class SI_PROTOTYPE_API ASI_NPC_Interactable : public ASI_NPC, public ISI_InteractInterface
{
	GENERATED_BODY()

public:
		
	ASI_NPC_Interactable();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* NPC_Cam;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* NickCam;

	UPROPERTY()
	class ASI_NPCController_Interactable* AIController;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* NickPosition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	FText CharacterName;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	USI_InteractableComponent* InteractableComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category = "Interaction")
	UWidgetComponent* InteractionIcon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	UWidgetComponent* InteractionPrompt;
	
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(ASI_Nick* InNickActor);
	UFUNCTION()
	void OnEndOverlap(ASI_Nick* InNickActor);
	UFUNCTION()
	virtual void OnInteract_Implementation(AActor* Caller) override;
	UFUNCTION()
	virtual void OnInteractEnd_Implementation(AActor* Caller) override;
	UFUNCTION()
	virtual UWidgetComponent* GetInteractionIconComponent_Implementation() override;
	UFUNCTION()
	virtual UWidgetComponent* GetInteractionPromptComponent_Implementation() override;
	
	
};
