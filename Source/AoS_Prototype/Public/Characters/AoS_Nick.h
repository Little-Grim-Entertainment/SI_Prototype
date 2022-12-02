// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AoS_Character.h"
#include "AoS_Nick.generated.h"

class UAoS_NickCharacterData;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class AOS_PROTOTYPE_API AAoS_Nick : public AAoS_Character
{
	GENERATED_BODY()
	
public:

	AAoS_Nick();

	// ================== VARIABLES ==================
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ObservationCamera;
		
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

	
protected:

	virtual void BeginPlay() override;
};
