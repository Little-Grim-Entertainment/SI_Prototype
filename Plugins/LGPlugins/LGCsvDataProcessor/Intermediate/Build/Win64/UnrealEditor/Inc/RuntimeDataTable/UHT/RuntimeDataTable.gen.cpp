// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RuntimeDataTable.h"
#include "EasyCsv.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRuntimeDataTable() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	EASYCSV_API UScriptStruct* Z_Construct_UScriptStruct_FEasyCsvInfo();
	RUNTIMEDATATABLE_API UClass* Z_Construct_UClass_URuntimeDataTableObject();
	RUNTIMEDATATABLE_API UClass* Z_Construct_UClass_URuntimeDataTableObject_NoRegister();
	RUNTIMEDATATABLE_API UClass* Z_Construct_UClass_URuntimeDataTableWebToken();
	RUNTIMEDATATABLE_API UClass* Z_Construct_UClass_URuntimeDataTableWebToken_NoRegister();
	RUNTIMEDATATABLE_API UEnum* Z_Construct_UEnum_RuntimeDataTable_ERuntimeDataTableBackupResultCode();
	RUNTIMEDATATABLE_API UFunction* Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature();
	RUNTIMEDATATABLE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo();
	RUNTIMEDATATABLE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams();
	RUNTIMEDATATABLE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo();
	UPackage* Z_Construct_UPackage__Script_RuntimeDataTable();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_RuntimeDataTableCallbackInfo;
class UScriptStruct* FRuntimeDataTableCallbackInfo::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_RuntimeDataTableCallbackInfo.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_RuntimeDataTableCallbackInfo.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo, (UObject*)Z_Construct_UPackage__Script_RuntimeDataTable(), TEXT("RuntimeDataTableCallbackInfo"));
	}
	return Z_Registration_Info_UScriptStruct_RuntimeDataTableCallbackInfo.OuterSingleton;
}
template<> RUNTIMEDATATABLE_API UScriptStruct* StaticStruct<FRuntimeDataTableCallbackInfo>()
{
	return FRuntimeDataTableCallbackInfo::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OperationName_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_OperationName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bWasSuccessful_MetaData[];
#endif
		static void NewProp_bWasSuccessful_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bWasSuccessful;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ResponseAsString_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_ResponseAsString;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ResponseCode_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ResponseCode;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Returned in every delegate\n" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returned in every delegate" },
#endif
	};
#endif
	void* Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRuntimeDataTableCallbackInfo>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_OperationName_MetaData[] = {
		{ "Category", "Runtime DataTable" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_OperationName = { "OperationName", nullptr, (EPropertyFlags)0x0010000000020005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRuntimeDataTableCallbackInfo, OperationName), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_OperationName_MetaData), Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_OperationName_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_bWasSuccessful_MetaData[] = {
		{ "Category", "Runtime DataTable" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_bWasSuccessful_SetBit(void* Obj)
	{
		((FRuntimeDataTableCallbackInfo*)Obj)->bWasSuccessful = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_bWasSuccessful = { "bWasSuccessful", nullptr, (EPropertyFlags)0x0010000000020005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FRuntimeDataTableCallbackInfo), &Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_bWasSuccessful_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_bWasSuccessful_MetaData), Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_bWasSuccessful_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_ResponseAsString_MetaData[] = {
		{ "Category", "Runtime DataTable" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_ResponseAsString = { "ResponseAsString", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRuntimeDataTableCallbackInfo, ResponseAsString), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_ResponseAsString_MetaData), Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_ResponseAsString_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_ResponseCode_MetaData[] = {
		{ "Category", "Runtime DataTable" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_ResponseCode = { "ResponseCode", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRuntimeDataTableCallbackInfo, ResponseCode), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_ResponseCode_MetaData), Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_ResponseCode_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_OperationName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_bWasSuccessful,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_ResponseAsString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewProp_ResponseCode,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_RuntimeDataTable,
		nullptr,
		&NewStructOps,
		"RuntimeDataTableCallbackInfo",
		Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::PropPointers),
		sizeof(FRuntimeDataTableCallbackInfo),
		alignof(FRuntimeDataTableCallbackInfo),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::Struct_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::PropPointers) < 2048);
	UScriptStruct* Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo()
	{
		if (!Z_Registration_Info_UScriptStruct_RuntimeDataTableCallbackInfo.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_RuntimeDataTableCallbackInfo.InnerSingleton, Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_RuntimeDataTableCallbackInfo.InnerSingleton;
	}
	struct Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature_Statics
	{
		struct _Script_RuntimeDataTable_eventRDTGetStringDelegate_Parms
		{
			FRuntimeDataTableCallbackInfo CallbackInfo;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_CallbackInfo;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature_Statics::NewProp_CallbackInfo = { "CallbackInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_RuntimeDataTable_eventRDTGetStringDelegate_Parms, CallbackInfo), Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo, METADATA_PARAMS(0, nullptr) }; // 3918684402
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature_Statics::NewProp_CallbackInfo,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_RuntimeDataTable, nullptr, "RDTGetStringDelegate__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature_Statics::_Script_RuntimeDataTable_eventRDTGetStringDelegate_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature_Statics::_Script_RuntimeDataTable_eventRDTGetStringDelegate_Parms) < MAX_uint16);
	UFunction* Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FRDTGetStringDelegate_DelegateWrapper(const FScriptDelegate& RDTGetStringDelegate, FRuntimeDataTableCallbackInfo CallbackInfo)
{
	struct _Script_RuntimeDataTable_eventRDTGetStringDelegate_Parms
	{
		FRuntimeDataTableCallbackInfo CallbackInfo;
	};
	_Script_RuntimeDataTable_eventRDTGetStringDelegate_Parms Parms;
	Parms.CallbackInfo=CallbackInfo;
	RDTGetStringDelegate.ProcessDelegate<UObject>(&Parms);
}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_RuntimeDataTableOperationParams;
class UScriptStruct* FRuntimeDataTableOperationParams::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_RuntimeDataTableOperationParams.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_RuntimeDataTableOperationParams.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams, (UObject*)Z_Construct_UPackage__Script_RuntimeDataTable(), TEXT("RuntimeDataTableOperationParams"));
	}
	return Z_Registration_Info_UScriptStruct_RuntimeDataTableOperationParams.OuterSingleton;
}
template<> RUNTIMEDATATABLE_API UScriptStruct* StaticStruct<FRuntimeDataTableOperationParams>()
{
	return FRuntimeDataTableOperationParams::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OperationName_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_OperationName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RequestTimeout_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_RequestTimeout;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Sent with every operation\n" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sent with every operation" },
#endif
	};
#endif
	void* Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRuntimeDataTableOperationParams>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::NewProp_OperationName_MetaData[] = {
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** A name for your operation for tracking purposes */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A name for your operation for tracking purposes" },
#endif
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::NewProp_OperationName = { "OperationName", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRuntimeDataTableOperationParams, OperationName), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::NewProp_OperationName_MetaData), Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::NewProp_OperationName_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::NewProp_RequestTimeout_MetaData[] = {
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** How long to wait for the operation to complete before a timeout is considered */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How long to wait for the operation to complete before a timeout is considered" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::NewProp_RequestTimeout = { "RequestTimeout", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRuntimeDataTableOperationParams, RequestTimeout), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::NewProp_RequestTimeout_MetaData), Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::NewProp_RequestTimeout_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::NewProp_OperationName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::NewProp_RequestTimeout,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_RuntimeDataTable,
		nullptr,
		&NewStructOps,
		"RuntimeDataTableOperationParams",
		Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::PropPointers),
		sizeof(FRuntimeDataTableOperationParams),
		alignof(FRuntimeDataTableOperationParams),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::Struct_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::PropPointers) < 2048);
	UScriptStruct* Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams()
	{
		if (!Z_Registration_Info_UScriptStruct_RuntimeDataTableOperationParams.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_RuntimeDataTableOperationParams.InnerSingleton, Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_RuntimeDataTableOperationParams.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_RuntimeDataTableTokenInfo;
class UScriptStruct* FRuntimeDataTableTokenInfo::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_RuntimeDataTableTokenInfo.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_RuntimeDataTableTokenInfo.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo, (UObject*)Z_Construct_UPackage__Script_RuntimeDataTable(), TEXT("RuntimeDataTableTokenInfo"));
	}
	return Z_Registration_Info_UScriptStruct_RuntimeDataTableTokenInfo.OuterSingleton;
}
template<> RUNTIMEDATATABLE_API UScriptStruct* StaticStruct<FRuntimeDataTableTokenInfo>()
{
	return FRuntimeDataTableTokenInfo::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PrivateKey_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_PrivateKey;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ServiceAccountEmail_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_ServiceAccountEmail;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ClaimUrl_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_ClaimUrl;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TokenUri_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_TokenUri;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SecondsUntilExpiration_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_SecondsUntilExpiration;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Used to build an authentication token\n" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Used to build an authentication token" },
#endif
	};
#endif
	void* Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRuntimeDataTableTokenInfo>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_PrivateKey_MetaData[] = {
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Maps to: private_key in the json\n" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maps to: private_key in the json" },
#endif
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_PrivateKey = { "PrivateKey", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRuntimeDataTableTokenInfo, PrivateKey), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_PrivateKey_MetaData), Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_PrivateKey_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_ServiceAccountEmail_MetaData[] = {
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Maps to: client_email in the json\n" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maps to: client_email in the json" },
#endif
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_ServiceAccountEmail = { "ServiceAccountEmail", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRuntimeDataTableTokenInfo, ServiceAccountEmail), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_ServiceAccountEmail_MetaData), Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_ServiceAccountEmail_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_ClaimUrl_MetaData[] = {
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Only change this value if you know it needs to be changed. Not found in the json.\n" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Only change this value if you know it needs to be changed. Not found in the json." },
#endif
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_ClaimUrl = { "ClaimUrl", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRuntimeDataTableTokenInfo, ClaimUrl), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_ClaimUrl_MetaData), Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_ClaimUrl_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_TokenUri_MetaData[] = {
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Maps to: token_uri in the json. Only change this value if you know it needs to be changed\n" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maps to: token_uri in the json. Only change this value if you know it needs to be changed" },
#endif
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_TokenUri = { "TokenUri", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRuntimeDataTableTokenInfo, TokenUri), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_TokenUri_MetaData), Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_TokenUri_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_SecondsUntilExpiration_MetaData[] = {
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// How long should this token last? Min is 1 second, Max is 3600 seconds (1 hour).\n// Generally it's best practice to keep the expiration short and generate a new token for each operation.\n" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How long should this token last? Min is 1 second, Max is 3600 seconds (1 hour).\nGenerally it's best practice to keep the expiration short and generate a new token for each operation." },
#endif
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_SecondsUntilExpiration = { "SecondsUntilExpiration", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRuntimeDataTableTokenInfo, SecondsUntilExpiration), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_SecondsUntilExpiration_MetaData), Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_SecondsUntilExpiration_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_PrivateKey,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_ServiceAccountEmail,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_ClaimUrl,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_TokenUri,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewProp_SecondsUntilExpiration,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_RuntimeDataTable,
		nullptr,
		&NewStructOps,
		"RuntimeDataTableTokenInfo",
		Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::PropPointers),
		sizeof(FRuntimeDataTableTokenInfo),
		alignof(FRuntimeDataTableTokenInfo),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::Struct_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::PropPointers) < 2048);
	UScriptStruct* Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo()
	{
		if (!Z_Registration_Info_UScriptStruct_RuntimeDataTableTokenInfo.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_RuntimeDataTableTokenInfo.InnerSingleton, Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_RuntimeDataTableTokenInfo.InnerSingleton;
	}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_ERuntimeDataTableBackupResultCode;
	static UEnum* ERuntimeDataTableBackupResultCode_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_ERuntimeDataTableBackupResultCode.OuterSingleton)
		{
			Z_Registration_Info_UEnum_ERuntimeDataTableBackupResultCode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_RuntimeDataTable_ERuntimeDataTableBackupResultCode, (UObject*)Z_Construct_UPackage__Script_RuntimeDataTable(), TEXT("ERuntimeDataTableBackupResultCode"));
		}
		return Z_Registration_Info_UEnum_ERuntimeDataTableBackupResultCode.OuterSingleton;
	}
	template<> RUNTIMEDATATABLE_API UEnum* StaticEnum<ERuntimeDataTableBackupResultCode>()
	{
		return ERuntimeDataTableBackupResultCode_StaticEnum();
	}
	struct Z_Construct_UEnum_RuntimeDataTable_ERuntimeDataTableBackupResultCode_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_RuntimeDataTable_ERuntimeDataTableBackupResultCode_Statics::Enumerators[] = {
		{ "ERuntimeDataTableBackupResultCode::DownloadFailedWithoutBackup", (int64)ERuntimeDataTableBackupResultCode::DownloadFailedWithoutBackup },
		{ "ERuntimeDataTableBackupResultCode::DownloadFailedAndBackupExistsBuCouldNotBeLoaded", (int64)ERuntimeDataTableBackupResultCode::DownloadFailedAndBackupExistsBuCouldNotBeLoaded },
		{ "ERuntimeDataTableBackupResultCode::DownloadSucceededButCsvCouldNotBeParsed", (int64)ERuntimeDataTableBackupResultCode::DownloadSucceededButCsvCouldNotBeParsed },
		{ "ERuntimeDataTableBackupResultCode::DownloadFailedAndBackupLoaded", (int64)ERuntimeDataTableBackupResultCode::DownloadFailedAndBackupLoaded },
		{ "ERuntimeDataTableBackupResultCode::DownloadSucceededAndBackupSaved", (int64)ERuntimeDataTableBackupResultCode::DownloadSucceededAndBackupSaved },
		{ "ERuntimeDataTableBackupResultCode::DownloadSucceededAndBackupCouldNotBeSaved", (int64)ERuntimeDataTableBackupResultCode::DownloadSucceededAndBackupCouldNotBeSaved },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_RuntimeDataTable_ERuntimeDataTableBackupResultCode_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "DownloadFailedAndBackupExistsBuCouldNotBeLoaded.Name", "ERuntimeDataTableBackupResultCode::DownloadFailedAndBackupExistsBuCouldNotBeLoaded" },
		{ "DownloadFailedAndBackupLoaded.Name", "ERuntimeDataTableBackupResultCode::DownloadFailedAndBackupLoaded" },
		{ "DownloadFailedWithoutBackup.Name", "ERuntimeDataTableBackupResultCode::DownloadFailedWithoutBackup" },
		{ "DownloadSucceededAndBackupCouldNotBeSaved.Name", "ERuntimeDataTableBackupResultCode::DownloadSucceededAndBackupCouldNotBeSaved" },
		{ "DownloadSucceededAndBackupSaved.Name", "ERuntimeDataTableBackupResultCode::DownloadSucceededAndBackupSaved" },
		{ "DownloadSucceededButCsvCouldNotBeParsed.Name", "ERuntimeDataTableBackupResultCode::DownloadSucceededButCsvCouldNotBeParsed" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_RuntimeDataTable_ERuntimeDataTableBackupResultCode_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_RuntimeDataTable,
		nullptr,
		"ERuntimeDataTableBackupResultCode",
		"ERuntimeDataTableBackupResultCode",
		Z_Construct_UEnum_RuntimeDataTable_ERuntimeDataTableBackupResultCode_Statics::Enumerators,
		RF_Public|RF_Transient|RF_MarkAsNative,
		UE_ARRAY_COUNT(Z_Construct_UEnum_RuntimeDataTable_ERuntimeDataTableBackupResultCode_Statics::Enumerators),
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_RuntimeDataTable_ERuntimeDataTableBackupResultCode_Statics::Enum_MetaDataParams), Z_Construct_UEnum_RuntimeDataTable_ERuntimeDataTableBackupResultCode_Statics::Enum_MetaDataParams)
	};
	UEnum* Z_Construct_UEnum_RuntimeDataTable_ERuntimeDataTableBackupResultCode()
	{
		if (!Z_Registration_Info_UEnum_ERuntimeDataTableBackupResultCode.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ERuntimeDataTableBackupResultCode.InnerSingleton, Z_Construct_UEnum_RuntimeDataTable_ERuntimeDataTableBackupResultCode_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_ERuntimeDataTableBackupResultCode.InnerSingleton;
	}
	DEFINE_FUNCTION(URuntimeDataTableWebToken::execGetTokenText)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetTokenText();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableWebToken::execGetNumberOfSecondsUntilExpiration)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetNumberOfSecondsUntilExpiration();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableWebToken::execHasTokenExpired)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->HasTokenExpired();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableWebToken::execInit)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InTokenText);
		P_GET_PROPERTY(FIntProperty,Z_Param_SecondsUntilExpiration);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->Init(Z_Param_InTokenText,Z_Param_SecondsUntilExpiration);
		P_NATIVE_END;
	}
	void URuntimeDataTableWebToken::StaticRegisterNativesURuntimeDataTableWebToken()
	{
		UClass* Class = URuntimeDataTableWebToken::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetNumberOfSecondsUntilExpiration", &URuntimeDataTableWebToken::execGetNumberOfSecondsUntilExpiration },
			{ "GetTokenText", &URuntimeDataTableWebToken::execGetTokenText },
			{ "HasTokenExpired", &URuntimeDataTableWebToken::execHasTokenExpired },
			{ "Init", &URuntimeDataTableWebToken::execInit },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration_Statics
	{
		struct RuntimeDataTableWebToken_eventGetNumberOfSecondsUntilExpiration_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableWebToken_eventGetNumberOfSecondsUntilExpiration_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration_Statics::Function_MetaDataParams[] = {
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns the number of seconds remaining until this token's authorization expiration.\n\x09 */" },
#endif
		{ "Keywords", "age, time" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns the number of seconds remaining until this token's authorization expiration." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableWebToken, nullptr, "GetNumberOfSecondsUntilExpiration", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration_Statics::RuntimeDataTableWebToken_eventGetNumberOfSecondsUntilExpiration_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration_Statics::RuntimeDataTableWebToken_eventGetNumberOfSecondsUntilExpiration_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText_Statics
	{
		struct RuntimeDataTableWebToken_eventGetTokenText_Parms
		{
			FString ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableWebToken_eventGetTokenText_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText_Statics::Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* Get the token string needed to pass into REST requests. */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the token string needed to pass into REST requests." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableWebToken, nullptr, "GetTokenText", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText_Statics::RuntimeDataTableWebToken_eventGetTokenText_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x40020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText_Statics::RuntimeDataTableWebToken_eventGetTokenText_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics
	{
		struct RuntimeDataTableWebToken_eventHasTokenExpired_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((RuntimeDataTableWebToken_eventHasTokenExpired_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RuntimeDataTableWebToken_eventHasTokenExpired_Parms), &Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::Function_MetaDataParams[] = {
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns true if the specified number of seconds until expiration have passed since authentication.\n\x09 */" },
#endif
		{ "Keywords", "age, time" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns true if the specified number of seconds until expiration have passed since authentication." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableWebToken, nullptr, "HasTokenExpired", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::RuntimeDataTableWebToken_eventHasTokenExpired_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::RuntimeDataTableWebToken_eventHasTokenExpired_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics
	{
		struct RuntimeDataTableWebToken_eventInit_Parms
		{
			FString InTokenText;
			int32 SecondsUntilExpiration;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InTokenText_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InTokenText;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SecondsUntilExpiration_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_SecondsUntilExpiration;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::NewProp_InTokenText_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::NewProp_InTokenText = { "InTokenText", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableWebToken_eventInit_Parms, InTokenText), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::NewProp_InTokenText_MetaData), Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::NewProp_InTokenText_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::NewProp_SecondsUntilExpiration_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::NewProp_SecondsUntilExpiration = { "SecondsUntilExpiration", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableWebToken_eventInit_Parms, SecondsUntilExpiration), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::NewProp_SecondsUntilExpiration_MetaData), Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::NewProp_SecondsUntilExpiration_MetaData) };
	void Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((RuntimeDataTableWebToken_eventInit_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RuntimeDataTableWebToken_eventInit_Parms), &Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::NewProp_InTokenText,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::NewProp_SecondsUntilExpiration,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* Initialize the token with the appropriate information */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Initialize the token with the appropriate information" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableWebToken, nullptr, "Init", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::RuntimeDataTableWebToken_eventInit_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::RuntimeDataTableWebToken_eventInit_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableWebToken_Init()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableWebToken_Init_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(URuntimeDataTableWebToken);
	UClass* Z_Construct_UClass_URuntimeDataTableWebToken_NoRegister()
	{
		return URuntimeDataTableWebToken::StaticClass();
	}
	struct Z_Construct_UClass_URuntimeDataTableWebToken_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_URuntimeDataTableWebToken_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_RuntimeDataTable,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableWebToken_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_URuntimeDataTableWebToken_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_URuntimeDataTableWebToken_GetNumberOfSecondsUntilExpiration, "GetNumberOfSecondsUntilExpiration" }, // 1840314077
		{ &Z_Construct_UFunction_URuntimeDataTableWebToken_GetTokenText, "GetTokenText" }, // 2156365908
		{ &Z_Construct_UFunction_URuntimeDataTableWebToken_HasTokenExpired, "HasTokenExpired" }, // 2212012421
		{ &Z_Construct_UFunction_URuntimeDataTableWebToken_Init, "Init" }, // 3088750327
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableWebToken_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableWebToken_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// A class that contains authentication token information\n" },
#endif
		{ "IncludePath", "RuntimeDataTable.h" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A class that contains authentication token information" },
#endif
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_URuntimeDataTableWebToken_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URuntimeDataTableWebToken>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_URuntimeDataTableWebToken_Statics::ClassParams = {
		&URuntimeDataTableWebToken::StaticClass,
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
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableWebToken_Statics::Class_MetaDataParams), Z_Construct_UClass_URuntimeDataTableWebToken_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_URuntimeDataTableWebToken()
	{
		if (!Z_Registration_Info_UClass_URuntimeDataTableWebToken.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URuntimeDataTableWebToken.OuterSingleton, Z_Construct_UClass_URuntimeDataTableWebToken_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_URuntimeDataTableWebToken.OuterSingleton;
	}
	template<> RUNTIMEDATATABLE_API UClass* StaticClass<URuntimeDataTableWebToken>()
	{
		return URuntimeDataTableWebToken::StaticClass();
	}
	URuntimeDataTableWebToken::URuntimeDataTableWebToken(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(URuntimeDataTableWebToken);
	URuntimeDataTableWebToken::~URuntimeDataTableWebToken() {}
	DEFINE_FUNCTION(URuntimeDataTableObject::execGetAllObjectVariableNames)
	{
		P_GET_OBJECT(UObject,Z_Param_Object);
		P_GET_UBOOL(Z_Param_bIncludeOnlyConfigVariables);
		P_GET_UBOOL(Z_Param_bIncludeInheritedVariables);
		P_GET_PROPERTY(FStrProperty,Z_Param_MemberBlacklist);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=URuntimeDataTableObject::GetAllObjectVariableNames(Z_Param_Object,Z_Param_bIncludeOnlyConfigVariables,Z_Param_bIncludeInheritedVariables,Z_Param_MemberBlacklist);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableObject::execWriteCsvToSheet)
	{
		P_GET_STRUCT(FRuntimeDataTableTokenInfo,Z_Param_InTokenInfo);
		P_GET_STRUCT(FRuntimeDataTableOperationParams,Z_Param_OperationParams);
		P_GET_PROPERTY_REF(FDelegateProperty,Z_Param_Out_CallOnComplete);
		P_GET_PROPERTY(FStrProperty,Z_Param_InSpreadsheetId);
		P_GET_PROPERTY(FIntProperty,Z_Param_InSheetId);
		P_GET_PROPERTY(FStrProperty,Z_Param_InCsv);
		P_FINISH;
		P_NATIVE_BEGIN;
		URuntimeDataTableObject::WriteCsvToSheet(Z_Param_InTokenInfo,Z_Param_OperationParams,FRDTGetStringDelegate(Z_Param_Out_CallOnComplete),Z_Param_InSpreadsheetId,Z_Param_InSheetId,Z_Param_InCsv);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableObject::execValidateGoogleSheetsDownloadAndLoadBackupIfNeeded)
	{
		P_GET_STRUCT(FRuntimeDataTableCallbackInfo,Z_Param_InCallbackInfo);
		P_GET_STRUCT_REF(FEasyCsvInfo,Z_Param_Out_OutCsvInfo);
		P_GET_ENUM_REF(ERuntimeDataTableBackupResultCode,Z_Param_Out_OutResultCode);
		P_GET_PROPERTY(FStrProperty,Z_Param_BackupSavePath);
		P_GET_PROPERTY(FStrProperty,Z_Param_BackupLoadPath);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=URuntimeDataTableObject::ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded(Z_Param_InCallbackInfo,Z_Param_Out_OutCsvInfo,(ERuntimeDataTableBackupResultCode&)(Z_Param_Out_OutResultCode),Z_Param_BackupSavePath,Z_Param_BackupLoadPath);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableObject::execBuildGoogleSheetDownloadLinkAndGetAsCsv)
	{
		P_GET_STRUCT(FRuntimeDataTableTokenInfo,Z_Param_InTokenInfo);
		P_GET_STRUCT(FRuntimeDataTableOperationParams,Z_Param_OperationParams);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CallOnComplete);
		P_GET_PROPERTY(FStrProperty,Z_Param_InSheetURL);
		P_GET_UBOOL(Z_Param_bSheetIsPublic);
		P_FINISH;
		P_NATIVE_BEGIN;
		URuntimeDataTableObject::BuildGoogleSheetDownloadLinkAndGetAsCsv(Z_Param_InTokenInfo,Z_Param_OperationParams,FRDTGetStringDelegate(Z_Param_CallOnComplete),Z_Param_InSheetURL,Z_Param_bSheetIsPublic);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableObject::execAutoGenerateKeys)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FName>*)Z_Param__Result=URuntimeDataTableObject::AutoGenerateKeys();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableObject::execGetGoogleSheetsBatchUpdateURL)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InSpreadsheetId);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=URuntimeDataTableObject::GetGoogleSheetsBatchUpdateURL(Z_Param_InSpreadsheetId);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableObject::execGetGoogleSheetsValuesBatchUpdateURL)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InSpreadsheetId);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=URuntimeDataTableObject::GetGoogleSheetsValuesBatchUpdateURL(Z_Param_InSpreadsheetId);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableObject::execGetGoogleSheetsApiUrlPrefix)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=URuntimeDataTableObject::GetGoogleSheetsApiUrlPrefix();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableObject::execGetMimeCsv)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=URuntimeDataTableObject::GetMimeCsv();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableObject::execGetGoogleSheetsUrlPrefix)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=URuntimeDataTableObject::GetGoogleSheetsUrlPrefix();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableObject::execGetSheetIdFromUrl_Int)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_SheetURL);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=URuntimeDataTableObject::GetSheetIdFromUrl_Int(Z_Param_SheetURL);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableObject::execGetSheetIdFromUrl)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_SheetURL);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=URuntimeDataTableObject::GetSheetIdFromUrl(Z_Param_SheetURL);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableObject::execGetSpreadsheetIdFromUrl)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_SheetURL);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=URuntimeDataTableObject::GetSpreadsheetIdFromUrl(Z_Param_SheetURL);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableObject::execGenerateTokenInfoFromFile)
	{
		P_GET_STRUCT_REF(FRuntimeDataTableTokenInfo,Z_Param_Out_OutTokenInfo);
		P_GET_PROPERTY(FStrProperty,Z_Param_InPathToFile);
		P_GET_PROPERTY(FIntProperty,Z_Param_DesiredSecondsUntilExpiration);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=URuntimeDataTableObject::GenerateTokenInfoFromFile(Z_Param_Out_OutTokenInfo,Z_Param_InPathToFile,Z_Param_DesiredSecondsUntilExpiration);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URuntimeDataTableObject::execGenerateTokenInfoFromString)
	{
		P_GET_STRUCT_REF(FRuntimeDataTableTokenInfo,Z_Param_Out_OutTokenInfo);
		P_GET_PROPERTY(FStrProperty,Z_Param_InJsonString);
		P_GET_PROPERTY(FIntProperty,Z_Param_DesiredSecondsUntilExpiration);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=URuntimeDataTableObject::GenerateTokenInfoFromString(Z_Param_Out_OutTokenInfo,Z_Param_InJsonString,Z_Param_DesiredSecondsUntilExpiration);
		P_NATIVE_END;
	}
	void URuntimeDataTableObject::StaticRegisterNativesURuntimeDataTableObject()
	{
		UClass* Class = URuntimeDataTableObject::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AutoGenerateKeys", &URuntimeDataTableObject::execAutoGenerateKeys },
			{ "BuildGoogleSheetDownloadLinkAndGetAsCsv", &URuntimeDataTableObject::execBuildGoogleSheetDownloadLinkAndGetAsCsv },
			{ "GenerateCsvFromArray", &URuntimeDataTableObject::execGenerateCsvFromArray },
			{ "GenerateTokenInfoFromFile", &URuntimeDataTableObject::execGenerateTokenInfoFromFile },
			{ "GenerateTokenInfoFromString", &URuntimeDataTableObject::execGenerateTokenInfoFromString },
			{ "GetAllObjectVariableNames", &URuntimeDataTableObject::execGetAllObjectVariableNames },
			{ "GetGoogleSheetsApiUrlPrefix", &URuntimeDataTableObject::execGetGoogleSheetsApiUrlPrefix },
			{ "GetGoogleSheetsBatchUpdateURL", &URuntimeDataTableObject::execGetGoogleSheetsBatchUpdateURL },
			{ "GetGoogleSheetsUrlPrefix", &URuntimeDataTableObject::execGetGoogleSheetsUrlPrefix },
			{ "GetGoogleSheetsValuesBatchUpdateURL", &URuntimeDataTableObject::execGetGoogleSheetsValuesBatchUpdateURL },
			{ "GetMimeCsv", &URuntimeDataTableObject::execGetMimeCsv },
			{ "GetSheetIdFromUrl", &URuntimeDataTableObject::execGetSheetIdFromUrl },
			{ "GetSheetIdFromUrl_Int", &URuntimeDataTableObject::execGetSheetIdFromUrl_Int },
			{ "GetSpreadsheetIdFromUrl", &URuntimeDataTableObject::execGetSpreadsheetIdFromUrl },
			{ "UpdateArrayFromCsvInfo", &URuntimeDataTableObject::execUpdateArrayFromCsvInfo },
			{ "ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded", &URuntimeDataTableObject::execValidateGoogleSheetsDownloadAndLoadBackupIfNeeded },
			{ "WriteCsvToSheet", &URuntimeDataTableObject::execWriteCsvToSheet },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics
	{
		struct RuntimeDataTableObject_eventAutoGenerateKeys_Parms
		{
			TArray<FName> ReturnValue;
		};
		static const UECodeGen_Private::FNamePropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventAutoGenerateKeys_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::Function_MetaDataParams[] = {
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * If you want to have row keys generated for you on export, insert the return value from this function into the export function's \"Keys\" parameter. You can also use \"Make Array\" with blank entries in blueprint or create a new TArray<FName> (or simply \"{}\") in C++ if you prefer.\n\x09 * @return This is a blank array of FName. This signifies to the function that we should generate row keys on export. \n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If you want to have row keys generated for you on export, insert the return value from this function into the export function's \"Keys\" parameter. You can also use \"Make Array\" with blank entries in blueprint or create a new TArray<FName> (or simply \"{}\") in C++ if you prefer.\n@return This is a blank array of FName. This signifies to the function that we should generate row keys on export." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "AutoGenerateKeys", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::RuntimeDataTableObject_eventAutoGenerateKeys_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::RuntimeDataTableObject_eventAutoGenerateKeys_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics
	{
		struct RuntimeDataTableObject_eventBuildGoogleSheetDownloadLinkAndGetAsCsv_Parms
		{
			FRuntimeDataTableTokenInfo InTokenInfo;
			FRuntimeDataTableOperationParams OperationParams;
			FScriptDelegate CallOnComplete;
			FString InSheetURL;
			bool bSheetIsPublic;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InTokenInfo_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_InTokenInfo;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OperationParams_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_OperationParams;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CallOnComplete_MetaData[];
#endif
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CallOnComplete;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InSheetURL_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InSheetURL;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bSheetIsPublic_MetaData[];
#endif
		static void NewProp_bSheetIsPublic_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bSheetIsPublic;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_InTokenInfo_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_InTokenInfo = { "InTokenInfo", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventBuildGoogleSheetDownloadLinkAndGetAsCsv_Parms, InTokenInfo), Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_InTokenInfo_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_InTokenInfo_MetaData) }; // 546094522
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_OperationParams_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_OperationParams = { "OperationParams", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventBuildGoogleSheetDownloadLinkAndGetAsCsv_Parms, OperationParams), Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_OperationParams_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_OperationParams_MetaData) }; // 1745228001
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_CallOnComplete_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_CallOnComplete = { "CallOnComplete", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventBuildGoogleSheetDownloadLinkAndGetAsCsv_Parms, CallOnComplete), Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_CallOnComplete_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_CallOnComplete_MetaData) }; // 3660932638
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_InSheetURL_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_InSheetURL = { "InSheetURL", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventBuildGoogleSheetDownloadLinkAndGetAsCsv_Parms, InSheetURL), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_InSheetURL_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_InSheetURL_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_bSheetIsPublic_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_bSheetIsPublic_SetBit(void* Obj)
	{
		((RuntimeDataTableObject_eventBuildGoogleSheetDownloadLinkAndGetAsCsv_Parms*)Obj)->bSheetIsPublic = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_bSheetIsPublic = { "bSheetIsPublic", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RuntimeDataTableObject_eventBuildGoogleSheetDownloadLinkAndGetAsCsv_Parms), &Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_bSheetIsPublic_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_bSheetIsPublic_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_bSheetIsPublic_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_InTokenInfo,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_OperationParams,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_CallOnComplete,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_InSheetURL,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::NewProp_bSheetIsPublic,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::Function_MetaDataParams[] = {
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Get any full sheet as CSV. This works for public or private sheets, provided you are authenticated. Set bSheetIsPublic to true if your sheet is public.\n\x09 * @param InTokenInfo A validated URuntimeDataTableWebToken object. Used to authenticate the Sheets operation. Can be default if the sheet is public.\n\x09 * @param OperationParams Generic request operation parameters\n\x09 * @param InSheetURL The URL at which this sheet can be found.\n\x09 * @param CallOnComplete This delegate will be called when the operation completes and tell you whether or not it was successful and return the response as a string.\n     * @param bSheetIsPublic Set this parameter to true if your sheet does not require authentication because it is public and you have not provided a valid InTokenInfo. This avoids token validation.\n\x09*/" },
#endif
		{ "CPP_Default_bSheetIsPublic", "false" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get any full sheet as CSV. This works for public or private sheets, provided you are authenticated. Set bSheetIsPublic to true if your sheet is public.\n@param InTokenInfo A validated URuntimeDataTableWebToken object. Used to authenticate the Sheets operation. Can be default if the sheet is public.\n@param OperationParams Generic request operation parameters\n@param InSheetURL The URL at which this sheet can be found.\n@param CallOnComplete This delegate will be called when the operation completes and tell you whether or not it was successful and return the response as a string.\n@param bSheetIsPublic Set this parameter to true if your sheet does not require authentication because it is public and you have not provided a valid InTokenInfo. This avoids token validation." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "BuildGoogleSheetDownloadLinkAndGetAsCsv", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::RuntimeDataTableObject_eventBuildGoogleSheetDownloadLinkAndGetAsCsv_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::RuntimeDataTableObject_eventBuildGoogleSheetDownloadLinkAndGetAsCsv_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics
	{
		struct RuntimeDataTableObject_eventGenerateCsvFromArray_Parms
		{
			TArray<int32> ArrayToExport;
			FString OutCSV_String;
			TArray<FName> Keys;
			FString MembersToInclude;
			bool bSortColumnsAlphanumerically;
			const UObject* OwningObject;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ArrayToExport_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ArrayToExport_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ArrayToExport;
		static const UECodeGen_Private::FStrPropertyParams NewProp_OutCSV_String;
		static const UECodeGen_Private::FNamePropertyParams NewProp_Keys_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Keys;
		static const UECodeGen_Private::FStrPropertyParams NewProp_MembersToInclude;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bSortColumnsAlphanumerically_MetaData[];
#endif
		static void NewProp_bSortColumnsAlphanumerically_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bSortColumnsAlphanumerically;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OwningObject_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OwningObject;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_ArrayToExport_Inner = { "ArrayToExport", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_ArrayToExport_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_ArrayToExport = { "ArrayToExport", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGenerateCsvFromArray_Parms, ArrayToExport), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_ArrayToExport_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_ArrayToExport_MetaData) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_OutCSV_String = { "OutCSV_String", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGenerateCsvFromArray_Parms, OutCSV_String), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_Keys_Inner = { "Keys", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_Keys = { "Keys", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGenerateCsvFromArray_Parms, Keys), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_MembersToInclude = { "MembersToInclude", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGenerateCsvFromArray_Parms, MembersToInclude), METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_bSortColumnsAlphanumerically_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_bSortColumnsAlphanumerically_SetBit(void* Obj)
	{
		((RuntimeDataTableObject_eventGenerateCsvFromArray_Parms*)Obj)->bSortColumnsAlphanumerically = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_bSortColumnsAlphanumerically = { "bSortColumnsAlphanumerically", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RuntimeDataTableObject_eventGenerateCsvFromArray_Parms), &Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_bSortColumnsAlphanumerically_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_bSortColumnsAlphanumerically_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_bSortColumnsAlphanumerically_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_OwningObject_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_OwningObject = { "OwningObject", nullptr, (EPropertyFlags)0x0010040000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGenerateCsvFromArray_Parms, OwningObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_OwningObject_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_OwningObject_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_ArrayToExport_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_ArrayToExport,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_OutCSV_String,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_Keys_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_Keys,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_MembersToInclude,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_bSortColumnsAlphanumerically,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::NewProp_OwningObject,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::Function_MetaDataParams[] = {
		{ "AdvancedDisplay", "OwningObject" },
		{ "ArrayParm", "ArrayToExport" },
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Attempts to build a CSV from an array of structs/objects. Takes a set of Keys for the first column of the CSV and an array of FNames to act as a variable whitelist. Note that if you use a whitelist for a struct array, you'll need to always use MatchStructMemberNames when importing data for that struct in the future.\n\x09 * Does not return an RDT actor or call a delegate. Returns a boolean reflecting whether successfully able to write to disk.\n\x09 * @param ArrayToExport An array of the structs or objects you'd like to export.\n\x09 * @param OutCSV_String A string representing the array data in CSV form.\n\x09 * @param Keys A set of keys used in the first column of the CSV to uniquely identify rows. Does not enforce unique values, so be sure to do that prior to calling. An array is required, but you don't need to match the number of keys to the number of structs. They will be auto-generated if not supplied in matching numbers. For all generated keys, use \"AutoGenerateKeys().\"\n\x09 * @param MembersToInclude Optional: Names of variables in your structs or objects that you want to export. Separate names by comma. Leave blank to include all variables, but be careful when using objects. Leaving this blank will include EVERY variable name including inherited and engine variables. For help creating this whitelist for objects, see GetAllObjectVariableNames().\n\x09 * @param bSortColumnsAlphanumerically If true, sort columns 0->9, A->Z\n\x09 * @param OwningObject The object or instantiation of a class that has the struct array as one of its variables. Defaults to the calling object or 'Self' and only applies to struct arrays.\n\x09 */" },
#endif
		{ "CustomThunk", "true" },
		{ "DefaultToSelf", "OwningObject" },
		{ "Keywords", "Export, String" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Attempts to build a CSV from an array of structs/objects. Takes a set of Keys for the first column of the CSV and an array of FNames to act as a variable whitelist. Note that if you use a whitelist for a struct array, you'll need to always use MatchStructMemberNames when importing data for that struct in the future.\nDoes not return an RDT actor or call a delegate. Returns a boolean reflecting whether successfully able to write to disk.\n@param ArrayToExport An array of the structs or objects you'd like to export.\n@param OutCSV_String A string representing the array data in CSV form.\n@param Keys A set of keys used in the first column of the CSV to uniquely identify rows. Does not enforce unique values, so be sure to do that prior to calling. An array is required, but you don't need to match the number of keys to the number of structs. They will be auto-generated if not supplied in matching numbers. For all generated keys, use \"AutoGenerateKeys().\"\n@param MembersToInclude Optional: Names of variables in your structs or objects that you want to export. Separate names by comma. Leave blank to include all variables, but be careful when using objects. Leaving this blank will include EVERY variable name including inherited and engine variables. For help creating this whitelist for objects, see GetAllObjectVariableNames().\n@param bSortColumnsAlphanumerically If true, sort columns 0->9, A->Z\n@param OwningObject The object or instantiation of a class that has the struct array as one of its variables. Defaults to the calling object or 'Self' and only applies to struct arrays." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "GenerateCsvFromArray", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::RuntimeDataTableObject_eventGenerateCsvFromArray_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::RuntimeDataTableObject_eventGenerateCsvFromArray_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics
	{
		struct RuntimeDataTableObject_eventGenerateTokenInfoFromFile_Parms
		{
			FRuntimeDataTableTokenInfo OutTokenInfo;
			FString InPathToFile;
			int32 DesiredSecondsUntilExpiration;
			bool ReturnValue;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_OutTokenInfo;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InPathToFile_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InPathToFile;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DesiredSecondsUntilExpiration_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_DesiredSecondsUntilExpiration;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_OutTokenInfo = { "OutTokenInfo", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGenerateTokenInfoFromFile_Parms, OutTokenInfo), Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo, METADATA_PARAMS(0, nullptr) }; // 546094522
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_InPathToFile_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_InPathToFile = { "InPathToFile", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGenerateTokenInfoFromFile_Parms, InPathToFile), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_InPathToFile_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_InPathToFile_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_DesiredSecondsUntilExpiration_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_DesiredSecondsUntilExpiration = { "DesiredSecondsUntilExpiration", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGenerateTokenInfoFromFile_Parms, DesiredSecondsUntilExpiration), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_DesiredSecondsUntilExpiration_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_DesiredSecondsUntilExpiration_MetaData) };
	void Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((RuntimeDataTableObject_eventGenerateTokenInfoFromFile_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RuntimeDataTableObject_eventGenerateTokenInfoFromFile_Parms), &Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_OutTokenInfo,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_InPathToFile,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_DesiredSecondsUntilExpiration,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::Function_MetaDataParams[] = {
		{ "Category", "Runtime DataTable|Token" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Generate an FGoogleSheetsTokenInfo struct from a file.\n\x09 * If you have a json key file downloaded from your Google Service Account, you can create this struct by loading the file instead of copying the data into a Make node.\n\x09 * If you wish not to keep the file accessible on disk, call GenerateTokenInfoFromString() instead.\n\x09 * @param OutTokenInfo A FGoogleSheetsTokenInfo struct used to create and authenticate a URuntimeDataTableWebToken.\n\x09 * @param InPathToFile Where on disk the key file resides.\n\x09 * @param DesiredSecondsUntilExpiration How long should this token last? Min is 1 second, Max is 3600 seconds (1 hour). Generally it's best practice to keep the expiration short and generate a new token for each operation.\n\x09 * @return Returns true if the file could be loaded, parsed, and had the required information to create a token.\n\x09 */" },
#endif
		{ "CPP_Default_DesiredSecondsUntilExpiration", "60" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Generate an FGoogleSheetsTokenInfo struct from a file.\nIf you have a json key file downloaded from your Google Service Account, you can create this struct by loading the file instead of copying the data into a Make node.\nIf you wish not to keep the file accessible on disk, call GenerateTokenInfoFromString() instead.\n@param OutTokenInfo A FGoogleSheetsTokenInfo struct used to create and authenticate a URuntimeDataTableWebToken.\n@param InPathToFile Where on disk the key file resides.\n@param DesiredSecondsUntilExpiration How long should this token last? Min is 1 second, Max is 3600 seconds (1 hour). Generally it's best practice to keep the expiration short and generate a new token for each operation.\n@return Returns true if the file could be loaded, parsed, and had the required information to create a token." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "GenerateTokenInfoFromFile", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::RuntimeDataTableObject_eventGenerateTokenInfoFromFile_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::RuntimeDataTableObject_eventGenerateTokenInfoFromFile_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics
	{
		struct RuntimeDataTableObject_eventGenerateTokenInfoFromString_Parms
		{
			FRuntimeDataTableTokenInfo OutTokenInfo;
			FString InJsonString;
			int32 DesiredSecondsUntilExpiration;
			bool ReturnValue;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_OutTokenInfo;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InJsonString_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InJsonString;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DesiredSecondsUntilExpiration_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_DesiredSecondsUntilExpiration;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_OutTokenInfo = { "OutTokenInfo", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGenerateTokenInfoFromString_Parms, OutTokenInfo), Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo, METADATA_PARAMS(0, nullptr) }; // 546094522
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_InJsonString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_InJsonString = { "InJsonString", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGenerateTokenInfoFromString_Parms, InJsonString), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_InJsonString_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_InJsonString_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_DesiredSecondsUntilExpiration_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_DesiredSecondsUntilExpiration = { "DesiredSecondsUntilExpiration", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGenerateTokenInfoFromString_Parms, DesiredSecondsUntilExpiration), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_DesiredSecondsUntilExpiration_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_DesiredSecondsUntilExpiration_MetaData) };
	void Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((RuntimeDataTableObject_eventGenerateTokenInfoFromString_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RuntimeDataTableObject_eventGenerateTokenInfoFromString_Parms), &Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_OutTokenInfo,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_InJsonString,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_DesiredSecondsUntilExpiration,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::Function_MetaDataParams[] = {
		{ "Category", "Runtime DataTable|Token" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Generate an FGoogleSheetsTokenInfo struct from a string. This is the same data found in the json key file downloaded from your Google Service Account.\n\x09 * If you prefer to just load the file, call GenerateTokenInfoFromFile instead.\n\x09 * This function is for users who wish to not keep the private key in an accessible file. Alternatively, you can use a Make node.\n\x09 * @param OutTokenInfo A FGoogleSheetsTokenInfo struct used to create and authenticate a URuntimeDataTableWebToken.\n\x09 * @param InJsonString The contents of a private key file\n\x09 * @param DesiredSecondsUntilExpiration How long should this token last? Min is 1 second, Max is 3600 seconds (1 hour). Generally it's best practice to keep the expiration short and generate a new token for each operation.\n\x09 * @return Returns true if the file could be loaded, parsed, and had the required information to create a token.\n\x09 */" },
#endif
		{ "CPP_Default_DesiredSecondsUntilExpiration", "60" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Generate an FGoogleSheetsTokenInfo struct from a string. This is the same data found in the json key file downloaded from your Google Service Account.\nIf you prefer to just load the file, call GenerateTokenInfoFromFile instead.\nThis function is for users who wish to not keep the private key in an accessible file. Alternatively, you can use a Make node.\n@param OutTokenInfo A FGoogleSheetsTokenInfo struct used to create and authenticate a URuntimeDataTableWebToken.\n@param InJsonString The contents of a private key file\n@param DesiredSecondsUntilExpiration How long should this token last? Min is 1 second, Max is 3600 seconds (1 hour). Generally it's best practice to keep the expiration short and generate a new token for each operation.\n@return Returns true if the file could be loaded, parsed, and had the required information to create a token." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "GenerateTokenInfoFromString", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::RuntimeDataTableObject_eventGenerateTokenInfoFromString_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::RuntimeDataTableObject_eventGenerateTokenInfoFromString_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics
	{
		struct RuntimeDataTableObject_eventGetAllObjectVariableNames_Parms
		{
			const UObject* Object;
			bool bIncludeOnlyConfigVariables;
			bool bIncludeInheritedVariables;
			FString MemberBlacklist;
			FString ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Object_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Object;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bIncludeOnlyConfigVariables_MetaData[];
#endif
		static void NewProp_bIncludeOnlyConfigVariables_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIncludeOnlyConfigVariables;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bIncludeInheritedVariables_MetaData[];
#endif
		static void NewProp_bIncludeInheritedVariables_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIncludeInheritedVariables;
		static const UECodeGen_Private::FStrPropertyParams NewProp_MemberBlacklist;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_Object_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_Object = { "Object", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetAllObjectVariableNames_Parms, Object), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_Object_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_Object_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_bIncludeOnlyConfigVariables_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_bIncludeOnlyConfigVariables_SetBit(void* Obj)
	{
		((RuntimeDataTableObject_eventGetAllObjectVariableNames_Parms*)Obj)->bIncludeOnlyConfigVariables = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_bIncludeOnlyConfigVariables = { "bIncludeOnlyConfigVariables", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RuntimeDataTableObject_eventGetAllObjectVariableNames_Parms), &Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_bIncludeOnlyConfigVariables_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_bIncludeOnlyConfigVariables_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_bIncludeOnlyConfigVariables_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_bIncludeInheritedVariables_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_bIncludeInheritedVariables_SetBit(void* Obj)
	{
		((RuntimeDataTableObject_eventGetAllObjectVariableNames_Parms*)Obj)->bIncludeInheritedVariables = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_bIncludeInheritedVariables = { "bIncludeInheritedVariables", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RuntimeDataTableObject_eventGetAllObjectVariableNames_Parms), &Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_bIncludeInheritedVariables_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_bIncludeInheritedVariables_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_bIncludeInheritedVariables_MetaData) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_MemberBlacklist = { "MemberBlacklist", nullptr, (EPropertyFlags)0x0010040000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetAllObjectVariableNames_Parms, MemberBlacklist), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetAllObjectVariableNames_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_Object,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_bIncludeOnlyConfigVariables,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_bIncludeInheritedVariables,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_MemberBlacklist,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::Function_MetaDataParams[] = {
		{ "AdvancedDisplay", "IncludeInheritedVariables, MemberBlacklist" },
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns all of the variables, including components, attached to a given object. Excludes \"UberGraphFrame\" & \"DefaultSceneRoot\" by default.\n\x09 * @param Object The object with the variables you want to list. Defaults to the calling object or 'Self'.\n\x09 * @param bIncludeOnlyConfigVariables If true, only members marked as \"Config\" in blueprint or given the CPF_Config PropertyFlag in C++ will be included, assuming they are not blacklisted. If none are marked as Config, no variables will be included.\n\x09 * @param bIncludeInheritedVariables If true will include all variables from parent classes as well. Keep in mind this means the Super classes too, so you may end up with a lot of variables you don't want. You'll need to filter these out yourself. Try overloading a method from the desired base class all the way down.\n\x09 * @param MemberBlacklist A comma-separated list of members you do NOT want to return. Useful for filtering out members that don't matter to you. Ex: \"ActorScale, ActorColor, ActorRotation\"\n\x09 */" },
#endif
		{ "CPP_Default_bIncludeInheritedVariables", "false" },
		{ "CPP_Default_bIncludeOnlyConfigVariables", "false" },
		{ "CPP_Default_MemberBlacklist", "UberGraphFrame, DefaultSceneRoot" },
		{ "DefaultToSelf", "Object" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns all of the variables, including components, attached to a given object. Excludes \"UberGraphFrame\" & \"DefaultSceneRoot\" by default.\n@param Object The object with the variables you want to list. Defaults to the calling object or 'Self'.\n@param bIncludeOnlyConfigVariables If true, only members marked as \"Config\" in blueprint or given the CPF_Config PropertyFlag in C++ will be included, assuming they are not blacklisted. If none are marked as Config, no variables will be included.\n@param bIncludeInheritedVariables If true will include all variables from parent classes as well. Keep in mind this means the Super classes too, so you may end up with a lot of variables you don't want. You'll need to filter these out yourself. Try overloading a method from the desired base class all the way down.\n@param MemberBlacklist A comma-separated list of members you do NOT want to return. Useful for filtering out members that don't matter to you. Ex: \"ActorScale, ActorColor, ActorRotation\"" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "GetAllObjectVariableNames", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::RuntimeDataTableObject_eventGetAllObjectVariableNames_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::RuntimeDataTableObject_eventGetAllObjectVariableNames_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix_Statics
	{
		struct RuntimeDataTableObject_eventGetGoogleSheetsApiUrlPrefix_Parms
		{
			FString ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetGoogleSheetsApiUrlPrefix_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix_Statics::Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// sheets.googleapis.com/v4/spreadsheets/\n" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "sheets.googleapis.com/v4/spreadsheets/" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "GetGoogleSheetsApiUrlPrefix", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix_Statics::RuntimeDataTableObject_eventGetGoogleSheetsApiUrlPrefix_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix_Statics::RuntimeDataTableObject_eventGetGoogleSheetsApiUrlPrefix_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics
	{
		struct RuntimeDataTableObject_eventGetGoogleSheetsBatchUpdateURL_Parms
		{
			FString InSpreadsheetId;
			FString ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InSpreadsheetId_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InSpreadsheetId;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::NewProp_InSpreadsheetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::NewProp_InSpreadsheetId = { "InSpreadsheetId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetGoogleSheetsBatchUpdateURL_Parms, InSpreadsheetId), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::NewProp_InSpreadsheetId_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::NewProp_InSpreadsheetId_MetaData) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetGoogleSheetsBatchUpdateURL_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::NewProp_InSpreadsheetId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// sheets.googleapis.com/v4/spreadsheets/{spreadsheetId}:batchUpdate\n" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "sheets.googleapis.com/v4/spreadsheets/{spreadsheetId}:batchUpdate" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "GetGoogleSheetsBatchUpdateURL", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::RuntimeDataTableObject_eventGetGoogleSheetsBatchUpdateURL_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::RuntimeDataTableObject_eventGetGoogleSheetsBatchUpdateURL_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix_Statics
	{
		struct RuntimeDataTableObject_eventGetGoogleSheetsUrlPrefix_Parms
		{
			FString ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetGoogleSheetsUrlPrefix_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix_Statics::Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// docs.google.com/spreadsheets/d/\n" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "docs.google.com/spreadsheets/d/" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "GetGoogleSheetsUrlPrefix", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix_Statics::RuntimeDataTableObject_eventGetGoogleSheetsUrlPrefix_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix_Statics::RuntimeDataTableObject_eventGetGoogleSheetsUrlPrefix_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics
	{
		struct RuntimeDataTableObject_eventGetGoogleSheetsValuesBatchUpdateURL_Parms
		{
			FString InSpreadsheetId;
			FString ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InSpreadsheetId_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InSpreadsheetId;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::NewProp_InSpreadsheetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::NewProp_InSpreadsheetId = { "InSpreadsheetId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetGoogleSheetsValuesBatchUpdateURL_Parms, InSpreadsheetId), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::NewProp_InSpreadsheetId_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::NewProp_InSpreadsheetId_MetaData) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetGoogleSheetsValuesBatchUpdateURL_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::NewProp_InSpreadsheetId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// sheets.googleapis.com/v4/spreadsheets/{spreadsheetId}/values:batchUpdate\n" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "sheets.googleapis.com/v4/spreadsheets/{spreadsheetId}/values:batchUpdate" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "GetGoogleSheetsValuesBatchUpdateURL", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::RuntimeDataTableObject_eventGetGoogleSheetsValuesBatchUpdateURL_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::RuntimeDataTableObject_eventGetGoogleSheetsValuesBatchUpdateURL_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv_Statics
	{
		struct RuntimeDataTableObject_eventGetMimeCsv_Parms
		{
			FString ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetMimeCsv_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "GetMimeCsv", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv_Statics::RuntimeDataTableObject_eventGetMimeCsv_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv_Statics::RuntimeDataTableObject_eventGetMimeCsv_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics
	{
		struct RuntimeDataTableObject_eventGetSheetIdFromUrl_Parms
		{
			FString SheetURL;
			FString ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SheetURL_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_SheetURL;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::NewProp_SheetURL_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::NewProp_SheetURL = { "SheetURL", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetSheetIdFromUrl_Parms, SheetURL), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::NewProp_SheetURL_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::NewProp_SheetURL_MetaData) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetSheetIdFromUrl_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::NewProp_SheetURL,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::Function_MetaDataParams[] = {
		{ "Category", "Runtime DataTable|Google Sheets" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns the GID from a Google Sheet URL. The GID identifies a specific sheet or tab. Returns empty if the gid is not present.\n\x09 */" },
#endif
		{ "Keywords", "gid, key" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns the GID from a Google Sheet URL. The GID identifies a specific sheet or tab. Returns empty if the gid is not present." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "GetSheetIdFromUrl", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::RuntimeDataTableObject_eventGetSheetIdFromUrl_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::RuntimeDataTableObject_eventGetSheetIdFromUrl_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics
	{
		struct RuntimeDataTableObject_eventGetSheetIdFromUrl_Int_Parms
		{
			FString SheetURL;
			int32 ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SheetURL_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_SheetURL;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::NewProp_SheetURL_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::NewProp_SheetURL = { "SheetURL", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetSheetIdFromUrl_Int_Parms, SheetURL), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::NewProp_SheetURL_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::NewProp_SheetURL_MetaData) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetSheetIdFromUrl_Int_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::NewProp_SheetURL,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::Function_MetaDataParams[] = {
		{ "Category", "Runtime DataTable|Google Sheets" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns the GID from a Google Sheet URL. The GID identifies a specific sheet or tab. Returns empty if the gid is not present.\n\x09 */" },
#endif
		{ "Keywords", "gid, key" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns the GID from a Google Sheet URL. The GID identifies a specific sheet or tab. Returns empty if the gid is not present." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "GetSheetIdFromUrl_Int", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::RuntimeDataTableObject_eventGetSheetIdFromUrl_Int_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::RuntimeDataTableObject_eventGetSheetIdFromUrl_Int_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics
	{
		struct RuntimeDataTableObject_eventGetSpreadsheetIdFromUrl_Parms
		{
			FString SheetURL;
			FString ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SheetURL_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_SheetURL;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::NewProp_SheetURL_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::NewProp_SheetURL = { "SheetURL", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetSpreadsheetIdFromUrl_Parms, SheetURL), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::NewProp_SheetURL_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::NewProp_SheetURL_MetaData) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventGetSpreadsheetIdFromUrl_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::NewProp_SheetURL,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::Function_MetaDataParams[] = {
		{ "Category", "Runtime DataTable|Google Sheets" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Returns the Sheet ID from a Google Sheet URL. This identifies a spreadsheet asset.\n\x09 */" },
#endif
		{ "Keywords", "key" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns the Sheet ID from a Google Sheet URL. This identifies a spreadsheet asset." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "GetSpreadsheetIdFromUrl", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::RuntimeDataTableObject_eventGetSpreadsheetIdFromUrl_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::RuntimeDataTableObject_eventGetSpreadsheetIdFromUrl_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics
	{
		struct RuntimeDataTableObject_eventUpdateArrayFromCsvInfo_Parms
		{
			TArray<int32> ArrayToUpdate;
			bool Successful;
			FEasyCsvInfo CSVInfo;
			bool MatchStructMemberNames;
			const UObject* OwningObject;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ArrayToUpdate_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ArrayToUpdate_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ArrayToUpdate;
		static void NewProp_Successful_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_Successful;
		static const UECodeGen_Private::FStructPropertyParams NewProp_CSVInfo;
		static void NewProp_MatchStructMemberNames_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_MatchStructMemberNames;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OwningObject_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OwningObject;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_ArrayToUpdate_Inner = { "ArrayToUpdate", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_ArrayToUpdate_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_ArrayToUpdate = { "ArrayToUpdate", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventUpdateArrayFromCsvInfo_Parms, ArrayToUpdate), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_ArrayToUpdate_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_ArrayToUpdate_MetaData) };
	void Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_Successful_SetBit(void* Obj)
	{
		((RuntimeDataTableObject_eventUpdateArrayFromCsvInfo_Parms*)Obj)->Successful = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_Successful = { "Successful", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RuntimeDataTableObject_eventUpdateArrayFromCsvInfo_Parms), &Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_Successful_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_CSVInfo = { "CSVInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventUpdateArrayFromCsvInfo_Parms, CSVInfo), Z_Construct_UScriptStruct_FEasyCsvInfo, METADATA_PARAMS(0, nullptr) }; // 795079476
	void Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_MatchStructMemberNames_SetBit(void* Obj)
	{
		((RuntimeDataTableObject_eventUpdateArrayFromCsvInfo_Parms*)Obj)->MatchStructMemberNames = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_MatchStructMemberNames = { "MatchStructMemberNames", nullptr, (EPropertyFlags)0x0010040000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RuntimeDataTableObject_eventUpdateArrayFromCsvInfo_Parms), &Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_MatchStructMemberNames_SetBit, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_OwningObject_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_OwningObject = { "OwningObject", nullptr, (EPropertyFlags)0x0010040000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventUpdateArrayFromCsvInfo_Parms, OwningObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_OwningObject_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_OwningObject_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_ArrayToUpdate_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_ArrayToUpdate,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_Successful,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_CSVInfo,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_MatchStructMemberNames,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::NewProp_OwningObject,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::Function_MetaDataParams[] = {
		{ "AdvancedDisplay", "MatchStructMemberNames, OwningObject" },
		{ "ArrayParm", "ArrayToUpdate" },
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Fills an array of structs/objects with matching variables using a CSV_Info struct from MakeCsvInfoFromString or MakeCsvInfoFromFile.\n\x09 * A bool is also returned reflecting whether the array could be updated.\n\x09 * C++ users should use UpdateArrayFromCsvInfo_Internal instead.\n\x09 * @param ArrayToUpdate An array of the type of struct/object you'd like to update using values from the loaded CSV. Struct arrays will be emptied prior to filling, object arrays will be updated in-place.\n\x09 * @param CSVInfo The script will attempt to update the array using this struct. You can generate the struct using MakeSCV_InfoFromString() or MakeCSV_InfoFromFile().\n\x09 * @param MatchStructMemberNames When true will attempt to match column names in your CSV with variables inside of your struct. This makes it so you don't have to have all variables in your struct represented sequentially in your CSV file. Name matching is slower than sequential updates so when working with very large data sets updates could take sometime longer to complete. This parameter has no effect when using an array of objects as objects will always use name matching.\n\x09 * @param OwningObject The object or instantiation of a class that has the struct array as one of its variables. Defaults to the calling object or 'Self' and only applies to struct arrays.\n\x09 */" },
#endif
		{ "CustomThunk", "true" },
		{ "DefaultToSelf", "OwningObject" },
		{ "KeyWords", "Fill" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fills an array of structs/objects with matching variables using a CSV_Info struct from MakeCsvInfoFromString or MakeCsvInfoFromFile.\nA bool is also returned reflecting whether the array could be updated.\nC++ users should use UpdateArrayFromCsvInfo_Internal instead.\n@param ArrayToUpdate An array of the type of struct/object you'd like to update using values from the loaded CSV. Struct arrays will be emptied prior to filling, object arrays will be updated in-place.\n@param CSVInfo The script will attempt to update the array using this struct. You can generate the struct using MakeSCV_InfoFromString() or MakeCSV_InfoFromFile().\n@param MatchStructMemberNames When true will attempt to match column names in your CSV with variables inside of your struct. This makes it so you don't have to have all variables in your struct represented sequentially in your CSV file. Name matching is slower than sequential updates so when working with very large data sets updates could take sometime longer to complete. This parameter has no effect when using an array of objects as objects will always use name matching.\n@param OwningObject The object or instantiation of a class that has the struct array as one of its variables. Defaults to the calling object or 'Self' and only applies to struct arrays." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "UpdateArrayFromCsvInfo", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::RuntimeDataTableObject_eventUpdateArrayFromCsvInfo_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::RuntimeDataTableObject_eventUpdateArrayFromCsvInfo_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics
	{
		struct RuntimeDataTableObject_eventValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Parms
		{
			FRuntimeDataTableCallbackInfo InCallbackInfo;
			FEasyCsvInfo OutCsvInfo;
			ERuntimeDataTableBackupResultCode OutResultCode;
			FString BackupSavePath;
			FString BackupLoadPath;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InCallbackInfo_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_InCallbackInfo;
		static const UECodeGen_Private::FStructPropertyParams NewProp_OutCsvInfo;
		static const UECodeGen_Private::FBytePropertyParams NewProp_OutResultCode_Underlying;
		static const UECodeGen_Private::FEnumPropertyParams NewProp_OutResultCode;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BackupSavePath_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_BackupSavePath;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BackupLoadPath_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_BackupLoadPath;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_InCallbackInfo_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_InCallbackInfo = { "InCallbackInfo", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Parms, InCallbackInfo), Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_InCallbackInfo_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_InCallbackInfo_MetaData) }; // 3918684402
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_OutCsvInfo = { "OutCsvInfo", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Parms, OutCsvInfo), Z_Construct_UScriptStruct_FEasyCsvInfo, METADATA_PARAMS(0, nullptr) }; // 795079476
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_OutResultCode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_OutResultCode = { "OutResultCode", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Parms, OutResultCode), Z_Construct_UEnum_RuntimeDataTable_ERuntimeDataTableBackupResultCode, METADATA_PARAMS(0, nullptr) }; // 4033296090
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_BackupSavePath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_BackupSavePath = { "BackupSavePath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Parms, BackupSavePath), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_BackupSavePath_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_BackupSavePath_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_BackupLoadPath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_BackupLoadPath = { "BackupLoadPath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Parms, BackupLoadPath), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_BackupLoadPath_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_BackupLoadPath_MetaData) };
	void Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((RuntimeDataTableObject_eventValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RuntimeDataTableObject_eventValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Parms), &Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_InCallbackInfo,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_OutCsvInfo,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_OutResultCode_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_OutResultCode,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_BackupSavePath,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_BackupLoadPath,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::Function_MetaDataParams[] = {
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Determines if your CSV download was successful and tries to save the download to BackupSavePath if provided.\n\x09 * If the download failed, will attempt to load the CSV from a local backup.\n\x09 * If a CSV exists after that, will attempt to create and output FEasyCsvInfo from it.\n\x09 * @return Whether FEasyCsvInfo could be parsed or not, regardless of whether it came from Google Sheets or a backup.\n\x09 * @param InCallbackInfo A struct generated after calling BuildGoogleSheetDownloadLinkAndGetAsCsv. Contains information about the response from Google.\n\x09 * @param OutCsvInfo If the download succeeded or the backup was loaded, this is the output FEasyCsvInfo.\n\x09 * @param OutResultCode A result code describing the action or error resulting from this function.\n\x09 * @param BackupSavePath Optional: If you have downloaded a sheet, you may save the sheet to a local path on disk.\n\x09 * @param BackupLoadPath Optional: If no \"InSheetURL\" is specified or the sheet could not be downloaded for any reason, will attempt to load the CSV from the local disk at the specified path instead.\n\x09 */" },
#endif
		{ "CPP_Default_BackupLoadPath", "" },
		{ "CPP_Default_BackupSavePath", "" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Determines if your CSV download was successful and tries to save the download to BackupSavePath if provided.\nIf the download failed, will attempt to load the CSV from a local backup.\nIf a CSV exists after that, will attempt to create and output FEasyCsvInfo from it.\n@return Whether FEasyCsvInfo could be parsed or not, regardless of whether it came from Google Sheets or a backup.\n@param InCallbackInfo A struct generated after calling BuildGoogleSheetDownloadLinkAndGetAsCsv. Contains information about the response from Google.\n@param OutCsvInfo If the download succeeded or the backup was loaded, this is the output FEasyCsvInfo.\n@param OutResultCode A result code describing the action or error resulting from this function.\n@param BackupSavePath Optional: If you have downloaded a sheet, you may save the sheet to a local path on disk.\n@param BackupLoadPath Optional: If no \"InSheetURL\" is specified or the sheet could not be downloaded for any reason, will attempt to load the CSV from the local disk at the specified path instead." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::RuntimeDataTableObject_eventValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::RuntimeDataTableObject_eventValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics
	{
		struct RuntimeDataTableObject_eventWriteCsvToSheet_Parms
		{
			FRuntimeDataTableTokenInfo InTokenInfo;
			FRuntimeDataTableOperationParams OperationParams;
			FScriptDelegate CallOnComplete;
			FString InSpreadsheetId;
			int32 InSheetId;
			FString InCsv;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_InTokenInfo;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OperationParams_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_OperationParams;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CallOnComplete_MetaData[];
#endif
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CallOnComplete;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InSpreadsheetId_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InSpreadsheetId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InSheetId_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_InSheetId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InCsv_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InCsv;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InTokenInfo = { "InTokenInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventWriteCsvToSheet_Parms, InTokenInfo), Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo, METADATA_PARAMS(0, nullptr) }; // 546094522
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_OperationParams_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_OperationParams = { "OperationParams", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventWriteCsvToSheet_Parms, OperationParams), Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_OperationParams_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_OperationParams_MetaData) }; // 1745228001
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_CallOnComplete_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_CallOnComplete = { "CallOnComplete", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventWriteCsvToSheet_Parms, CallOnComplete), Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_CallOnComplete_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_CallOnComplete_MetaData) }; // 3660932638
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InSpreadsheetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InSpreadsheetId = { "InSpreadsheetId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventWriteCsvToSheet_Parms, InSpreadsheetId), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InSpreadsheetId_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InSpreadsheetId_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InSheetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InSheetId = { "InSheetId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventWriteCsvToSheet_Parms, InSheetId), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InSheetId_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InSheetId_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InCsv_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InCsv = { "InCsv", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RuntimeDataTableObject_eventWriteCsvToSheet_Parms, InCsv), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InCsv_MetaData), Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InCsv_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InTokenInfo,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_OperationParams,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_CallOnComplete,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InSpreadsheetId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InSheetId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::NewProp_InCsv,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::Function_MetaDataParams[] = {
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Get any full sheet as CSV. This works for public or private sheets, provided you are authenticated.\n\x09 * @param InTokenInfo A validated URuntimeDataTableWebToken object. Used to authenticate the Sheets operation. When writing to a sheet, you must provide a valid InTokenInfo even if the sheet is public.\n\x09 * @param OperationParams Generic request operation parameters\n\x09 * @param InSpreadsheetId This is the spreadsheet ID number or key. Get it from your spreadsheet URL by calling GetSpreadsheetIdFromUrl.\n\x09 * @param InSheetId The GID for the desired sheet tab\n\x09 * @param InCsv This is the Csv data represented as a string. To load a CSV document from a file, use LoadStringFromFile(). To generate a CSV from a struct/object array, use GenerateCsvFromArray (BP) or GenerateCsvFromArray_Internal (C++)\n\x09 * @param CallOnComplete This delegate will be called when the operation completes and tell you whether or not it was successful and return the response as a string.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get any full sheet as CSV. This works for public or private sheets, provided you are authenticated.\n@param InTokenInfo A validated URuntimeDataTableWebToken object. Used to authenticate the Sheets operation. When writing to a sheet, you must provide a valid InTokenInfo even if the sheet is public.\n@param OperationParams Generic request operation parameters\n@param InSpreadsheetId This is the spreadsheet ID number or key. Get it from your spreadsheet URL by calling GetSpreadsheetIdFromUrl.\n@param InSheetId The GID for the desired sheet tab\n@param InCsv This is the Csv data represented as a string. To load a CSV document from a file, use LoadStringFromFile(). To generate a CSV from a struct/object array, use GenerateCsvFromArray (BP) or GenerateCsvFromArray_Internal (C++)\n@param CallOnComplete This delegate will be called when the operation completes and tell you whether or not it was successful and return the response as a string." },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URuntimeDataTableObject, nullptr, "WriteCsvToSheet", nullptr, nullptr, Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::PropPointers), sizeof(Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::RuntimeDataTableObject_eventWriteCsvToSheet_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::Function_MetaDataParams), Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::RuntimeDataTableObject_eventWriteCsvToSheet_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(URuntimeDataTableObject);
	UClass* Z_Construct_UClass_URuntimeDataTableObject_NoRegister()
	{
		return URuntimeDataTableObject::StaticClass();
	}
	struct Z_Construct_UClass_URuntimeDataTableObject_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CachedCsvInfo_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CachedCsvInfo;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_URuntimeDataTableObject_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_RuntimeDataTable,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableObject_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_URuntimeDataTableObject_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_URuntimeDataTableObject_AutoGenerateKeys, "AutoGenerateKeys" }, // 2180243509
		{ &Z_Construct_UFunction_URuntimeDataTableObject_BuildGoogleSheetDownloadLinkAndGetAsCsv, "BuildGoogleSheetDownloadLinkAndGetAsCsv" }, // 2066636084
		{ &Z_Construct_UFunction_URuntimeDataTableObject_GenerateCsvFromArray, "GenerateCsvFromArray" }, // 410602615
		{ &Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromFile, "GenerateTokenInfoFromFile" }, // 751887985
		{ &Z_Construct_UFunction_URuntimeDataTableObject_GenerateTokenInfoFromString, "GenerateTokenInfoFromString" }, // 2135849457
		{ &Z_Construct_UFunction_URuntimeDataTableObject_GetAllObjectVariableNames, "GetAllObjectVariableNames" }, // 3382347825
		{ &Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsApiUrlPrefix, "GetGoogleSheetsApiUrlPrefix" }, // 3012272875
		{ &Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsBatchUpdateURL, "GetGoogleSheetsBatchUpdateURL" }, // 4006844932
		{ &Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsUrlPrefix, "GetGoogleSheetsUrlPrefix" }, // 3069183201
		{ &Z_Construct_UFunction_URuntimeDataTableObject_GetGoogleSheetsValuesBatchUpdateURL, "GetGoogleSheetsValuesBatchUpdateURL" }, // 417391459
		{ &Z_Construct_UFunction_URuntimeDataTableObject_GetMimeCsv, "GetMimeCsv" }, // 1110057425
		{ &Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl, "GetSheetIdFromUrl" }, // 2046245812
		{ &Z_Construct_UFunction_URuntimeDataTableObject_GetSheetIdFromUrl_Int, "GetSheetIdFromUrl_Int" }, // 3570283284
		{ &Z_Construct_UFunction_URuntimeDataTableObject_GetSpreadsheetIdFromUrl, "GetSpreadsheetIdFromUrl" }, // 3911734271
		{ &Z_Construct_UFunction_URuntimeDataTableObject_UpdateArrayFromCsvInfo, "UpdateArrayFromCsvInfo" }, // 1583606299
		{ &Z_Construct_UFunction_URuntimeDataTableObject_ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded, "ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded" }, // 2961447908
		{ &Z_Construct_UFunction_URuntimeDataTableObject_WriteCsvToSheet, "WriteCsvToSheet" }, // 2983501037
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableObject_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableObject_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "RuntimeDataTable.h" },
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableObject_Statics::NewProp_CachedCsvInfo_MetaData[] = {
		{ "Category", "Runtime DataTable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// This is a struct from easyCSV that contains information about the loaded CSV. Use this when using Google Sheets.\n" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "This is a struct from easyCSV that contains information about the loaded CSV. Use this when using Google Sheets." },
#endif
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_URuntimeDataTableObject_Statics::NewProp_CachedCsvInfo = { "CachedCsvInfo", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URuntimeDataTableObject, CachedCsvInfo), Z_Construct_UScriptStruct_FEasyCsvInfo, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableObject_Statics::NewProp_CachedCsvInfo_MetaData), Z_Construct_UClass_URuntimeDataTableObject_Statics::NewProp_CachedCsvInfo_MetaData) }; // 795079476
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URuntimeDataTableObject_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableObject_Statics::NewProp_CachedCsvInfo,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_URuntimeDataTableObject_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URuntimeDataTableObject>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_URuntimeDataTableObject_Statics::ClassParams = {
		&URuntimeDataTableObject::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_URuntimeDataTableObject_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableObject_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableObject_Statics::Class_MetaDataParams), Z_Construct_UClass_URuntimeDataTableObject_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableObject_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_URuntimeDataTableObject()
	{
		if (!Z_Registration_Info_UClass_URuntimeDataTableObject.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URuntimeDataTableObject.OuterSingleton, Z_Construct_UClass_URuntimeDataTableObject_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_URuntimeDataTableObject.OuterSingleton;
	}
	template<> RUNTIMEDATATABLE_API UClass* StaticClass<URuntimeDataTableObject>()
	{
		return URuntimeDataTableObject::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(URuntimeDataTableObject);
	URuntimeDataTableObject::~URuntimeDataTableObject() {}
	struct Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_Statics::EnumInfo[] = {
		{ ERuntimeDataTableBackupResultCode_StaticEnum, TEXT("ERuntimeDataTableBackupResultCode"), &Z_Registration_Info_UEnum_ERuntimeDataTableBackupResultCode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4033296090U) },
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_Statics::ScriptStructInfo[] = {
		{ FRuntimeDataTableCallbackInfo::StaticStruct, Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics::NewStructOps, TEXT("RuntimeDataTableCallbackInfo"), &Z_Registration_Info_UScriptStruct_RuntimeDataTableCallbackInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FRuntimeDataTableCallbackInfo), 3918684402U) },
		{ FRuntimeDataTableOperationParams::StaticStruct, Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics::NewStructOps, TEXT("RuntimeDataTableOperationParams"), &Z_Registration_Info_UScriptStruct_RuntimeDataTableOperationParams, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FRuntimeDataTableOperationParams), 1745228001U) },
		{ FRuntimeDataTableTokenInfo::StaticStruct, Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics::NewStructOps, TEXT("RuntimeDataTableTokenInfo"), &Z_Registration_Info_UScriptStruct_RuntimeDataTableTokenInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FRuntimeDataTableTokenInfo), 546094522U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_URuntimeDataTableWebToken, URuntimeDataTableWebToken::StaticClass, TEXT("URuntimeDataTableWebToken"), &Z_Registration_Info_UClass_URuntimeDataTableWebToken, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URuntimeDataTableWebToken), 87880283U) },
		{ Z_Construct_UClass_URuntimeDataTableObject, URuntimeDataTableObject::StaticClass, TEXT("URuntimeDataTableObject"), &Z_Registration_Info_UClass_URuntimeDataTableObject, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URuntimeDataTableObject), 240823975U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_1418921306(TEXT("/Script/RuntimeDataTable"),
		Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_Statics::ScriptStructInfo),
		Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
