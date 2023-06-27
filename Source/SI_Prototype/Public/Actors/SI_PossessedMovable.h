// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SI_PossessedMovable.generated.h"

class UCameraComponent;
class UATPCCameraComponent;
class ASI_PlayerCameraManager;

UCLASS()
class SI_PROTOTYPE_API ASI_PossessedMovable : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASI_PossessedMovable();
	
	void UpdateActiveMesh(UStaticMesh* InMesh);
	void SetActiveMeshToDefault();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

protected:

	UPROPERTY()
	ASI_PlayerCameraManager* PlayerCameraManager;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	UStaticMesh* DefaultMesh;
	UPROPERTY(BlueprintReadOnly, Category = Camera)
	UATPCCameraComponent* ATPCCamera;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PossessedFollowCamera;

};