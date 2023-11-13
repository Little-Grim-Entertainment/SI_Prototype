// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LGDialogueSystem/Public/LGDialogueTypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLGDialogueTypes() {}
// Cross Module References
	LGDIALOGUESYSTEM_API UScriptStruct* Z_Construct_UScriptStruct_FLGPrimaryDialogue();
	UPackage* Z_Construct_UPackage__Script_LGDialogueSystem();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LGPrimaryDialogue;
class UScriptStruct* FLGPrimaryDialogue::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LGPrimaryDialogue.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LGPrimaryDialogue.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLGPrimaryDialogue, (UObject*)Z_Construct_UPackage__Script_LGDialogueSystem(), TEXT("LGPrimaryDialogue"));
	}
	return Z_Registration_Info_UScriptStruct_LGPrimaryDialogue.OuterSingleton;
}
template<> LGDIALOGUESYSTEM_API UScriptStruct* StaticStruct<FLGPrimaryDialogue>()
{
	return FLGPrimaryDialogue::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLGPrimaryDialogue_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGPrimaryDialogue_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LGDialogueTypes.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLGPrimaryDialogue_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLGPrimaryDialogue>();
	}
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLGPrimaryDialogue_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LGDialogueSystem,
		nullptr,
		&NewStructOps,
		"LGPrimaryDialogue",
		nullptr,
		0,
		sizeof(FLGPrimaryDialogue),
		alignof(FLGPrimaryDialogue),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPrimaryDialogue_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLGPrimaryDialogue_Statics::Struct_MetaDataParams)
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLGPrimaryDialogue()
	{
		if (!Z_Registration_Info_UScriptStruct_LGPrimaryDialogue.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LGPrimaryDialogue.InnerSingleton, Z_Construct_UScriptStruct_FLGPrimaryDialogue_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LGPrimaryDialogue.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_LGDialogueTypes_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_LGDialogueTypes_h_Statics::ScriptStructInfo[] = {
		{ FLGPrimaryDialogue::StaticStruct, Z_Construct_UScriptStruct_FLGPrimaryDialogue_Statics::NewStructOps, TEXT("LGPrimaryDialogue"), &Z_Registration_Info_UScriptStruct_LGPrimaryDialogue, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLGPrimaryDialogue), 71634215U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_LGDialogueTypes_h_2069535868(TEXT("/Script/LGDialogueSystem"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_LGDialogueTypes_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_LGDialogueTypes_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
