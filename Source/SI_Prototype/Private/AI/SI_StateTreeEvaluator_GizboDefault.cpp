// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SI_StateTreeEvaluator_GizboDefault.h"

#include "StateTreeExecutionContext.h"
#include "Characters/SI_Gizbo.h"
#include "Characters/SI_Nick.h"
#include "SI_Prototype/SI_Prototype.h"

void USI_StateTreeEvaluator_GizboDefault::TreeStart(FStateTreeExecutionContext& Context)
{
	Super::TreeStart(Context);

	Gizbo = Cast<ASI_Gizbo>(Context.GetOwner());
	if(!IsValid(Gizbo)) {LG_LOG(LogSI_AI, Error, "Gizbo is invalid") return; }
	Nick = Cast<ASI_Nick>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(!IsValid(Nick)) {LG_LOG(LogSI_AI, Error, "Nick is invalid") return; }
}
