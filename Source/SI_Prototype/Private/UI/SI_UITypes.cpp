// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_UITypes.h"

bool FSI_InputOptionSettings::IsValid() const
{
	return TargetInputMapping != nullptr && TargetInputAction != nullptr;
}

bool FSI_InputOptionSettings::operator==(const FSI_InputOptionSettings& OtherInputOptionSettings) const
{
	return TargetInputMapping == OtherInputOptionSettings.TargetInputMapping && TargetInputAction == OtherInputOptionSettings.TargetInputAction;
}

bool FSI_InputOptionSettings::operator!=(const FSI_InputOptionSettings& OtherInputOptionSettings) const
{
	return TargetInputMapping != OtherInputOptionSettings.TargetInputMapping || TargetInputAction != OtherInputOptionSettings.TargetInputAction;
}
