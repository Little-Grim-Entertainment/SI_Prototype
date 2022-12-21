// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AoS_Character.h"
#include "AoS_Nick.generated.h"

class UAoS_NickCharacterData;
class USpringArmComponent;
class UCameraComponent;
<<<<<<< HEAD
class UAoS_AIPerceptionStimuliSource;
=======
class UAoS_LevelManager;
class UAoS_MapData;
>>>>>>> cce4cdcfa9286d95bddaf46848769a82dd2c851b

UCLASS()
class AOS_PROTOTYPE_API AAoS_Nick : public AAoS_Character
{
	GENERATED_BODY()
	
public:

	AAoS_Nick();

	// ================== VARIABLES ==================
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
<<<<<<< HEAD
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ObservationCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear, Category = AI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAoS_AIPerceptionStimuliSource> PerceptionStimuliSourceComponent = nullptr;
=======
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* ObservationCamera;

	UPROPERTY()
	ACameraActor* FollowCameraActor;
	UPROPERTY()
	ACameraActor* ObservationCameraActor;
	
	
	UPROPERTY()
	UAoS_LevelManager* LevelManager;
>>>>>>> cce4cdcfa9286d95bddaf46848769a82dd2c851b
		
	// ================== FUNCTIONS ==================

	UFUNCTION()
	void OnLevelLoaded(UAoS_MapData* LoadedLevel, bool bShouldFade = false);

	//begin overlap for checking collision with camera actor
	UFUNCTION()
	void OnBeginOverlapCameraActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//end overlap for checking collision with camera actor
	UFUNCTION()
	void OnEndOverlapCameraActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Clothing")
	UAoS_NickCharacterData* NickCharacterData;
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UChildActorComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns ObservationCamera subobject **/
<<<<<<< HEAD
	FORCEINLINE UCameraComponent* GetObservationCamera() const { return ObservationCamera; }
	/** Returns PerceptionStimuliSourceComponent subobject **/
	FORCEINLINE UAoS_AIPerceptionStimuliSource* GetPerceptionStimuliSource() const { return PerceptionStimuliSourceComponent; }
=======
	FORCEINLINE UChildActorComponent* GetObservationCamera() const { return ObservationCamera; }
	/** Returns FollowCamera Actor **/
	FORCEINLINE ACameraActor* GetFollowCameraActor() const { return FollowCameraActor; }
	/** Returns ObservationCamera Actor **/
	FORCEINLINE ACameraActor* GetObservationCameraActor() const { return ObservationCameraActor; }
>>>>>>> cce4cdcfa9286d95bddaf46848769a82dd2c851b
	
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
};
