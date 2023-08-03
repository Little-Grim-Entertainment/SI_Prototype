// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Cases/SI_CaseManager.h"

#include "SI_GameInstance.h"
#include "Data/Cases/SI_CaseData.h"
#include "Data/Cases/SI_PartData.h"
#include "Data/Cases/SI_ObjectiveData.h"
#include "Data/Cases/SI_CaseList.h"
#include "GameModes/SI_GameMode.h"
#include "Levels/SI_LevelManager.h"
#include "Data/Media/SI_CinematicDataAsset.h"
#include "Data/Media/SI_VideoDataAsset.h"
#include "Media/SI_MediaManager.h"
#include "SI_GameplayTagManager.h"
#include "SI_PlayerManager.h"
#include "Data/Maps/SI_MapData.h"

USI_CaseManager::USI_CaseManager()
{
	bCasesInitialized = false;
}

FOnCaseAccepted& USI_CaseManager::OnCaseAccepted()
{
	return OnCaseAcceptedDelegate;
}

FOnCaseActivated& USI_CaseManager::OnCaseActivated()
{
	return OnCaseActivatedDelegate;
}

FOnCaseDeactivated& USI_CaseManager::OnCaseDeactivated()
{
	return OnCaseDeactivatedDelegate;
}

FOnCaseComplete& USI_CaseManager::OnCaseComplete()
{
	return OnCaseCompleteDelegate;
}

FOnPartActivated& USI_CaseManager::OnPartActivated()
{
	return OnPartActivatedDelegate;
}

FOnPartComplete& USI_CaseManager::OnPartComplete()
{
	return OnPartCompleteDelegate;
}

FOnObjectiveActivated& USI_CaseManager::OnObjectiveActivated()
{
	return OnObjectiveActivatedDelegate;
}

FOnObjectiveComplete& USI_CaseManager::OnObjectiveComplete()
{
	return OnObjectiveCompleteDelegate;
}

FOnCaseTitleCardComplete& USI_CaseManager::OnCaseTitleCardComplete()
{
	return OnCaseTitleCardCompleteDelegate;
}

void USI_CaseManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();

	if(!bCasesInitialized)
	{
		InitializeCases();
	}
	
	PlayIntroMedia();
}

void USI_CaseManager::AcceptCase(USI_CaseData* CaseToAccept) 
{
	if (!IsValid(CaseToAccept)) {return;}
	
	if (!AcceptedCases.Contains(CaseToAccept))
	{
		if (!IsValid(ActiveCase))
		{
			SetActiveCase(CaseToAccept);
		}
		
		AcceptedCases.AddUnique(CaseToAccept);
		OnCaseAcceptedDelegate.Broadcast(CaseToAccept);	
	}
}

void USI_CaseManager::SetActiveCase(USI_CaseData* CaseToSet)
{
	if (!IsValid(CaseToSet) || CaseToSet == ActiveCase)
	{
		return;
	}
	
	if (IsValid(ActiveCase))
	{
		DeactivateCase(ActiveCase);
	}

	FSI_CaseDetails* CaseToSetDetails = GetCaseDetails(CaseToSet);
	if (!IsValid(CaseToSetDetails->GetCaseData())){return;}

	ActiveCase = CaseToSet;
	CaseToSetDetails->SetIsCaseActive(true);
	OnCaseActivatedDelegate.Broadcast(ActiveCase);

	PostCaseActivated(ActiveCase);
}

void USI_CaseManager::DeactivateCase(USI_CaseData* CaseToDeactivate)
{
	OnCaseDeactivatedDelegate.Broadcast(ActiveCase);
}

void USI_CaseManager::CompleteObjective(USI_ObjectiveData* ObjectiveToComplete)
{
	if (!IsValid(ActiveCase), !IsValid(ObjectiveToComplete)){return;}

	FSI_ObjectiveDetails* ObjectiveToCompleteDetails = GetObjectiveDetails(ObjectiveToComplete);
	if(!IsValid(ObjectiveToCompleteDetails->GetObjectiveData()) || ObjectiveToCompleteDetails->IsObjectiveComplete() || !ObjectiveToCompleteDetails->IsObjectiveActive()){return;}
		
	FSI_PartDetails* ActivePartDetails = GetPartDetails(GetActivePart());
	if(!IsValid(ActivePartDetails->GetPartData())){return;}

	if(ActivePartDetails->CompleteObjective(ObjectiveToComplete))
	{
		OnObjectiveCompleteDelegate.Broadcast(ObjectiveToComplete);
		PostObjectiveCompleted(ObjectiveToComplete);
	}
}

void USI_CaseManager::ResetAllCases()
{
	for (const TPair<USI_CaseData*, FSI_CaseDetails*>& CurrentCase : AllCases)
	{
		if (!IsValid(CurrentCase.Key)) {continue;}

		FSI_CaseDetails* CurrentCaseDetails = GetCaseDetails(CurrentCase.Key);

		if (!IsValid(CurrentCaseDetails->GetCaseData())) {continue;}
		CurrentCaseDetails->ResetCase();
	}
	
	ActiveCase = nullptr;
	AcceptedCases.Empty();
	CompletedCases.Empty();
}

void USI_CaseManager::ResetCase(USI_CaseData* CaseToReset)
{
	if (!IsValid(CaseToReset)) {return;}
	
	for (const TPair<USI_CaseData*, FSI_CaseDetails*>& CurrentCase : AllCases)
	{
		if (!IsValid(CurrentCase.Key)) {continue;}

		if(CurrentCase.Key == CaseToReset)
		{
			FSI_CaseDetails* CurrentCaseDetails = GetCaseDetails(CurrentCase.Key);

			if (!IsValid(CurrentCaseDetails->GetCaseData())) {continue;}
			CurrentCaseDetails->ResetCase();
			break;
		}
	}

	if (CaseToReset == ActiveCase)
	{
		ActiveCase = nullptr;
	}

	AcceptedCases.RemoveSingle(CaseToReset);
	CompletedCases.RemoveSingle(CaseToReset);
}

FSI_CaseDetails* USI_CaseManager::GetCaseDetails(const USI_CaseData* InCaseData)
{
	if(AllCases.IsEmpty() || !AllCases.Contains(InCaseData))
	{
		static FSI_CaseDetails DefaultCaseDetails;
		return &DefaultCaseDetails;
	}
	return *AllCases.Find(InCaseData);
}

USI_CaseData* USI_CaseManager::GetActiveCase()
{
	return ActiveCase;
}

USI_CaseData* USI_CaseManager::GetCaseByName(const FString& InCaseName)
{
	for(const TPair<USI_CaseData*, FSI_CaseDetails*>& CurrentCase : AllCases)
	{
		if(CurrentCase.Key->CaseName.ToString() == InCaseName)
		{
			return CurrentCase.Key;
		}
	}
	return nullptr;
}

TArray<USI_CaseData*> USI_CaseManager::GetAcceptedCases()
{
	return AcceptedCases;
}

TArray<USI_CaseData*> USI_CaseManager::GetCompletedCases()
{
	return CompletedCases;
}

FSI_PartDetails* USI_CaseManager::GetPartDetails(const USI_PartData* InPartData)
{
	for (const TPair<USI_CaseData*, FSI_CaseDetails*>& CurrentCase: AllCases)
	{
		for (const USI_PartData* CurrentPartData : CurrentCase.Key->GetAllParts())
		{
			if (CurrentPartData == InPartData)
			{
				return CurrentCase.Value->GetPartDetails(CurrentPartData);
			}
		}
	}

	static FSI_PartDetails EmptyPartDetails = FSI_PartDetails(nullptr);
	return &EmptyPartDetails;
}

USI_PartData* USI_CaseManager::GetActivePart()
{
	if(IsValid(ActiveCase))
	{
		return GetCaseDetails(ActiveCase)->GetActivePart();
	}

	return nullptr;
}

FSI_ObjectiveDetails* USI_CaseManager::GetObjectiveDetails(const USI_ObjectiveData* InObjectiveData)
{
	for (const TPair<USI_CaseData*, FSI_CaseDetails*>& CurrentCase: AllCases)
	{
		for (const USI_PartData* CurrentPartData : CurrentCase.Key->GetAllParts())
		{
			for (const USI_ObjectiveData* CurrentObjectiveData : CurrentPartData->GetAllObjectives())
			{
				if(CurrentObjectiveData == InObjectiveData)
				{
					return CurrentCase.Value->GetPartDetails(CurrentPartData)->GetObjectiveDetails(CurrentObjectiveData);
				}
			}
		}
	}

	static FSI_ObjectiveDetails EmptyObjectiveDetails = FSI_ObjectiveDetails(nullptr);
	return &EmptyObjectiveDetails;
}

TArray<USI_ObjectiveData*> USI_CaseManager::GetActiveObjectives()
{
	if(IsValid(ActiveCase))
	{
		const USI_PartData* CurrentActivePart = GetCaseDetails(ActiveCase)->GetActivePart();
		if (IsValid(CurrentActivePart))
		{
			FSI_PartDetails* ActivePartDetails = GetPartDetails(CurrentActivePart);
			return ActivePartDetails->GetActiveObjectives();
		}
	}
	TArray<USI_ObjectiveData*> EmptyArray;

	return GetPartDetails(GetCaseDetails(ActiveCase)->GetActivePart())->GetActiveObjectives();
}

void USI_CaseManager::InitializeCases()
{
	if (!IsValid(GameInstance) || !IsValid(GameInstance->CaseList)) {return;}

	if(AllCases.Num() > 0)
	{
		AllCases.Empty();
	}
	
	for (USI_CaseData* CurrentCaseData : GameInstance->CaseList->GetAllCases())
	{
		if (!IsValid(CurrentCaseData)) {continue;}

		static FSI_CaseDetails NewCaseDetails = FSI_CaseDetails(CurrentCaseData);
		AllCases.Add(CurrentCaseData, &NewCaseDetails);
	}
	
	InitializeParts();

	bCasesInitialized = true;
}

void USI_CaseManager::InitializeParts()
{	
	for (TPair<USI_CaseData*, FSI_CaseDetails*>& CurrentCase : AllCases)
	{
		for (USI_PartData* CurrentPart : CurrentCase.Key->GetAllParts())
		{
			if (!IsValid(CurrentPart)){continue;}

			static FSI_PartDetails NewPartDetails = FSI_PartDetails(CurrentPart);
			CurrentCase.Value->GetCaseParts().Add(CurrentPart, &NewPartDetails);
		}
	}
	
	InitializeObjectives();
}

void USI_CaseManager::InitializeObjectives()
{
	for (TPair<USI_CaseData*, FSI_CaseDetails*>& CurrentCase : AllCases)
	{
		for (TPair<USI_PartData*, FSI_PartDetails*>& CurrentPart : CurrentCase.Value->GetCaseParts())
		{
			for (USI_ObjectiveData* CurrentObjective : CurrentPart.Key->GetAllObjectives())
			{
				if (!IsValid(CurrentObjective)){continue;}

				static FSI_ObjectiveDetails NewObjectiveDetails = FSI_ObjectiveDetails(CurrentObjective);
				CurrentPart.Value->GetPartObjectives().Add(CurrentObjective, &NewObjectiveDetails);
			}
		}
	}
}

bool USI_CaseManager::CompleteCase(USI_CaseData* InCaseToComplete)
{
	FSI_CaseDetails* ActiveCaseDetails = GetCaseDetails(InCaseToComplete);
	if(!IsValid(ActiveCaseDetails->GetCaseData())){return false;}
		
	ActiveCaseDetails->SetIsCaseComplete(true);
	PostCaseCompleted(InCaseToComplete);
	return true;
}

void USI_CaseManager::PostCaseActivated(const USI_CaseData* ActivatedCase)
{
	if (!IsValid(ActivatedCase)) {return;}
	
	ActivatePart();
}

void USI_CaseManager::PostCaseCompleted(USI_CaseData* CompletedCase)
{
	if (!IsValid(CompletedCase)){return;}

	OnCaseCompleteDelegate.Broadcast(CompletedCase);
	CompletedCases.AddUnique(CompletedCase);
	ActiveCase = nullptr;
}

void USI_CaseManager::ActivatePart()
{
	FSI_CaseDetails* ActiveCastDetails = GetCaseDetails(GetActiveCase());
	for (TPair<USI_PartData*, FSI_PartDetails*>& CurrentPart : ActiveCastDetails->GetCaseParts())
	{
		if(!CurrentPart.Value->IsPartComplete())
		{
			CurrentPart.Value->SetIsPartActive(true);
			ActiveCastDetails->SetActivePart(CurrentPart.Key);
			OnPartActivatedDelegate.Broadcast(CurrentPart.Key);
			PostPartActivated(CurrentPart.Key);
		}
	}
}

void USI_CaseManager::PostPartActivated(const USI_PartData* ActivatedPart)
{
	if(!IsValid(ActivatedPart)){return;}

	ActivateObjectives();	
}

bool USI_CaseManager::CompletePart(USI_PartData* InPartToComplete)
{
	if (!IsValid(InPartToComplete)){return false;}
	
	FSI_PartDetails* ActivePartDetails = GetPartDetails(InPartToComplete);
	if(!IsValid(ActivePartDetails->GetPartData())){return false;}
		
	ActivePartDetails->SetIsPartComplete(true);
	PostPartCompleted(InPartToComplete);
	OnPartCompleteDelegate.Broadcast(InPartToComplete);
	return true;
}

void USI_CaseManager::PostPartCompleted(const USI_PartData* CompletedPart)
{
	if (!IsValid(CompletedPart) || CheckForCompletedCase()){return;}

	ActivatePart();
}

void USI_CaseManager::ActivateObjectives()
{
	FSI_PartDetails* ActivePartDetails = GetPartDetails(GetActivePart());
	
	for (TPair<USI_ObjectiveData*, FSI_ObjectiveDetails*>& CurrentObjective : ActivePartDetails->GetPartObjectives())
	{
		if(CurrentObjective.Value->IsObjectiveActive() || CurrentObjective.Value->IsObjectiveComplete()) {continue;}

		CurrentObjective.Value->SetIsObjectiveActive(true);
		ActivePartDetails->GetActiveObjectives().AddUnique(CurrentObjective.Key);

		if(CurrentObjective.Key->HasLevelMediaAssignments())
		{
			AssignMedia();
		}
		
		if (ActivePartDetails->GetPartData()->bCompleteObjectivesInOrder) {return;}
	}
}

void USI_CaseManager::AssignMedia()
{
	USI_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_LevelManager>();
	if(!IsValid(LevelManager))
	{
		return;
	}

	FSI_PartDetails* ActivePartDetails = GetPartDetails(GetActivePart());
	
	for (const TPair<USI_ObjectiveData*, FSI_ObjectiveDetails*>& CurrentObjective : ActivePartDetails->GetPartObjectives())
	{
		if(CurrentObjective.Value->IsObjectiveActive())
		{
			for (const FSI_LevelMediaAssignment& CurrentMediaAssignment : CurrentObjective.Key->LevelMediaAssignments)
			{
				FSI_MapState* AssociatedMapState = LevelManager->GetMapStateByTag(CurrentMediaAssignment.AssociatedLevelTag);

				if(IsValid(CurrentMediaAssignment.IntroCinematic))
				{
					AssociatedMapState->LoadedIntroMedia = CurrentMediaAssignment.IntroCinematic;
				}
				else if (IsValid(CurrentMediaAssignment.IntroVideo))
				{
					AssociatedMapState->LoadedIntroMedia = CurrentMediaAssignment.IntroVideo;
				}

				if(IsValid(CurrentMediaAssignment.OutroCinematic))
				{
					AssociatedMapState->LoadedOutroMedia = CurrentMediaAssignment.OutroCinematic;
				}
				else if (IsValid(CurrentMediaAssignment.IntroVideo))
				{
					AssociatedMapState->LoadedOutroMedia = CurrentMediaAssignment.OutroVideo;
				}
			}
		}
	}
}

void USI_CaseManager::PlayIntroMedia()
{
	USI_MediaManager* MediaManager = GetWorld()->GetSubsystem<USI_MediaManager>();
	USI_LevelManager* LevelManager = GetGameInstance()->GetSubsystem<USI_LevelManager>();

	if(!IsValid(MediaManager) || !IsValid(LevelManager)) {return;}

	FSI_MapState* LoadedMapState = LevelManager->GetCurrentLoadedMapState();
	if(!LoadedMapState->IsStateValid()) {return;}

	if (LoadedMapState->HasIntroMedia() && !MediaManager->HasMediaPlayed(LoadedMapState->GetLoadedIntroMedia()) && !SITagManager->HasGameplayTag(SITag_Debug_DisableAllMedia))
	{
		MediaManager->PlayMedia(LoadedMapState->GetLoadedIntroMedia(), LoadedMapState->GetOutroSettings());
	}
}

void USI_CaseManager::PostObjectiveCompleted(const USI_ObjectiveData* CompletedObjective)
{
	const USI_PartData* CurrentActivePart = GetActivePart();
	if (!IsValid(CompletedObjective) || CheckForCompletedPart() || !IsValid(CurrentActivePart)){return;}
	
	if (CurrentActivePart->bCompleteObjectivesInOrder)
	{
		FSI_PartDetails* ActivePartDetails = GetPartDetails(CurrentActivePart);
		ActivePartDetails->GetActiveObjectives().Empty();
		ActivateObjectives();
	}
}

bool USI_CaseManager::CheckForCompletedPart()
{
	int32 CompletedObjectives = 0;
	for (const USI_ObjectiveData* CurrentObjective : GetActiveObjectives())
	{
		FSI_ObjectiveDetails* CurrentObjectiveDetails = GetObjectiveDetails(CurrentObjective);
		if(CurrentObjectiveDetails->IsObjectiveComplete())
		{
			CompletedObjectives++;
		}
	}

	USI_PartData* PartToComplete = GetActivePart();
	
	if (CompletedObjectives == PartToComplete->GetAllObjectives().Num())
	{
		return CompletePart(PartToComplete);
	}
	return false;
}

bool USI_CaseManager::CheckForCompletedCase()
{
	int32 CompletedParts = 0;
	USI_CaseData* CurrentActiveCase = ActiveCase;
	
	for (const USI_PartData* CurrentPart : CurrentActiveCase->GetAllParts())
	{
		if(!IsValid(CurrentPart)) {continue;}
		
		FSI_PartDetails* CurrentPartDetails = GetPartDetails(CurrentPart);
		if(CurrentPartDetails->IsPartComplete())
		{
			CompletedParts++;
		}
	}
	
	if (CompletedParts == CurrentActiveCase->GetAllParts().Num())
	{
		return CompleteCase(CurrentActiveCase);
	}
	return false;
}
