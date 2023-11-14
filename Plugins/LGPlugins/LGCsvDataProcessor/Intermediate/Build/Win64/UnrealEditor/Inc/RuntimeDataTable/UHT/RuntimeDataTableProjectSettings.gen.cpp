// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RuntimeDataTableProjectSettings.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRuntimeDataTableProjectSettings() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	RUNTIMEDATATABLE_API UClass* Z_Construct_UClass_URuntimeDataTableProjectSettings();
	RUNTIMEDATATABLE_API UClass* Z_Construct_UClass_URuntimeDataTableProjectSettings_NoRegister();
	UPackage* Z_Construct_UPackage__Script_RuntimeDataTable();
// End Cross Module References
	void URuntimeDataTableProjectSettings::StaticRegisterNativesURuntimeDataTableProjectSettings()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(URuntimeDataTableProjectSettings);
	UClass* Z_Construct_UClass_URuntimeDataTableProjectSettings_NoRegister()
	{
		return URuntimeDataTableProjectSettings::StaticClass();
	}
	struct Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics
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
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GoogleSheetsUrlPrefix_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_GoogleSheetsUrlPrefix;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GoogleSheetsApiUrlPrefix_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_GoogleSheetsApiUrlPrefix;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GoogleSheetsBatchUpdateCommand_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_GoogleSheetsBatchUpdateCommand;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GoogleSheetsValuesBatchUpdateCommand_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_GoogleSheetsValuesBatchUpdateCommand;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GoogleSheetsMimeCsv_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_GoogleSheetsMimeCsv;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_RuntimeDataTable,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "RuntimeDataTableProjectSettings.h" },
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_LogCharacterLimit_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *The number of characters that can be printed in any given print. -1 means no limit.\n\x09 *This is useful when printing responses which can be enormous with very large sheets.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The number of characters that can be printed in any given print. -1 means no limit.\nThis is useful when printing responses which can be enormous with very large sheets." },
#endif
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_LogCharacterLimit = { "LogCharacterLimit", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URuntimeDataTableProjectSettings, LogCharacterLimit), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_LogCharacterLimit_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_LogCharacterLimit_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintDisplayMessagesToLog_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *If true, \"Display\" type messages will be printed to the log. These will not display on screen.\n\x09 *\"Display\" type messages are informational messages most end users don't have much interest in seeing.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, \"Display\" type messages will be printed to the log. These will not display on screen.\n\"Display\" type messages are informational messages most end users don't have much interest in seeing." },
#endif
	};
#endif
	void Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintDisplayMessagesToLog_SetBit(void* Obj)
	{
		((URuntimeDataTableProjectSettings*)Obj)->bPrintDisplayMessagesToLog = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintDisplayMessagesToLog = { "bPrintDisplayMessagesToLog", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(URuntimeDataTableProjectSettings), &Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintDisplayMessagesToLog_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintDisplayMessagesToLog_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintDisplayMessagesToLog_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintDisplayMessagesToScreen_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *If true, \"Display\" type messages will be printed to the screen. These will not appear in the output log.\n\x09 *\"Display\" type messages are informational messages most end users don't have much interest in seeing.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, \"Display\" type messages will be printed to the screen. These will not appear in the output log.\n\"Display\" type messages are informational messages most end users don't have much interest in seeing." },
#endif
	};
#endif
	void Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintDisplayMessagesToScreen_SetBit(void* Obj)
	{
		((URuntimeDataTableProjectSettings*)Obj)->bPrintDisplayMessagesToScreen = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintDisplayMessagesToScreen = { "bPrintDisplayMessagesToScreen", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(URuntimeDataTableProjectSettings), &Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintDisplayMessagesToScreen_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintDisplayMessagesToScreen_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintDisplayMessagesToScreen_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_DisplayMessagesOnScreenLifetime_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_DisplayMessagesOnScreenLifetime = { "DisplayMessagesOnScreenLifetime", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URuntimeDataTableProjectSettings, DisplayMessagesOnScreenLifetime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_DisplayMessagesOnScreenLifetime_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_DisplayMessagesOnScreenLifetime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintWarningMessagesToLog_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *If true, \"Warning\" type messages will be printed to the log. These will not display on screen.\n\x09 *\"Warning\" type messages are important to most end users, but warnings are not fatal.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, \"Warning\" type messages will be printed to the log. These will not display on screen.\n\"Warning\" type messages are important to most end users, but warnings are not fatal." },
#endif
	};
#endif
	void Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintWarningMessagesToLog_SetBit(void* Obj)
	{
		((URuntimeDataTableProjectSettings*)Obj)->bPrintWarningMessagesToLog = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintWarningMessagesToLog = { "bPrintWarningMessagesToLog", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(URuntimeDataTableProjectSettings), &Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintWarningMessagesToLog_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintWarningMessagesToLog_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintWarningMessagesToLog_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintWarningMessagesToScreen_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *If true, \"Warning\" type messages will be printed to the screen. These will not appear in the output log.\n\x09 *\"Warning\" type messages are important to most end users, but warnings are not fatal. \n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, \"Warning\" type messages will be printed to the screen. These will not appear in the output log.\n\"Warning\" type messages are important to most end users, but warnings are not fatal." },
#endif
	};
#endif
	void Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintWarningMessagesToScreen_SetBit(void* Obj)
	{
		((URuntimeDataTableProjectSettings*)Obj)->bPrintWarningMessagesToScreen = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintWarningMessagesToScreen = { "bPrintWarningMessagesToScreen", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(URuntimeDataTableProjectSettings), &Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintWarningMessagesToScreen_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintWarningMessagesToScreen_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintWarningMessagesToScreen_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_WarningMessagesOnScreenLifetime_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_WarningMessagesOnScreenLifetime = { "WarningMessagesOnScreenLifetime", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URuntimeDataTableProjectSettings, WarningMessagesOnScreenLifetime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_WarningMessagesOnScreenLifetime_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_WarningMessagesOnScreenLifetime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintErrorMessagesToLog_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *If true, \"Error\" type messages will be printed to the log. These will not display on screen.\n\x09 *\"Error\" type messages are very important to the end user as they explain fatal issues.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, \"Error\" type messages will be printed to the log. These will not display on screen.\n\"Error\" type messages are very important to the end user as they explain fatal issues." },
#endif
	};
#endif
	void Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintErrorMessagesToLog_SetBit(void* Obj)
	{
		((URuntimeDataTableProjectSettings*)Obj)->bPrintErrorMessagesToLog = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintErrorMessagesToLog = { "bPrintErrorMessagesToLog", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(URuntimeDataTableProjectSettings), &Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintErrorMessagesToLog_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintErrorMessagesToLog_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintErrorMessagesToLog_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintErrorMessagesToScreen_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *If true, \"Error\" type messages will be printed to the screen. These will not appear in the output log.\n\x09 *\"Error\" type messages are very important to the end user as they explain fatal issues.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, \"Error\" type messages will be printed to the screen. These will not appear in the output log.\n\"Error\" type messages are very important to the end user as they explain fatal issues." },
#endif
	};
#endif
	void Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintErrorMessagesToScreen_SetBit(void* Obj)
	{
		((URuntimeDataTableProjectSettings*)Obj)->bPrintErrorMessagesToScreen = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintErrorMessagesToScreen = { "bPrintErrorMessagesToScreen", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(URuntimeDataTableProjectSettings), &Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintErrorMessagesToScreen_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintErrorMessagesToScreen_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintErrorMessagesToScreen_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_ErrorMessagesOnScreenLifetime_MetaData[] = {
		{ "Category", "Google Sheets Operator|Logging" },
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_ErrorMessagesOnScreenLifetime = { "ErrorMessagesOnScreenLifetime", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URuntimeDataTableProjectSettings, ErrorMessagesOnScreenLifetime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_ErrorMessagesOnScreenLifetime_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_ErrorMessagesOnScreenLifetime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsUrlPrefix_MetaData[] = {
		{ "Category", "Google Sheets Operator|Advanced|URI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *Determines the beginning of the URL used to build a locator for a spreadsheet resource.\n\x09 *Only change this parameter if you know you need to.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Determines the beginning of the URL used to build a locator for a spreadsheet resource.\nOnly change this parameter if you know you need to." },
#endif
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsUrlPrefix = { "GoogleSheetsUrlPrefix", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URuntimeDataTableProjectSettings, GoogleSheetsUrlPrefix), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsUrlPrefix_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsUrlPrefix_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsApiUrlPrefix_MetaData[] = {
		{ "Category", "Google Sheets Operator|Advanced|URI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *Determines the beginning of the URL used to build a locator for a spreadsheet resource as it relates to the Google Sheets API.\n\x09 *Only change this parameter if you know you need to.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Determines the beginning of the URL used to build a locator for a spreadsheet resource as it relates to the Google Sheets API.\nOnly change this parameter if you know you need to." },
#endif
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsApiUrlPrefix = { "GoogleSheetsApiUrlPrefix", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URuntimeDataTableProjectSettings, GoogleSheetsApiUrlPrefix), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsApiUrlPrefix_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsApiUrlPrefix_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsBatchUpdateCommand_MetaData[] = {
		{ "Category", "Google Sheets Operator|Advanced|URI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *The command used to perform a batch update of sheet properties.\n\x09 *Only change this parameter if you know you need to.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The command used to perform a batch update of sheet properties.\nOnly change this parameter if you know you need to." },
#endif
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsBatchUpdateCommand = { "GoogleSheetsBatchUpdateCommand", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URuntimeDataTableProjectSettings, GoogleSheetsBatchUpdateCommand), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsBatchUpdateCommand_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsBatchUpdateCommand_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsValuesBatchUpdateCommand_MetaData[] = {
		{ "Category", "Google Sheets Operator|Advanced|URI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *The command used to perform a batch update of sheet values.\n\x09 *Only change this parameter if you know you need to.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The command used to perform a batch update of sheet values.\nOnly change this parameter if you know you need to." },
#endif
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsValuesBatchUpdateCommand = { "GoogleSheetsValuesBatchUpdateCommand", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URuntimeDataTableProjectSettings, GoogleSheetsValuesBatchUpdateCommand), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsValuesBatchUpdateCommand_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsValuesBatchUpdateCommand_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsMimeCsv_MetaData[] = {
		{ "Category", "Google Sheets Operator|Advanced|URI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 *The selector used to specify data as type CSV.\n\x09 *Only change this parameter if you know you need to.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/RuntimeDataTableProjectSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The selector used to specify data as type CSV.\nOnly change this parameter if you know you need to." },
#endif
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsMimeCsv = { "GoogleSheetsMimeCsv", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URuntimeDataTableProjectSettings, GoogleSheetsMimeCsv), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsMimeCsv_MetaData), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsMimeCsv_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_LogCharacterLimit,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintDisplayMessagesToLog,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintDisplayMessagesToScreen,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_DisplayMessagesOnScreenLifetime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintWarningMessagesToLog,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintWarningMessagesToScreen,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_WarningMessagesOnScreenLifetime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintErrorMessagesToLog,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_bPrintErrorMessagesToScreen,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_ErrorMessagesOnScreenLifetime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsUrlPrefix,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsApiUrlPrefix,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsBatchUpdateCommand,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsValuesBatchUpdateCommand,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::NewProp_GoogleSheetsMimeCsv,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URuntimeDataTableProjectSettings>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::ClassParams = {
		&URuntimeDataTableProjectSettings::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::PropPointers),
		0,
		0x001000A6u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_URuntimeDataTableProjectSettings()
	{
		if (!Z_Registration_Info_UClass_URuntimeDataTableProjectSettings.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URuntimeDataTableProjectSettings.OuterSingleton, Z_Construct_UClass_URuntimeDataTableProjectSettings_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_URuntimeDataTableProjectSettings.OuterSingleton;
	}
	template<> RUNTIMEDATATABLE_API UClass* StaticClass<URuntimeDataTableProjectSettings>()
	{
		return URuntimeDataTableProjectSettings::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(URuntimeDataTableProjectSettings);
	URuntimeDataTableProjectSettings::~URuntimeDataTableProjectSettings() {}
	struct Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTableProjectSettings_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTableProjectSettings_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_URuntimeDataTableProjectSettings, URuntimeDataTableProjectSettings::StaticClass, TEXT("URuntimeDataTableProjectSettings"), &Z_Registration_Info_UClass_URuntimeDataTableProjectSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URuntimeDataTableProjectSettings), 3230470351U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTableProjectSettings_h_1241712690(TEXT("/Script/RuntimeDataTable"),
		Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTableProjectSettings_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTableProjectSettings_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
