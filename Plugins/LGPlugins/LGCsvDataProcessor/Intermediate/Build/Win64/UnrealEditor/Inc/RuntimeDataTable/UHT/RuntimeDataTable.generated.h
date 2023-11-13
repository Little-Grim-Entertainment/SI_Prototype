// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "RuntimeDataTable.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
enum class ERuntimeDataTableBackupResultCode : uint8;
struct FEasyCsvInfo;
struct FRuntimeDataTableCallbackInfo;
struct FRuntimeDataTableOperationParams;
struct FRuntimeDataTableTokenInfo;
#ifdef RUNTIMEDATATABLE_RuntimeDataTable_generated_h
#error "RuntimeDataTable.generated.h already included, missing '#pragma once' in RuntimeDataTable.h"
#endif
#define RUNTIMEDATATABLE_RuntimeDataTable_generated_h

#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_21_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FRuntimeDataTableCallbackInfo_Statics; \
	RUNTIMEDATATABLE_API static class UScriptStruct* StaticStruct();


template<> RUNTIMEDATATABLE_API UScriptStruct* StaticStruct<struct FRuntimeDataTableCallbackInfo>();

#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_39_DELEGATE \
RUNTIMEDATATABLE_API void FRDTGetStringDelegate_DelegateWrapper(const FScriptDelegate& RDTGetStringDelegate, FRuntimeDataTableCallbackInfo CallbackInfo);


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_45_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FRuntimeDataTableOperationParams_Statics; \
	RUNTIMEDATATABLE_API static class UScriptStruct* StaticStruct();


template<> RUNTIMEDATATABLE_API UScriptStruct* StaticStruct<struct FRuntimeDataTableOperationParams>();

#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_60_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FRuntimeDataTableTokenInfo_Statics; \
	RUNTIMEDATATABLE_API static class UScriptStruct* StaticStruct();


template<> RUNTIMEDATATABLE_API UScriptStruct* StaticStruct<struct FRuntimeDataTableTokenInfo>();

#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_SPARSE_DATA
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetTokenText); \
	DECLARE_FUNCTION(execGetNumberOfSecondsUntilExpiration); \
	DECLARE_FUNCTION(execHasTokenExpired); \
	DECLARE_FUNCTION(execInit);


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesURuntimeDataTableWebToken(); \
	friend struct Z_Construct_UClass_URuntimeDataTableWebToken_Statics; \
public: \
	DECLARE_CLASS(URuntimeDataTableWebToken, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/RuntimeDataTable"), NO_API) \
	DECLARE_SERIALIZER(URuntimeDataTableWebToken)


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API URuntimeDataTableWebToken(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API URuntimeDataTableWebToken(URuntimeDataTableWebToken&&); \
	NO_API URuntimeDataTableWebToken(const URuntimeDataTableWebToken&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, URuntimeDataTableWebToken); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(URuntimeDataTableWebToken); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(URuntimeDataTableWebToken) \
	NO_API virtual ~URuntimeDataTableWebToken();


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_96_PROLOG
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_SPARSE_DATA \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_INCLASS_NO_PURE_DECLS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_101_ENHANCED_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> RUNTIMEDATATABLE_API UClass* StaticClass<class URuntimeDataTableWebToken>();

#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_SPARSE_DATA
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetAllObjectVariableNames); \
	DECLARE_FUNCTION(execWriteCsvToSheet); \
	DECLARE_FUNCTION(execValidateGoogleSheetsDownloadAndLoadBackupIfNeeded); \
	DECLARE_FUNCTION(execBuildGoogleSheetDownloadLinkAndGetAsCsv); \
	DECLARE_FUNCTION(execAutoGenerateKeys); \
	DECLARE_FUNCTION(execGetGoogleSheetsBatchUpdateURL); \
	DECLARE_FUNCTION(execGetGoogleSheetsValuesBatchUpdateURL); \
	DECLARE_FUNCTION(execGetGoogleSheetsApiUrlPrefix); \
	DECLARE_FUNCTION(execGetMimeCsv); \
	DECLARE_FUNCTION(execGetGoogleSheetsUrlPrefix); \
	DECLARE_FUNCTION(execGetSheetIdFromUrl_Int); \
	DECLARE_FUNCTION(execGetSheetIdFromUrl); \
	DECLARE_FUNCTION(execGetSpreadsheetIdFromUrl); \
	DECLARE_FUNCTION(execGenerateTokenInfoFromFile); \
	DECLARE_FUNCTION(execGenerateTokenInfoFromString);


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesURuntimeDataTableObject(); \
	friend struct Z_Construct_UClass_URuntimeDataTableObject_Statics; \
public: \
	DECLARE_CLASS(URuntimeDataTableObject, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/RuntimeDataTable"), NO_API) \
	DECLARE_SERIALIZER(URuntimeDataTableObject)


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API URuntimeDataTableObject(URuntimeDataTableObject&&); \
	NO_API URuntimeDataTableObject(const URuntimeDataTableObject&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, URuntimeDataTableObject); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(URuntimeDataTableObject); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(URuntimeDataTableObject) \
	NO_API virtual ~URuntimeDataTableObject();


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_131_PROLOG
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_SPARSE_DATA \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_INCLASS_NO_PURE_DECLS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h_134_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> RUNTIMEDATATABLE_API UClass* StaticClass<class URuntimeDataTableObject>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_RuntimeDataTable_Public_RuntimeDataTable_h


#define FOREACH_ENUM_ERUNTIMEDATATABLEBACKUPRESULTCODE(op) \
	op(ERuntimeDataTableBackupResultCode::DownloadFailedWithoutBackup) \
	op(ERuntimeDataTableBackupResultCode::DownloadFailedAndBackupExistsBuCouldNotBeLoaded) \
	op(ERuntimeDataTableBackupResultCode::DownloadSucceededButCsvCouldNotBeParsed) \
	op(ERuntimeDataTableBackupResultCode::DownloadFailedAndBackupLoaded) \
	op(ERuntimeDataTableBackupResultCode::DownloadSucceededAndBackupSaved) \
	op(ERuntimeDataTableBackupResultCode::DownloadSucceededAndBackupCouldNotBeSaved) 

enum class ERuntimeDataTableBackupResultCode : uint8;
template<> struct TIsUEnumClass<ERuntimeDataTableBackupResultCode> { enum { Value = true }; };
template<> RUNTIMEDATATABLE_API UEnum* StaticEnum<ERuntimeDataTableBackupResultCode>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
