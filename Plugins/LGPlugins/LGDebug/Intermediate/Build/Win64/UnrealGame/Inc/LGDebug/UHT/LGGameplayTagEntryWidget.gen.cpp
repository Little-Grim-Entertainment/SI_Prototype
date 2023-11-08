// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LGDebug/Public/UI/GameplayTags/LGGameplayTagEntryWidget.h"
#include "GameplayTagContainer.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLGGameplayTagEntryWidget() {}
// Cross Module References
	GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTag();
	LGDEBUG_API UClass* Z_Construct_UClass_ULGGameplayTagEntryWidget();
	LGDEBUG_API UClass* Z_Construct_UClass_ULGGameplayTagEntryWidget_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_LGDebug();
// End Cross Module References
	DEFINE_FUNCTION(ULGGameplayTagEntryWidget::execSetGameplayTagText)
	{
		P_GET_STRUCT_REF(FGameplayTag,Z_Param_Out_InGameplayTag);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetGameplayTagText(Z_Param_Out_InGameplayTag);
		P_NATIVE_END;
	}
	void ULGGameplayTagEntryWidget::StaticRegisterNativesULGGameplayTagEntryWidget()
	{
		UClass* Class = ULGGameplayTagEntryWidget::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SetGameplayTagText", &ULGGameplayTagEntryWidget::execSetGameplayTagText },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics
	{
		struct LGGameplayTagEntryWidget_eventSetGameplayTagText_Parms
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
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::NewProp_InGameplayTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::NewProp_InGameplayTag = { "InGameplayTag", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LGGameplayTagEntryWidget_eventSetGameplayTagText_Parms, InGameplayTag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::NewProp_InGameplayTag_MetaData), Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::NewProp_InGameplayTag_MetaData) }; // 2083603574
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::NewProp_InGameplayTag,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameplayTagDebug" },
		{ "ModuleRelativePath", "Public/UI/GameplayTags/LGGameplayTagEntryWidget.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULGGameplayTagEntryWidget, nullptr, "SetGameplayTagText", nullptr, nullptr, Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::PropPointers), sizeof(Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::LGGameplayTagEntryWidget_eventSetGameplayTagText_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::LGGameplayTagEntryWidget_eventSetGameplayTagText_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULGGameplayTagEntryWidget);
	UClass* Z_Construct_UClass_ULGGameplayTagEntryWidget_NoRegister()
	{
		return ULGGameplayTagEntryWidget::StaticClass();
	}
	struct Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GameplayTagText_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_GameplayTagText;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_LGDebug,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULGGameplayTagEntryWidget_SetGameplayTagText, "SetGameplayTagText" }, // 3392564953
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "UI/GameplayTags/LGGameplayTagEntryWidget.h" },
		{ "ModuleRelativePath", "Public/UI/GameplayTags/LGGameplayTagEntryWidget.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::NewProp_GameplayTagText_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/GameplayTags/LGGameplayTagEntryWidget.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::NewProp_GameplayTagText = { "GameplayTagText", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULGGameplayTagEntryWidget, GameplayTagText), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::NewProp_GameplayTagText_MetaData), Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::NewProp_GameplayTagText_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::NewProp_GameplayTagText,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULGGameplayTagEntryWidget>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::ClassParams = {
		&ULGGameplayTagEntryWidget::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ULGGameplayTagEntryWidget()
	{
		if (!Z_Registration_Info_UClass_ULGGameplayTagEntryWidget.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULGGameplayTagEntryWidget.OuterSingleton, Z_Construct_UClass_ULGGameplayTagEntryWidget_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ULGGameplayTagEntryWidget.OuterSingleton;
	}
	template<> LGDEBUG_API UClass* StaticClass<ULGGameplayTagEntryWidget>()
	{
		return ULGGameplayTagEntryWidget::StaticClass();
	}
	ULGGameplayTagEntryWidget::ULGGameplayTagEntryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULGGameplayTagEntryWidget);
	ULGGameplayTagEntryWidget::~ULGGameplayTagEntryWidget() {}
	struct Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagEntryWidget_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagEntryWidget_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ULGGameplayTagEntryWidget, ULGGameplayTagEntryWidget::StaticClass, TEXT("ULGGameplayTagEntryWidget"), &Z_Registration_Info_UClass_ULGGameplayTagEntryWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULGGameplayTagEntryWidget), 2464687637U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagEntryWidget_h_2506766252(TEXT("/Script/LGDebug"),
		Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagEntryWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_GameplayTags_LGGameplayTagEntryWidget_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
