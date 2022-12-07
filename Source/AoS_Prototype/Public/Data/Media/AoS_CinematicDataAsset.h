// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneSequencePlayer.h"
#include "Data/Media/AoS_MediaDataAsset.h"
#include "AoS_CinematicDataAsset.generated.h"

class ULevelSequencePlayer;
class ALevelSequenceActor;
class ULevelSequence;

UCLASS()
class AOS_PROTOTYPE_API UAoS_CinematicDataAsset : public UAoS_MediaDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cinematics")
	ULevelSequence* LevelSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cinematics")
	FMovieSceneSequencePlaybackSettings PlaybackSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cinematics")
	ALevelSequenceActor* LevelSequenceActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cinematics")
	ULevelSequencePlayer* CinematicPlayer;

	virtual void StartMedia() override;
	virtual void SkipMedia() override;

protected:

	virtual void ClearDelegates() override;

private:

	UFUNCTION()
	void OnCinematicEnd();
};
