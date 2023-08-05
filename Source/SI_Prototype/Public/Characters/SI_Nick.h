// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SI_Character.h"
#include "SI_Types.h"
#include "AbilitySystemInterface.h"
#include "Abilities/SI_GameplayAbility.h"
#include "Actors/SI_InteractableActor.h"
#include "Actors/Gadgets/SI_Flashlight.h"
#include "SI_Nick.generated.h"

class USI_AbilitySystemComponent;
class APostProcessVolume;
class UATPCCameraComponent;
class USI_NickCharacterData;
class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class USI_AIPerceptionStimuliSource;
class USI_LevelManager;
class USI_MapData;

// ****************  TODO: DELETE WHEN GADGET SYSTEM IS IMPLEMENTED
class ASI_Flashlight;

UCLASS()
class SI_PROTOTYPE_API ASI_Nick : public ASI_Character, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:

	// ****************  TODO: DELETE WHEN GADGET SYSTEM IS IMPLEMENTED
	// *** Need to understand TSubclassOf properly
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASI_Flashlight> FlashlightClass = ASI_Flashlight::StaticClass();
	UPROPERTY(EditAnywhere)
	ASI_Flashlight* Flashlight;


	
	ASI_Nick();

	// ================== VARIABLES ==================

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UATPCCameraComponent* ATPCCamera;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Abilities)
	USI_AbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Abilities)
	TArray<TSubclassOf<USI_GameplayAbility>> DefaultAbilities;
	
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear, Category = AI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USI_AIPerceptionStimuliSource> PerceptionStimuliSourceComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* NickFollowCamera;
	
	UPROPERTY()
	ASI_InteractableActor* CurrentInteractableActor;
		
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
	
	/** Returns CameraBoom SubObject **/
	FORCEINLINE UATPCCameraComponent* GetATPCCamera() { return ATPCCamera; }
	/** Returns FollowCamera SubObject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return NickFollowCamera; }
	/** Returns PerceptionStimuliSourceComponent SubObject **/
	FORCEINLINE USI_AIPerceptionStimuliSource* GetPerceptionStimuliSource() const { return PerceptionStimuliSourceComponent; }
	
	/** Turn off visibility of Nick's meshes **/
	void HideMeshes(bool Value);

	USI_AbilitySystemComponent* GetSIAbilitySystemComponent() const;
	void GiveAbilities();
	ASI_InteractableActor* GetCurrentInteractableActor() { return CurrentInteractableActor; }
	void SetCurrentInteractableActor(ASI_InteractableActor* InInteractableActor) { CurrentInteractableActor = InInteractableActor; }
	
protected:

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
