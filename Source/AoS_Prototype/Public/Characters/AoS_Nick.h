// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AoS_Character.h"
#include "AoS_Nick.generated.h"

class UATPCCameraComponent;
class UAoS_NickCharacterData;
class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class UAoS_AIPerceptionStimuliSource;
class UAoS_LevelManager;
class UAoS_MapData;

UCLASS()
class AOS_PROTOTYPE_API AAoS_Nick : public AAoS_Character
{
	GENERATED_BODY()
	
public:

	AAoS_Nick();

	// ================== VARIABLES ==================

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UATPCCameraComponent* ATPCCamera;
	
private:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear, Category = AI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAoS_AIPerceptionStimuliSource> PerceptionStimuliSourceComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* NickFollowCamera;
	
	UPROPERTY()
	UAoS_LevelManager* LevelManager;
		
	// ================== FUNCTIONS ==================

	UFUNCTION()
	void OnLevelLoaded(UAoS_MapData* LoadedLevel, bool bShouldFade = false);
	UFUNCTION()
	void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Clothing")
	UAoS_NickCharacterData* NickCharacterData;
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE UATPCCameraComponent* GetATPCCamera() const { return ATPCCamera; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return NickFollowCamera; }
	/** Returns PerceptionStimuliSourceComponent subobject **/
	FORCEINLINE UAoS_AIPerceptionStimuliSource* GetPerceptionStimuliSource() const { return PerceptionStimuliSourceComponent; }

	/** Turn off visibility of Nick's meshes **/
	void HideMeshes(bool Value);
	
protected:

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
};
