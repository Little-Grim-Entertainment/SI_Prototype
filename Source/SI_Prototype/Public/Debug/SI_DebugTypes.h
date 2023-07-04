#pragma once

#include "CoreMinimal.h"
#include "SI_DebugTypes.generated.h"

USTRUCT()
struct FSI_DebugVariable
{
	GENERATED_BODY()

	FSI_DebugVariable(){}
	FSI_DebugVariable(const FString& InDebugString);

	const FString& GetDebugString() const {return DebugString;}

protected:
	
	FString DebugString;
};

USTRUCT()
struct FSI_DebugBool: public FSI_DebugVariable
{
	GENERATED_BODY()

	FSI_DebugBool(){}
	FSI_DebugBool(const FString& InDebugString, const bool bInValue);

	bool GetDebugBool() const {return bValue;}

private:
	
	bool bValue = false;

	operator bool() const;
};