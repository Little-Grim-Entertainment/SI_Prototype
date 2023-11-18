// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "LGCsvDataProcessorFunctionLibrary.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLGCsvInfoImportPayload;
struct FRuntimeDataTableCallbackInfo;
#ifdef LGCSVDATAPROCESSOR_LGCsvDataProcessorFunctionLibrary_generated_h
#error "LGCsvDataProcessorFunctionLibrary.generated.h already included, missing '#pragma once' in LGCsvDataProcessorFunctionLibrary.h"
#endif
#define LGCSVDATAPROCESSOR_LGCsvDataProcessorFunctionLibrary_generated_h

#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_SPARSE_DATA
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnSheetStructsDownloaded); \
	DECLARE_FUNCTION(execFNameArrayToFStringArray); \
	DECLARE_FUNCTION(execImportCsvFromURL);


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULGCsvDataProcessorFunctionLibrary(); \
	friend struct Z_Construct_UClass_ULGCsvDataProcessorFunctionLibrary_Statics; \
public: \
	DECLARE_CLASS(ULGCsvDataProcessorFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LGCsvDataProcessor"), NO_API) \
	DECLARE_SERIALIZER(ULGCsvDataProcessorFunctionLibrary)


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULGCsvDataProcessorFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULGCsvDataProcessorFunctionLibrary(ULGCsvDataProcessorFunctionLibrary&&); \
	NO_API ULGCsvDataProcessorFunctionLibrary(const ULGCsvDataProcessorFunctionLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULGCsvDataProcessorFunctionLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULGCsvDataProcessorFunctionLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULGCsvDataProcessorFunctionLibrary) \
	NO_API virtual ~ULGCsvDataProcessorFunctionLibrary();


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_13_PROLOG
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_SPARSE_DATA \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_INCLASS_NO_PURE_DECLS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LGCSVDATAPROCESSOR_API UClass* StaticClass<class ULGCsvDataProcessorFunctionLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_LGCsvDataProcessorFunctionLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
