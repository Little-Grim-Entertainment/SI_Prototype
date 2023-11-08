// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LGDebug/Public/UI/GameplayTags/LGGameplayTagViewer.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLGGameplayTagViewer() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	LGDEBUG_API UClass* Z_Construct_UClass_ULGGameplayTagCategoryWidget_NoRegister();
	LGDEBUG_API UClass* Z_Construct_UClass_ULGGameplayTagEntryWidget_NoRegister();
	LGDEBUG_API UClass* Z_Construct_UClass_ULGGameplayTagViewer();
	LGDEBUG_API UClass* Z_Construct_UClass_ULGGameplayTagViewer_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UPanelWidget_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_LGDebug();
// End Cross Module References
	DEFINE_FUNCTION(ULGGameplayTagViewer::execCreateTagCategory)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InCategoryLabel);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(ULGGameplayTagCategoryWidget**)Z_Param__Result=P_THIS->CreateTagCategory(Z_Param_InCategoryLabel);
		P_NATIVE_END;
	}
	void ULGGameplayTagViewer::StaticRegisterNativesULGGameplayTagViewer()
	{
		UClass* Class = ULGGameplayTagViewer::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CreateTagCategory", &ULGGameplayTagViewer::execCreateTagCategory },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics
	{
		struct LGGameplayTagViewer_eventCreateTagCategory_Parms
		{
			FString InCategoryLabel;
			ULGGameplayTagCategoryWidget* ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InCategoryLabel_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InCategoryLabel;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::NewProp_InCategoryLabel_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::NewProp_InCategoryLabel = { "InCategoryLabel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LGGameplayTagViewer_eventCreateTagCategory_Parms, InCategoryLabel), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::NewProp_InCategoryLabel_MetaData), Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::NewProp_InCategoryLabel_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::NewProp_ReturnValue_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000080588, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LGGameplayTagViewer_eventCreateTagCategory_Parms, ReturnValue), Z_Construct_UClass_ULGGameplayTagCategoryWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::NewProp_ReturnValue_MetaData), Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::NewProp_ReturnValue_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::NewProp_InCategoryLabel,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameplayTagDebug" },
		{ "ModuleRelativePath", "Public/UI/GameplayTags/LGGameplayTagViewer.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULGGameplayTagViewer, nullptr, "CreateTagCategory", nullptr, nullptr, Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::PropPointers), sizeof(Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::LGGameplayTagViewer_eventCreateTagCategory_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::LGGameplayTagViewer_eventCreateTagCategory_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULGGameplayTagViewer);
	UClass* Z_Construct_UClass_ULGGameplayTagViewer_NoRegister()
	{
		return ULGGameplayTagViewer::StaticClass();
	}
	struct Z_Construct_UClass_ULGGameplayTagViewer_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TagCategoryWidgetClass_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_TagCategoryWidgetClass;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TagEntryWidgetClass_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_TagEntryWidgetClass;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TagListContainer_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_TagListContainer;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULGGameplayTagViewer_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_LGDebug,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagViewer_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_ULGGameplayTagViewer_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULGGameplayTagViewer_CreateTagCategory, "CreateTagCategory" }, // 774859295
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagViewer_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGGameplayTagViewer_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "UI/GameplayTags/LGGameplayTagViewer.h" },
		{ "ModuleRelativePath", "Public/UI/GameplayTags/LGGameplayTagViewer.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagCategoryWidgetClass_MetaData[] = {
		{ "Category", "GameplayTagDebug" },
		{ "ModuleRelativePath", "Public/UI/GameplayTags/LGGameplayTagViewer.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagCategoryWidgetClass = { "TagCategoryWidgetClass", nullptr, (EPropertyFlags)0x0044000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULGGameplayTagViewer, TagCategoryWidgetClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ULGGameplayTagCategoryWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagCategoryWidgetClass_MetaData), Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagCategoryWidgetClass_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagEntryWidgetClass_MetaData[] = {
		{ "Category", "GameplayTagDebug" },
		{ "ModuleRelativePath", "Public/UI/GameplayTags/LGGameplayTagViewer.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagEntryWidgetClass = { "TagEntryWidgetClass", nullptr, (EPropertyFlags)0x0044000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULGGameplayTagViewer, TagEntryWidgetClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ULGGameplayTagEntryWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagEntryWidgetClass_MetaData), Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagEntryWidgetClass_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagListContainer_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/GameplayTags/LGGameplayTagViewer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagListContainer = { "TagListContainer", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULGGameplayTagViewer, TagListContainer), Z_Construct_UClass_UPanelWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagListContainer_MetaData), Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagListContainer_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULGGameplayTagViewer_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagCategoryWidgetClass,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagEntryWidgetClass,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULGGameplayTagViewer_Statics::NewProp_TagListContainer,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULGGameplayTagViewer_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULGGameplayTagViewer>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ULGGameplayTagViewer_Statics::ClassParams = {
		&ULGGameplayTagViewer::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULGGameplayTagViewer_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagViewer_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagViewer_Statics::Class_MetaDataParams), Z_Construct_UClass_ULGGameplayTagViewer_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagViewer_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ULGGameplayTagViewer()
	{
		if (!Z_Registration_Info_UClass_ULGGameplayTagViewer.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULGGameplayTagViewer.OuterSingleton, Z_Construct_UClass_ULGGameplayTagViewer_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ULGGameplayTagViewer.OuterSingleton;
	}
	template<> LGDEBUG_API UClass* StaticClass<ULGGameplayTagViewer>()
	{
		return ULGGameplayTagViewer::StaticClass();
	}
	ULGGameplayTagViewer::ULGGameplayTagViewer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULGGameplayTagViewer);
	ULGGameplayTagViewer::~ULGGameplayTagViewer() {}
	struct Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagViewer_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagViewer_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ULGGameplayTagViewer, ULGGameplayTagViewer::StaticClass, TEXT("ULGGameplayTagViewer"), &Z_Registration_Info_UClass_ULGGameplayTagViewer, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULGGameplayTagViewer), 1035940433U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagViewer_h_1719049916(TEXT("/Script/LGDebug"),
		Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagViewer_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagViewer_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
