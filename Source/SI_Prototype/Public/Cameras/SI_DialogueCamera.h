// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SI_DialogueCamera.generated.h"

class ASI_Character;
class UCameraComponent;
class UATPCCameraComponent;

UCLASS()
class SI_PROTOTYPE_API ASI_DialogueCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASI_DialogueCamera();

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UATPCCameraComponent* ATPCCamera;

	UFUNCTION(BlueprintCallable, Category = "DialogueCamera")
	void SetNewFocusedCharacter(ASI_Character* InNewFocusedCharacter);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraSettings | Offsets | NickSpade")
	float NickSpawnForwardOffset = 80.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraSettings | Offsets | NickSpade")
	float NickSpawnRightOffset = 50.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraSettings | Offsets | NickSpade")
	float NickSpawnZOffset = -50.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraSettings | Offsets | NickSpade")
	float NickYawRotationOffset = 35.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraSettings | Offsets | NickSpade")
	float NickPitchRotationOffset = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraSettings | Offsets | NPC")
	float NPCSpawnForwardOffset = 80.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraSettings | Offsets | NPC")
	float NPCSpawnRightOffset = 50.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraSettings | Offsets | NPC")
	float NPCSpawnZOffset = -60.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraSettings | Offsets | NPC")
	float NPCYawRotationOffset = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraSettings | Offsets | NPC")
	float NPCPitchRotationOffset = 0.0f;
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* DialogueCamera;
	
	ASI_Character* FocusedCharacter = nullptr;

	FVector GetOffsetLocation(float InSpawnForwardOffset, float InSpawnRightOffset, float InZOffset);
	FRotator GetOffsetRotation(float InYawRotationOffset, float InPitchRotationOffset);
	
	void OnFocusedCharacterChanged();
	void InitializeCharacterTransforms();
};
