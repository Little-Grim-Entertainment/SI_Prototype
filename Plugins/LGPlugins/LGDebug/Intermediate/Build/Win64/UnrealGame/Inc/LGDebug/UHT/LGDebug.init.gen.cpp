// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLGDebug_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_LGDebug;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_LGDebug()
	{
		if (!Z_Registration_Info_UPackage__Script_LGDebug.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/LGDebug",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x712305C8,
				0xEFBC7FA8,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_LGDebug.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_LGDebug.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_LGDebug(Z_Construct_UPackage__Script_LGDebug, TEXT("/Script/LGDebug"), Z_Registration_Info_UPackage__Script_LGDebug, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x712305C8, 0xEFBC7FA8));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
