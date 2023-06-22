// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Interfaces/SI_InteractInterface.h"
#include "SI_InteractableActor.generated.h"

class USI_AbilitySystemComponent;
class USI_InteractionIcon;
class USI_InteractionPrompt;
class ASI_Nick;
class USI_InteractableComponent;
class UBoxComponent;
class UWidgetComponent;

UCLASS()
class SI_PROTOTYPE_API ASI_InteractableActor : public AActor, public ISI_InteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASI_InteractableActor();

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* HighlightMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	USI_InteractableComponent* InteractableComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UWidgetComponent* InteractionIcon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UWidgetComponent* InteractionPrompt;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	FGameplayTag InteractionTag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	USI_AbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	bool bIsObservable = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	virtual void OnBeginOverlap(ASI_Nick* InNickActor);
	UFUNCTION()
	virtual void OnEndOverlap(ASI_Nick* InNickActor);
	
	void DisableHighlight();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HighlightBeginTimer();
private:

	UFUNCTION()
	virtual UWidgetComponent* GetInteractionIconComponent_Implementation() override;
	UFUNCTION()
	virtual UWidgetComponent* GetInteractionPromptComponent_Implementation() override;

	FTimerHandle HighlightTimerHandle;
};
