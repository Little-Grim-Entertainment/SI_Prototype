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
	LGDIALOGUESYSTEM_API UClass* Z_Construct_UClass_ULGDialogueDataAsset_NoRegister();
	LGDIALOGUESYSTEM_API UScriptStruct* Z_Construct_UScriptStruct_FLGCharacterDialogue();
	LGDIALOGUESYSTEM_API UScriptStruct* Z_Construct_UScriptStruct_FLGDialogueURL();
	UPackage* Z_Construct_UPackage__Script_LGDialogueSystem();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LGDialogueURL;
class UScriptStruct* FLGDialogueURL::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LGDialogueURL.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LGDialogueURL.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLGDialogueURL, (UObject*)Z_Construct_UPackage__Script_LGDialogueSystem(), TEXT("LGDialogueURL"));
	}
	return Z_Registration_Info_UScriptStruct_LGDialogueURL.OuterSingleton;
}
template<> LGDIALOGUESYSTEM_API UScriptStruct* StaticStruct<FLGDialogueURL>()
{
	return FLGDialogueURL::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLGDialogueURL_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_URL_Name_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_URL_Name;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_URL_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_URL;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGDialogueURL_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/LGDialogueTypes.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLGDialogueURL_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLGDialogueURL>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGDialogueURL_Statics::NewProp_URL_Name_MetaData[] = {
		{ "Category", "LGDialogueURL" },
		{ "ModuleRelativePath", "Public/LGDialogueTypes.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLGDialogueURL_Statics::NewProp_URL_Name = { "URL_Name", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLGDialogueURL, URL_Name), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGDialogueURL_Statics::NewProp_URL_Name_MetaData), Z_Construct_UScriptStruct_FLGDialogueURL_Statics::NewProp_URL_Name_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGDialogueURL_Statics::NewProp_URL_MetaData[] = {
		{ "Category", "LGDialogueURL" },
		{ "ModuleRelativePath", "Public/LGDialogueTypes.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLGDialogueURL_Statics::NewProp_URL = { "URL", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLGDialogueURL, URL), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGDialogueURL_Statics::NewProp_URL_MetaData), Z_Construct_UScriptStruct_FLGDialogueURL_Statics::NewProp_URL_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLGDialogueURL_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGDialogueURL_Statics::NewProp_URL_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGDialogueURL_Statics::NewProp_URL,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLGDialogueURL_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LGDialogueSystem,
		nullptr,
		&NewStructOps,
		"LGDialogueURL",
		Z_Construct_UScriptStruct_FLGDialogueURL_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGDialogueURL_Statics::PropPointers),
		sizeof(FLGDialogueURL),
		alignof(FLGDialogueURL),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGDialogueURL_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLGDialogueURL_Statics::Struct_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGDialogueURL_Statics::PropPointers) < 2048);
	UScriptStruct* Z_Construct_UScriptStruct_FLGDialogueURL()
	{
		if (!Z_Registration_Info_UScriptStruct_LGDialogueURL.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LGDialogueURL.InnerSingleton, Z_Construct_UScriptStruct_FLGDialogueURL_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LGDialogueURL.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LGCharacterDialogue;
class UScriptStruct* FLGCharacterDialogue::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LGCharacterDialogue.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LGCharacterDialogue.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLGCharacterDialogue, (UObject*)Z_Construct_UPackage__Script_LGDialogueSystem(), TEXT("LGCharacterDialogue"));
	}
	return Z_Registration_Info_UScriptStruct_LGCharacterDialogue.OuterSingleton;
}
template<> LGDIALOGUESYSTEM_API UScriptStruct* StaticStruct<FLGCharacterDialogue>()
{
	return FLGCharacterDialogue::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CharacterName_MetaData[];
#endif
		static const UECodeGen_Private::FTextPropertyParams NewProp_CharacterName;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_DialogueData_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DialogueData_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_DialogueData;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/LGDialogueTypes.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLGCharacterDialogue>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::NewProp_CharacterName_MetaData[] = {
		{ "Category", "LGCharacterDialogue" },
		{ "ModuleRelativePath", "Public/LGDialogueTypes.h" },
	};
#endif
	const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::NewProp_CharacterName = { "CharacterName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLGCharacterDialogue, CharacterName), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::NewProp_CharacterName_MetaData), Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::NewProp_CharacterName_MetaData) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::NewProp_DialogueData_Inner = { "DialogueData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_ULGDialogueDataAsset_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::NewProp_DialogueData_MetaData[] = {
		{ "Category", "LGCharacterDialogue" },
		{ "ModuleRelativePath", "Public/LGDialogueTypes.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::NewProp_DialogueData = { "DialogueData", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLGCharacterDialogue, DialogueData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::NewProp_DialogueData_MetaData), Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::NewProp_DialogueData_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::NewProp_CharacterName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::NewProp_DialogueData_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::NewProp_DialogueData,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LGDialogueSystem,
		nullptr,
		&NewStructOps,
		"LGCharacterDialogue",
		Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::PropPointers),
		sizeof(FLGCharacterDialogue),
		alignof(FLGCharacterDialogue),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::Struct_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::PropPointers) < 2048);
	UScriptStruct* Z_Construct_UScriptStruct_FLGCharacterDialogue()
	{
		if (!Z_Registration_Info_UScriptStruct_LGCharacterDialogue.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LGCharacterDialogue.InnerSingleton, Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LGCharacterDialogue.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_LGDialogueTypes_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_LGDialogueTypes_h_Statics::ScriptStructInfo[] = {
		{ FLGDialogueURL::StaticStruct, Z_Construct_UScriptStruct_FLGDialogueURL_Statics::NewStructOps, TEXT("LGDialogueURL"), &Z_Registration_Info_UScriptStruct_LGDialogueURL, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLGDialogueURL), 4085560945U) },
		{ FLGCharacterDialogue::StaticStruct, Z_Construct_UScriptStruct_FLGCharacterDialogue_Statics::NewStructOps, TEXT("LGCharacterDialogue"), &Z_Registration_Info_UScriptStruct_LGCharacterDialogue, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLGCharacterDialogue), 4173466436U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_LGDialogueTypes_h_2716185367(TEXT("/Script/LGDialogueSystem"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_LGDialogueTypes_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_LGDialogueTypes_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
