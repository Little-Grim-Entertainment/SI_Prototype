// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LGCoreTypes.generated.h"

USTRUCT(BlueprintType)
struct LGCORELIBRARY_API FLGGuid : public FGuid
{
	GENERATED_BODY()

	FLGGuid(){}
	FLGGuid(const FGuid& InGuid);
	~FLGGuid(){}
	
	template<class TLGGuid>
	static TLGGuid NewLGGuid();
};

template <class TLGGuid>
TLGGuid FLGGuid::NewLGGuid()
{
	FGuid NewGuid = FGuid::NewGuid();
	TLGGuid* NewLGGuid = static_cast<TLGGuid*>(&NewGuid);
	if(NewLGGuid)
	{
		return *NewLGGuid;
	}
	return TLGGuid();
}
