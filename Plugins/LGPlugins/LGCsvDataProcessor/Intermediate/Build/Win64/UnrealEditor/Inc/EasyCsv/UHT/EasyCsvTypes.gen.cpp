// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "EasyCsvTypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEasyCsvTypes() {}
// Cross Module References
	EASYCSV_API UScriptStruct* Z_Construct_UScriptStruct_FEasyCsvInfo();
	EASYCSV_API UScriptStruct* Z_Construct_UScriptStruct_FEasyCsvStringValueArray();
	UPackage* Z_Construct_UPackage__Script_EasyCsv();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_EasyCsvStringValueArray;
class UScriptStruct* FEasyCsvStringValueArray::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_EasyCsvStringValueArray.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_EasyCsvStringValueArray.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEasyCsvStringValueArray, (UObject*)Z_Construct_UPackage__Script_EasyCsv(), TEXT("EasyCsvStringValueArray"));
	}
	return Z_Registration_Info_UScriptStruct_EasyCsvStringValueArray.OuterSingleton;
}
template<> EASYCSV_API UScriptStruct* StaticStruct<FEasyCsvStringValueArray>()
{
	return FEasyCsvStringValueArray::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FStrPropertyParams NewProp_StringValues_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_StringValues_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_StringValues;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/EasyCsvTypes.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEasyCsvStringValueArray>();
	}
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::NewProp_StringValues_Inner = { "StringValues", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::NewProp_StringValues_MetaData[] = {
		{ "Category", "easyCSV" },
		{ "ModuleRelativePath", "Public/EasyCsvTypes.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::NewProp_StringValues = { "StringValues", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEasyCsvStringValueArray, StringValues), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::NewProp_StringValues_MetaData), Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::NewProp_StringValues_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::NewProp_StringValues_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::NewProp_StringValues,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_EasyCsv,
		nullptr,
		&NewStructOps,
		"EasyCsvStringValueArray",
		Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::PropPointers),
		sizeof(FEasyCsvStringValueArray),
		alignof(FEasyCsvStringValueArray),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::Struct_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::PropPointers) < 2048);
	UScriptStruct* Z_Construct_UScriptStruct_FEasyCsvStringValueArray()
	{
		if (!Z_Registration_Info_UScriptStruct_EasyCsvStringValueArray.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_EasyCsvStringValueArray.InnerSingleton, Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_EasyCsvStringValueArray.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_EasyCsvInfo;
class UScriptStruct* FEasyCsvInfo::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_EasyCsvInfo.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_EasyCsvInfo.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEasyCsvInfo, (UObject*)Z_Construct_UPackage__Script_EasyCsv(), TEXT("EasyCsvInfo"));
	}
	return Z_Registration_Info_UScriptStruct_EasyCsvInfo.OuterSingleton;
}
template<> EASYCSV_API UScriptStruct* StaticStruct<FEasyCsvInfo>()
{
	return FEasyCsvInfo::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FEasyCsvInfo_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FStructPropertyParams NewProp_CSV_Map_ValueProp;
		static const UECodeGen_Private::FNamePropertyParams NewProp_CSV_Map_Key_KeyProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CSV_Map_MetaData[];
#endif
		static const UECodeGen_Private::FMapPropertyParams NewProp_CSV_Map;
		static const UECodeGen_Private::FNamePropertyParams NewProp_CSV_Keys_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CSV_Keys_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_CSV_Keys;
		static const UECodeGen_Private::FStrPropertyParams NewProp_CSV_Headers_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CSV_Headers_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_CSV_Headers;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/EasyCsvTypes.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEasyCsvInfo>();
	}
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map_ValueProp = { "CSV_Map", nullptr, (EPropertyFlags)0x0000000000020001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UScriptStruct_FEasyCsvStringValueArray, METADATA_PARAMS(0, nullptr) }; // 1661058582
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map_Key_KeyProp = { "CSV_Map_Key", nullptr, (EPropertyFlags)0x0000000000020001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map_MetaData[] = {
		{ "Category", "easyCSV" },
		{ "ModuleRelativePath", "Public/EasyCsvTypes.h" },
	};
#endif
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map = { "CSV_Map", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEasyCsvInfo, CSV_Map), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map_MetaData), Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map_MetaData) }; // 1661058582
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Keys_Inner = { "CSV_Keys", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Keys_MetaData[] = {
		{ "Category", "easyCSV" },
		{ "ModuleRelativePath", "Public/EasyCsvTypes.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Keys = { "CSV_Keys", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEasyCsvInfo, CSV_Keys), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Keys_MetaData), Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Keys_MetaData) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Headers_Inner = { "CSV_Headers", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Headers_MetaData[] = {
		{ "Category", "easyCSV" },
		{ "ModuleRelativePath", "Public/EasyCsvTypes.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Headers = { "CSV_Headers", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEasyCsvInfo, CSV_Headers), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Headers_MetaData), Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Headers_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Keys_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Keys,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Headers_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Headers,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_EasyCsv,
		nullptr,
		&NewStructOps,
		"EasyCsvInfo",
		Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::PropPointers),
		sizeof(FEasyCsvInfo),
		alignof(FEasyCsvInfo),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::Struct_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::PropPointers) < 2048);
	UScriptStruct* Z_Construct_UScriptStruct_FEasyCsvInfo()
	{
		if (!Z_Registration_Info_UScriptStruct_EasyCsvInfo.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_EasyCsvInfo.InnerSingleton, Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_EasyCsvInfo.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsvTypes_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsvTypes_h_Statics::ScriptStructInfo[] = {
		{ FEasyCsvStringValueArray::StaticStruct, Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::NewStructOps, TEXT("EasyCsvStringValueArray"), &Z_Registration_Info_UScriptStruct_EasyCsvStringValueArray, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEasyCsvStringValueArray), 1661058582U) },
		{ FEasyCsvInfo::StaticStruct, Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewStructOps, TEXT("EasyCsvInfo"), &Z_Registration_Info_UScriptStruct_EasyCsvInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEasyCsvInfo), 2071183195U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsvTypes_h_4207742590(TEXT("/Script/EasyCsv"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsvTypes_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsvTypes_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
