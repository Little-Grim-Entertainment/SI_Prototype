#include "Debug/SI_DebugTypes.h"

FSI_DebugVariable::FSI_DebugVariable(const FString& InDebugString) :
	DebugString(InDebugString)
{
}

FSI_DebugBool::FSI_DebugBool(const FString& InDebugString, const bool bInValue) :
	bValue(bInValue)
{
	DebugString = InDebugString;
}

FSI_DebugBool::operator bool() const
{
	return bValue;
}
