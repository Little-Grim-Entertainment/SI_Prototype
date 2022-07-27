// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_GameInstance.h"
#include "Cases/AoS_CaseManager.h"
#include "Characters/AoS_CharacterData.h"
#include "Characters/AoS_Nick.h"
#include "Characters/AoS_Character.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

UAoS_GameInstance::UAoS_GameInstance()
{
	
}

void UAoS_GameInstance::ResetCase(FString CaseToResetName)
{
	if (CaseManager)
	{
		if (CaseToResetName == "All")
		{
			CaseManager->ResetAllCases();
		}
		else
		{
			CaseManager->ResetCase(CaseToResetName);
		}
	}
}

void UAoS_GameInstance::SpawnPlayer()
{
	if (const APlayerStart* PlayerStart = GetPlayerStart())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Player Start Found!"));	
		if (!NickSpadeCharacter)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Nick Character Not Found!"));
			NickClassRef = CDA_NickSpade->CharacterClass;
			if (NickClassRef != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Nick Class Found!"));	

				const FActorSpawnParameters PlayerSpawnParameters;
				NickSpadeCharacter = GetWorld()->SpawnActor<AAoS_Nick>(NickClassRef, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), PlayerSpawnParameters);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Nick Class Not Found!"));	
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Nick Character Found!"));	
			NickSpadeCharacter->SetActorLocation(PlayerStart->GetActorLocation());
			NickSpadeCharacter->SetActorRotation(PlayerStart->GetActorRotation());
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No Player Start Found!"));	
	}
}

EPlayerMode UAoS_GameInstance::GetPlayerMode() const
{
	return PlayerMode;
}

void UAoS_GameInstance::SetPlayerMode(EPlayerMode InPlayerMode)
{
	PlayerMode = InPlayerMode;
	OnPlayerModeChanged.Broadcast(InPlayerMode);
}

void UAoS_GameInstance::Init()
{
	Super::Init();

	CaseManager = GetSubsystem<UAoS_CaseManager>();
}

APlayerStart* UAoS_GameInstance::GetPlayerStart() const
{
	TArray<AActor*> PlayerStartActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStartActors);

	for (AActor* CurrentActor : PlayerStartActors)
	{
		if (APlayerStart* PlayerStart = Cast<APlayerStart>(CurrentActor))
		{
			return PlayerStart;
		}
	}
	return nullptr;
}
