// Copyright 2023, PROTOWLF, All Rights Reserved


#include "ProtoRichTextUserWidget.h"


void UProtoRichTextUserWidget::CallOnClicked()
{
	OnClicked.Broadcast(MetaDataName);
}


void UProtoRichTextUserWidget::CallOnPressed()
{
	OnPressed.Broadcast(MetaDataName);
}


void UProtoRichTextUserWidget::CallOnReleased()
{
	OnReleased.Broadcast(MetaDataName);
}


void UProtoRichTextUserWidget::CallOnHovered()
{
	OnHovered.Broadcast(MetaDataName);
}


void UProtoRichTextUserWidget::CallOnUnhovered()
{
	OnUnhovered.Broadcast(MetaDataName);
}

