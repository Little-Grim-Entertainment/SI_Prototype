// Copyright 2024 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ATPCTypes.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "ATPCCameraModeDataAsset.generated.h"

UCLASS()
class ADVANCEDTHIRDPERSONCAMERA_API UATPCCameraModeDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	//~ Begin UObject Interface
	virtual void Serialize(FArchive& Ar) override;
	//~ End UObject Interface

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FGameplayTag CameraModeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FATPCCameraMode CameraModeSettings;

	/** 
	* Classes of objects that will be created when camera mode is activated. 
	* This is a useful thing to add custom user code that will be executed during the work of camera mode
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Settings")
	TArray<class UATPCCameraModeScript*> CameraModeScripts;
};