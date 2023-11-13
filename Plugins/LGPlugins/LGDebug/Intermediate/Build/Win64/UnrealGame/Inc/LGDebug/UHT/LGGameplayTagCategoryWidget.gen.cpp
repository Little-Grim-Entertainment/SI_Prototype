// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LGDebug/Public/UI/GameplayTags/LGGameplayTagCategoryWidget.h"
#include "GameplayTagContainer.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLGGameplayTagCategoryWidget() {}
// Cross Module References
	GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTag();
	LGDEBUG_API UClass* Z_Construct_UClass_ULGGameplayTagCategoryWidget();
	LGDEBUG_API UClass* Z_Construct_UClass_ULGGameplayTagCategoryWidget_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UPanelWidget_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_LGDebug();
// End Cross Module References
	DEFINE_FUNCTION(ULGGameplayTagCategoryWidget::execHasTagEntry)
	{
		P_GET_STRUCT_REF(FGameplayTag,Z_Param_Out_InGameplayTag);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->HasTagEntry(Z_Param_Out_InGameplayTag);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULGGameplayTagCategoryWidget::execAddTagEntry)
	{
		P_GET_STRUCT_REF(FGameplayTag,Z_Param_Out_InGameplayTag);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AddTagEntry(Z_Param_Out_InGameplayTag);
		P_NATIVE_END;
	}
	void ULGGameplayTagCategoryWidget::StaticRegisterNativesULGGameplayTagCategoryWidget()
	{
		UClass* Class = ULGGameplayTagCategoryWidget::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddTagEntry", &ULGGameplayTagCategoryWidget::execAddTagEntry },
			{ "HasTagEntry", &ULGGameplayTagCategoryWidget::execHasTagEntry },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics
	{
		struct LGGameplayTagCategoryWidget_eventAddTagEntry_Parms
		{
			FGameplayTag InGameplayTag;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InGameplayTag_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_InGameplayTag;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::NewProp_InGameplayTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::NewProp_InGameplayTag = { "InGameplayTag", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LGGameplayTagCategoryWidget_eventAddTagEntry_Parms, InGameplayTag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::NewProp_InGameplayTag_MetaData), Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::NewProp_InGameplayTag_MetaData) }; // 2083603574
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::NewProp_InGameplayTag,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameplayTagDebug" },
		{ "ModuleRelativePath", "Public/UI/GameplayTags/LGGameplayTagCategoryWidget.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULGGameplayTagCategoryWidget, nullptr, "AddTagEntry", nullptr, nullptr, Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::PropPointers), sizeof(Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::LGGameplayTagCategoryWidget_eventAddTagEntry_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::LGGameplayTagCategoryWidget_eventAddTagEntry_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics
	{
		struct LGGameplayTagCategoryWidget_eventHasTagEntry_Parms
		{
			FGameplayTag InGameplayTag;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InGameplayTag_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_InGameplayTag;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::NewProp_InGameplayTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::NewProp_InGameplayTag = { "InGameplayTag", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LGGameplayTagCategoryWidget_eventHasTagEntry_Parms, InGameplayTag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::NewProp_InGameplayTag_MetaData), Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::NewProp_InGameplayTag_MetaData) }; // 2083603574
	void Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LGGameplayTagCategoryWidget_eventHasTagEntry_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(LGGameplayTagCategoryWidget_eventHasTagEntry_Parms), &Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::NewProp_InGameplayTag,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameplayTagDebug" },
		{ "ModuleRelativePath", "Public/UI/GameplayTags/LGGameplayTagCategoryWidget.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULGGameplayTagCategoryWidget, nullptr, "HasTagEntry", nullptr, nullptr, Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::PropPointers), sizeof(Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::LGGameplayTagCategoryWidget_eventHasTagEntry_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::LGGameplayTagCategoryWidget_eventHasTagEntry_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULGGameplayTagCategoryWidget);
	UClass* Z_Construct_UClass_ULGGameplayTagCategoryWidget_NoRegister()
	{
		return ULGGameplayTagCategoryWidget::StaticClass();
	}
	struct Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TXT_CategoryLabel_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_TXT_CategoryLabel;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TagEntriesContainer_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_TagEntriesContainer;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_LGDebug,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULGGameplayTagCategoryWidget_AddTagEntry, "AddTagEntry" }, // 2191120723
		{ &Z_Construct_UFunction_ULGGameplayTagCategoryWidget_HasTagEntry, "HasTagEntry" }, // 1532940294
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "UI/GameplayTags/LGGameplayTagCategoryWidget.h" },
		{ "ModuleRelativePath", "Public/UI/GameplayTags/LGGameplayTagCategoryWidget.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::NewProp_TXT_CategoryLabel_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/GameplayTags/LGGameplayTagCategoryWidget.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::NewProp_TXT_CategoryLabel = { "TXT_CategoryLabel", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULGGameplayTagCategoryWidget, TXT_CategoryLabel), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::NewProp_TXT_CategoryLabel_MetaData), Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::NewProp_TXT_CategoryLabel_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::NewProp_TagEntriesContainer_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/GameplayTags/LGGameplayTagCategoryWidget.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::NewProp_TagEntriesContainer = { "TagEntriesContainer", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULGGameplayTagCategoryWidget, TagEntriesContainer), Z_Construct_UClass_UPanelWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::NewProp_TagEntriesContainer_MetaData), Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::NewProp_TagEntriesContainer_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::NewProp_TXT_CategoryLabel,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::NewProp_TagEntriesContainer,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULGGameplayTagCategoryWidget>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::ClassParams = {
		&ULGGameplayTagCategoryWidget::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ULGGameplayTagCategoryWidget()
	{
		if (!Z_Registration_Info_UClass_ULGGameplayTagCategoryWidget.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULGGameplayTagCategoryWidget.OuterSingleton, Z_Construct_UClass_ULGGameplayTagCategoryWidget_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ULGGameplayTagCategoryWidget.OuterSingleton;
	}
	template<> LGDEBUG_API UClass* StaticClass<ULGGameplayTagCategoryWidget>()
	{
		return ULGGameplayTagCategoryWidget::StaticClass();
	}
	ULGGameplayTagCategoryWidget::ULGGameplayTagCategoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULGGameplayTagCategoryWidget);
	ULGGameplayTagCategoryWidget::~ULGGameplayTagCategoryWidget() {}
	struct Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagCategoryWidget_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagCategoryWidget_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ULGGameplayTagCategoryWidget, ULGGameplayTagCategoryWidget::StaticClass, TEXT("ULGGameplayTagCategoryWidget"), &Z_Registration_Info_UClass_ULGGameplayTagCategoryWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULGGameplayTagCategoryWidget), 2921649649U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagCategoryWidget_h_343230370(TEXT("/Script/LGDebug"),
		Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagCategoryWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagCategoryWidget_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
