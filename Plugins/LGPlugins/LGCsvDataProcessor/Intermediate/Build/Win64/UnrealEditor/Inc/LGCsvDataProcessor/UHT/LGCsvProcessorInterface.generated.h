// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Interfaces/LGCsvProcessorInterface.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
struct FLGCsvInfo;
#ifdef LGCSVDATAPROCESSOR_LGCsvProcessorInterface_generated_h
#error "LGCsvProcessorInterface.generated.h already included, missing '#pragma once' in LGCsvProcessorInterface.h"
#endif
#define LGCSVDATAPROCESSOR_LGCsvProcessorInterface_generated_h

#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_SPARSE_DATA
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void OnInteractComplete_Implementation(UObject* Caller, FLGCsvInfo const& InCvsInfo) {}; \
 \
	DECLARE_FUNCTION(execOnInteractComplete);


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_CALLBACK_WRAPPERS
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULGCsvProcessorInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULGCsvProcessorInterface(ULGCsvProcessorInterface&&); \
	NO_API ULGCsvProcessorInterface(const ULGCsvProcessorInterface&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULGCsvProcessorInterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULGCsvProcessorInterface); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULGCsvProcessorInterface) \
	NO_API virtual ~ULGCsvProcessorInterface();


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesULGCsvProcessorInterface(); \
	friend struct Z_Construct_UClass_ULGCsvProcessorInterface_Statics; \
public: \
	DECLARE_CLASS(ULGCsvProcessorInterface, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/LGCsvDataProcessor"), NO_API) \
	DECLARE_SERIALIZER(ULGCsvProcessorInterface)


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_GENERATED_UINTERFACE_BODY() \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~ILGCsvProcessorInterface() {} \
public: \
	typedef ULGCsvProcessorInterface UClassType; \
	typedef ILGCsvProcessorInterface ThisClass; \
	static void Execute_OnInteractComplete(UObject* O, UObject* Caller, FLGCsvInfo const& InCvsInfo); \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_11_PROLOG
#define FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_SPARSE_DATA \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_CALLBACK_WRAPPERS \
	FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_14_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LGCSVDATAPROCESSOR_API UClass* StaticClass<class ULGCsvProcessorInterface>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
