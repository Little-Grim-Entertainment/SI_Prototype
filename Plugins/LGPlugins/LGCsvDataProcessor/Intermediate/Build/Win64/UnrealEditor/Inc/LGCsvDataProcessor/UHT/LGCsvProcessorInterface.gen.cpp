// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LGCsvDataProcessor/Public/Interfaces/LGCsvProcessorInterface.h"
#include "LGCsvDataProcessor/Public/LGCsvDataTypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLGCsvProcessorInterface() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	LGCSVDATAPROCESSOR_API UClass* Z_Construct_UClass_ULGCsvProcessorInterface();
	LGCSVDATAPROCESSOR_API UClass* Z_Construct_UClass_ULGCsvProcessorInterface_NoRegister();
	LGCSVDATAPROCESSOR_API UScriptStruct* Z_Construct_UScriptStruct_FLGCsvInfo();
	UPackage* Z_Construct_UPackage__Script_LGCsvDataProcessor();
// End Cross Module References
	DEFINE_FUNCTION(ILGCsvProcessorInterface::execOnInteractComplete)
	{
		P_GET_OBJECT(UObject,Z_Param_Caller);
		P_GET_STRUCT_REF(FLGCsvInfo,Z_Param_Out_InCvsInfo);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnInteractComplete_Implementation(Z_Param_Caller,Z_Param_Out_InCvsInfo);
		P_NATIVE_END;
	}
	struct LGCsvProcessorInterface_eventOnInteractComplete_Parms
	{
		UObject* Caller;
		FLGCsvInfo InCvsInfo;
	};
	void ILGCsvProcessorInterface::OnInteractComplete(UObject* Caller, FLGCsvInfo const& InCvsInfo)
	{
		check(0 && "Do not directly call Event functions in Interfaces. Call Execute_OnInteractComplete instead.");
	}
	void ULGCsvProcessorInterface::StaticRegisterNativesULGCsvProcessorInterface()
	{
		UClass* Class = ULGCsvProcessorInterface::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnInteractComplete", &ILGCsvProcessorInterface::execOnInteractComplete },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics
	{
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Caller;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InCvsInfo_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_InCvsInfo;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::NewProp_Caller = { "Caller", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LGCsvProcessorInterface_eventOnInteractComplete_Parms, Caller), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::NewProp_InCvsInfo_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::NewProp_InCvsInfo = { "InCvsInfo", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LGCsvProcessorInterface_eventOnInteractComplete_Parms, InCvsInfo), Z_Construct_UScriptStruct_FLGCsvInfo, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::NewProp_InCvsInfo_MetaData), Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::NewProp_InCvsInfo_MetaData) }; // 1190441655
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::NewProp_Caller,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::NewProp_InCvsInfo,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::Function_MetaDataParams[] = {
		{ "Category", "DialogueProcessing" },
		{ "ModuleRelativePath", "Public/Interfaces/LGCsvProcessorInterface.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULGCsvProcessorInterface, nullptr, "OnInteractComplete", nullptr, nullptr, Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::PropPointers), sizeof(LGCsvProcessorInterface_eventOnInteractComplete_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0C420C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::PropPointers) < 2048);
	static_assert(sizeof(LGCsvProcessorInterface_eventOnInteractComplete_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULGCsvProcessorInterface);
	UClass* Z_Construct_UClass_ULGCsvProcessorInterface_NoRegister()
	{
		return ULGCsvProcessorInterface::StaticClass();
	}
	struct Z_Construct_UClass_ULGCsvProcessorInterface_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULGCsvProcessorInterface_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UInterface,
		(UObject* (*)())Z_Construct_UPackage__Script_LGCsvDataProcessor,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGCsvProcessorInterface_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_ULGCsvProcessorInterface_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULGCsvProcessorInterface_OnInteractComplete, "OnInteractComplete" }, // 552562015
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULGCsvProcessorInterface_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULGCsvProcessorInterface_Statics::Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Interfaces/LGCsvProcessorInterface.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULGCsvProcessorInterface_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ILGCsvProcessorInterface>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ULGCsvProcessorInterface_Statics::ClassParams = {
		&ULGCsvProcessorInterface::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x000040A1u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULGCsvProcessorInterface_Statics::Class_MetaDataParams), Z_Construct_UClass_ULGCsvProcessorInterface_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ULGCsvProcessorInterface()
	{
		if (!Z_Registration_Info_UClass_ULGCsvProcessorInterface.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULGCsvProcessorInterface.OuterSingleton, Z_Construct_UClass_ULGCsvProcessorInterface_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ULGCsvProcessorInterface.OuterSingleton;
	}
	template<> LGCSVDATAPROCESSOR_API UClass* StaticClass<ULGCsvProcessorInterface>()
	{
		return ULGCsvProcessorInterface::StaticClass();
	}
	ULGCsvProcessorInterface::ULGCsvProcessorInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULGCsvProcessorInterface);
	ULGCsvProcessorInterface::~ULGCsvProcessorInterface() {}
	static FName NAME_ULGCsvProcessorInterface_OnInteractComplete = FName(TEXT("OnInteractComplete"));
	void ILGCsvProcessorInterface::Execute_OnInteractComplete(UObject* O, UObject* Caller, FLGCsvInfo const& InCvsInfo)
	{
		check(O != NULL);
		check(O->GetClass()->ImplementsInterface(ULGCsvProcessorInterface::StaticClass()));
		LGCsvProcessorInterface_eventOnInteractComplete_Parms Parms;
		UFunction* const Func = O->FindFunction(NAME_ULGCsvProcessorInterface_OnInteractComplete);
		if (Func)
		{
			Parms.Caller=Caller;
			Parms.InCvsInfo=InCvsInfo;
			O->ProcessEvent(Func, &Parms);
		}
		else if (auto I = (ILGCsvProcessorInterface*)(O->GetNativeInterfaceAddress(ULGCsvProcessorInterface::StaticClass())))
		{
			I->OnInteractComplete_Implementation(Caller,InCvsInfo);
		}
	}
	struct Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ULGCsvProcessorInterface, ULGCsvProcessorInterface::StaticClass, TEXT("ULGCsvProcessorInterface"), &Z_Registration_Info_UClass_ULGCsvProcessorInterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULGCsvProcessorInterface), 3104988546U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_3499485756(TEXT("/Script/LGCsvDataProcessor"),
		Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SI_Prototype_Plugins_LGPlugins_LGCsvDataProcessor_Source_LGCsvDataProcessor_Public_Interfaces_LGCsvProcessorInterface_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
