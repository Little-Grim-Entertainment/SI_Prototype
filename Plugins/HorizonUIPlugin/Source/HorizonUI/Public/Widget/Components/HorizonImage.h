// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net
#pragma once

#include "Components/Image.h"
#include "HorizonImage.generated.h"

/**
 * 
 */
UCLASS()
class HORIZONUI_API UHorizonImage : public UImage
{
	GENERATED_BODY()
	
public:
	UHorizonImage();
#if WITH_EDITOR
	//~ Begin UWidget Interface
	//#if (ENGINE_MAJOR_VERSION <= 4) && (ENGINE_MINOR_VERSION <= 12)
	//virtual const FSlateBrush* GetEditorIcon() override;
	//#endif
	virtual const FText GetPaletteCategory() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	virtual void SynchronizeProperties();
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	FBox2D UVRegion = FBox2D(FVector2D::ZeroVector, FVector2D::UnitVector);
	
};
