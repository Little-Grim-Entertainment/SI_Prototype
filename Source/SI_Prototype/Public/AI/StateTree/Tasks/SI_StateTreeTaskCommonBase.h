// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "SmartObjectSubsystem.h"
#include "SI_StateTreeTaskCommonBase.generated.h"

class USmartObjectSubsystem;
class USI_TagManager;

USTRUCT()
struct FStateTreeTaskCommonBase_InstanceData
{
	GENERATED_BODY()
};

USTRUCT(Meta=(Hidden))
struct SI_PROTOTYPE_API FSI_StateTreeTaskCommonBase : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FSI_StateTreeTaskCommonBase() = default;
	
	using FInstanceDataType = FStateTreeTaskCommonBase_InstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual bool Link(FStateTreeLinker& Linker) override;
	
	/** Handle to retrieve USmartObjectSubsystem. */
	TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;
};