// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SI_EQSTest.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"

USI_EQSTest::USI_EQSTest()
{
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
}

void USI_EQSTest::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UObject* QueryOwner = QueryInstance.Owner.Get();
	if(!IsValid(QueryOwner)) return;

	FloatValueMin.BindData(QueryOwner, QueryInstance.QueryID);
	float MinThresholdValue = FloatValueMin.GetValue();

	FloatValueMax.BindData(QueryOwner, QueryInstance.QueryID);
	float MaxThresholdValue = FloatValueMax.GetValue();

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		float PlayerScore = 0;
		if(AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex()))
		{
			//PlayerScore = IAI_Interface::Execute_GetPlayerScore(ItemActor);
		}
		It.SetScore(TestPurpose, FilterType, PlayerScore, MinThresholdValue, MaxThresholdValue);
	}
}

