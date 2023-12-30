// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/NavigationObjectBase.h"
#include "SI_CharacterSpawner.generated.h"

class USI_CharacterData;
class ASI_Character;

UCLASS(Blueprintable)
class SI_PROTOTYPE_API ASI_CharacterSpawner : public ANavigationObjectBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASI_CharacterSpawner(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	USI_CharacterData* CharacterData;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void SpawnPreviewCharacter(const TSubclassOf<ASI_Character>& InCharacterClass);
	void DuplicateSkeletalMeshComponents(const TArray<USkeletalMeshComponent*>& InSkeletalMeshArray);
	void DuplicateStaticMeshComponents(const TArray<UStaticMeshComponent*>& InStaticMeshArray);
#endif
	
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TArray<USkeletalMeshComponent*> PreviewSkeletalMeshComponents;
	UPROPERTY()
	TArray<UStaticMeshComponent*> PreviewStaticMeshComponents;
#endif

#if WITH_EDITORONLY_DATA
private:
	UPROPERTY()
	TObjectPtr<class UArrowComponent> ArrowComponent;

	/** Returns ArrowComponent subobject **/
	UArrowComponent* GetArrowComponent() const;

	void ResetCharacterSpawner();
#endif

private:

	UPROPERTY()
	TSoftObjectPtr<ASI_Character> SpawnedCharacter;
	
	void SpawnCharacter();
};
