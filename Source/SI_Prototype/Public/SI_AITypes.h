// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "GameplayTags/SI_NativeGameplayTagLibrary.h"
#include "SI_AITypes.generated.h"

class ASI_NPCController;
class ASI_Nick;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMoveToLocationUpdated, FVector&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMoveToRotationUpdated, FRotator&)

USTRUCT(BlueprintType)
struct FSI_NPCMemory
{
	GENERATED_BODY()

	FSI_NPCMemory() = default;
	FSI_NPCMemory(FVector& InLocation, FRotator& InRotation, FGameplayTag& InNextActionTag);

	FVector& GetMoveToLocation() { return MoveToLocation; }
	void SetMoveToLocation(const FVector& InLocation);
	FRotator& GetMoveToRotation()  { return MoveToRotation; }
	void SetMoveToRotation(const FRotator& InRotation);
	TObjectPtr<ASI_Nick> GetNick() { return Nick; }
	void SetNick(TObjectPtr<ASI_Nick> InNick);
	TObjectPtr<AActor> GetTargetObject() const { return TargetObject; }
	void SetTargetObject(TObjectPtr<AActor> InTargetObject);
	TObjectPtr<AActor> GetAbilityCaller() const { return AbilityCaller; }
	void SetAbilityCaller(TObjectPtr<AActor> InAbilityCaller);
	TObjectPtr<AActor> GetAbilityInstigator() const { return AbilityInstigator; }
	void SetAbilityInstigator(TObjectPtr<AActor> InAbilityInstigator);
	
	const FGameplayTag& GetNextActionTag() { return NextActionTag; }
	void SetNextActionTag(const FGameplayTag& InNextActionTag);
	
	UPROPERTY(EditAnywhere, Category = "AI | Memory")
	FGameplayTag NextActionTag = SI_NativeGameplayTagLibrary::SITag_None;
	
	UPROPERTY(EditAnywhere, Category = "AI | Memory")
	TObjectPtr<ASI_Nick> Nick = nullptr;
	UPROPERTY(EditAnywhere, Category = "AI | Memory")
	FVector MoveToLocation = FVector();
	UPROPERTY(EditAnywhere, Category = "AI | Memory")
	FRotator MoveToRotation = FRotator();
	UPROPERTY(EditAnywhere, Category = "AI | Memory")
	TObjectPtr<AActor> TargetObject = nullptr;
	UPROPERTY(EditAnywhere, Category = "AI | Memory")
	TObjectPtr<AActor> AbilityCaller = nullptr;
	UPROPERTY(EditAnywhere, Category = "AI | Memory")
	TObjectPtr<AActor> AbilityInstigator = nullptr;
	
	FOnMoveToLocationUpdated OnMoveToLocationUpdated;
	FOnMoveToRotationUpdated OnMoveToRotationUpdated;
	
	bool operator == (const FSI_NPCMemory& Other) const;
	bool operator != (const FSI_NPCMemory& Other) const;
};

USTRUCT(BlueprintType)
struct FSI_NPCMovementHelper
{
	GENERATED_BODY()

	FSI_NPCMovementHelper() = default;

	float CalculateMovementSpeed(float InCurrentDistance, float InCurrentTargetSpeed);
	
	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MinDistance = 1.0f;
	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MaxDistance = 250.0f;
	
	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MinSpeed = 1.0f;
	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MaxSpeed = 300.0f;
	
	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MinTargetSpeed = 1.0f;
	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MaxTargetSpeed = 300.0f;
};