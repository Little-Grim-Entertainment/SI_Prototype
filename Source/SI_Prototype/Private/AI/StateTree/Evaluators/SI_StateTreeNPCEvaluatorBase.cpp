// Fill out your copyright notice in the Description page of Project Settings.



#include "AI/StateTree/Evaluators/SI_StateTreeNPCEvaluatorBase.h"

#include "LG_DebugMacros.h"
#include "StateTreeExecutionContext.h"
#include "Controllers/SI_NPCController.h"
#include "StateTreeLinker.h"
#include "Characters/SI_Gizbo.h"
#include "Controllers/SI_GizboController.h"


//-----------------------------------------------------
// USI_StateTreeNPCEvaluatorBase_InstanceData
//-----------------------------------------------------
void USI_StateTreeNPCEvaluatorBase_InstanceData::OnTreeStart(FStateTreeExecutionContext& Context, FSI_NPCMemory& InNPCMemory) 
{
	InNPCMemory.OnMoveToLocationUpdated.AddUObject(this, &USI_StateTreeNPCEvaluatorBase_InstanceData::SetMoveToLocation);
}

void USI_StateTreeNPCEvaluatorBase_InstanceData::SetMoveToLocation(FVector& InMoveLotLocation) 
{
	MoveToLocation = InMoveLotLocation;
}

//-----------------------------------------------------
// FSI_StateTreeNPCEvaluatorBase
//-----------------------------------------------------
void FSI_StateTreeNPCEvaluatorBase::TreeStart(FStateTreeExecutionContext& Context) const
{
	Super::TreeStart(Context);
	
	UInstanceDataType* InstanceData = Context.GetInstanceDataPtr<UInstanceDataType>(*this);

	ASI_Gizbo* Gizbo = Cast<ASI_Gizbo>(Context.GetOwner());
	ASI_GizboController* GizboController = Cast<ASI_GizboController>(Gizbo->GetController());
	InstanceData->Nick = GizboController->Nick;
	
	ASI_NPCController& Controller = Context.GetExternalData(ControllerHandle);
	InstanceData->OnTreeStart(Context, *Controller.NPCMemory);
}

void FSI_StateTreeNPCEvaluatorBase::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{

}

void FSI_StateTreeNPCEvaluatorBase::TreeStop(FStateTreeExecutionContext& Context) const
{

}

bool FSI_StateTreeNPCEvaluatorBase::Link(FStateTreeLinker& Linker)
{
	Linker.LinkExternalData(ControllerHandle);
	return true;
}
