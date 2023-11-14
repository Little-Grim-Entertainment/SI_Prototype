// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "EasyCsvProjectSettings.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEasyCsvProjectSettings() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	EASYCSV_API UClass* Z_Construct_UClass_UEasyCsvProjectSettings();
	EASYCSV_API UClass* Z_Construct_UClass_UEasyCsvProjectSettings_NoRegister();
	UPackage* Z_Construct_UPackage__Script_EasyCsv();
// End Cross Module References
	void UEasyCsvProjectSettings::StaticRegisterNativesUEasyCsvProjectSettings()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UEasyCsvProjectSettings);
	UClass* Z_Construct_UClass_UEasyCsvProjectSettings_NoRegister()
	{
		return UEasyCsvProjectSettings::StaticClass();
	}
	struct Z_Construct_UClass_UEasyCsvProjectSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LogCharacterLimit_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_LogCharacterLimit;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bPrintDisplayMessagesToLog_MetaData[];
#endif
		static void NewProp_bPrintDisplayMessagesToLog_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bPrintDisplayMessagesToLog;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bPrintDisplayMessagesToScreen_MetaData[];
#endif
		static void NewProp_bPrintDisplayMessagesToScreen_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bPrintDisplayMessagesToScreen;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DisplayMessagesOnScreenLifetime_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_DisplayMessagesOnScreenLifetime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bPrintWarningMessagesToLog_MetaData[];
#endif
		static void NewProp_bPrintWarningMessagesToLog_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bPrintWarningMessagesToLog;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bPrintWarningMessagesToScreen_MetaData[];
#endif
		static void NewProp_bPrintWarningMessagesToScreen_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bPrintWarningMessagesToScreen;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WarningMessagesOnScreenLifetime_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_WarningMessagesOnScreenLifetime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bPrintErrorMessagesToLog_MetaData[];
#endif
		static void NewProp_bPrintErrorMessagesToLog_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bPrintErrorMessagesToLog;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bPrintErrorMessagesToScreen_MetaData[];
#endif
		static void NewProp_bPrintErrorMessagesToScreen_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bPrintErrorMessagesToScreen;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ErrorMessagesOnScreenLifetime_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ErrorMessagesOnScreenLifetime;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UEasyCsvProjectSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_EasyCsv,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsvProjectSettings_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEasyCsvProjectSettings_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "EasyCsvProjectSettings.h" },
		{ "ModuleRelativePath", "Public/EasyCsvProjectSettings.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_LogCharacterLimit_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *The number of characters that can be printed in any given print. -1 means no limit.\n\x09 *This is useful when printing responses which can be enormous with very large sheets.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsvProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The number of characters that can be printed in any given print. -1 means no limit.\nThis is useful when printing responses which can be enormous with very large sheets." },
#endif
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_LogCharacterLimit = { "LogCharacterLimit", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEasyCsvProjectSettings, LogCharacterLimit), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_LogCharacterLimit_MetaData), Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_LogCharacterLimit_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintDisplayMessagesToLog_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *If true, \"Display\" type messages will be printed to the log. These will not display on screen.\n\x09 *\"Display\" type messages are informational messages most end users don't have much interest in seeing.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsvProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, \"Display\" type messages will be printed to the log. These will not display on screen.\n\"Display\" type messages are informational messages most end users don't have much interest in seeing." },
#endif
	};
#endif
	void Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintDisplayMessagesToLog_SetBit(void* Obj)
	{
		((UEasyCsvProjectSettings*)Obj)->bPrintDisplayMessagesToLog = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintDisplayMessagesToLog = { "bPrintDisplayMessagesToLog", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UEasyCsvProjectSettings), &Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintDisplayMessagesToLog_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintDisplayMessagesToLog_MetaData), Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintDisplayMessagesToLog_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintDisplayMessagesToScreen_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *If true, \"Display\" type messages will be printed to the screen. These will not appear in the output log.\n\x09 *\"Display\" type messages are informational messages most end users don't have much interest in seeing.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsvProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, \"Display\" type messages will be printed to the screen. These will not appear in the output log.\n\"Display\" type messages are informational messages most end users don't have much interest in seeing." },
#endif
	};
#endif
	void Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintDisplayMessagesToScreen_SetBit(void* Obj)
	{
		((UEasyCsvProjectSettings*)Obj)->bPrintDisplayMessagesToScreen = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintDisplayMessagesToScreen = { "bPrintDisplayMessagesToScreen", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UEasyCsvProjectSettings), &Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintDisplayMessagesToScreen_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintDisplayMessagesToScreen_MetaData), Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintDisplayMessagesToScreen_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_DisplayMessagesOnScreenLifetime_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
		{ "ModuleRelativePath", "Public/EasyCsvProjectSettings.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_DisplayMessagesOnScreenLifetime = { "DisplayMessagesOnScreenLifetime", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEasyCsvProjectSettings, DisplayMessagesOnScreenLifetime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_DisplayMessagesOnScreenLifetime_MetaData), Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_DisplayMessagesOnScreenLifetime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintWarningMessagesToLog_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *If true, \"Warning\" type messages will be printed to the log. These will not display on screen.\n\x09 *\"Warning\" type messages are important to most end users, but warnings are not fatal.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsvProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, \"Warning\" type messages will be printed to the log. These will not display on screen.\n\"Warning\" type messages are important to most end users, but warnings are not fatal." },
#endif
	};
#endif
	void Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintWarningMessagesToLog_SetBit(void* Obj)
	{
		((UEasyCsvProjectSettings*)Obj)->bPrintWarningMessagesToLog = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintWarningMessagesToLog = { "bPrintWarningMessagesToLog", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UEasyCsvProjectSettings), &Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintWarningMessagesToLog_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintWarningMessagesToLog_MetaData), Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintWarningMessagesToLog_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintWarningMessagesToScreen_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *If true, \"Warning\" type messages will be printed to the screen. These will not appear in the output log.\n\x09 *\"Warning\" type messages are important to most end users, but warnings are not fatal. \n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsvProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, \"Warning\" type messages will be printed to the screen. These will not appear in the output log.\n\"Warning\" type messages are important to most end users, but warnings are not fatal." },
#endif
	};
#endif
	void Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintWarningMessagesToScreen_SetBit(void* Obj)
	{
		((UEasyCsvProjectSettings*)Obj)->bPrintWarningMessagesToScreen = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintWarningMessagesToScreen = { "bPrintWarningMessagesToScreen", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UEasyCsvProjectSettings), &Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintWarningMessagesToScreen_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintWarningMessagesToScreen_MetaData), Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintWarningMessagesToScreen_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_WarningMessagesOnScreenLifetime_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
		{ "ModuleRelativePath", "Public/EasyCsvProjectSettings.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_WarningMessagesOnScreenLifetime = { "WarningMessagesOnScreenLifetime", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEasyCsvProjectSettings, WarningMessagesOnScreenLifetime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_WarningMessagesOnScreenLifetime_MetaData), Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_WarningMessagesOnScreenLifetime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintErrorMessagesToLog_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *If true, \"Error\" type messages will be printed to the log. These will not display on screen.\n\x09 *\"Error\" type messages are very important to the end user as they explain fatal issues.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsvProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, \"Error\" type messages will be printed to the log. These will not display on screen.\n\"Error\" type messages are very important to the end user as they explain fatal issues." },
#endif
	};
#endif
	void Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintErrorMessagesToLog_SetBit(void* Obj)
	{
		((UEasyCsvProjectSettings*)Obj)->bPrintErrorMessagesToLog = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintErrorMessagesToLog = { "bPrintErrorMessagesToLog", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UEasyCsvProjectSettings), &Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintErrorMessagesToLog_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintErrorMessagesToLog_MetaData), Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintErrorMessagesToLog_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintErrorMessagesToScreen_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *If true, \"Error\" type messages will be printed to the screen. These will not appear in the output log.\n\x09 *\"Error\" type messages are very important to the end user as they explain fatal issues.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/EasyCsvProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, \"Error\" type messages will be printed to the screen. These will not appear in the output log.\n\"Error\" type messages are very important to the end user as they explain fatal issues." },
#endif
	};
#endif
	void Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintErrorMessagesToScreen_SetBit(void* Obj)
	{
		((UEasyCsvProjectSettings*)Obj)->bPrintErrorMessagesToScreen = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintErrorMessagesToScreen = { "bPrintErrorMessagesToScreen", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UEasyCsvProjectSettings), &Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintErrorMessagesToScreen_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintErrorMessagesToScreen_MetaData), Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintErrorMessagesToScreen_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_ErrorMessagesOnScreenLifetime_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
		{ "ModuleRelativePath", "Public/EasyCsvProjectSettings.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_ErrorMessagesOnScreenLifetime = { "ErrorMessagesOnScreenLifetime", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEasyCsvProjectSettings, ErrorMessagesOnScreenLifetime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_ErrorMessagesOnScreenLifetime_MetaData), Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_ErrorMessagesOnScreenLifetime_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UEasyCsvProjectSettings_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_LogCharacterLimit,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintDisplayMessagesToLog,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintDisplayMessagesToScreen,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_DisplayMessagesOnScreenLifetime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintWarningMessagesToLog,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintWarningMessagesToScreen,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_WarningMessagesOnScreenLifetime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintErrorMessagesToLog,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_bPrintErrorMessagesToScreen,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEasyCsvProjectSettings_Statics::NewProp_ErrorMessagesOnScreenLifetime,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UEasyCsvProjectSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEasyCsvProjectSettings>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UEasyCsvProjectSettings_Statics::ClassParams = {
		&UEasyCsvProjectSettings::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UEasyCsvProjectSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsvProjectSettings_Statics::PropPointers),
		0,
		0x001000A6u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsvProjectSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UEasyCsvProjectSettings_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEasyCsvProjectSettings_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UEasyCsvProjectSettings()
	{
		if (!Z_Registration_Info_UClass_UEasyCsvProjectSettings.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UEasyCsvProjectSettings.OuterSingleton, Z_Construct_UClass_UEasyCsvProjectSettings_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UEasyCsvProjectSettings.OuterSingleton;
	}
	template<> EASYCSV_API UClass* StaticClass<UEasyCsvProjectSettings>()
	{
		return UEasyCsvProjectSettings::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UEasyCsvProjectSettings);
	UEasyCsvProjectSettings::~UEasyCsvProjectSettings() {}
	struct Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsvProjectSettings_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsvProjectSettings_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UEasyCsvProjectSettings, UEasyCsvProjectSettings::StaticClass, TEXT("UEasyCsvProjectSettings"), &Z_Registration_Info_UClass_UEasyCsvProjectSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UEasyCsvProjectSettings), 8112586U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsvProjectSettings_h_1696637367(TEXT("/Script/EasyCsv"),
		Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsvProjectSettings_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsvProjectSettings_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
