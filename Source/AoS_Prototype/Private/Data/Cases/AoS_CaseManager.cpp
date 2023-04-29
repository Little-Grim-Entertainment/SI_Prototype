// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Cases/AoS_CaseManager.h"
#include "Data/Cases/AoS_CaseData.h"
#include "Data/Cases/AoS_PartData.h"
#include "Data/Cases/AoS_ObjectiveData.h"
#include "Data/Cases/UAoS_CaseList.h"
#include "GameModes/AoS_GameMode.h"
#include "Levels/AoS_LevelManager.h"
#include "Data/Media/AoS_CinematicDataAsset.h"
#include "Data/Media/AoS_VideoDataAsset.h"

UAoS_CaseManager::UAoS_CaseManager()
{
	
}

FOnCaseAccepted& UAoS_CaseManager::OnCaseAccepted()
{
	return OnCaseAcceptedDelegate;
}

FOnCaseActivated& UAoS_CaseManager::OnCaseActivated()
{
	return OnCaseActivatedDelegate;
}

FOnCaseDeactivated& UAoS_CaseManager::OnCaseDeactivated()
{
	return OnCaseDeactivatedDelegate;
}

FOnCaseComplete& UAoS_CaseManager::OnCaseComplete()
{
	return OnCaseCompleteDelegate;
}

FOnPartActivated& UAoS_CaseManager::OnPartActivated()
{
	return OnPartActivatedDelegate;
}

FOnPartComplete& UAoS_CaseManager::OnPartComplete()
{
	return OnPartCompleteDelegate;
}

FOnObjectiveActivated& UAoS_CaseManager::OnObjectiveActivated()
{
	return OnObjectiveActivatedDelegate;
}

FOnObjectiveComplete& UAoS_CaseManager::OnObjectiveComplete()
{
	return OnObjectiveCompleteDelegate;
}

FOnCaseTitleCardComplete& UAoS_CaseManager::OnCaseTitleCardComplete()
{
	return OnCaseTitleCardCompleteDelegate;
}

void UAoS_CaseManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();

	InitializeCases();
}

void UAoS_CaseManager::AcceptCase(UAoS_CaseData* CaseToAccept) 
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

void UAoS_CaseManager::SetActiveCase(UAoS_CaseData* CaseToSet)
{
	if (!IsValid(CaseToSet) || CaseToSet == ActiveCase)
	{
		return;
	}
	
	if (IsValid(ActiveCase))
	{
		DeactivateCase(ActiveCase);
	}

	FAoS_CaseDetails& CaseToSetDetails = GetCaseDetails(CaseToSet);
	if (!IsValid(CaseToSetDetails.GetCaseData())){return;}

	ActiveCase = CaseToSet;
	CaseToSetDetails.SetIsCaseActive(true);
	OnCaseActivatedDelegate.Broadcast(ActiveCase);

	PostCaseActivated(ActiveCase);
}

void UAoS_CaseManager::DeactivateCase(UAoS_CaseData* CaseToDeactivate)
{
	OnCaseDeactivatedDelegate.Broadcast(ActiveCase);
}

void UAoS_CaseManager::CompleteObjective(UAoS_ObjectiveData* ObjectiveToComplete)
{
	if (!IsValid(ActiveCase), !IsValid(ObjectiveToComplete)){return;}

	FAoS_ObjectiveDetails& ObjectiveToCompleteDetails = GetObjectiveDetails(ObjectiveToComplete);
	if(!IsValid(ObjectiveToCompleteDetails.GetObjectiveData()) || ObjectiveToCompleteDetails.IsObjectiveComplete() || !ObjectiveToCompleteDetails.IsObjectiveActive()){return;}
		
	FAoS_PartDetails& ActivePartDetails = GetPartDetails(GetActivePart());
	if(!IsValid(ActivePartDetails.GetPartData())){return;}

	if(ActivePartDetails.CompleteObjective(ObjectiveToComplete))
	{
		OnObjectiveCompleteDelegate.Broadcast(ObjectiveToComplete);
		PostObjectiveCompleted(ObjectiveToComplete);
	}
}

void UAoS_CaseManager::ResetAllCases()
{
	for (const TPair<UAoS_CaseData*, FAoS_CaseDetails>& CurrentCase : AllCases)
	{
		if (!IsValid(CurrentCase.Key)) {continue;}

		FAoS_CaseDetails& CurrentCaseDetails = GetCaseDetails(CurrentCase.Key);

		if (!IsValid(CurrentCaseDetails.GetCaseData())) {continue;}
		CurrentCaseDetails.ResetCase();
	}
	
	ActiveCase = nullptr;
	AcceptedCases.Empty();
	CompletedCases.Empty();
}

void UAoS_CaseManager::ResetCase(UAoS_CaseData* CaseToReset)
{
	if (!IsValid(CaseToReset)) {return;}
	
	for (const TPair<UAoS_CaseData*, FAoS_CaseDetails>& CurrentCase : AllCases)
	{
		if (!IsValid(CurrentCase.Key)) {continue;}

		if(CurrentCase.Key == CaseToReset)
		{
			FAoS_CaseDetails& CurrentCaseDetails = GetCaseDetails(CurrentCase.Key);

			if (!IsValid(CurrentCaseDetails.GetCaseData())) {continue;}
			CurrentCaseDetails.ResetCase();
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

FAoS_CaseDetails& UAoS_CaseManager::GetCaseDetails(const UAoS_CaseData* InCaseData)
{
	return *AllCases.Find(InCaseData);
}

UAoS_CaseData* UAoS_CaseManager::GetActiveCase()
{
	return ActiveCase;
}

UAoS_CaseData* UAoS_CaseManager::GetCaseByName(const FString InCaseName)
{
	for(const TPair<UAoS_CaseData*, FAoS_CaseDetails>& CurrentCase : AllCases)
	{
		if(CurrentCase.Key->CaseName.ToString() == InCaseName)
		{
			return CurrentCase.Key;
		}
	}
	return nullptr;
}

TArray<UAoS_CaseData*> UAoS_CaseManager::GetAcceptedCases()
{
	return AcceptedCases;
}

TArray<UAoS_CaseData*> UAoS_CaseManager::GetCompletedCases()
{
	return CompletedCases;
}

FAoS_PartDetails& UAoS_CaseManager::GetPartDetails(const UAoS_PartData* InPartData)
{
	for (TPair<UAoS_CaseData*, FAoS_CaseDetails>& CurrentCase: AllCases)
	{
		for (const UAoS_PartData* CurrentPartData : CurrentCase.Key->GetAllParts())
		{
			if (CurrentPartData == InPartData)
			{
				return CurrentCase.Value.GetPartDetails(CurrentPartData);
			}
		}
	}

	static FAoS_PartDetails EmptyPartDetails = FAoS_PartDetails(nullptr);
	return EmptyPartDetails;
}

UAoS_PartData* UAoS_CaseManager::GetActivePart()
{
	if(IsValid(ActiveCase))
	{
		return GetCaseDetails(ActiveCase).GetActivePart();
	}

	return nullptr;
}

FAoS_ObjectiveDetails& UAoS_CaseManager::GetObjectiveDetails(const UAoS_ObjectiveData* InObjectiveData)
{
	for (TPair<UAoS_CaseData*, FAoS_CaseDetails>& CurrentCase: AllCases)
	{
		for (const UAoS_PartData* CurrentPartData : CurrentCase.Key->GetAllParts())
		{
			for (const UAoS_ObjectiveData* CurrentObjectiveData : CurrentPartData->GetAllObjectives())
			{
				if(CurrentObjectiveData == InObjectiveData)
				{
					return CurrentCase.Value.GetPartDetails(CurrentPartData).GetObjectiveDetails(CurrentObjectiveData);
				}
			}
		}
	}

	static FAoS_ObjectiveDetails EmptyObjectiveDetails = FAoS_ObjectiveDetails(nullptr);
	return EmptyObjectiveDetails;
}

TArray<UAoS_ObjectiveData*> UAoS_CaseManager::GetActiveObjectives()
{
	if(IsValid(ActiveCase))
	{
		const UAoS_PartData* CurrentActivePart = GetCaseDetails(ActiveCase).GetActivePart();
		if (IsValid(CurrentActivePart))
		{
			FAoS_PartDetails& ActivePartDetails = GetPartDetails(CurrentActivePart);
			return ActivePartDetails.GetActiveObjectives();
		}
	}
	TArray<UAoS_ObjectiveData*> EmptyArray;

	return GetPartDetails(GetCaseDetails(ActiveCase).GetActivePart()).GetActiveObjectives();
}

void UAoS_CaseManager::InitializeCases()
{
	const AAoS_GameMode* GameMode = Cast<AAoS_GameMode>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GameMode) || !IsValid(GameMode->CaseList)) {return;}
	
	for (UAoS_CaseData* CurrentCaseData : GameMode->CaseList->GetAllCases())
	{
		if (!IsValid(CurrentCaseData)) {continue;}

		FAoS_CaseDetails NewCaseDetails = FAoS_CaseDetails(CurrentCaseData);
		AllCases.Add(CurrentCaseData, NewCaseDetails);
	}
	
	InitializeParts();		
}

void UAoS_CaseManager::InitializeParts()
{
	for (TPair<UAoS_CaseData*, FAoS_CaseDetails>& CurrentCase : AllCases)
	{
		for (UAoS_PartData* CurrentPart : CurrentCase.Key->GetAllParts())
		{
			if (!IsValid(CurrentPart)){continue;}

			FAoS_PartDetails NewPartDetails = FAoS_PartDetails(CurrentPart);
			CurrentCase.Value.GetCaseParts().Add(CurrentPart, NewPartDetails);
		}
	}
	
	InitializeObjectives();
}

void UAoS_CaseManager::InitializeObjectives()
{
	for (TPair<UAoS_CaseData*, FAoS_CaseDetails>& CurrentCase : AllCases)
	{
		for (TPair<UAoS_PartData*, FAoS_PartDetails>& CurrentPart : CurrentCase.Value.GetCaseParts())
		{
			for (UAoS_ObjectiveData* CurrentObjective : CurrentPart.Key->GetAllObjectives())
			{
				if (!IsValid(CurrentObjective)){continue;}

				FAoS_ObjectiveDetails NewObjectiveDetails = FAoS_ObjectiveDetails(CurrentObjective);
				CurrentPart.Value.GetPartObjectives().Add(CurrentObjective, NewObjectiveDetails);
			}
		}
	}
}

bool UAoS_CaseManager::CompleteCase(UAoS_CaseData* InCaseToComplete)
{
	FAoS_CaseDetails& ActiveCaseDetails = GetCaseDetails(InCaseToComplete);
	if(!IsValid(ActiveCaseDetails.GetCaseData())){return false;}
		
	ActiveCaseDetails.SetIsCaseComplete(true);
	PostCaseCompleted(InCaseToComplete);
	return true;
}

void UAoS_CaseManager::PostCaseActivated(const UAoS_CaseData* ActivatedCase)
{
	if (!IsValid(ActivatedCase)) {return;}
	
	ActivatePart();
}

void UAoS_CaseManager::PostCaseCompleted(UAoS_CaseData* CompletedCase)
{
	if (!IsValid(CompletedCase)){return;}

	OnCaseCompleteDelegate.Broadcast(CompletedCase);
	CompletedCases.AddUnique(CompletedCase);
	ActiveCase = nullptr;
}

void UAoS_CaseManager::ActivatePart()
{
	FAoS_CaseDetails& ActiveCastDetails = GetCaseDetails(GetActiveCase());
	for (TPair<UAoS_PartData*, FAoS_PartDetails>& CurrentPart : ActiveCastDetails.GetCaseParts())
	{
		if(!CurrentPart.Value.IsPartComplete())
		{
			CurrentPart.Value.SetIsPartActive(true);
			ActiveCastDetails.SetActivePart(CurrentPart.Key);
			OnPartActivatedDelegate.Broadcast(CurrentPart.Key);
			PostPartActivated(CurrentPart.Key);
		}
	}
}

void UAoS_CaseManager::PostPartActivated(const UAoS_PartData* ActivatedPart)
{
	if(!IsValid(ActivatedPart)){return;}

	ActivateObjectives();	
}

bool UAoS_CaseManager::CompletePart(UAoS_PartData* InPartToComplete)
{
	if (!IsValid(InPartToComplete)){return false;}
	
	FAoS_PartDetails& ActivePartDetails = GetPartDetails(InPartToComplete);
	if(!IsValid(ActivePartDetails.GetPartData())){return false;}
		
	ActivePartDetails.SetIsPartComplete(true);
	PostPartCompleted(InPartToComplete);
	OnPartCompleteDelegate.Broadcast(InPartToComplete);
	return true;
}

void UAoS_CaseManager::PostPartCompleted(const UAoS_PartData* CompletedPart)
{
	if (!IsValid(CompletedPart) || CheckForCompletedCase()){return;}

	ActivatePart();
}

void UAoS_CaseManager::ActivateObjectives()
{
	FAoS_PartDetails& ActivePartDetails = GetPartDetails(GetActivePart());
	
	for (TPair<UAoS_ObjectiveData*, FAoS_ObjectiveDetails>& CurrentObjective : ActivePartDetails.GetPartObjectives())
	{
		if(CurrentObjective.Value.IsObjectiveActive() || CurrentObjective.Value.IsObjectiveComplete()) {continue;}

		CurrentObjective.Value.SetIsObjectiveActive(true);
		ActivePartDetails.GetActiveObjectives().AddUnique(CurrentObjective.Key);

		UAoS_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_LevelManager>();
		if(IsValid(LevelManager) && CurrentObjective.Key->HasLevelMediaAssignments())
		{
			AssignObjectiveMedia(LevelManager);
		}
		
		if (ActivePartDetails.GetPartData()->bCompleteObjectivesInOrder) {return;}
	}
}

void UAoS_CaseManager::AssignObjectiveMedia(UAoS_LevelManager* InLevelManager)
{
	if(!IsValid(InLevelManager)){return;}

	FAoS_PartDetails& ActivePartDetails = GetPartDetails(GetActivePart());
	
	for (TPair<UAoS_ObjectiveData*, FAoS_ObjectiveDetails>& CurrentObjective : ActivePartDetails.GetPartObjectives())
	{
		if(CurrentObjective.Value.IsObjectiveActive())
		{
			for (const FAoS_LevelMediaAssignment& CurrentMediaAssignment : CurrentObjective.Key->LevelMediaAssignments)
			{
				FAoS_MapState& AssociatedMapState = InLevelManager->GetMapStateByTag(CurrentMediaAssignment.AssociatedLevelTag);

				if(IsValid(CurrentMediaAssignment.IntroCinematic))
				{
					AssociatedMapState.LoadedIntroMedia = CurrentMediaAssignment.IntroCinematic;
				}
				else if (IsValid(CurrentMediaAssignment.IntroVideo))
				{
					AssociatedMapState.LoadedIntroMedia = CurrentMediaAssignment.IntroVideo;
				}

				if(IsValid(CurrentMediaAssignment.OutroCinematic))
				{
					AssociatedMapState.LoadedOutroMedia = CurrentMediaAssignment.OutroCinematic;
				}
				else if (IsValid(CurrentMediaAssignment.IntroVideo))
				{
					AssociatedMapState.LoadedOutroMedia = CurrentMediaAssignment.OutroVideo;
				}
			}
		}
	}
}

void UAoS_CaseManager::PostObjectiveCompleted(const UAoS_ObjectiveData* CompletedObjective)
{
	const UAoS_PartData* CurrentActivePart = GetActivePart();
	if (!IsValid(CompletedObjective) || CheckForCompletedPart() || !IsValid(CurrentActivePart)){return;}
	
	if (CurrentActivePart->bCompleteObjectivesInOrder)
	{
		FAoS_PartDetails& ActivePartDetails = GetPartDetails(CurrentActivePart);
		ActivePartDetails.GetActiveObjectives().Empty();
		ActivateObjectives();
		
		UAoS_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_LevelManager>();
		if(IsValid(LevelManager))
		{
			AssignObjectiveMedia(LevelManager);
		}
	}
}

bool UAoS_CaseManager::CheckForCompletedPart()
{
	int32 CompletedObjectives = 0;
	for (const UAoS_ObjectiveData* CurrentObjective : GetActiveObjectives())
	{
		FAoS_ObjectiveDetails& CurrentObjectiveDetails = GetObjectiveDetails(CurrentObjective);
		if(CurrentObjectiveDetails.IsObjectiveComplete())
		{
			CompletedObjectives++;
		}
	}

	UAoS_PartData* PartToComplete = GetActivePart();
	
	if (CompletedObjectives == PartToComplete->GetAllObjectives().Num())
	{
		return CompletePart(PartToComplete);
	}
	return false;
}

bool UAoS_CaseManager::CheckForCompletedCase()
{
	int32 CompletedParts = 0;
	UAoS_CaseData* CurrentActiveCase = ActiveCase;
	
	for (const UAoS_PartData* CurrentPart : CurrentActiveCase->GetAllParts())
	{
		if(!IsValid(CurrentPart)) {continue;}
		
		FAoS_PartDetails& CurrentPartDetails = GetPartDetails(CurrentPart);
		if(CurrentPartDetails.IsPartComplete())
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
