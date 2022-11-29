// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/AoS_GameMode.h"

#include "AoS_GameInstance.h"
#include "Data/Characters/AoS_CharacterData.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/AoS_LevelManager.h"

AAoS_GameMode::AAoS_GameMode()
{
	if (NickSpadeCDA)
	{
		DefaultPawnClass = NickSpadeCDA->CharacterClass;
	}
}

void AAoS_GameMode::InitGameState()
{
	Super::InitGameState();

	if (IsValid(GameInstance))
	{
		GameInstance->SetCurrentGameMode(this);
	}	
}
	
void AAoS_GameMode::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	if (!IsValid(GameInstance)){return;}

	GameInstance->SetCurrentGameMode(this);
	
	LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_LevelManager>();
	if (IsValid(LevelManager))
	{
		LevelManager->LevelLoaded();
	}

	GameInstance->OnGameModeBeginPlay.Broadcast();
}

APlayerStart* AAoS_GameMode::GetPlayerStart(FString InPlayerStartTag) const
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

TArray<APlayerStart*> AAoS_GameMode::GetAllPlayerStarts() const
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
