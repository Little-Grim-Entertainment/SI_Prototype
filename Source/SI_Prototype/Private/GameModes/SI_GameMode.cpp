// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/SI_GameMode.h"

#include "EngineUtils.h"
#include "SI_GameInstance.h"
#include "Data/Characters/SI_CharacterData.h"
#include "Data/Input/SI_InputConfig.h"
#include "Abilities/SI_GameplayAbility.h"
#include "Debug/SI_DebugManager.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Media/SI_MediaManager.h"

ASI_GameMode::ASI_GameMode()
{
	if (NickSpadeCDA)
	{
		DefaultPawnClass = NickSpadeCDA->CharacterClass;
	}
}

void ASI_GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	if (!IsValid(GameInstance))	{return;}

	GameInstance->OnGameModeBeginPlay().Broadcast();
	
	USI_DebugManager* DebugManager = GameInstance->GetSubsystem<USI_DebugManager>();
	if(!IsValid(DebugManager)) {return;}

	DebugManager->InitializeDebugCommands(Options);
}

void ASI_GameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	FString PlayerStartTag = UKismetStringLibrary::GetSubstring(OptionsString, 1, OptionsString.Len() - 1);
	if (PlayerStartTag.IsEmpty())
	{
		PlayerStartTag = "Nick_DefaultSpawn";
	}
	
	AActor* PlayerStart = FindPlayerStart(GetWorld()->GetFirstPlayerController(), PlayerStartTag);

	const APlayerStart* PlayerStartActor = Cast<APlayerStart>(PlayerStart);

	if(IsValid(PlayerStartActor) && PlayerStartActor->PlayerStartTag != FName(*PlayerStartTag))
	{
		PlayerStartTag = "Nick_DefaultSpawn";
		PlayerStart = FindPlayerStart(GetWorld()->GetFirstPlayerController(), PlayerStartTag);
	}

	RestartPlayerAtPlayerStart(GetWorld()->GetFirstPlayerController(), PlayerStart);

	if(IsValid(GameInstance))
	{
		GameInstance->OnPlayerStart().Broadcast();
	}
}

APlayerStart* ASI_GameMode::GetPlayerStart(FString InPlayerStartTag) const
{
	for (APlayerStart* PlayerStart : GetAllPlayerStarts())
	{
		if (InPlayerStartTag != FString(TEXT("")))
		{
			if(PlayerStart->PlayerStartTag.ToString() == InPlayerStartTag)
			{
				return PlayerStart;					
			}
		}
		else
		{
			return PlayerStart;
		}
	}
	
	return nullptr;
}

TArray<APlayerStart*> ASI_GameMode::GetAllPlayerStarts() const
{
	TArray<AActor*> PlayerStartActors;
	TArray<APlayerStart*> PlayerStarts;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStartActors);

	for (AActor* CurrentActor : PlayerStartActors)
	{
		if (APlayerStart* PlayerStart = Cast<APlayerStart>(CurrentActor))
		{
			PlayerStarts.AddUnique(PlayerStart);
		}
	}
	
	return PlayerStarts;
}

void ASI_GameMode::RestartNickSpawn()
{
	HandleStartingNewPlayer(GetWorld()->GetFirstPlayerController());
}

USI_GameplayAbility* ASI_GameMode::GetGameplayAbility(FGameplayTag InAbilityTag)
{
	return GameplayAbilities.Find(InAbilityTag)->GetDefaultObject();
}
