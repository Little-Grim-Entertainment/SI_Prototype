// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRuntimeDataTable_init() {}
	RUNTIMEDATATABLE_API UFunction* Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_RuntimeDataTable;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_RuntimeDataTable()
	{
		if (!Z_Registration_Info_UPackage__Script_RuntimeDataTable.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_RuntimeDataTable_RDTGetStringDelegate__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/RuntimeDataTable",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x2456AF46,
				0x2C06A8E8,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_RuntimeDataTable.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_RuntimeDataTable.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_RuntimeDataTable(Z_Construct_UPackage__Script_RuntimeDataTable, TEXT("/Script/RuntimeDataTable"), Z_Registration_Info_UPackage__Script_RuntimeDataTable, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x2456AF46, 0x2C06A8E8));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
