// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AoS_NPC.h"
#include "Interfaces/AoS_InteractInterface.h"
#include "AoS_NPC_Interactable.generated.h"


class AAoS_Nick;
class UAoS_InteractableComponent;

UCLASS()
class AOS_PROTOTYPE_API AAoS_NPC_Interactable : public AAoS_NPC, public IAoS_InteractInterface
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* NPC_Cam;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* NickCam;
	
public:
		
	AAoS_NPC_Interactable();

	UPROPERTY()
	class AAoS_NPCController_Interactable* AIController;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* NickPosition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	FText CharacterName;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	UAoS_InteractableComponent* InteractableComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category = "Interaction")
	UWidgetComponent* InteractionIcon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	UWidgetComponent* InteractionPrompt;
	
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(AAoS_Nick* InNickActor);
	UFUNCTION()
	void OnEndOverlap(AAoS_Nick* InNickActor);
	
	UFUNCTION()
	virtual UWidgetComponent* GetInteractionIconComponent_Implementation() override;
	UFUNCTION()
	virtual UWidgetComponent* GetInteractionPromptComponent_Implementation() override;
	
};
