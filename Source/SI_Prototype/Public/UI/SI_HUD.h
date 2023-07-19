// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SI_UserWidget.h"
#include "SI_HUD.generated.h"

class USI_QuickActionWidget;
class USI_DialogueBox;
class USI_CaseManager;
class USI_CaseData;
class USI_PartData;
class USI_ObjectiveData;

UCLASS()
class SI_PROTOTYPE_API USI_HUD : public USI_UserWidget
{
	GENERATED_BODY()

public:
	
	USI_HUD();

	UFUNCTION(BlueprintCallable)
	USI_DialogueBox* GetDialogueBox() const;

	UFUNCTION(BlueprintCallable)
	USI_UserWidget* GetReticle() const;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnObjectiveComplete(USI_ObjectiveData* CompletedObjective);

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void ShowCaseAcceptedWidget();

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USI_DialogueBox* DialogueBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USI_UserWidget* Reticle;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USI_UserWidget* CaseAcceptedWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USI_QuickActionWidget* QuickActionWidget;
	
private:

	UPROPERTY()
	USI_CaseManager* CaseManagerRef;
	bool bBindingsSetup;
	
	virtual void NativeConstruct() override;
	void SetupBindings();
	
};
