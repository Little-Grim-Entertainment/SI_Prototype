// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AoS_InteractableActor.generated.h"

UCLASS()
class AOS_PROTOTYPE_API AAoS_InteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAoS_InteractableActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	class UAoS_InteractableComponent* InteractableComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	class UBoxComponent* OverlapBox;
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	class UWidgetComponent* InteractionIcon;
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	class UWidgetComponent* InteractionPrompt;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
