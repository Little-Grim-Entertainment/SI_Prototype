// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/AoS_UserWidget.h"
#include "AoS_HUD.generated.h"

class UAoS_DialogueBox;
class UAoS_CaseManager;
class UAoS_CaseData;
class UAoS_PartData;
class UAoS_ObjectiveData;

UCLASS()
class AOS_PROTOTYPE_API UAoS_HUD : public UAoS_UserWidget
{
	GENERATED_BODY()

public:
	
	UAoS_HUD();

	UFUNCTION(BlueprintCallable)
	UAoS_DialogueBox* GetDialogueBox() const;

	UFUNCTION(BlueprintCallable)
	UAoS_UserWidget* GetReticle() const;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnObjectiveComplete(UAoS_ObjectiveData* CompletedObjective);

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void ShowCaseAcceptedWidget();

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UAoS_DialogueBox* DialogueBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UAoS_UserWidget* Reticle;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UAoS_UserWidget* CaseAcceptedWidget;
	
private:

	UPROPERTY()
	UAoS_CaseManager* CaseManagerRef;
	bool bBindingsSetup;
	
	virtual void NativeConstruct() override;
	void SetupBindings();
	
};
