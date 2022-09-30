// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#include "Widget/Components/HorizonTextBlock.h"
#include "HorizonUIPrivate.h"


#if WITH_EDITOR

const FText UHorizonTextBlock::GetPaletteCategory()
{
	return NSLOCTEXT("HorizonPlugin", "HorizonPlugin", "HorizonPlugin");
}





void UHorizonTextBlock::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	Super::PostEditChangeProperty(PropertyChangedEvent);

}
#endif //#if WITH_EDITOR


