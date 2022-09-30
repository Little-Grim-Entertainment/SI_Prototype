// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net
#pragma once

#include "Components/TextBlock.h"
#include "HorizonTextBlock.generated.h"

/**
 * 
 */
UCLASS()
class HORIZONUI_API UHorizonTextBlock : public UTextBlock
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|TextBlock|Appearance")
		FORCEINLINE TEnumAsByte<ETextJustify::Type> GetJustification() const { return Justification; }
	
public:
#if WITH_EDITOR
	//~ Begin UWidget Interface
	//#if (ENGINE_MAJOR_VERSION <= 4) && (ENGINE_MINOR_VERSION <= 12)
	//virtual const FSlateBrush* GetEditorIcon() override;
	//#endif
	virtual const FText GetPaletteCategory() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
