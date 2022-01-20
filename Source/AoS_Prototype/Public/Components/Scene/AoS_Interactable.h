// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AoS_Interactable.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerBeginOverlap, class AAoS_Nick*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerEndOverlap, class AAoS_Nick*, Player);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AOS_PROTOTYPE_API UAoS_Interactable : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAoS_Interactable();

	UPROPERTY(EditAnywhere)
	class UBoxComponent* OverlapBox;
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* InteractionTypeIcon;
	UPROPERTY(BlueprintAssignable, Category = "Overlap")
	FOnPlayerBeginOverlap OnPlayerBeginOverlap;
	UPROPERTY(BlueprintAssignable, Category = "Overlap")
	FOnPlayerEndOverlap OnPlayerEndOverlap;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
