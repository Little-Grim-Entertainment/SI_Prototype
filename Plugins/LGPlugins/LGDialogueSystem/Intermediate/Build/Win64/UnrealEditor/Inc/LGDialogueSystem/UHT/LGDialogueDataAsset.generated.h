// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Data/LGDialogueDataAsset.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FRuntimeDataTableCallbackInfo;
#ifdef LGDIALOGUESYSTEM_LGDialogueDataAsset_generated_h
#error "LGDialogueDataAsset.generated.h already included, missing '#pragma once' in LGDialogueDataAsset.h"
#endif
#define LGDIALOGUESYSTEM_LGDialogueDataAsset_generated_h

#define FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_SPARSE_DATA
#define FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execUpdateDialogue); \
	DECLARE_FUNCTION(execOnSheetStructsDownloaded);


#define FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_ACCESSORS
#define FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULGDialogueDataAsset(); \
	friend struct Z_Construct_UClass_ULGDialogueDataAsset_Statics; \
public: \
	DECLARE_CLASS(ULGDialogueDataAsset, UDataAsset, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LGDialogueSystem"), NO_API) \
	DECLARE_SERIALIZER(ULGDialogueDataAsset) \
	virtual UObject* _getUObject() const override { return const_cast<ULGDialogueDataAsset*>(this); }


#define FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULGDialogueDataAsset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULGDialogueDataAsset(ULGDialogueDataAsset&&); \
	NO_API ULGDialogueDataAsset(const ULGDialogueDataAsset&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULGDialogueDataAsset); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULGDialogueDataAsset); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULGDialogueDataAsset) \
	NO_API virtual ~ULGDialogueDataAsset();


#define FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_14_PROLOG
#define FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_SPARSE_DATA \
	FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_ACCESSORS \
	FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_INCLASS_NO_PURE_DECLS \
	FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LGDIALOGUESYSTEM_API UClass* StaticClass<class ULGDialogueDataAsset>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_SI_Prototype_Plugins_LGPlugins_LGDialogueSystem_Source_LGDialogueSystem_Public_Data_LGDialogueDataAsset_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
