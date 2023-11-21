// Fill out your copyright notice in the Description page of Project Settings.



#include "AI/StateTree/Evaluators/SI_StateTreeNPCEvaluatorBase.h"

#include "LG_DebugMacros.h"
#include "StateTreeExecutionContext.h"
#include "Controllers/SI_NPCController.h"
#include "Characters/SI_NPC.h"
#include "SI_Prototype/SI_Prototype.h"

//-----------------------------------------------------
// USI_StateTreeNPCEvaluatorBase_InstanceData
//-----------------------------------------------------
void USI_StateTreeNPCEvaluatorBase_InstanceData::OnTreeStart(FStateTreeExecutionContext& Context) 
{
	LG_LOG(LogLG_StateTree, Log, "USI_StateTreeNPCEvaluatorBase_InstanceData::OnTreeStart")
	NPCController = NPC->GetController<ASI_NPCController>();
	if(!IsValid(NPCController)) {LG_LOG(LogLG_StateTree, Error, "NPCController is invalid cannot Start Tree") return;}
	FSI_NPCMemory* NPCMemory = NPCController->GetNPCMemory();

	Nick = NPCMemory->GetNick();
	
	NPCMemory->OnMoveToLocationUpdated.AddUObject(this, &USI_StateTreeNPCEvaluatorBase_InstanceData::SetMoveToLocation);
}

void USI_StateTreeNPCEvaluatorBase_InstanceData::SetMoveToLocation(FVector& InMoveToLocation) 
{
	MoveToLocation = InMoveToLocation;
}

//-----------------------------------------------------
// FSI_StateTreeNPCEvaluatorBase
//-----------------------------------------------------
void FSI_StateTreeNPCEvaluatorBase::TreeStart(FStateTreeExecutionContext& Context) const
{
	LG_LOG(LogLG_StateTree, Log, "FSI_StateTreeNPCEvaluatorBase::TreeStart")
	Super::TreeStart(Context);
	
	UInstanceDataType* InstanceData = Context.GetInstanceDataPtr<UInstanceDataType>(*this);
	InstanceData->OnTreeStart(Context);
}

void FSI_StateTreeNPCEvaluatorBase::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
}

void FSI_StateTreeNPCEvaluatorBase::TreeStop(FStateTreeExecutionContext& Context) const
{
	LG_LOG(LogLG_StateTree, Log, "FSI_StateTreeNPCEvaluatorBase::TreeStop")
}