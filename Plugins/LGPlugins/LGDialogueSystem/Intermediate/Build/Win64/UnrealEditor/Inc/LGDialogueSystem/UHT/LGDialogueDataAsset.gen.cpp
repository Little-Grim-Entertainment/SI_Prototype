// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LGDialogueSystem/Public/Data/LGDialogueDataAsset.h"
#include "LGDialogueSystem/Public/LGDialogueTypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLGDialogueDataAsset() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
	LGDIALOGUESYSTEM_API UClass* Z_Construct_UClass_ULGDialogueDataAsset();
	LGDIALOGUESYSTEM_API UClass* Z_Construct_UClass_ULGDialogueDataAsset_NoRegister();
	LGDIALOGUESYSTEM_API UScriptStruct* Z_Construct_UScriptStruct_FLGDialogueURL();
	UPackage* Z_Construct_UPackage__Script_LGDialogueSystem();
// End Cross Module References
	DEFINE_FUNCTION(ULGDialogueDataAsset::execUpdateDialogue)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UpdateDialogue();
		P_NATIVE_END;
	}
	void ULGDialogueDataAsset::StaticRegisterNativesULGDialogueDataAsset()
	{
		UClass* Class = ULGDialogueDataAsset::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "UpdateDialogue", &ULGDialogueDataAsset::execUpdateDialogue },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULGDialogueDataAsset_UpdateDialogue_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGDialogueDataAsset_UpdateDialogue_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "ModuleRelativePath", "Public/Data/LGDialogueDataAsset.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULGDialogueDataAsset_UpdateDialogue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULGDialogueDataAsset, nullptr, "UpdateDialogue", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGDialogueDataAsset_UpdateDialogue_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULGDialogueDataAsset_UpdateDialogue_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_ULGDialogueDataAsset_UpdateDialogue()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULGDialogueDataAsset_UpdateDialogue_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULGDialogueDataAsset);
	UClass* Z_Construct_UClass_ULGDialogueDataAsset_NoRegister()
	{
		return ULGDialogueDataAsset::StaticClass();
	}
	struct Z_Construct_UClass_ULGDialogueDataAsset_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FolderPath_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_FolderPath;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CsvName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_CsvName;
		static const UECodeGen_Private::FStructPropertyParams NewProp_DialogueURLs_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DialogueURLs_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_DialogueURLs;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULGDialogueDataAsset_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDataAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_LGDialogueSystem,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGDialogueDataAsset_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_ULGDialogueDataAsset_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULGDialogueDataAsset_UpdateDialogue, "UpdateDialogue" }, // 2345485307
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGDialogueDataAsset_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGDialogueDataAsset_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Data/LGDialogueDataAsset.h" },
		{ "ModuleRelativePath", "Public/Data/LGDialogueDataAsset.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_FolderPath_MetaData[] = {
		{ "Category", "LGDialogueDataAsset" },
		{ "ModuleRelativePath", "Public/Data/LGDialogueDataAsset.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_FolderPath = { "FolderPath", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULGDialogueDataAsset, FolderPath), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_FolderPath_MetaData), Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_FolderPath_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_CsvName_MetaData[] = {
		{ "Category", "LGDialogueDataAsset" },
		{ "ModuleRelativePath", "Public/Data/LGDialogueDataAsset.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_CsvName = { "CsvName", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULGDialogueDataAsset, CsvName), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_CsvName_MetaData), Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_CsvName_MetaData) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_DialogueURLs_Inner = { "DialogueURLs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FLGDialogueURL, METADATA_PARAMS(0, nullptr) }; // 4085560945
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_DialogueURLs_MetaData[] = {
		{ "Category", "URLs" },
		{ "ModuleRelativePath", "Public/Data/LGDialogueDataAsset.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_DialogueURLs = { "DialogueURLs", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULGDialogueDataAsset, DialogueURLs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_DialogueURLs_MetaData), Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_DialogueURLs_MetaData) }; // 4085560945
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULGDialogueDataAsset_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_FolderPath,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_CsvName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_DialogueURLs_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULGDialogueDataAsset_Statics::NewProp_DialogueURLs,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULGDialogueDataAsset_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULGDialogueDataAsset>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ULGDialogueDataAsset_Statics::ClassParams = {
		&ULGDialogueDataAsset::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULGDialogueDataAsset_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULGDialogueDataAsset_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGDialogueDataAsset_Statics::Class_MetaDataParams), Z_Construct_UClass_ULGDialogueDataAsset_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGDialogueDataAsset_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ULGDialogueDataAsset()
	{
		if (!Z_Registration_Info_UClass_ULGDialogueDataAsset.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULGDialogueDataAsset.OuterSingleton, Z_Construct_UClass_ULGDialogueDataAsset_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ULGDialogueDataAsset.OuterSingleton;
	}
	template<> LGDIALOGUESYSTEM_API UClass* StaticClass<ULGDialogueDataAsset>()
	{
		return ULGDialogueDataAsset::StaticClass();
	}
	ULGDialogueDataAsset::ULGDialogueDataAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULGDialogueDataAsset);
	ULGDialogueDataAsset::~ULGDialogueDataAsset() {}
	struct Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ULGDialogueDataAsset, ULGDialogueDataAsset::StaticClass, TEXT("ULGDialogueDataAsset"), &Z_Registration_Info_UClass_ULGDialogueDataAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULGDialogueDataAsset), 3995119375U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_692713099(TEXT("/Script/LGDialogueSystem"),
		Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
