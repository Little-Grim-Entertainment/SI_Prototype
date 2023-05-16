// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SI_Character.h"
#include "SI_Types.h"
#include "SI_Nick.generated.h"

class UATPCCameraComponent;
class USI_NickCharacterData;
class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class USI_AIPerceptionStimuliSource;
class USI_LevelManager;
class USI_MapData;

UCLASS()
class SI_PROTOTYPE_API ASI_Nick : public ASI_Character
{
	GENERATED_BODY()
	
public:

	ASI_Nick();

	// ================== VARIABLES ==================

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UATPCCameraComponent* ATPCCamera;
	
private:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear, Category = AI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USI_AIPerceptionStimuliSource> PerceptionStimuliSourceComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* NickFollowCamera;
	
	UPROPERTY()
	USI_LevelManager* LevelManager;
		
	// ================== FUNCTIONS ==================

	UFUNCTION()
	void OnLevelLoaded(USI_MapData* LoadedLevel, bool bShouldFade = false);
	UFUNCTION()
	void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Clothing")
	USI_NickCharacterData* NickCharacterData;
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE UATPCCameraComponent* GetATPCCamera() const { return ATPCCamera; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return NickFollowCamera; }
	/** Returns PerceptionStimuliSourceComponent subobject **/
	FORCEINLINE USI_AIPerceptionStimuliSource* GetPerceptionStimuliSource() const { return PerceptionStimuliSourceComponent; }

	/** Turn off visibility of Nick's meshes **/
	void HideMeshes(bool Value);
	
protected:

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
};
