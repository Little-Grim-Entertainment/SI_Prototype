// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "EasyCsv.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FEasyCsvInfo;
#ifdef EASYCSV_EasyCsv_generated_h
#error "EasyCsv.generated.h already included, missing '#pragma once' in EasyCsv.h"
#endif
#define EASYCSV_EasyCsv_generated_h

#define FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_SPARSE_DATA
#define FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execConvertQuatStringToRotatorArray); \
	DECLARE_FUNCTION(execConvertQuatStringToRotator); \
	DECLARE_FUNCTION(execConvertStringToQuatArray); \
	DECLARE_FUNCTION(execConvertStringToQuat); \
	DECLARE_FUNCTION(execConvertStringToRotatorArray); \
	DECLARE_FUNCTION(execConvertStringToRotator); \
	DECLARE_FUNCTION(execGetFTextComponentsFromRepresentativeFString); \
	DECLARE_FUNCTION(execEscapeCharacters); \
	DECLARE_FUNCTION(execReplaceEscapedCharacters); \
	DECLARE_FUNCTION(execDoesStringRepresentContainer); \
	DECLARE_FUNCTION(execMakeCsvInfoStructFromFile); \
	DECLARE_FUNCTION(execMakeCsvInfoStructFromString); \
	DECLARE_FUNCTION(execGetColumnCount); \
	DECLARE_FUNCTION(execGetRowCount); \
	DECLARE_FUNCTION(execGetMapKeyIndex); \
	DECLARE_FUNCTION(execGetMapHeaders); \
	DECLARE_FUNCTION(execGetMapKeys); \
	DECLARE_FUNCTION(execGetRowValueAsString); \
	DECLARE_FUNCTION(execGetRowAsStringArray); \
	DECLARE_FUNCTION(execGetColumnAsStringArray); \
	DECLARE_FUNCTION(execLoadStringFromLocalFile); \
	DECLARE_FUNCTION(execSaveStringToFileWithFullPath); \
	DECLARE_FUNCTION(execSaveStringToFile);


#define FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_ACCESSORS
#define FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUEasyCsv(); \
	friend struct Z_Construct_UClass_UEasyCsv_Statics; \
public: \
	DECLARE_CLASS(UEasyCsv, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/EasyCsv"), NO_API) \
	DECLARE_SERIALIZER(UEasyCsv)


#define FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UEasyCsv(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UEasyCsv(UEasyCsv&&); \
	NO_API UEasyCsv(const UEasyCsv&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UEasyCsv); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UEasyCsv); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UEasyCsv) \
	NO_API virtual ~UEasyCsv();


#define FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_9_PROLOG
#define FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_SPARSE_DATA \
	FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_ACCESSORS \
	FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_INCLASS_NO_PURE_DECLS \
	FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> EASYCSV_API UClass* StaticClass<class UEasyCsv>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_SpadeInvestigations_SpadeInvestigations_Plugins_LGPlugins_LGCsvDataProcessor_Source_EasyCsv_Public_EasyCsv_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
