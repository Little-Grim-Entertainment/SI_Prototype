// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/AoS_InteractInterface.h"
#include "AoS_InteractableActor.generated.h"

class UAoS_InteractionIcon;
class UAoS_InteractionPrompt;
class AAoS_Nick;
class UAoS_InteractableComponent;
class UBoxComponent;
class UWidgetComponent;

UCLASS()
class AOS_PROTOTYPE_API AAoS_InteractableActor : public AActor, public IAoS_InteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAoS_InteractableActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	UAoS_InteractableComponent* InteractableComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UWidgetComponent* InteractionIcon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UWidgetComponent* InteractionPrompt;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(AAoS_Nick* InNickActor);
	UFUNCTION()
	virtual void OnEndOverlap(AAoS_Nick* InNickActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:



	UFUNCTION()
	virtual UWidgetComponent* GetInteractionIconComponent_Implementation() override;
	UFUNCTION()
	virtual UWidgetComponent* GetInteractionPromptComponent_Implementation() override;

};
