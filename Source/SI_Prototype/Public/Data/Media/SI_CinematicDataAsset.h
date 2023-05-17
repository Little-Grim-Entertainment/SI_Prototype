// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneSequencePlayer.h"
#include "Data/Media/SI_MediaDataAsset.h"
#include "SI_CinematicDataAsset.generated.h"

class ULevelSequencePlayer;
class ALevelSequenceActor;
class ULevelSequence;

UCLASS()
class SI_PROTOTYPE_API USI_CinematicDataAsset : public USI_MediaDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Media | Cinematics")
	ULevelSequence* LevelSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Media | Cinematics")
	FMovieSceneSequencePlaybackSettings PlaybackSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Media | Cinematics")
	ALevelSequenceActor* LevelSequenceActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Media | Cinematics")
	ULevelSequencePlayer* CinematicPlayer;
};
