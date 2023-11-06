// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LGDebug/Public/UI/LGDebugWidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLGDebugWidget() {}
// Cross Module References
	LGDEBUG_API UClass* Z_Construct_UClass_ULGDebugWidget();
	LGDEBUG_API UClass* Z_Construct_UClass_ULGDebugWidget_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_LGDebug();
// End Cross Module References
	void ULGDebugWidget::StaticRegisterNativesULGDebugWidget()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULGDebugWidget);
	UClass* Z_Construct_UClass_ULGDebugWidget_NoRegister()
	{
		return ULGDebugWidget::StaticClass();
	}
	struct Z_Construct_UClass_ULGDebugWidget_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULGDebugWidget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_LGDebug,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGDebugWidget_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGDebugWidget_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "UI/LGDebugWidget.h" },
		{ "ModuleRelativePath", "Public/UI/LGDebugWidget.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULGDebugWidget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULGDebugWidget>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ULGDebugWidget_Statics::ClassParams = {
		&ULGDebugWidget::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x00B010A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGDebugWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_ULGDebugWidget_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ULGDebugWidget()
	{
		if (!Z_Registration_Info_UClass_ULGDebugWidget.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULGDebugWidget.OuterSingleton, Z_Construct_UClass_ULGDebugWidget_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ULGDebugWidget.OuterSingleton;
	}
	template<> LGDEBUG_API UClass* StaticClass<ULGDebugWidget>()
	{
		return ULGDebugWidget::StaticClass();
	}
	ULGDebugWidget::ULGDebugWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULGDebugWidget);
	ULGDebugWidget::~ULGDebugWidget() {}
	struct Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_LGDebugWidget_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_LGDebugWidget_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ULGDebugWidget, ULGDebugWidget::StaticClass, TEXT("ULGDebugWidget"), &Z_Registration_Info_UClass_ULGDebugWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULGDebugWidget), 3519548792U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_LGDebugWidget_h_1316309288(TEXT("/Script/LGDebug"),
		Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_LGDebugWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGDebug_Source_LGDebug_Public_UI_LGDebugWidget_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
