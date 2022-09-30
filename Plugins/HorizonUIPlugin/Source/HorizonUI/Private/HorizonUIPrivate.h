// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#pragma once

// Core
#include "Algo/Accumulate.h"
#include "Engine/Texture2D.h"
#include "HAL/PlatformFileManager.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Logging/MessageLog.h"
#include "Misc/AssertionMacros.h"
#include "Misc/CommandLine.h"
#include "Misc/EngineVersionComparison.h"


//Engine
#include "Components/CanvasPanelSlot.h"
#include "Engine/Brush.h"
#include "Engine/Font.h"
#include "Engine/Font.h"
#include "Fonts/FontMeasure.h"
#include "Framework/Application/SlateApplication.h"
#include "GameFramework/WorldSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Materials/Material.h"
#include "Misc/FileHelper.h"
#include "Modules/ModuleManager.h"
#include "PaperFlipbook.h"
#include "Sound/SoundBase.h"

// UObject
#include "UObject/ConstructorHelpers.h"


// Sound
#include "Sound/SoundBase.h"

// Paper2D
#include "PaperSprite.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

//SlateCore
#include "Fonts/SlateFontInfo.h"

//UMG
#include "UMGStyle.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CheckBox.h"
#include "Components/Image.h"


// XmlParser
#include "XmlParser.h"


//General Log
//CORE_API DECLARE_LOG_CATEGORY_EXTERN(LogTemp, Log, All);
//HORIZONLIBRARY_API 
DECLARE_LOG_CATEGORY_EXTERN(LogHorizonUI, Log, All);
#define UE_HORIZONUI_FATAL(msg, ...)		UE_LOG(LogHorizonUI, Fatal, TEXT(msg), ##__VA_ARGS__)
#define UE_HORIZONUI_ERROR(msg, ...)		UE_LOG(LogHorizonUI, Error, TEXT(msg), ##__VA_ARGS__)
#define UE_HORIZONUI_WARNING(msg, ...)		UE_LOG(LogHorizonUI, Warning, TEXT(msg), ##__VA_ARGS__)
#define UE_HORIZONUI_DISPLAY(msg, ...)		UE_LOG(LogHorizonUI, Display, TEXT(msg), ##__VA_ARGS__)
#define UE_HORIZONUI_LOG(msg, ...)			UE_LOG(LogHorizonUI, Log, TEXT(msg), ##__VA_ARGS__)
#define UE_HORIZONUI_VERBOSE(msg, ...)		UE_LOG(LogHorizonUI, Verbose, TEXT(msg), ##__VA_ARGS__)
#define UE_HORIZONUI_VERY_VERBOSE(msg, ...) UE_LOG(LogHorizonUI, VeryVerbose, TEXT(msg), ##__VA_ARGS__)


#define HORIZONUI_STRINGIZE_NX(A) #A
#define HORIZONUI_STRINGIZE(A) HORIZONUI_STRINGIZE_NX(A)


DECLARE_STATS_GROUP(TEXT("HorizonUI"), STATGROUP_HorizonUI, STATCAT_Advanced);

#define DECLARE_HORIZONUI_SCOPE_CYCLE_COUNTER(CounterName,Stat) \
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT(CounterName), Stat, STATGROUP_HorizonUI);


#define DECLARE_HORIZONUI_QUICK_SCOPE_CYCLE_COUNTER(ClassName,FunctionName) \
	SCOPED_NAMED_EVENT_TEXT(HORIZONUI_STRINGIZE(ClassName::)HORIZONUI_STRINGIZE(FunctionName), FColor::Magenta); \
	DECLARE_HORIZONUI_SCOPE_CYCLE_COUNTER(HORIZONUI_STRINGIZE(ClassName::)HORIZONUI_STRINGIZE(FunctionName), \
	STAT##_##ClassName##_##FunctionName)