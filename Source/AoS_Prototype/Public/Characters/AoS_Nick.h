// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AoS_Character.h"
#include "AoS_Nick.generated.h"

class UAoS_NickCharacterData;
class USpringArmComponent;
class UCameraComponent;
class UAoS_AIPerceptionStimuliSource;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ObservationCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear, Category = AI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAoS_AIPerceptionStimuliSource> PerceptionStimuliSourceComponent = nullptr;
		
	// ================== FUNCTIONS ==================
public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Clothing")
	UAoS_NickCharacterData* NickCharacterData;
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns ObservationCamera subobject **/
	FORCEINLINE UCameraComponent* GetObservationCamera() const { return ObservationCamera; }
	/** Returns PerceptionStimuliSourceComponent subobject **/
	FORCEINLINE UAoS_AIPerceptionStimuliSource* GetPerceptionStimuliSource() const { return PerceptionStimuliSourceComponent; }
	
protected:

	virtual void BeginPlay() override;
};
