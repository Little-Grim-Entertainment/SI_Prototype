// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net
#include "Widget/Blueprint/HorizonDesignableUserWidget.h"
#include "HorizonUIPrivate.h"
void UHorizonDesignableUserWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	OnSynchronizeProperties();
}

