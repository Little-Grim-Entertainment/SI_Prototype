// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AoS_Character.h"
#include "AoS_Nick.generated.h"

class UAoS_HUD;

UCLASS()
class AOS_PROTOTYPE_API AAoS_Nick : public AAoS_Character
{
	GENERATED_BODY()
	
public:

	AAoS_Nick();

	// ================== VARIABLES ==================

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<UAoS_HUD> PlayerHUDClass;
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY()
	UAoS_HUD* PlayerHUD;
		
	// ================== FUNCTIONS ==================
public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	void ShowHUD();
	UFUNCTION(BlueprintCallable)
	void HideHUD();
	
	// Getters
	
protected:

	virtual void BeginPlay() override;
};
