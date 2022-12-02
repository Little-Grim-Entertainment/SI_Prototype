// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Characters/AoS_CharacterData.h"
#include "AoS_NickCharacterData.generated.h"

USTRUCT(BlueprintType)
struct FNickClothingOptions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ClothingName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* ClothingBaseMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<USkeletalMesh*> ClothingAddition;
};

UCLASS()
class AOS_PROTOTYPE_API UAoS_NickCharacterData : public UAoS_CharacterData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterDetails")
	TArray<FNickClothingOptions> ClothingOptions;

	UFUNCTION(BlueprintCallable, Category = "Clothing")
	USkeletalMesh* GetClothingMeshFromName(FName InClothingName) const;
};
