// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Decorator/HorizonDialogueMsgDecorator.h"
#include "HorizonDialogueMsgSpaceDecorator.generated.h"

/**
 * 
 */
UCLASS()
class HORIZONUI_API UHorizonDialogueMsgSpaceDecorator : public UHorizonDialogueMsgDecorator
{
	GENERATED_BODY()
public:
	virtual bool BuildSegment_Implementation(UHorizonDialogueMsgTextBlock* InMsgTextBlock,
		int32 InCurrentSegInfoIndex, FHorizonDialogueSegmentInfo& InCurrentSegInfo,
		const TArray<FHorizonDialogueSegmentInfo>& InSegInfos) override;


public:

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Content")
	FText FirstLineSpaceL = FText::FromString(TEXT("  "));

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Content")
	FText Space = FText::FromString(TEXT(" "));
};
