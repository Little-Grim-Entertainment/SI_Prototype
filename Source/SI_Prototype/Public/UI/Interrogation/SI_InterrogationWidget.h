// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SI_UserWidget.h"
#include "SI_InterrogationWidget.generated.h"

class USI_DialogueManager;
class UOverlay;
class UImage;
class USI_InterrogationDialogueBubble;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIntroAnimationComplete);

UCLASS()
class SI_PROTOTYPE_API USI_InterrogationWidget : public USI_UserWidget
{
	GENERATED_BODY()
	
public:
	
	void SetNickDialogue(const FText& InDialogue);
	void SetNPCDialogue(const FText& InDialogue);
	void SetNPCImage(UTexture2D* InNPCImage);
	
	FOnIntroAnimationComplete& OnIntroAnimationComplete();
		
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USI_InterrogationDialogueBubble* NickDialogueBubble;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USI_InterrogationDialogueBubble* NPCDialogueBubble;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* IMG_NPCImage;

	UPROPERTY(BlueprintReadOnly, BlueprintCallable, BlueprintAssignable)
	FOnIntroAnimationComplete OnIntroAnimationCompleteDelegate;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnIntroAnimationComplete_Internal();

private:

	UPROPERTY()
	USI_InterrogationDialogueBubble* VisibleDialogueBubble;

	UPROPERTY()
	TSoftObjectPtr<USI_DialogueManager> DialogueManager;

	void SetVisibleDialogueBubble(USI_InterrogationDialogueBubble* InVisibleDialogueBubble);
};
