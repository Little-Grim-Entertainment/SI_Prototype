// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LGDialogueSystem/Public/Data/LGProjectDialogueData.h"
#include "LGDialogueSystem/Public/LGDialogueTypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLGProjectDialogueData() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
	LGDIALOGUESYSTEM_API UClass* Z_Construct_UClass_ULGProjectDialogueData();
	LGDIALOGUESYSTEM_API UClass* Z_Construct_UClass_ULGProjectDialogueData_NoRegister();
	LGDIALOGUESYSTEM_API UScriptStruct* Z_Construct_UScriptStruct_FLGCharacterDialogue();
	UPackage* Z_Construct_UPackage__Script_LGDialogueSystem();
// End Cross Module References
	DEFINE_FUNCTION(ULGProjectDialogueData::execUpdateAllDialogue)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UpdateAllDialogue();
		P_NATIVE_END;
	}
	void ULGProjectDialogueData::StaticRegisterNativesULGProjectDialogueData()
	{
		UClass* Class = ULGProjectDialogueData::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "UpdateAllDialogue", &ULGProjectDialogueData::execUpdateAllDialogue },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULGProjectDialogueData_UpdateAllDialogue_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGProjectDialogueData_UpdateAllDialogue_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "ModuleRelativePath", "Public/Data/LGProjectDialogueData.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULGProjectDialogueData_UpdateAllDialogue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULGProjectDialogueData, nullptr, "UpdateAllDialogue", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGProjectDialogueData_UpdateAllDialogue_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULGProjectDialogueData_UpdateAllDialogue_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_ULGProjectDialogueData_UpdateAllDialogue()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULGProjectDialogueData_UpdateAllDialogue_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULGProjectDialogueData);
	UClass* Z_Construct_UClass_ULGProjectDialogueData_NoRegister()
	{
		return ULGProjectDialogueData::StaticClass();
	}
	struct Z_Construct_UClass_ULGProjectDialogueData_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_CharacterDialogue_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CharacterDialogue_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_CharacterDialogue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULGProjectDialogueData_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDataAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_LGDialogueSystem,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGProjectDialogueData_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_ULGProjectDialogueData_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULGProjectDialogueData_UpdateAllDialogue, "UpdateAllDialogue" }, // 1141590668
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGProjectDialogueData_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGProjectDialogueData_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Data/LGProjectDialogueData.h" },
		{ "ModuleRelativePath", "Public/Data/LGProjectDialogueData.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULGProjectDialogueData_Statics::NewProp_CharacterDialogue_Inner = { "CharacterDialogue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FLGCharacterDialogue, METADATA_PARAMS(0, nullptr) }; // 4173466436
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGProjectDialogueData_Statics::NewProp_CharacterDialogue_MetaData[] = {
		{ "Category", "Dialogue" },
		{ "ModuleRelativePath", "Public/Data/LGProjectDialogueData.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ULGProjectDialogueData_Statics::NewProp_CharacterDialogue = { "CharacterDialogue", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULGProjectDialogueData, CharacterDialogue), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGProjectDialogueData_Statics::NewProp_CharacterDialogue_MetaData), Z_Construct_UClass_ULGProjectDialogueData_Statics::NewProp_CharacterDialogue_MetaData) }; // 4173466436
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULGProjectDialogueData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULGProjectDialogueData_Statics::NewProp_CharacterDialogue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULGProjectDialogueData_Statics::NewProp_CharacterDialogue,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULGProjectDialogueData_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULGProjectDialogueData>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ULGProjectDialogueData_Statics::ClassParams = {
		&ULGProjectDialogueData::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULGProjectDialogueData_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULGProjectDialogueData_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGProjectDialogueData_Statics::Class_MetaDataParams), Z_Construct_UClass_ULGProjectDialogueData_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGProjectDialogueData_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ULGProjectDialogueData()
	{
		if (!Z_Registration_Info_UClass_ULGProjectDialogueData.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULGProjectDialogueData.OuterSingleton, Z_Construct_UClass_ULGProjectDialogueData_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ULGProjectDialogueData.OuterSingleton;
	}
	template<> LGDIALOGUESYSTEM_API UClass* StaticClass<ULGProjectDialogueData>()
	{
		return ULGProjectDialogueData::StaticClass();
	}
	ULGProjectDialogueData::ULGProjectDialogueData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULGProjectDialogueData);
	ULGProjectDialogueData::~ULGProjectDialogueData() {}
	struct Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGProjectDialogueData_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGProjectDialogueData_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ULGProjectDialogueData, ULGProjectDialogueData::StaticClass, TEXT("ULGProjectDialogueData"), &Z_Registration_Info_UClass_ULGProjectDialogueData, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULGProjectDialogueData), 1036913440U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGProjectDialogueData_h_527622788(TEXT("/Script/LGDialogueSystem"),
		Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGProjectDialogueData_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGProjectDialogueData_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
