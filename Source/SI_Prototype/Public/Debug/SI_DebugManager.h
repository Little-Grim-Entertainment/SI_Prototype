// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SI_DebugTypes.h"
#include "SI_DebugManager.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_DebugManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USI_DebugManager();

	void InitializeDebugCommands(const FString& Options);

	bool DebugCommandsHaveInitialized() const;

	void CreateDebugBoolType(const FString& InDebugString, const bool bInValue, const FGameplayTag& InAssociatedTag);

protected:

	virtual void Deinitialize() override;
	
private:
	
	bool bDebugCommandsInitialized;

	TMap<FGameplayTag, FSI_DebugVariable*> DebugVariables;

	template<typename T>
	T* GetDebugVariableTypeByTag(const FGameplayTag& InGameplayTag);
};

template <typename T>
T* USI_DebugManager::GetDebugVariableTypeByTag(const FGameplayTag& InGameplayTag)
{
	T* Variable = static_cast<T*>(DebugVariables.Find(InGameplayTag));
	return Variable;
}
