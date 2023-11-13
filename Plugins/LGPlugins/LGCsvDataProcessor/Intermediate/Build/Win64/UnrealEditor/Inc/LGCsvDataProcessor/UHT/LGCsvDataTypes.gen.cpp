// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LGCsvDataProcessor/Public/LGCsvDataTypes.h"
#include "EasyCsv.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLGCsvDataTypes() {}
// Cross Module References
	EASYCSV_API UScriptStruct* Z_Construct_UScriptStruct_FEasyCsvInfo();
	LGCSVDATAPROCESSOR_API UScriptStruct* Z_Construct_UScriptStruct_FLGCsvInfo();
	LGCSVDATAPROCESSOR_API UScriptStruct* Z_Construct_UScriptStruct_FLGCsvStrings();
	UPackage* Z_Construct_UPackage__Script_LGCsvDataProcessor();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LGCsvStrings;
class UScriptStruct* FLGCsvStrings::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LGCsvStrings.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LGCsvStrings.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLGCsvStrings, (UObject*)Z_Construct_UPackage__Script_LGCsvDataProcessor(), TEXT("LGCsvStrings"));
	}
	return Z_Registration_Info_UScriptStruct_LGCsvStrings.OuterSingleton;
}
template<> LGCSVDATAPROCESSOR_API UScriptStruct* StaticStruct<FLGCsvStrings>()
{
	return FLGCsvStrings::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLGCsvStrings_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGCsvStrings_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LGCsvDataTypes.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLGCsvStrings_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLGCsvStrings>();
	}
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLGCsvStrings_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LGCsvDataProcessor,
		nullptr,
		&NewStructOps,
		"LGCsvStrings",
		nullptr,
		0,
		sizeof(FLGCsvStrings),
		alignof(FLGCsvStrings),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGCsvStrings_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLGCsvStrings_Statics::Struct_MetaDataParams)
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLGCsvStrings()
	{
		if (!Z_Registration_Info_UScriptStruct_LGCsvStrings.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LGCsvStrings.InnerSingleton, Z_Construct_UScriptStruct_FLGCsvStrings_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LGCsvStrings.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LGCsvInfo;
class UScriptStruct* FLGCsvInfo::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LGCsvInfo.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LGCsvInfo.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLGCsvInfo, (UObject*)Z_Construct_UPackage__Script_LGCsvDataProcessor(), TEXT("LGCsvInfo"));
	}
	return Z_Registration_Info_UScriptStruct_LGCsvInfo.OuterSingleton;
}
template<> LGCSVDATAPROCESSOR_API UScriptStruct* StaticStruct<FLGCsvInfo>()
{
	return FLGCsvInfo::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLGCsvInfo_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FStructPropertyParams NewProp_PrimaryDialogues_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PrimaryDialogues_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_PrimaryDialogues;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CSVToWrite_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_CSVToWrite;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CSVInfoResults_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CSVInfoResults;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ExportKeys_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ExportKeys_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ExportKeys;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGCsvInfo_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/LGCsvDataTypes.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLGCsvInfo>();
	}
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_PrimaryDialogues_Inner = { "PrimaryDialogues", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FLGCsvStrings, METADATA_PARAMS(0, nullptr) }; // 805924169
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_PrimaryDialogues_MetaData[] = {
		{ "ModuleRelativePath", "Public/LGCsvDataTypes.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_PrimaryDialogues = { "PrimaryDialogues", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLGCsvInfo, PrimaryDialogues), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_PrimaryDialogues_MetaData), Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_PrimaryDialogues_MetaData) }; // 805924169
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_CSVToWrite_MetaData[] = {
		{ "ModuleRelativePath", "Public/LGCsvDataTypes.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_CSVToWrite = { "CSVToWrite", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLGCsvInfo, CSVToWrite), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_CSVToWrite_MetaData), Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_CSVToWrite_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_CSVInfoResults_MetaData[] = {
		{ "ModuleRelativePath", "Public/LGCsvDataTypes.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_CSVInfoResults = { "CSVInfoResults", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLGCsvInfo, CSVInfoResults), Z_Construct_UScriptStruct_FEasyCsvInfo, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_CSVInfoResults_MetaData), Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_CSVInfoResults_MetaData) }; // 795079476
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_ExportKeys_Inner = { "ExportKeys", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_ExportKeys_MetaData[] = {
		{ "ModuleRelativePath", "Public/LGCsvDataTypes.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_ExportKeys = { "ExportKeys", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLGCsvInfo, ExportKeys), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_ExportKeys_MetaData), Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_ExportKeys_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLGCsvInfo_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_PrimaryDialogues_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_PrimaryDialogues,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_CSVToWrite,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_CSVInfoResults,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_ExportKeys_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewProp_ExportKeys,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLGCsvInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LGCsvDataProcessor,
		nullptr,
		&NewStructOps,
		"LGCsvInfo",
		Z_Construct_UScriptStruct_FLGCsvInfo_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGCsvInfo_Statics::PropPointers),
		sizeof(FLGCsvInfo),
		alignof(FLGCsvInfo),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGCsvInfo_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLGCsvInfo_Statics::Struct_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGCsvInfo_Statics::PropPointers) < 2048);
	UScriptStruct* Z_Construct_UScriptStruct_FLGCsvInfo()
	{
		if (!Z_Registration_Info_UScriptStruct_LGCsvInfo.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LGCsvInfo.InnerSingleton, Z_Construct_UScriptStruct_FLGCsvInfo_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LGCsvInfo.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataTypes_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataTypes_h_Statics::ScriptStructInfo[] = {
		{ FLGCsvStrings::StaticStruct, Z_Construct_UScriptStruct_FLGCsvStrings_Statics::NewStructOps, TEXT("LGCsvStrings"), &Z_Registration_Info_UScriptStruct_LGCsvStrings, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLGCsvStrings), 805924169U) },
		{ FLGCsvInfo::StaticStruct, Z_Construct_UScriptStruct_FLGCsvInfo_Statics::NewStructOps, TEXT("LGCsvInfo"), &Z_Registration_Info_UScriptStruct_LGCsvInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLGCsvInfo), 3551454201U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataTypes_h_2837279099(TEXT("/Script/LGCsvDataProcessor"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataTypes_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataTypes_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
