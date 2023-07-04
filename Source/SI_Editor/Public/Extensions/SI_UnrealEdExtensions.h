// Copyright Little Grim Entertainment LLC

#pragma once

#include "CoreMinimal.h"

class FMenuBuilder;
class FUICommandList;
class FExtender;

class SI_EDITOR_API SI_UnrealEdExtensions
{
public:

	static void InstallExtensions();
	static void RemoveExtensions();

private:

	static TSharedRef<FExtender> ExtendPIEMenu(const TSharedRef<FUICommandList> CommandList);
	static void CreateExtendedPIEMenu(FMenuBuilder& MenuBuilder);

	static void AddMediaToggleOptionPIEMenu(FMenuBuilder& MenuBuilder);
};
