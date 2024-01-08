// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

template <typename StructType>
StructType GetStructFromUStruct(UStruct* InUStruct)
{
	// Check if the UStruct is actually a UScriptStruct
	const UScriptStruct* ScriptStruct = Cast<UScriptStruct>(InUStruct);
	if (IsValid(ScriptStruct))
	{
		// Allocate memory for the struct instance
		void* StructInstance = FMemory::Malloc(ScriptStruct->GetStructureSize());

		// Initialize the struct instance (optional)
		ScriptStruct->InitializeStruct(StructInstance);

		// Convert the void pointer to the specific struct type
		StructType* ResultStruct = static_cast<StructType*>(StructInstance);

		// Return the struct instance
		return *ResultStruct;
	}

	// If the provided UStruct is not a UScriptStruct, return a default-constructed instance
	return StructType{};
}

