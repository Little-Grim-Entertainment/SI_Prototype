// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LGCsvDataProcessor/Public/LGCsvDataProcessorFunctionLibrary.h"
#include "LGCsvDataProcessor/Public/LGCsvDataTypes.h"
#include "RuntimeDataTable.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLGCsvDataProcessorFunctionLibrary() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	LGCSVDATAPROCESSOR_API UClass* Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary();
	LGCSVDATAPROCESSOR_API UClass* Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary_NoRegister();
	LGCSVDATAPROCESSOR_API UScriptStruct* Z_Construct_UScriptStruct_FLGCsvInfoImportPayload();
	RUNTIMEDATATABLE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo();
	UPackage* Z_Construct_UPackage__Script_LGCsvDataProcessor();
// End Cross Module References
	DEFINE_FUNCTION(ULGCsvDataProcessorFunctionLibrary::execOnSheetStructsDownloaded)
	{
		P_GET_STRUCT(FRuntimeDataTableCallbackInfo,Z_Param_InCallbackInfo);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnSheetStructsDownloaded(Z_Param_InCallbackInfo);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULGCsvDataProcessorFunctionLibrary::execFNameArrayToFStringArray)
	{
		P_GET_TARRAY_REF(FName,Z_Param_Out_InNameArray);
		P_GET_TARRAY_REF(FString,Z_Param_Out_OutStringArray);
		P_FINISH;
		P_NATIVE_BEGIN;
		ULGCsvDataProcessorFunctionLibrary::FNameArrayToFStringArray(Z_Param_Out_InNameArray,Z_Param_Out_OutStringArray);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULGCsvDataProcessorFunctionLibrary::execImportCsvFromURL)
	{
		P_GET_STRUCT_REF(FLGCsvInfoImportPayload,Z_Param_Out_InImportPayload);
		P_FINISH;
		P_NATIVE_BEGIN;
		ULGCsvDataProcessorFunctionLibrary::ImportCsvFromURL(Z_Param_Out_InImportPayload);
		P_NATIVE_END;
	}
	void ULGCsvDataProcessorFunctionLibrary::StaticRegisterNativesULGCsvDataProcessorFunctionLibrary()
	{
		UClass* Class = ULGCsvDataProcessorFunctionLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "FNameArrayToFStringArray", &ULGCsvDataProcessorFunctionLibrary::execFNameArrayToFStringArray },
			{ "ImportCsvFromURL", &ULGCsvDataProcessorFunctionLibrary::execImportCsvFromURL },
			{ "OnSheetStructsDownloaded", &ULGCsvDataProcessorFunctionLibrary::execOnSheetStructsDownloaded },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics
	{
		struct LGCsvDataProcessorFunctionLibrary_eventFNameArrayToFStringArray_Parms
		{
			TArray<FName> InNameArray;
			TArray<FString> OutStringArray;
		};
		static const UECodeGen_Private::FNamePropertyParams NewProp_InNameArray_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InNameArray_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_InNameArray;
		static const UECodeGen_Private::FStrPropertyParams NewProp_OutStringArray_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_OutStringArray;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::NewProp_InNameArray_Inner = { "InNameArray", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::NewProp_InNameArray_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::NewProp_InNameArray = { "InNameArray", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LGCsvDataProcessorFunctionLibrary_eventFNameArrayToFStringArray_Parms, InNameArray), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::NewProp_InNameArray_MetaData), Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::NewProp_InNameArray_MetaData) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::NewProp_OutStringArray_Inner = { "OutStringArray", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::NewProp_OutStringArray = { "OutStringArray", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LGCsvDataProcessorFunctionLibrary_eventFNameArrayToFStringArray_Parms, OutStringArray), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::NewProp_InNameArray_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::NewProp_InNameArray,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::NewProp_OutStringArray_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::NewProp_OutStringArray,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LGCsvDataProcessorFunctionLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary, nullptr, "FNameArrayToFStringArray", nullptr, nullptr, Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::PropPointers), sizeof(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::LGCsvDataProcessorFunctionLibrary_eventFNameArrayToFStringArray_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::LGCsvDataProcessorFunctionLibrary_eventFNameArrayToFStringArray_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics
	{
		struct LGCsvDataProcessorFunctionLibrary_eventImportCsvFromURL_Parms
		{
			FLGCsvInfoImportPayload InImportPayload;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InImportPayload_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_InImportPayload;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::NewProp_InImportPayload_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::NewProp_InImportPayload = { "InImportPayload", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LGCsvDataProcessorFunctionLibrary_eventImportCsvFromURL_Parms, InImportPayload), Z_Construct_UScriptStruct_FLGCsvInfoImportPayload, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::NewProp_InImportPayload_MetaData), Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::NewProp_InImportPayload_MetaData) }; // 3249358461
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::NewProp_InImportPayload,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LGCsvDataProcessorFunctionLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary, nullptr, "ImportCsvFromURL", nullptr, nullptr, Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::PropPointers), sizeof(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::LGCsvDataProcessorFunctionLibrary_eventImportCsvFromURL_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::LGCsvDataProcessorFunctionLibrary_eventImportCsvFromURL_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded_Statics
	{
		struct LGCsvDataProcessorFunctionLibrary_eventOnSheetStructsDownloaded_Parms
		{
			FRuntimeDataTableCallbackInfo InCallbackInfo;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_InCallbackInfo;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded_Statics::NewProp_InCallbackInfo = { "InCallbackInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LGCsvDataProcessorFunctionLibrary_eventOnSheetStructsDownloaded_Parms, InCallbackInfo), Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo, METADATA_PARAMS(0, nullptr) }; // 1597180715
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded_Statics::NewProp_InCallbackInfo,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LGCsvDataProcessorFunctionLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary, nullptr, "OnSheetStructsDownloaded", nullptr, nullptr, Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded_Statics::PropPointers), sizeof(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded_Statics::LGCsvDataProcessorFunctionLibrary_eventOnSheetStructsDownloaded_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded_Statics::LGCsvDataProcessorFunctionLibrary_eventOnSheetStructsDownloaded_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULGCsvDataProcessorFunctionLibrary);
	UClass* Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary_NoRegister()
	{
		return ULGCsvDataProcessorFunctionLibrary::StaticClass();
	}
	struct Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_LGCsvDataProcessor,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_FNameArrayToFStringArray, "FNameArrayToFStringArray" }, // 2102462141
		{ &Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_ImportCsvFromURL, "ImportCsvFromURL" }, // 3043076547
		{ &Z_Construct_UFunction_ULGCsvDataProcessorFunctionLibrary_OnSheetStructsDownloaded, "OnSheetStructsDownloaded" }, // 2452590260
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "LGCsvDataProcessorFunctionLibrary.h" },
		{ "ModuleRelativePath", "Public/LGCsvDataProcessorFunctionLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULGCsvDataProcessorFunctionLibrary>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary_Statics::ClassParams = {
		&ULGCsvDataProcessorFunctionLibrary::StaticClass,
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
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary()
	{
		if (!Z_Registration_Info_UClass_ULGCsvDataProcessorFunctionLibrary.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULGCsvDataProcessorFunctionLibrary.OuterSingleton, Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ULGCsvDataProcessorFunctionLibrary.OuterSingleton;
	}
	template<> LGCSVDATAPROCESSOR_API UClass* StaticClass<ULGCsvDataProcessorFunctionLibrary>()
	{
		return ULGCsvDataProcessorFunctionLibrary::StaticClass();
	}
	ULGCsvDataProcessorFunctionLibrary::ULGCsvDataProcessorFunctionLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULGCsvDataProcessorFunctionLibrary);
	ULGCsvDataProcessorFunctionLibrary::~ULGCsvDataProcessorFunctionLibrary() {}
	struct Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary, ULGCsvDataProcessorFunctionLibrary::StaticClass, TEXT("ULGCsvDataProcessorFunctionLibrary"), &Z_Registration_Info_UClass_ULGCsvDataProcessorFunctionLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULGCsvDataProcessorFunctionLibrary), 857595452U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_2441595901(TEXT("/Script/LGCsvDataProcessor"),
		Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
