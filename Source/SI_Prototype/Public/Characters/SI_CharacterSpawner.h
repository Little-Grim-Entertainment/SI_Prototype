// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/NavigationObjectBase.h"
#include "SI_CharacterSpawner.generated.h"

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
	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	FGameplayTag CharacterTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	TSubclassOf<ASI_Character> CharacterClass;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void SpawnPreviewCharacter(const TSubclassOf<ASI_Character>& InCharacterClass);
#endif
	
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	ASI_Character* PreviewCharacter;
#endif

#if WITH_EDITORONLY_DATA
private:
	UPROPERTY()
	TObjectPtr<class UArrowComponent> ArrowComponent;

	/** Returns ArrowComponent subobject **/
	UArrowComponent* GetArrowComponent() const;

	void ResetCharacterSpawner();
#endif
};
