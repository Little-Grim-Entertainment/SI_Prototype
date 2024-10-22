// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SI_DebugTypes.h"
#include "Subsystems/SI_GameInstanceSubsystem.h"
#include "SI_DebugManager.generated.h"

class USI_GameplayTagViewer;

UCLASS()
class SI_PROTOTYPE_API USI_DebugManager : public USI_GameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USI_DebugManager();

	void InitializeDebugCommands(const FString& Options);

	bool DebugCommandsHaveInitialized() const;

	void CreateDebugBoolType(const FString& InDebugString, const bool bInValue, const FGameplayTag& InAssociatedTag);

	FSI_DebugBool* GetDebugBoolByTag(const FGameplayTag& InAssociatedTag);
	
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