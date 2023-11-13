// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "EasyCsv.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEasyCsv() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FQuat();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
	EASYCSV_API UClass* Z_Construct_UClass_UEasyCsv();
	EASYCSV_API UClass* Z_Construct_UClass_UEasyCsv_NoRegister();
	EASYCSV_API UScriptStruct* Z_Construct_UScriptStruct_FEasyCsvInfo();
	EASYCSV_API UScriptStruct* Z_Construct_UScriptStruct_FEasyCsvStringValueArray();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
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
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
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
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
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
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEasyCsvInfo>();
	}
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map_ValueProp = { "CSV_Map", nullptr, (EPropertyFlags)0x0000000000020001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UScriptStruct_FEasyCsvStringValueArray, METADATA_PARAMS(0, nullptr) }; // 3498439254
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map_Key_KeyProp = { "CSV_Map_Key", nullptr, (EPropertyFlags)0x0000000000020001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map_MetaData[] = {
		{ "Category", "easyCSV" },
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
	};
#endif
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map = { "CSV_Map", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEasyCsvInfo, CSV_Map), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map_MetaData), Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Map_MetaData) }; // 3498439254
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Keys_Inner = { "CSV_Keys", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Keys_MetaData[] = {
		{ "Category", "easyCSV" },
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Keys = { "CSV_Keys", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEasyCsvInfo, CSV_Keys), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Keys_MetaData), Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Keys_MetaData) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Headers_Inner = { "CSV_Headers", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewProp_CSV_Headers_MetaData[] = {
		{ "Category", "easyCSV" },
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
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
		EStructFlags(0x00000001),
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
	DEFINE_FUNCTION(UEasyCsv::execConvertQuatStringToRotatorArray)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FRotator>*)Z_Param__Result=UEasyCsv::ConvertQuatStringToRotatorArray(Z_Param_InString);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execConvertQuatStringToRotator)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FRotator*)Z_Param__Result=UEasyCsv::ConvertQuatStringToRotator(Z_Param_InString);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execConvertStringToQuatArray)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FQuat>*)Z_Param__Result=UEasyCsv::ConvertStringToQuatArray(Z_Param_InString);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execConvertStringToQuat)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FQuat*)Z_Param__Result=UEasyCsv::ConvertStringToQuat(Z_Param_InString);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execConvertStringToRotatorArray)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FRotator>*)Z_Param__Result=UEasyCsv::ConvertStringToRotatorArray(Z_Param_InString);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execConvertStringToRotator)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FRotator*)Z_Param__Result=UEasyCsv::ConvertStringToRotator(Z_Param_InString);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execGetFTextComponentsFromRepresentativeFString)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_Namespace);
		P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_Key);
		P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_SourceString);
		P_FINISH;
		P_NATIVE_BEGIN;
		UEasyCsv::GetFTextComponentsFromRepresentativeFString(Z_Param_InString,Z_Param_Out_Namespace,Z_Param_Out_Key,Z_Param_Out_SourceString);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execEscapeCharacters)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=UEasyCsv::EscapeCharacters(Z_Param_InString);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execReplaceEscapedCharacters)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=UEasyCsv::ReplaceEscapedCharacters(Z_Param_InString);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execDoesStringRepresentContainer)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UEasyCsv::DoesStringRepresentContainer(Z_Param_InString);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execMakeCsvInfoStructFromFile)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InPath);
		P_GET_STRUCT_REF(FEasyCsvInfo,Z_Param_Out_OutCsvInfo);
		P_GET_UBOOL(Z_Param_ParseHeaders);
		P_GET_UBOOL(Z_Param_ParseKeys);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UEasyCsv::MakeCsvInfoStructFromFile(Z_Param_InPath,Z_Param_Out_OutCsvInfo,Z_Param_ParseHeaders,Z_Param_ParseKeys);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execMakeCsvInfoStructFromString)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_GET_STRUCT_REF(FEasyCsvInfo,Z_Param_Out_OutCsvInfo);
		P_GET_UBOOL(Z_Param_ParseHeaders);
		P_GET_UBOOL(Z_Param_ParseKeys);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UEasyCsv::MakeCsvInfoStructFromString(Z_Param_InString,Z_Param_Out_OutCsvInfo,Z_Param_ParseHeaders,Z_Param_ParseKeys);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execGetColumnCount)
	{
		P_GET_STRUCT_REF(FEasyCsvInfo,Z_Param_Out_CSV_Info);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UEasyCsv::GetColumnCount(Z_Param_Out_CSV_Info);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execGetRowCount)
	{
		P_GET_STRUCT_REF(FEasyCsvInfo,Z_Param_Out_CSV_Info);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UEasyCsv::GetRowCount(Z_Param_Out_CSV_Info);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execGetMapKeyIndex)
	{
		P_GET_STRUCT_REF(FEasyCsvInfo,Z_Param_Out_CSV_Info);
		P_GET_PROPERTY(FNameProperty,Z_Param_Key);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UEasyCsv::GetMapKeyIndex(Z_Param_Out_CSV_Info,Z_Param_Key);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execGetMapHeaders)
	{
		P_GET_STRUCT_REF(FEasyCsvInfo,Z_Param_Out_CSV_Info);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FString>*)Z_Param__Result=UEasyCsv::GetMapHeaders(Z_Param_Out_CSV_Info);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execGetMapKeys)
	{
		P_GET_STRUCT_REF(FEasyCsvInfo,Z_Param_Out_CSV_Info);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FName>*)Z_Param__Result=UEasyCsv::GetMapKeys(Z_Param_Out_CSV_Info);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execGetRowValueAsString)
	{
		P_GET_STRUCT_REF(FEasyCsvInfo,Z_Param_Out_CSV_Info);
		P_GET_PROPERTY(FStrProperty,Z_Param_ColumnName);
		P_GET_PROPERTY(FNameProperty,Z_Param_RowKey);
		P_GET_UBOOL_REF(Z_Param_Out_Success);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=UEasyCsv::GetRowValueAsString(Z_Param_Out_CSV_Info,Z_Param_ColumnName,Z_Param_RowKey,Z_Param_Out_Success);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execGetRowAsStringArray)
	{
		P_GET_STRUCT_REF(FEasyCsvInfo,Z_Param_Out_CSV_Info);
		P_GET_PROPERTY(FNameProperty,Z_Param_RowKey);
		P_GET_UBOOL_REF(Z_Param_Out_Success);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FString>*)Z_Param__Result=UEasyCsv::GetRowAsStringArray(Z_Param_Out_CSV_Info,Z_Param_RowKey,Z_Param_Out_Success);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execGetColumnAsStringArray)
	{
		P_GET_STRUCT_REF(FEasyCsvInfo,Z_Param_Out_CSV_Info);
		P_GET_PROPERTY(FStrProperty,Z_Param_ColumnName);
		P_GET_UBOOL_REF(Z_Param_Out_Success);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FString>*)Z_Param__Result=UEasyCsv::GetColumnAsStringArray(Z_Param_Out_CSV_Info,Z_Param_ColumnName,Z_Param_Out_Success);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execLoadStringFromLocalFile)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InPath);
		P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutString);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UEasyCsv::LoadStringFromLocalFile(Z_Param_InPath,Z_Param_Out_OutString);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execSaveStringToFileWithFullPath)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_GET_PROPERTY(FStrProperty,Z_Param_InFullPath);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UEasyCsv::SaveStringToFileWithFullPath(Z_Param_InString,Z_Param_InFullPath);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UEasyCsv::execSaveStringToFile)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_GET_PROPERTY(FStrProperty,Z_Param_InDirectory);
		P_GET_PROPERTY(FStrProperty,Z_Param_Filename);
		P_GET_PROPERTY(FStrProperty,Z_Param_Extension);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UEasyCsv::SaveStringToFile(Z_Param_InString,Z_Param_InDirectory,Z_Param_Filename,Z_Param_Extension);
		P_NATIVE_END;
	}
	void UEasyCsv::StaticRegisterNativesUEasyCsv()
	{
		UClass* Class = UEasyCsv::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ConvertQuatStringToRotator", &UEasyCsv::execConvertQuatStringToRotator },
			{ "ConvertQuatStringToRotatorArray", &UEasyCsv::execConvertQuatStringToRotatorArray },
			{ "ConvertStringToQuat", &UEasyCsv::execConvertStringToQuat },
			{ "ConvertStringToQuatArray", &UEasyCsv::execConvertStringToQuatArray },
			{ "ConvertStringToRotator", &UEasyCsv::execConvertStringToRotator },
			{ "ConvertStringToRotatorArray", &UEasyCsv::execConvertStringToRotatorArray },
			{ "DoesStringRepresentContainer", &UEasyCsv::execDoesStringRepresentContainer },
			{ "EscapeCharacters", &UEasyCsv::execEscapeCharacters },
			{ "GetColumnAsStringArray", &UEasyCsv::execGetColumnAsStringArray },
			{ "GetColumnCount", &UEasyCsv::execGetColumnCount },
			{ "GetFTextComponentsFromRepresentativeFString", &UEasyCsv::execGetFTextComponentsFromRepresentativeFString },
			{ "GetMapHeaders", &UEasyCsv::execGetMapHeaders },
			{ "GetMapKeyIndex", &UEasyCsv::execGetMapKeyIndex },
			{ "GetMapKeys", &UEasyCsv::execGetMapKeys },
			{ "GetRowAsStringArray", &UEasyCsv::execGetRowAsStringArray },
			{ "GetRowCount", &UEasyCsv::execGetRowCount },
			{ "GetRowValueAsString", &UEasyCsv::execGetRowValueAsString },
			{ "LoadStringFromLocalFile", &UEasyCsv::execLoadStringFromLocalFile },
			{ "MakeCsvInfoStructFromFile", &UEasyCsv::execMakeCsvInfoStructFromFile },
			{ "MakeCsvInfoStructFromString", &UEasyCsv::execMakeCsvInfoStructFromString },
			{ "ReplaceEscapedCharacters", &UEasyCsv::execReplaceEscapedCharacters },
			{ "SaveStringToFile", &UEasyCsv::execSaveStringToFile },
			{ "SaveStringToFileWithFullPath", &UEasyCsv::execSaveStringToFileWithFullPath },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics
	{
		struct EasyCsv_eventConvertQuatStringToRotator_Parms
		{
			FString InString;
			FRotator ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InString_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InString;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::NewProp_InString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventConvertQuatStringToRotator_Parms, InString), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::NewProp_InString_MetaData), Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::NewProp_InString_MetaData) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventConvertQuatStringToRotator_Parms, ReturnValue), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::NewProp_InString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Conversion" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Convert a string that represents an FQuat into an FRotator.\n\x09 * @return FRotator\n\x09 * @param InString An FQuat expressed as a string (ex: \"X=0 Y=0 Z=0 W=0\").\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Convert a string that represents an FQuat into an FRotator.\n@return FRotator\n@param InString An FQuat expressed as a string (ex: \"X=0 Y=0 Z=0 W=0\")." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "ConvertQuatStringToRotator", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::EasyCsv_eventConvertQuatStringToRotator_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::EasyCsv_eventConvertQuatStringToRotator_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics
	{
		struct EasyCsv_eventConvertQuatStringToRotatorArray_Parms
		{
			FString InString;
			TArray<FRotator> ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InString_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InString;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::NewProp_InString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventConvertQuatStringToRotatorArray_Parms, InString), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::NewProp_InString_MetaData), Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::NewProp_InString_MetaData) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventConvertQuatStringToRotatorArray_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::NewProp_InString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Conversion" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Convert a string into an array of FRotators.\n\x09 * @return Array of FRotator\n\x09 * @param InString An array of FQuats expressed as a string (ex: \"(\"X=0 Y=0 Z=0 W=0\",\"X=0 Y=0 Z=0 W=0\",\"X=0 Y=0 Z=0 W=0\")\").\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Convert a string into an array of FRotators.\n@return Array of FRotator\n@param InString An array of FQuats expressed as a string (ex: \"(\"X=0 Y=0 Z=0 W=0\",\"X=0 Y=0 Z=0 W=0\",\"X=0 Y=0 Z=0 W=0\")\")." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "ConvertQuatStringToRotatorArray", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::EasyCsv_eventConvertQuatStringToRotatorArray_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::EasyCsv_eventConvertQuatStringToRotatorArray_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics
	{
		struct EasyCsv_eventConvertStringToQuat_Parms
		{
			FString InString;
			FQuat ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InString_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InString;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::NewProp_InString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventConvertStringToQuat_Parms, InString), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::NewProp_InString_MetaData), Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::NewProp_InString_MetaData) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventConvertStringToQuat_Parms, ReturnValue), Z_Construct_UScriptStruct_FQuat, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::NewProp_InString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Conversion" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Convert a string into an FQuat.\n\x09 * @return FQuat\n\x09 * @param InString An FQuat expressed as a string (ex: \"X=0 Y=0 Z=0 W=0\"). ConvertQuatStringToRotator can convert quaternions to FRotators.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Convert a string into an FQuat.\n@return FQuat\n@param InString An FQuat expressed as a string (ex: \"X=0 Y=0 Z=0 W=0\"). ConvertQuatStringToRotator can convert quaternions to FRotators." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "ConvertStringToQuat", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::EasyCsv_eventConvertStringToQuat_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::EasyCsv_eventConvertStringToQuat_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics
	{
		struct EasyCsv_eventConvertStringToQuatArray_Parms
		{
			FString InString;
			TArray<FQuat> ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InString_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InString;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::NewProp_InString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventConvertStringToQuatArray_Parms, InString), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::NewProp_InString_MetaData), Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::NewProp_InString_MetaData) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FQuat, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventConvertStringToQuatArray_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::NewProp_InString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Conversion" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Convert a string into an array of FQuats.\n\x09 * @return Array of FQuat\n\x09 * @param InString An array of FQuats expressed as a string (ex: \"(\"X=0 Y=0 Z=0 W=0\",\"X=0 Y=0 Z=0 W=0\",\"X=0 Y=0 Z=0 W=0\")\"). ConvertQuatStringToRotatorArray can convert quaternions to FRotators.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Convert a string into an array of FQuats.\n@return Array of FQuat\n@param InString An array of FQuats expressed as a string (ex: \"(\"X=0 Y=0 Z=0 W=0\",\"X=0 Y=0 Z=0 W=0\",\"X=0 Y=0 Z=0 W=0\")\"). ConvertQuatStringToRotatorArray can convert quaternions to FRotators." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "ConvertStringToQuatArray", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::EasyCsv_eventConvertStringToQuatArray_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::EasyCsv_eventConvertStringToQuatArray_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics
	{
		struct EasyCsv_eventConvertStringToRotator_Parms
		{
			FString InString;
			FRotator ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_InString;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventConvertStringToRotator_Parms, InString), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventConvertStringToRotator_Parms, ReturnValue), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::NewProp_InString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Conversion" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Convert a string into an FRotator. Supports more formats than the built-in engine conversion.\n\x09 * @return FRotator\n\x09 * @param InString A rotator expressed as a string (ex: \"P=0 Y=0 R=0\" or \"Pitch=0 Yaw=0 Roll=0\"). Does not work for Quaternions expressed as string (use ConvertStringToQuat or ConvertQuatStringToRotator for that).\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Convert a string into an FRotator. Supports more formats than the built-in engine conversion.\n@return FRotator\n@param InString A rotator expressed as a string (ex: \"P=0 Y=0 R=0\" or \"Pitch=0 Yaw=0 Roll=0\"). Does not work for Quaternions expressed as string (use ConvertStringToQuat or ConvertQuatStringToRotator for that)." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "ConvertStringToRotator", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::EasyCsv_eventConvertStringToRotator_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14822401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::EasyCsv_eventConvertStringToRotator_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics
	{
		struct EasyCsv_eventConvertStringToRotatorArray_Parms
		{
			FString InString;
			TArray<FRotator> ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InString_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InString;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::NewProp_InString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventConvertStringToRotatorArray_Parms, InString), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::NewProp_InString_MetaData), Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::NewProp_InString_MetaData) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventConvertStringToRotatorArray_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::NewProp_InString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Conversion" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Converts a string into an array of FRotators. Supports more formats than the built-in engine conversion.\n\x09 * @return Array of FRotators\n\x09 * @param InString An array of rotators expressed as a string (ex: \"(\"P=0 Y=0 R=0\",\"P=1 Y=1 R=1\",\"P=2 Y=2 R=2\")\"). Does not work for Quaternions expressed as string (use ConvertStringToQuatArray or ConvertQuatStringToRotatorArray for that).\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Converts a string into an array of FRotators. Supports more formats than the built-in engine conversion.\n@return Array of FRotators\n@param InString An array of rotators expressed as a string (ex: \"(\"P=0 Y=0 R=0\",\"P=1 Y=1 R=1\",\"P=2 Y=2 R=2\")\"). Does not work for Quaternions expressed as string (use ConvertStringToQuatArray or ConvertQuatStringToRotatorArray for that)." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "ConvertStringToRotatorArray", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::EasyCsv_eventConvertStringToRotatorArray_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::EasyCsv_eventConvertStringToRotatorArray_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics
	{
		struct EasyCsv_eventDoesStringRepresentContainer_Parms
		{
			FString InString;
			bool ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_InString;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventDoesStringRepresentContainer_Parms, InString), METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((EasyCsv_eventDoesStringRepresentContainer_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EasyCsv_eventDoesStringRepresentContainer_Parms), &Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::NewProp_InString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|String" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns true if the specified string represents a struct, array, map or set.\n\x09 * @return bool\n\x09 * @param InString A string that may represent a container. If you've already parsed a CSV and have nested structs, arrays, maps or sets in specific cells this method will detect them.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns true if the specified string represents a struct, array, map or set.\n@return bool\n@param InString A string that may represent a container. If you've already parsed a CSV and have nested structs, arrays, maps or sets in specific cells this method will detect them." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "DoesStringRepresentContainer", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::EasyCsv_eventDoesStringRepresentContainer_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::EasyCsv_eventDoesStringRepresentContainer_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics
	{
		struct EasyCsv_eventEscapeCharacters_Parms
		{
			FString InString;
			FString ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InString_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InString;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::NewProp_InString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventEscapeCharacters_Parms, InString), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::NewProp_InString_MetaData), Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::NewProp_InString_MetaData) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventEscapeCharacters_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::NewProp_InString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|String" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns an const FString& with all characters that could be escaped turned into escaped characters ('\\\"', '\\r', '\\n', etc)\n\x09 * @return const FString& A string with all escaped characters converted into standard characters ('\\\"', '\\r', '\\n', etc)\n\x09 * @param InString A string that may contain escaped characters ('\\\"', '\\r', '\\n', etc)\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns an const FString& with all characters that could be escaped turned into escaped characters ('\\\"', '\\r', '\\n', etc)\n@return const FString& A string with all escaped characters converted into standard characters ('\\\"', '\\r', '\\n', etc)\n@param InString A string that may contain escaped characters ('\\\"', '\\r', '\\n', etc)" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "EscapeCharacters", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::EasyCsv_eventEscapeCharacters_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::EasyCsv_eventEscapeCharacters_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_EscapeCharacters()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_EscapeCharacters_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics
	{
		struct EasyCsv_eventGetColumnAsStringArray_Parms
		{
			FEasyCsvInfo CSV_Info;
			FString ColumnName;
			bool Success;
			TArray<FString> ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CSV_Info_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CSV_Info;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ColumnName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_ColumnName;
		static void NewProp_Success_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_Success;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_CSV_Info_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_CSV_Info = { "CSV_Info", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetColumnAsStringArray_Parms, CSV_Info), Z_Construct_UScriptStruct_FEasyCsvInfo, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_CSV_Info_MetaData), Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_CSV_Info_MetaData) }; // 795079476
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_ColumnName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_ColumnName = { "ColumnName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetColumnAsStringArray_Parms, ColumnName), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_ColumnName_MetaData), Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_ColumnName_MetaData) };
	void Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_Success_SetBit(void* Obj)
	{
		((EasyCsv_eventGetColumnAsStringArray_Parms*)Obj)->Success = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_Success = { "Success", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EasyCsv_eventGetColumnAsStringArray_Parms), &Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_Success_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetColumnAsStringArray_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_CSV_Info,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_ColumnName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_Success,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Post-Parse Operations" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns all values in a column, given the name of said column in the CSV, as an array of strings.\n\x09 * @return All values in a column, given the name of said column in the CSV, as an array of strings\n\x09 * @param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString.\n\x09 * @param ColumnName The name of the column in the CSV\n\x09 * @param Success Whether or not the column could be found by name\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns all values in a column, given the name of said column in the CSV, as an array of strings.\n@return All values in a column, given the name of said column in the CSV, as an array of strings\n@param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString.\n@param ColumnName The name of the column in the CSV\n@param Success Whether or not the column could be found by name" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "GetColumnAsStringArray", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::EasyCsv_eventGetColumnAsStringArray_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::EasyCsv_eventGetColumnAsStringArray_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics
	{
		struct EasyCsv_eventGetColumnCount_Parms
		{
			FEasyCsvInfo CSV_Info;
			int32 ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CSV_Info_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CSV_Info;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::NewProp_CSV_Info_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::NewProp_CSV_Info = { "CSV_Info", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetColumnCount_Parms, CSV_Info), Z_Construct_UScriptStruct_FEasyCsvInfo, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::NewProp_CSV_Info_MetaData), Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::NewProp_CSV_Info_MetaData) }; // 795079476
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetColumnCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::NewProp_CSV_Info,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Post-Parse Operations" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns the number of columns in a given CSV, not counting the Row Keys.\n\x09 * If no valid CSV_Info struct is passed in, this will return -1.\n\x09 * @return An integer reflecting the number of columns in a given CSV_Info struct's CSV map.\n\x09 * @param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns the number of columns in a given CSV, not counting the Row Keys.\nIf no valid CSV_Info struct is passed in, this will return -1.\n@return An integer reflecting the number of columns in a given CSV_Info struct's CSV map.\n@param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "GetColumnCount", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::EasyCsv_eventGetColumnCount_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::EasyCsv_eventGetColumnCount_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_GetColumnCount()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_GetColumnCount_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics
	{
		struct EasyCsv_eventGetFTextComponentsFromRepresentativeFString_Parms
		{
			FString InString;
			FString Namespace;
			FString Key;
			FString SourceString;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_InString;
		static const UECodeGen_Private::FStrPropertyParams NewProp_Namespace;
		static const UECodeGen_Private::FStrPropertyParams NewProp_Key;
		static const UECodeGen_Private::FStrPropertyParams NewProp_SourceString;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetFTextComponentsFromRepresentativeFString_Parms, InString), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::NewProp_Namespace = { "Namespace", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetFTextComponentsFromRepresentativeFString_Parms, Namespace), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetFTextComponentsFromRepresentativeFString_Parms, Key), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::NewProp_SourceString = { "SourceString", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetFTextComponentsFromRepresentativeFString_Parms, SourceString), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::NewProp_InString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::NewProp_Namespace,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::NewProp_Key,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::NewProp_SourceString,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|String" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns the namespace (if applicable), key (if applicable), and source string from an const FString& that represents a localizable FText with metadata (NSLOCTEXT, LOCTEXT, INVTEXT).\n\x09 * This function can be used to strip the metadata out of an const FString& that represents a localizable FText if you just use the return value 'SourceString.'\n\x09 * @param InString A string that represents a localizable FText with metadata (NSLOCTEXT, LOCTEXT, INVTEXT)\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns the namespace (if applicable), key (if applicable), and source string from an const FString& that represents a localizable FText with metadata (NSLOCTEXT, LOCTEXT, INVTEXT).\nThis function can be used to strip the metadata out of an const FString& that represents a localizable FText if you just use the return value 'SourceString.'\n@param InString A string that represents a localizable FText with metadata (NSLOCTEXT, LOCTEXT, INVTEXT)" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "GetFTextComponentsFromRepresentativeFString", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::EasyCsv_eventGetFTextComponentsFromRepresentativeFString_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::EasyCsv_eventGetFTextComponentsFromRepresentativeFString_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics
	{
		struct EasyCsv_eventGetMapHeaders_Parms
		{
			FEasyCsvInfo CSV_Info;
			TArray<FString> ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CSV_Info_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CSV_Info;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::NewProp_CSV_Info_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::NewProp_CSV_Info = { "CSV_Info", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetMapHeaders_Parms, CSV_Info), Z_Construct_UScriptStruct_FEasyCsvInfo, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::NewProp_CSV_Info_MetaData), Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::NewProp_CSV_Info_MetaData) }; // 795079476
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetMapHeaders_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::NewProp_CSV_Info,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Post-Parse Operations" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns the headers/column names for the given CSV as an array of FString, not counting the \"Key\" header.\n\x09 * If no CSV is loaded, this array will be blank.\n\x09 * @return An array of column names / headers as FString\n\x09 * @param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns the headers/column names for the given CSV as an array of FString, not counting the \"Key\" header.\nIf no CSV is loaded, this array will be blank.\n@return An array of column names / headers as FString\n@param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "GetMapHeaders", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::EasyCsv_eventGetMapHeaders_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::EasyCsv_eventGetMapHeaders_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_GetMapHeaders()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_GetMapHeaders_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics
	{
		struct EasyCsv_eventGetMapKeyIndex_Parms
		{
			FEasyCsvInfo CSV_Info;
			FName Key;
			int32 ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CSV_Info_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CSV_Info;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Key_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_Key;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::NewProp_CSV_Info_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::NewProp_CSV_Info = { "CSV_Info", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetMapKeyIndex_Parms, CSV_Info), Z_Construct_UScriptStruct_FEasyCsvInfo, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::NewProp_CSV_Info_MetaData), Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::NewProp_CSV_Info_MetaData) }; // 795079476
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::NewProp_Key_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetMapKeyIndex_Parms, Key), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::NewProp_Key_MetaData), Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::NewProp_Key_MetaData) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetMapKeyIndex_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::NewProp_CSV_Info,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::NewProp_Key,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Post-Parse Operations" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns the index of the given key in the CSV. -1 will be returned if the key is not found or if the CSV is not loaded.\n\x09 * This function can be used to find a specific row index in the CSV given the row key.\n\x09 * @return The index of the given key in the CSV\n\x09 * @param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString.\n\x09 * @param Key The key for the given row in the CSV\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns the index of the given key in the CSV. -1 will be returned if the key is not found or if the CSV is not loaded.\nThis function can be used to find a specific row index in the CSV given the row key.\n@return The index of the given key in the CSV\n@param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString.\n@param Key The key for the given row in the CSV" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "GetMapKeyIndex", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::EasyCsv_eventGetMapKeyIndex_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::EasyCsv_eventGetMapKeyIndex_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics
	{
		struct EasyCsv_eventGetMapKeys_Parms
		{
			FEasyCsvInfo CSV_Info;
			TArray<FName> ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CSV_Info_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CSV_Info;
		static const UECodeGen_Private::FNamePropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::NewProp_CSV_Info_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::NewProp_CSV_Info = { "CSV_Info", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetMapKeys_Parms, CSV_Info), Z_Construct_UScriptStruct_FEasyCsvInfo, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::NewProp_CSV_Info_MetaData), Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::NewProp_CSV_Info_MetaData) }; // 795079476
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetMapKeys_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::NewProp_CSV_Info,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Post-Parse Operations" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns the keys for the given CSV as an array of FNames. \n\x09 * This is deterministic; the keys will always be in the same order and will correspond to the order of the CSV. \n\x09 * If no CSV is loaded, this array will be blank.\n\x09 * @return An array of FNames corresponding to the CSV's row keys\n\x09 * @param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns the keys for the given CSV as an array of FNames.\nThis is deterministic; the keys will always be in the same order and will correspond to the order of the CSV.\nIf no CSV is loaded, this array will be blank.\n@return An array of FNames corresponding to the CSV's row keys\n@param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "GetMapKeys", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::EasyCsv_eventGetMapKeys_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::EasyCsv_eventGetMapKeys_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_GetMapKeys()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_GetMapKeys_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics
	{
		struct EasyCsv_eventGetRowAsStringArray_Parms
		{
			FEasyCsvInfo CSV_Info;
			FName RowKey;
			bool Success;
			TArray<FString> ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CSV_Info_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CSV_Info;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RowKey_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_RowKey;
		static void NewProp_Success_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_Success;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_CSV_Info_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_CSV_Info = { "CSV_Info", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetRowAsStringArray_Parms, CSV_Info), Z_Construct_UScriptStruct_FEasyCsvInfo, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_CSV_Info_MetaData), Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_CSV_Info_MetaData) }; // 795079476
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_RowKey_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_RowKey = { "RowKey", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetRowAsStringArray_Parms, RowKey), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_RowKey_MetaData), Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_RowKey_MetaData) };
	void Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_Success_SetBit(void* Obj)
	{
		((EasyCsv_eventGetRowAsStringArray_Parms*)Obj)->Success = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_Success = { "Success", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EasyCsv_eventGetRowAsStringArray_Parms), &Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_Success_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetRowAsStringArray_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_CSV_Info,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_RowKey,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_Success,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Post-Parse Operations" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns all values in a row given the key of a row in the CSV, as an array of strings.\n\x09 * @return All values in a row given the key of a row in the CSV, as an array of strings\n\x09 * @param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString.\n\x09 * @param RowKey The key of the row in the CSV\n\x09 * @param Success Whether or not the row could be found by key\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns all values in a row given the key of a row in the CSV, as an array of strings.\n@return All values in a row given the key of a row in the CSV, as an array of strings\n@param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString.\n@param RowKey The key of the row in the CSV\n@param Success Whether or not the row could be found by key" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "GetRowAsStringArray", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::EasyCsv_eventGetRowAsStringArray_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::EasyCsv_eventGetRowAsStringArray_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics
	{
		struct EasyCsv_eventGetRowCount_Parms
		{
			FEasyCsvInfo CSV_Info;
			int32 ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CSV_Info_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CSV_Info;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::NewProp_CSV_Info_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::NewProp_CSV_Info = { "CSV_Info", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetRowCount_Parms, CSV_Info), Z_Construct_UScriptStruct_FEasyCsvInfo, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::NewProp_CSV_Info_MetaData), Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::NewProp_CSV_Info_MetaData) }; // 795079476
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetRowCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::NewProp_CSV_Info,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Post-Parse Operations" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns the number of rows in a given CSV, not counting the column headers.\n\x09 * If no valid CSV_Info struct is passed in, this will return -1.\n\x09 * @return An integer reflecting the number of rows in a given CSV_Info struct's CSV map.\n\x09 * @param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns the number of rows in a given CSV, not counting the column headers.\nIf no valid CSV_Info struct is passed in, this will return -1.\n@return An integer reflecting the number of rows in a given CSV_Info struct's CSV map.\n@param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "GetRowCount", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::EasyCsv_eventGetRowCount_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::EasyCsv_eventGetRowCount_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_GetRowCount()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_GetRowCount_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics
	{
		struct EasyCsv_eventGetRowValueAsString_Parms
		{
			FEasyCsvInfo CSV_Info;
			FString ColumnName;
			FName RowKey;
			bool Success;
			FString ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CSV_Info_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CSV_Info;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ColumnName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_ColumnName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RowKey_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_RowKey;
		static void NewProp_Success_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_Success;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_CSV_Info_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_CSV_Info = { "CSV_Info", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetRowValueAsString_Parms, CSV_Info), Z_Construct_UScriptStruct_FEasyCsvInfo, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_CSV_Info_MetaData), Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_CSV_Info_MetaData) }; // 795079476
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_ColumnName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_ColumnName = { "ColumnName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetRowValueAsString_Parms, ColumnName), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_ColumnName_MetaData), Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_ColumnName_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_RowKey_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_RowKey = { "RowKey", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetRowValueAsString_Parms, RowKey), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_RowKey_MetaData), Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_RowKey_MetaData) };
	void Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_Success_SetBit(void* Obj)
	{
		((EasyCsv_eventGetRowValueAsString_Parms*)Obj)->Success = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_Success = { "Success", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EasyCsv_eventGetRowValueAsString_Parms), &Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_Success_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventGetRowValueAsString_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_CSV_Info,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_ColumnName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_RowKey,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_Success,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Post-Parse Operations" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns a single value given a column name and a row key as a string.\n\x09 * @return A single value given a column name and a row key as a string\n\x09 * @param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString.\n\x09 * @param ColumnName The name of the column in the CSV\n\x09 * @param RowKey The key for the given row in the CSV\n\x09 * @param Success Whether or not the value could be found by column name and/or row key\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns a single value given a column name and a row key as a string.\n@return A single value given a column name and a row key as a string\n@param CSV_Info A structure containing parsed CSV data. Can be created using MakeCSV_InfoFromString.\n@param ColumnName The name of the column in the CSV\n@param RowKey The key for the given row in the CSV\n@param Success Whether or not the value could be found by column name and/or row key" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "GetRowValueAsString", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::EasyCsv_eventGetRowValueAsString_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::EasyCsv_eventGetRowValueAsString_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_GetRowValueAsString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_GetRowValueAsString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics
	{
		struct EasyCsv_eventLoadStringFromLocalFile_Parms
		{
			FString InPath;
			FString OutString;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InPath_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InPath;
		static const UECodeGen_Private::FStrPropertyParams NewProp_OutString;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::NewProp_InPath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::NewProp_InPath = { "InPath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventLoadStringFromLocalFile_Parms, InPath), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::NewProp_InPath_MetaData), Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::NewProp_InPath_MetaData) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::NewProp_OutString = { "OutString", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventLoadStringFromLocalFile_Parms, OutString), METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((EasyCsv_eventLoadStringFromLocalFile_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EasyCsv_eventLoadStringFromLocalFile_Parms), &Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::NewProp_InPath,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::NewProp_OutString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::Function_MetaDataParams[] = {
		{ "Category", "Google Sheets Operator|Utilities" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Loads a text-based file from the specified path and outputs its contents as a string.\n\x09 * @return Whether or not the file could be successfully loaded\n\x09 * @param InPath The file path to the file you'd like to load\n\x09 * @param OutString The contents of the file as a string \n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Loads a text-based file from the specified path and outputs its contents as a string.\n@return Whether or not the file could be successfully loaded\n@param InPath The file path to the file you'd like to load\n@param OutString The contents of the file as a string" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "LoadStringFromLocalFile", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::EasyCsv_eventLoadStringFromLocalFile_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::EasyCsv_eventLoadStringFromLocalFile_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics
	{
		struct EasyCsv_eventMakeCsvInfoStructFromFile_Parms
		{
			FString InPath;
			FEasyCsvInfo OutCsvInfo;
			bool ParseHeaders;
			bool ParseKeys;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InPath_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InPath;
		static const UECodeGen_Private::FStructPropertyParams NewProp_OutCsvInfo;
		static void NewProp_ParseHeaders_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ParseHeaders;
		static void NewProp_ParseKeys_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ParseKeys;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_InPath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_InPath = { "InPath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventMakeCsvInfoStructFromFile_Parms, InPath), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_InPath_MetaData), Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_InPath_MetaData) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_OutCsvInfo = { "OutCsvInfo", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventMakeCsvInfoStructFromFile_Parms, OutCsvInfo), Z_Construct_UScriptStruct_FEasyCsvInfo, METADATA_PARAMS(0, nullptr) }; // 795079476
	void Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_ParseHeaders_SetBit(void* Obj)
	{
		((EasyCsv_eventMakeCsvInfoStructFromFile_Parms*)Obj)->ParseHeaders = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_ParseHeaders = { "ParseHeaders", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EasyCsv_eventMakeCsvInfoStructFromFile_Parms), &Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_ParseHeaders_SetBit, METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_ParseKeys_SetBit(void* Obj)
	{
		((EasyCsv_eventMakeCsvInfoStructFromFile_Parms*)Obj)->ParseKeys = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_ParseKeys = { "ParseKeys", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EasyCsv_eventMakeCsvInfoStructFromFile_Parms), &Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_ParseKeys_SetBit, METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((EasyCsv_eventMakeCsvInfoStructFromFile_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EasyCsv_eventMakeCsvInfoStructFromFile_Parms), &Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_InPath,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_OutCsvInfo,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_ParseHeaders,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_ParseKeys,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Main" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Used to parse a CSV into a map containing each cell's data as part of an array of FString. This is the node you want to start with.\n\x09 * @return Whether or not the parsing was successful\n\x09 * @param OutCsvInfo A struct with parsed CSV information. This can be used to access the information directly or pass into other easyCSV functions.\n\x09 * @param InPath This is the path to the CSV file\n\x09 * @param ParseHeaders If true, the parser will expect the first row of the CSV to be column labels, or headers. If false, vales will be generated.\n\x09 * @param ParseKeys If true, the parser will expect the first column of the CSV to be row labels, or keys. If false, values will be generated.\n\x09 */" },
#endif
		{ "CPP_Default_ParseHeaders", "true" },
		{ "CPP_Default_ParseKeys", "true" },
		{ "DisplayName", "Make CSV Info From File" },
		{ "Keywords", "parse" },
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Used to parse a CSV into a map containing each cell's data as part of an array of FString. This is the node you want to start with.\n@return Whether or not the parsing was successful\n@param OutCsvInfo A struct with parsed CSV information. This can be used to access the information directly or pass into other easyCSV functions.\n@param InPath This is the path to the CSV file\n@param ParseHeaders If true, the parser will expect the first row of the CSV to be column labels, or headers. If false, vales will be generated.\n@param ParseKeys If true, the parser will expect the first column of the CSV to be row labels, or keys. If false, values will be generated." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "MakeCsvInfoStructFromFile", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::EasyCsv_eventMakeCsvInfoStructFromFile_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::EasyCsv_eventMakeCsvInfoStructFromFile_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics
	{
		struct EasyCsv_eventMakeCsvInfoStructFromString_Parms
		{
			FString InString;
			FEasyCsvInfo OutCsvInfo;
			bool ParseHeaders;
			bool ParseKeys;
			bool ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_InString;
		static const UECodeGen_Private::FStructPropertyParams NewProp_OutCsvInfo;
		static void NewProp_ParseHeaders_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ParseHeaders;
		static void NewProp_ParseKeys_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ParseKeys;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventMakeCsvInfoStructFromString_Parms, InString), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_OutCsvInfo = { "OutCsvInfo", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventMakeCsvInfoStructFromString_Parms, OutCsvInfo), Z_Construct_UScriptStruct_FEasyCsvInfo, METADATA_PARAMS(0, nullptr) }; // 795079476
	void Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_ParseHeaders_SetBit(void* Obj)
	{
		((EasyCsv_eventMakeCsvInfoStructFromString_Parms*)Obj)->ParseHeaders = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_ParseHeaders = { "ParseHeaders", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EasyCsv_eventMakeCsvInfoStructFromString_Parms), &Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_ParseHeaders_SetBit, METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_ParseKeys_SetBit(void* Obj)
	{
		((EasyCsv_eventMakeCsvInfoStructFromString_Parms*)Obj)->ParseKeys = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_ParseKeys = { "ParseKeys", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EasyCsv_eventMakeCsvInfoStructFromString_Parms), &Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_ParseKeys_SetBit, METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((EasyCsv_eventMakeCsvInfoStructFromString_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EasyCsv_eventMakeCsvInfoStructFromString_Parms), &Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_InString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_OutCsvInfo,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_ParseHeaders,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_ParseKeys,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Main" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Used to parse a CSV into a map containing each cell's data as part of an array of FString. This is the node you want to start with.\n\x09 * @return Whether or not the parsing was successful\n\x09 * @param OutCsvInfo A struct with parsed CSV information. This can be used to access the information directly or pass into other easyCSV functions.\n\x09 * @param InString This is the string data found inside the CSV file. Can be loaded from a file using LoadStringFromFile.\n\x09 * @param ParseHeaders If true, the parser will expect the first row of the CSV to be column labels, or headers. If false, vales will be generated.\n\x09 * @param ParseKeys If true, the parser will expect the first column of the CSV to be row labels, or keys. If false, values will be generated.\n\x09 */" },
#endif
		{ "CPP_Default_ParseHeaders", "true" },
		{ "CPP_Default_ParseKeys", "true" },
		{ "DisplayName", "Make CSV Info From String" },
		{ "Keywords", "parse" },
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Used to parse a CSV into a map containing each cell's data as part of an array of FString. This is the node you want to start with.\n@return Whether or not the parsing was successful\n@param OutCsvInfo A struct with parsed CSV information. This can be used to access the information directly or pass into other easyCSV functions.\n@param InString This is the string data found inside the CSV file. Can be loaded from a file using LoadStringFromFile.\n@param ParseHeaders If true, the parser will expect the first row of the CSV to be column labels, or headers. If false, vales will be generated.\n@param ParseKeys If true, the parser will expect the first column of the CSV to be row labels, or keys. If false, values will be generated." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "MakeCsvInfoStructFromString", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::EasyCsv_eventMakeCsvInfoStructFromString_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::EasyCsv_eventMakeCsvInfoStructFromString_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics
	{
		struct EasyCsv_eventReplaceEscapedCharacters_Parms
		{
			FString InString;
			FString ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InString_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InString;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::NewProp_InString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventReplaceEscapedCharacters_Parms, InString), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::NewProp_InString_MetaData), Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::NewProp_InString_MetaData) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventReplaceEscapedCharacters_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::NewProp_InString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|String" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns an const FString& with all escaped characters turned into characters ('\\\"', '\\r', '\\n', etc). Also removes all leading backslashes.\n\x09 * @return const FString& A string with all escaped characters converted into standard characters ('\\\"', '\\r', '\\n', etc)\n\x09 * @param InString A string that may contain escaped characters ('\\\"', '\\r', '\\n', etc)\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns an const FString& with all escaped characters turned into characters ('\\\"', '\\r', '\\n', etc). Also removes all leading backslashes.\n@return const FString& A string with all escaped characters converted into standard characters ('\\\"', '\\r', '\\n', etc)\n@param InString A string that may contain escaped characters ('\\\"', '\\r', '\\n', etc)" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "ReplaceEscapedCharacters", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::EasyCsv_eventReplaceEscapedCharacters_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::EasyCsv_eventReplaceEscapedCharacters_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics
	{
		struct EasyCsv_eventSaveStringToFile_Parms
		{
			FString InString;
			FString InDirectory;
			FString Filename;
			FString Extension;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InString_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InString;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InDirectory_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InDirectory;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Filename_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Filename;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Extension_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Extension;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_InString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventSaveStringToFile_Parms, InString), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_InString_MetaData), Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_InString_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_InDirectory_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_InDirectory = { "InDirectory", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventSaveStringToFile_Parms, InDirectory), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_InDirectory_MetaData), Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_InDirectory_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_Filename_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_Filename = { "Filename", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventSaveStringToFile_Parms, Filename), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_Filename_MetaData), Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_Filename_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_Extension_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_Extension = { "Extension", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventSaveStringToFile_Parms, Extension), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_Extension_MetaData), Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_Extension_MetaData) };
	void Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((EasyCsv_eventSaveStringToFile_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EasyCsv_eventSaveStringToFile_Parms), &Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_InString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_InDirectory,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_Filename,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_Extension,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Utlities" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Saves a new file using an input string. Always overwrites and does not validate paths, so please be sure the directory exists. \n\x09 * Meant for saving a CSV, but can be used for any text-based file. Returns true if write is successful.\n\x09 * @param InString The string to save to a file\n\x09 * @param InDirectory The folder in which to save the new file\n\x09 * @param Filename The new file's name\n\x09 * @param Extension The file extension for the new file\n\x09 */" },
#endif
		{ "CPP_Default_Extension", ".csv" },
		{ "CPP_Default_Filename", "New_CSV" },
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Saves a new file using an input string. Always overwrites and does not validate paths, so please be sure the directory exists.\nMeant for saving a CSV, but can be used for any text-based file. Returns true if write is successful.\n@param InString The string to save to a file\n@param InDirectory The folder in which to save the new file\n@param Filename The new file's name\n@param Extension The file extension for the new file" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "SaveStringToFile", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::EasyCsv_eventSaveStringToFile_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::EasyCsv_eventSaveStringToFile_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_SaveStringToFile()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_SaveStringToFile_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics
	{
		struct EasyCsv_eventSaveStringToFileWithFullPath_Parms
		{
			FString InString;
			FString InFullPath;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InString_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InString;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InFullPath_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InFullPath;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::NewProp_InString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventSaveStringToFileWithFullPath_Parms, InString), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::NewProp_InString_MetaData), Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::NewProp_InString_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::NewProp_InFullPath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::NewProp_InFullPath = { "InFullPath", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EasyCsv_eventSaveStringToFileWithFullPath_Parms, InFullPath), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::NewProp_InFullPath_MetaData), Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::NewProp_InFullPath_MetaData) };
	void Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((EasyCsv_eventSaveStringToFileWithFullPath_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(EasyCsv_eventSaveStringToFileWithFullPath_Parms), &Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::NewProp_InString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::NewProp_InFullPath,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::Function_MetaDataParams[] = {
		{ "Category", "easyCSV|Utlities" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Saves a new file using an input string. Always overwrites and does not validate paths, so please be sure the directory exists. \n\x09 * Meant for saving a CSV, but can be used for any text-based file. Returns true if write is successful.\n\x09 * @param InString The string to save to a file\n\x09 * @param InFullPath The folder, filename and extension used to save the new file\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Saves a new file using an input string. Always overwrites and does not validate paths, so please be sure the directory exists.\nMeant for saving a CSV, but can be used for any text-based file. Returns true if write is successful.\n@param InString The string to save to a file\n@param InFullPath The folder, filename and extension used to save the new file" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEasyCsv, nullptr, "SaveStringToFileWithFullPath", nullptr, nullptr, Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::EasyCsv_eventSaveStringToFileWithFullPath_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::EasyCsv_eventSaveStringToFileWithFullPath_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UEasyCsv);
	UClass* Z_Construct_UClass_UEasyCsv_NoRegister()
	{
		return UEasyCsv::StaticClass();
	}
	struct Z_Construct_UClass_UEasyCsv_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UEasyCsv_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_EasyCsv,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsv_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UEasyCsv_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotator, "ConvertQuatStringToRotator" }, // 1630731953
		{ &Z_Construct_UFunction_UEasyCsv_ConvertQuatStringToRotatorArray, "ConvertQuatStringToRotatorArray" }, // 2938482120
		{ &Z_Construct_UFunction_UEasyCsv_ConvertStringToQuat, "ConvertStringToQuat" }, // 3812542959
		{ &Z_Construct_UFunction_UEasyCsv_ConvertStringToQuatArray, "ConvertStringToQuatArray" }, // 439728520
		{ &Z_Construct_UFunction_UEasyCsv_ConvertStringToRotator, "ConvertStringToRotator" }, // 468092426
		{ &Z_Construct_UFunction_UEasyCsv_ConvertStringToRotatorArray, "ConvertStringToRotatorArray" }, // 3986881911
		{ &Z_Construct_UFunction_UEasyCsv_DoesStringRepresentContainer, "DoesStringRepresentContainer" }, // 3595607891
		{ &Z_Construct_UFunction_UEasyCsv_EscapeCharacters, "EscapeCharacters" }, // 2761680963
		{ &Z_Construct_UFunction_UEasyCsv_GetColumnAsStringArray, "GetColumnAsStringArray" }, // 2331362377
		{ &Z_Construct_UFunction_UEasyCsv_GetColumnCount, "GetColumnCount" }, // 1296604502
		{ &Z_Construct_UFunction_UEasyCsv_GetFTextComponentsFromRepresentativeFString, "GetFTextComponentsFromRepresentativeFString" }, // 2985354178
		{ &Z_Construct_UFunction_UEasyCsv_GetMapHeaders, "GetMapHeaders" }, // 2229324676
		{ &Z_Construct_UFunction_UEasyCsv_GetMapKeyIndex, "GetMapKeyIndex" }, // 2497271754
		{ &Z_Construct_UFunction_UEasyCsv_GetMapKeys, "GetMapKeys" }, // 3324418802
		{ &Z_Construct_UFunction_UEasyCsv_GetRowAsStringArray, "GetRowAsStringArray" }, // 3445885662
		{ &Z_Construct_UFunction_UEasyCsv_GetRowCount, "GetRowCount" }, // 2256388058
		{ &Z_Construct_UFunction_UEasyCsv_GetRowValueAsString, "GetRowValueAsString" }, // 634903311
		{ &Z_Construct_UFunction_UEasyCsv_LoadStringFromLocalFile, "LoadStringFromLocalFile" }, // 652821818
		{ &Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromFile, "MakeCsvInfoStructFromFile" }, // 1245690195
		{ &Z_Construct_UFunction_UEasyCsv_MakeCsvInfoStructFromString, "MakeCsvInfoStructFromString" }, // 1456041266
		{ &Z_Construct_UFunction_UEasyCsv_ReplaceEscapedCharacters, "ReplaceEscapedCharacters" }, // 1900467677
		{ &Z_Construct_UFunction_UEasyCsv_SaveStringToFile, "SaveStringToFile" }, // 1414517685
		{ &Z_Construct_UFunction_UEasyCsv_SaveStringToFileWithFullPath, "SaveStringToFileWithFullPath" }, // 1332153972
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsv_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEasyCsv_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "EasyCsv.h" },
		{ "ModuleRelativePath", "Public/EasyCsv.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UEasyCsv_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEasyCsv>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UEasyCsv_Statics::ClassParams = {
		&UEasyCsv::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsv_Statics::Class_MetaDataParams), Z_Construct_UClass_UEasyCsv_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UEasyCsv()
	{
		if (!Z_Registration_Info_UClass_UEasyCsv.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UEasyCsv.OuterSingleton, Z_Construct_UClass_UEasyCsv_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UEasyCsv.OuterSingleton;
	}
	template<> EASYCSV_API UClass* StaticClass<UEasyCsv>()
	{
		return UEasyCsv::StaticClass();
	}
	UEasyCsv::UEasyCsv(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UEasyCsv);
	UEasyCsv::~UEasyCsv() {}
	struct Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_Statics::ScriptStructInfo[] = {
		{ FEasyCsvStringValueArray::StaticStruct, Z_Construct_UScriptStruct_FEasyCsvStringValueArray_Statics::NewStructOps, TEXT("EasyCsvStringValueArray"), &Z_Registration_Info_UScriptStruct_EasyCsvStringValueArray, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEasyCsvStringValueArray), 3498439254U) },
		{ FEasyCsvInfo::StaticStruct, Z_Construct_UScriptStruct_FEasyCsvInfo_Statics::NewStructOps, TEXT("EasyCsvInfo"), &Z_Registration_Info_UScriptStruct_EasyCsvInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEasyCsvInfo), 795079476U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UEasyCsv, UEasyCsv::StaticClass, TEXT("UEasyCsv"), &Z_Registration_Info_UClass_UEasyCsv, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UEasyCsv), 1743610757U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_2340137583(TEXT("/Script/EasyCsv"),
		Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
