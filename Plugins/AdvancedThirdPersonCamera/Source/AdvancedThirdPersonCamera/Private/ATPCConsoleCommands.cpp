// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#include "ATPCCameraComponent.h"
#include "ATPCCameraModeDataAsset.h"
#include "AdvancedThirdPersonCamera.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

class FStructVisitor
{
public:
	virtual ~FStructVisitor() = default;

	virtual void VisitNumericProperty(FNumericProperty* Property, const void* Value) = 0;
	virtual void VisitBoolProperty(FBoolProperty* Property, const void* Value) = 0;
	virtual void EnterStructProperty(FStructProperty* Property, const void* Value) = 0;
	virtual void ExitStructProperty() = 0;
};

class FSturctFinderVisitor : public FStructVisitor
{
public:
	FSturctFinderVisitor(const FString& InPathToProperty)
	{
		InPathToProperty.ParseIntoArray(PathToProperty, TEXT("."));
	}

	virtual void VisitNumericProperty(FNumericProperty* Property, const void* Value) override
	{
		VisitSimpleProperty(Property, Value);
	}
	virtual void VisitBoolProperty(FBoolProperty* Property, const void* Value) override
	{
		VisitSimpleProperty(Property, Value);
	}
	virtual void EnterStructProperty(FStructProperty* Property, const void* Value) override
	{
		if (PathToProperty.Num() != 0 && PathToProperty[0] == Property->GetNameCPP())
		{
			PathToProperty.RemoveAt(0);
		}
	}
	virtual void ExitStructProperty() override
	{
	}

	FProperty* GetFoundProperty() const
	{
		return FoundProperty;
	}

	const void* GetFoundPropertyValue() const
	{
		return FoundPropertyValue;
	}

private:
	void VisitSimpleProperty(FProperty* Property, const void* Value)
	{
		if (FoundProperty == nullptr && PathToProperty.Num() == 1 && PathToProperty[0] == Property->GetNameCPP())
		{
			FoundProperty = Property;
			FoundPropertyValue = Value;
		}
	}

private:
	FProperty* FoundProperty = nullptr;
	const void* FoundPropertyValue = nullptr;

	TArray<FString> PathToProperty;
};

void K2_OnEnterCameraModePropertyConsole(const TArray<FString>& Args, UWorld* World, FString PathToProperty);
class FStructRegisterVisitor : public FStructVisitor
{
public:
	virtual void VisitNumericProperty(FNumericProperty* Property, const void* Value) override
	{
		VisitSimpleProperty(Property, Value);
	}
	virtual void VisitBoolProperty(FBoolProperty* Property, const void* Value) override
	{
		VisitSimpleProperty(Property, Value);
	}
	virtual void EnterStructProperty(FStructProperty* Property, const void* Value) override
	{
		NameHierarchy.Add(Property->GetNameCPP());
	}

	virtual void ExitStructProperty() override
	{
		NameHierarchy.RemoveAt(NameHierarchy.Num() - 1);
	}

private:
	void VisitSimpleProperty(FProperty* Property, const void* Value)
	{
		FString pathToProperty;
		for (auto name : NameHierarchy)
		{
			pathToProperty.Append(name + TEXT("."));
		}
		pathToProperty.Append(Property->GetNameCPP());

		FString cmdName = TEXT("ATPC.CameraMode.") + pathToProperty;

		IConsoleManager::Get().RegisterConsoleCommand(
		    *cmdName,
		    TEXT(""),
		    FConsoleCommandWithWorldAndArgsDelegate::CreateStatic(K2_OnEnterCameraModePropertyConsole, pathToProperty));
	}

private:
	TArray<FString> NameHierarchy;
};

class FStructPrinterVisitor : public FStructVisitor
{
public:
	virtual void VisitNumericProperty(FNumericProperty* Property, const void* Value) override
	{
		StructData.AppendChars(TEXT("   "), NumStructs);
		StructData.Append(Property->GetNameCPP() + TEXT(":") + Property->GetNumericPropertyValueToString(Value) + LINE_TERMINATOR);
	}
	virtual void VisitBoolProperty(FBoolProperty* Property, const void* Value) override
	{
		StructData.AppendChars(TEXT("   "), NumStructs);

		FString stringPropValue = Property->GetPropertyValue(Value) ? TEXT("true") : TEXT("false");
		StructData.Append(Property->GetNameCPP() + TEXT(":") + stringPropValue + LINE_TERMINATOR);
	}
	virtual void EnterStructProperty(FStructProperty* Property, const void* Value) override
	{
		NumStructs++;
		StructData.Append(TEXT("---") + Property->GetNameCPP() + TEXT("---") + LINE_TERMINATOR);
	}
	virtual void ExitStructProperty() override
	{
		NumStructs--;
		StructData.Append(LINE_TERMINATOR);
	}

	const FString& GetStructAsString() const
	{
		return StructData;
	}

private:
	int32 NumStructs = 0;
	FString StructData;
};

class FStructIterator
{
public:
	FStructIterator(FStructVisitor& InVisitor, UStruct* InStruct, const void* InStructValue)
	    : Visitor(InVisitor), Struct(InStruct), StructValue(InStructValue)
	{
	}

	void Iterate()
	{
		for (auto propertyIt = TFieldIterator<FProperty>(Struct); propertyIt; ++propertyIt)
		{
			const void* propertyValue = propertyIt->ContainerPtrToValuePtr<const void>(StructValue);
			IterateOnProperty(*propertyIt, propertyValue);
		}
	}

private:
	void IterateOnProperty(FProperty* Property, const void* Value)
	{
		if (FNumericProperty* numericProperty = CastField<FNumericProperty>(Property))
		{
			Visitor.VisitNumericProperty(numericProperty, Value);
		}
		else if (FBoolProperty* boolProperty = CastField<FBoolProperty>(Property))
		{
			Visitor.VisitBoolProperty(boolProperty, Value);
		}
		else if (FStructProperty* structProperty = CastField<FStructProperty>(Property))
		{
			Visitor.EnterStructProperty(structProperty, Value);

			for (auto propertyIt = TFieldIterator<FProperty>(structProperty->Struct); propertyIt; ++propertyIt)
			{
				const void* propertyValue = propertyIt->ContainerPtrToValuePtr<const void>(Value);
				IterateOnProperty(*propertyIt, propertyValue);
			}

			Visitor.ExitStructProperty();
		}
	}

private:
	FStructVisitor& Visitor;
	UStruct* Struct;
	const void* StructValue;
};

UATPCCameraComponent* GetPlayerCameraComponentFromWorld(UWorld* World)
{
	UATPCCameraComponent* camera = nullptr;
	if (World != nullptr)
	{
		if (APlayerController* PC = World->GetFirstPlayerController())
		{
			if (APawn* Pawn = PC->GetPawn())
			{
				camera = Pawn->FindComponentByClass<UATPCCameraComponent>();
			}
		}
	}
	return camera;
}

static const TCHAR* SetCameraModeConsoleUsage = TEXT("SetCameraMode [CameraModeName] [bWithInterpolation(optional param)]");
void SetCameraModeConsole(const TArray<FString>& Args, UWorld* World)
{
	if (Args.Num() < 1 || Args.Num() > 2)
	{
		UE_LOG(LogATPC, Display, TEXT("SetCameraMode given incorrect number of argumets. Usage: %s"), SetCameraModeConsoleUsage);
		return;
	}

	if (UATPCCameraComponent* cameraComponent = GetPlayerCameraComponentFromWorld(World))
	{
		bool bWithInterp = Args.Num() > 1 ? bool(FCString::Atoi(*Args[1])) : false;
		FGameplayTag cameraModeTag = FGameplayTag::RequestGameplayTag(*Args[0], false);
		cameraComponent->SetCameraMode(cameraModeTag, bWithInterp);
	}
}

void PrintCameraModeConsole(UWorld* World)
{
	if (UATPCCameraComponent* cameraComponent = GetPlayerCameraComponentFromWorld(World))
	{
		FStructPrinterVisitor structPrinterVisitor;

		FStructIterator structIterator(structPrinterVisitor, FATPCCameraMode::StaticStruct(), &cameraComponent->GetCurrentCameraMode()->CameraModeSettings);
		structIterator.Iterate();
		UE_LOG(LogATPC, Display, TEXT("CameraMode: %s%s %s"), *cameraComponent->GetCurrentCameraModeTag().ToString(), LINE_TERMINATOR, *structPrinterVisitor.GetStructAsString());
	}
}

void K2_OnEnterCameraModePropertyConsole(const TArray<FString>& Args, UWorld* World, FString PathToProperty)
{
	if (UATPCCameraComponent* cameraComponent = GetPlayerCameraComponentFromWorld(World))
	{
		FSturctFinderVisitor finderSturctVisitor(PathToProperty);

		FStructIterator structIterator(finderSturctVisitor, FATPCCameraMode::StaticStruct(), &cameraComponent->GetCurrentCameraMode()->CameraModeSettings);
		structIterator.Iterate();

		if (finderSturctVisitor.GetFoundProperty() != nullptr)
		{
			FString stringPropValue;
			void* propertyValue = const_cast<void*>(finderSturctVisitor.GetFoundPropertyValue());
			if (FNumericProperty* numericProperty = CastField<FNumericProperty>(finderSturctVisitor.GetFoundProperty()))
			{
				if (Args.Num() != 0)
				{
					numericProperty->SetNumericPropertyValueFromString(propertyValue, *Args[0]);
					cameraComponent->ValidateComponents(true);
				}
				else
				{
					stringPropValue = numericProperty->GetNumericPropertyValueToString(propertyValue);
				}
			}
			else if (FBoolProperty* boolProperty = CastField<FBoolProperty>(finderSturctVisitor.GetFoundProperty()))
			{
				if (Args.Num() != 0)
				{
					boolProperty->SetPropertyValue(propertyValue, Args[0].ToBool());
					cameraComponent->ValidateComponents(true);
				}
				else
				{
					stringPropValue = numericProperty->GetNumericPropertyValueToString(propertyValue);
				}
			}

			if (stringPropValue.Len() != 0)
			{
				UE_LOG(LogATPC, Warning, TEXT("%s: %s"), *finderSturctVisitor.GetFoundProperty()->GetNameCPP(), *stringPropValue);
			}
		}
	}
}

void UATPCCameraComponent::RegisterConsoleCommands()
{
	static bool bIsRegistered = false;
	if(bIsRegistered)
	{
		return;
	}
	bIsRegistered = true;
	
	IConsoleManager::Get().RegisterConsoleCommand(
	    TEXT("ATPC.SetCameraMode"),
	    SetCameraModeConsoleUsage,
	    FConsoleCommandWithWorldAndArgsDelegate::CreateStatic(SetCameraModeConsole));

	IConsoleManager::Get().RegisterConsoleCommand(
	    TEXT("ATPC.PrintCameraMode"),
	    SetCameraModeConsoleUsage,
	    FConsoleCommandWithWorldDelegate::CreateStatic(PrintCameraModeConsole));

	FStructRegisterVisitor registerStructVisitor;
	FATPCCameraMode cameraMode;
	FStructIterator structIterator(registerStructVisitor, FATPCCameraMode::StaticStruct(), &cameraMode);
	structIterator.Iterate();
}
